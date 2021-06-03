#include "NNTaylor.h"

using namespace flowstar;
using namespace std;

NNTaylor::NNTaylor()
{
}

NNTaylor::NNTaylor(NeuralNetwork nn)
{
    this->nn = nn;
}

void NNTaylor::set_taylor_linear(vector<string> state_vars, vector<Interval> network_input_box)
{
    Matrix<double> center(this->nn.get_num_of_inputs(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        center[j][0] = network_input_box[j].midpoint();
    }

    Matrix<double> half_len(this->nn.get_num_of_inputs(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        half_len[j][0] = network_input_box[j].width() / 2.0;
    }

    // layer_info_all_layer stores all the information (value/range of output/jocobian/hessian) of all the layers
    vector<vector<Neuron>> layer_info_all_layer;

    // process the input layer
    vector<Neuron> layer_info;

    for (int i = 0; i < this->nn.get_num_of_inputs(); i++)
    {
        Matrix<Interval> first_order_der_value(this->nn.get_num_of_inputs(), 1);
        first_order_der_value[i][0] = Interval(1, 1);
        Matrix<Interval> first_order_der_range(this->nn.get_num_of_inputs(), 1);
        first_order_der_range[i][0] = Interval(1, 1);

        // Matrix<Interval> second_order_der_value(this->nn.get_num_of_inputs(), this->nn.get_num_of_inputs());
        // for (int p = 0; p < this->nn.get_num_of_inputs(); p++)
        // {
        //     for (int q = 0; q < this->nn.get_num_of_inputs(); q++)
        //     {
        //         second_order_der_value[p][q] = Interval(0);
        //     }
        // }
        Matrix<Interval> second_order_der_range(this->nn.get_num_of_inputs(), this->nn.get_num_of_inputs());
        // for (int p = 0; p < this->nn.get_num_of_inputs(); p++)
        // {
        //     for (int q = 0; q < this->nn.get_num_of_inputs(); q++)
        //     {
        //         second_order_der_range[p][q] = Interval(0);
        //     }
        // }

        Neuron neuron(this->nn.get_num_of_inputs());
        neuron.set_input_value(Interval(center[i][0], center[i][0]));
        // cout << neuron.get_input_value() << endl;
        neuron.set_input_range(network_input_box[i]);
        // cout << neuron.get_input_range() << endl;
        neuron.set_first_order_der_value(first_order_der_value);
        // cout << "Input layer, Neuron " << i << ", first order value: " << neuron.get_first_order_der_value() << endl;
        neuron.set_first_order_der_range(first_order_der_range);
        // cout << "Input layer, Neuron " << i << ", first order range: " << neuron.get_first_order_der_range() << endl;
        // neuron.set_second_order_der_value(second_order_der_value);
        neuron.set_second_order_der_range(second_order_der_range);
        // cout << "123: " << neuron.get_second_order_der_value() << endl;
        // cout << "456: " << neuron.get_second_order_der_range() << endl;
        neuron.set_activation_info("Affine", "taylor");
        // cout << "Input layer, Neuron " << i << ", first order value after activation: " << neuron.get_activation_info().get_de() << endl;
        // cout << "Input layer, Neuron " << i << ", first order range after activation: " << neuron.get_activation_info().get_de_range() << endl;

        layer_info.push_back(neuron);
    }
    layer_info_all_layer.push_back(layer_info);

    // start to process hidden layers and output layer
    // may be incorrect since I did not define copy constructor
    vector<Neuron> last_layer_info = layer_info;
    for (int s = 0; s < this->nn.get_num_of_hidden_layers() + 1; s++)
    {
        // cout << "s: " << s << endl;

        vector<Neuron> this_layer_info;
        Layer layer = this->nn.get_layers()[s];
        Matrix<Interval> weight = layer.get_weight();
        Matrix<Interval> bias = layer.get_bias();

        for (int i = 0; i < layer.get_neuron_number_this_layer(); i++)
        {
            Matrix<Interval> weight_i(1, layer.get_neuron_number_last_layer());
            weight.getRowVec(weight_i, i);
            // cout << "Layer " << s << ", Neuron " << i << ", weight: " << weight_i << endl;
            Matrix<Interval> bias_i_matrix(1, 1);
            bias.getRowVec(bias_i_matrix, i);
            Interval bias_i = bias_i_matrix[0][0];

            Neuron neuron(this->nn.get_num_of_inputs());
            neuron.set_input_value(last_layer_info, weight_i, bias_i);
            neuron.set_input_range(last_layer_info, weight_i, bias_i);
            neuron.set_first_order_der_value(last_layer_info, weight_i);
            // cout << "Layer " << s << ", Neuron " << i << ", first order value: " << neuron.get_first_order_der_value() << endl;
            neuron.set_first_order_der_range(last_layer_info, weight_i);
            // cout << "Layer " << s << ", Neuron " << i << ", first order range: " << neuron.get_first_order_der_range() << endl;
            // neuron.set_second_order_der_value(last_layer_info, weight_i);
            neuron.set_second_order_der_range(last_layer_info, weight_i);
            neuron.set_activation_info(layer.get_activation(), "taylor");
            // cout << "Layer " << s << ", Neuron " << i << ", first order value after activation: " << neuron.get_activation_info().get_de() << endl;
            // cout << "Layer " << s << ", Neuron " << i << ", first order range after activation: " << neuron.get_activation_info().get_de_range() << endl;

            this_layer_info.push_back(neuron);
        }

        layer_info_all_layer.push_back(this_layer_info);
        last_layer_info = this_layer_info;
    }

    // process the scalar and offset by constructing an addtional virtual single-neuron layer
    Interval scale_factor = this->nn.get_scale_factor();
    Interval offset = this->nn.get_offset();
    vector<Neuron> virtual_layer_info;
    Neuron virtual_neruon(this->nn.get_num_of_inputs());
    Matrix<Interval> virtual_weight(1, 1);
    virtual_weight[0][0] = scale_factor;
    Interval virtual_bias = -offset * scale_factor;
    virtual_neruon.set_input_value(last_layer_info, virtual_weight, virtual_bias);
    virtual_neruon.set_input_range(last_layer_info, virtual_weight, virtual_bias);
    virtual_neruon.set_first_order_der_value(last_layer_info, virtual_weight);
    virtual_neruon.set_first_order_der_range(last_layer_info, virtual_weight);
    // virtual_neruon.set_second_order_der_value(last_layer_info, virtual_weight);
    virtual_neruon.set_second_order_der_range(last_layer_info, virtual_weight);
    virtual_neruon.set_activation_info("Affine", "taylor");

    Interval const nn_output = virtual_neruon.get_input_value();
    this->output = nn_output.inf();
    // cout << "output on center: " << nn_output.inf() << endl;
    Matrix<Interval> jacobian_value = virtual_neruon.get_first_order_der_value();
    cout << "jocobian_range: " << virtual_neruon.get_first_order_der_range() << endl;
    // cout << "jocobian: " << jacobian_value << endl;
    // cout << "output_der on center: ";
    for (int i = 0; i < jacobian_value.rows(); i++)
    {
        // cout << jacobian_value[i][0].inf() << ", ";
    }
    cout << endl;
    for (int i = 0; i < jacobian_value.rows(); i++)
    {
        this->jacobian.push_back(jacobian_value[i][0].inf());
    }

    string expression = to_string(nn_output.inf());
    for (int i = 0; i < state_vars.size(); i++)
    {
        expression = expression + " + (" + to_string(jacobian_value[i][0].inf()) + ") * (" + state_vars[i] + " - (" + to_string(center[i][0]) + "))";
    }
    this->taylor_linear_expression = expression;

    Matrix<Interval> hessian_range = virtual_neruon.get_second_order_der_range();
    // cout << "hessian_range: " << hessian_range << endl;
    // Matrix<double> hessian_max(this->nn.get_num_of_inputs(), this->nn.get_num_of_inputs());
    // for (int i = 0; i < hessian_max.rows(); i++)
    // {
    //     for (int j = 0; j < hessian_max.cols(); j++)
    //     {
    //         hessian_max[i][j] = max(abs(hessian_range[i][j].inf()), abs(hessian_range[i][j].sup()));
    //     }
    // }
    // // cout << inf_norm(half_len) << endl;
    // double error = 0.5 * inf_norm(half_len) * inf_norm(hessian_max);

    // double error1 = remainder_norm_based(network_input_box, hessian_range);
    double error2 = remainder_interval_arithmetic(network_input_box, hessian_range);
    // cout << "error1: " << error1 << endl;
    // cout << "error2: " << error2 << endl;

    this->taylor_linear_remainder = Interval(-error2, error2);
    // cout << "output range: " << virtual_neruon.get_input_range() << endl;
}

void NNTaylor::set_range_by_IBP(vector<Interval> network_input_box)
{
    Matrix<double> center(this->nn.get_num_of_inputs(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        center[j][0] = network_input_box[j].midpoint();
    }

    Matrix<double> half_len(this->nn.get_num_of_inputs(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        half_len[j][0] = network_input_box[j].width();
    }

    // layer_info_all_layer stores all the information (value/range of output/jocobian/hessian) of all the layers
    vector<vector<Neuron>> layer_info_all_layer;

    // process the input layer
    vector<Neuron> layer_info;

    for (int i = 0; i < this->nn.get_num_of_inputs(); i++)
    {
        Neuron neuron(this->nn.get_num_of_inputs());
        neuron.set_input_value(Interval(center[i][0], center[i][0]));
        // cout << neuron.get_input_value() << endl;
        neuron.set_input_range(network_input_box[i]);
        // cout << neuron.get_input_range() << endl;
        neuron.set_activation_info("Affine", "IBP");

        layer_info.push_back(neuron);
    }
    layer_info_all_layer.push_back(layer_info);

    // start to process hidden layers and output layer
    // may be incorrect since I did not define copy constructor
    vector<Neuron> last_layer_info = layer_info;
    // cout << "num_of_hidden_layers: " << this->nn.get_num_of_hidden_layers() << endl;
    for (int s = 0; s < this->nn.get_num_of_hidden_layers() + 1; s++)
    {
        // cout << "s: " << s << endl;

        vector<Neuron> this_layer_info;
        Layer layer = this->nn.get_layers()[s];
        Matrix<Interval> weight = layer.get_weight();
        Matrix<Interval> bias = layer.get_bias();

        // cout << "this layer neuron number : " << layer.get_neuron_number_this_layer() << endl;

        // cout << "Layer " << s << ", Weight: " << weight << endl;
        // cout << "Layer " << s << ", Bias: " << bias << endl;

        for (int i = 0; i < layer.get_neuron_number_this_layer(); i++)
        {
            Matrix<Interval> weight_i(1, layer.get_neuron_number_last_layer());
            weight.getRowVec(weight_i, i);
            // cout << "Layer " << s << ", Neuron " << i << ", weight: " << weight_i << endl;
            Matrix<Interval> bias_i_matrix(1, 1);
            bias.getRowVec(bias_i_matrix, i);
            Interval bias_i = bias_i_matrix[0][0];
            // cout << "Layer " << s << ", Neuron " << i << ", bias: " << bias_i << endl;

            Neuron neuron(this->nn.get_num_of_inputs());
            neuron.set_input_value(last_layer_info, weight_i, bias_i);
            // cout << "Layer " << s << ", Neuron " << i << ", input value: " << neuron.get_input_value() << endl;
            neuron.set_input_range(last_layer_info, weight_i, bias_i);
            // cout << "Layer " << s << ", Neuron " << i << ", input range: " << neuron.get_input_range() << endl;
            neuron.set_activation_info(layer.get_activation(), "IBP");
            this_layer_info.push_back(neuron);
        }

        layer_info_all_layer.push_back(this_layer_info);
        last_layer_info = this_layer_info;
    }

    // process the scalar and offset by constructing an addtional virtual single-neuron layer
    Interval scale_factor = this->nn.get_scale_factor();
    Interval offset = this->nn.get_offset();
    vector<Neuron> virtual_layer_info;
    Neuron virtual_neruon(this->nn.get_num_of_inputs());
    Matrix<Interval> virtual_weight(1, 1);
    virtual_weight[0][0] = scale_factor;
    Interval virtual_bias = -offset * scale_factor;
    virtual_neruon.set_input_value(last_layer_info, virtual_weight, virtual_bias);
    virtual_neruon.set_input_range(last_layer_info, virtual_weight, virtual_bias);
    virtual_neruon.set_activation_info("Affine", "IBP");

    this->output_range_IBP = virtual_neruon.get_input_range();

    Interval const nn_output_value = virtual_neruon.get_input_value();
    // cout << "output on center: " << nn_output_value.inf() << endl;
    Interval nn_output_range = virtual_neruon.get_input_range();
    cout << "output range: " << nn_output_range << endl;
}

void NNTaylor::set_tm_by_TMP(vector<string> state_vars, vector<Interval> network_input_box, TaylorInfo ti, vector<Interval> tmv_domain)
{

    TaylorModelVec<Real> tmv_input(network_input_box, tmv_domain);

    // layer_info_all_layer stores all the information (value/range of output/jocobian/hessian) of all the layers
    vector<vector<Neuron>> layer_info_all_layer;

    // process the input layer
    vector<Neuron> layer_info;
    for (int i = 0; i < this->nn.get_num_of_inputs(); i++)
    {
        Neuron neuron(this->nn.get_num_of_inputs());
        neuron.set_taylor_model(tmv_input.tms[i]);
        neuron.set_activation_info("Affine", ti, tmv_domain);
        layer_info.push_back(neuron);
    }
    vector<TaylorModel<Real>> temp_tm_v;
    for (int i = 0; i < this->nn.get_num_of_inputs(); i++)
    {
        temp_tm_v.push_back(layer_info[i].get_taylor_model());
    }
    TaylorModelVec<Real> temp_tmv(temp_tm_v);
    this->input_tmv = temp_tmv;
    layer_info_all_layer.push_back(layer_info);

    // start to process hidden layers and output layer
    vector<Neuron> last_layer_info = layer_info;
    for (int s = 0; s < this->nn.get_num_of_hidden_layers() + 1; s++)
    {
        vector<Neuron> this_layer_info;
        Layer layer = this->nn.get_layers()[s];
        Matrix<Interval> weight = layer.get_weight();
        Matrix<Interval> bias = layer.get_bias();

        // cout << "this layer neuron number : " << layer.get_neuron_number_this_layer() << endl;

        // cout << "Layer " << s << ", Weight: " << weight << endl;
        // cout << "Layer " << s << ", Bias: " << bias << endl;

        for (int i = 0; i < layer.get_neuron_number_this_layer(); i++)
        {
            Matrix<Interval> weight_i(1, layer.get_neuron_number_last_layer());
            weight.getRowVec(weight_i, i);
            Matrix<Interval> bias_i_matrix(1, 1);
            bias.getRowVec(bias_i_matrix, i);
            Interval bias_i = bias_i_matrix[0][0];

            Neuron neuron(this->nn.get_num_of_inputs());
            neuron.set_taylor_model(last_layer_info, weight_i, bias_i);
            neuron.set_activation_info(layer.get_activation(), ti, tmv_domain);
            this_layer_info.push_back(neuron);
        }

        layer_info_all_layer.push_back(this_layer_info);
        last_layer_info = this_layer_info;
    }

    // process the scalar and offset by constructing an addtional virtual single-neuron layer
    Interval scale_factor = this->nn.get_scale_factor();
    Interval offset = this->nn.get_offset();
    vector<Neuron> virtual_layer_info;
    Neuron virtual_neruon(this->nn.get_num_of_inputs());
    Matrix<Interval> virtual_weight(1, 1);
    virtual_weight[0][0] = scale_factor;
    Interval virtual_bias = -offset * scale_factor;
    virtual_neruon.set_taylor_model(last_layer_info, virtual_weight, virtual_bias);
    virtual_neruon.set_activation_info("Affine", ti, tmv_domain);

    this->output_tm = virtual_neruon.get_taylor_model();
}

string NNTaylor::get_taylor_expression()
{
    return this->taylor_linear_expression;
}

Interval NNTaylor::get_taylor_remainder()
{
    return this->taylor_linear_remainder;
}

double NNTaylor::get_output()
{
    return this->output;
}

vector<double> NNTaylor::get_jacobian()
{
    return this->jacobian;
}

Interval NNTaylor::get_range_by_IBP()
{
    return this->output_range_IBP;
}

TaylorModelVec<Real> NNTaylor::get_input_tmv()
{
    return this->input_tmv;
}

TaylorModel<Real> NNTaylor::get_output_tm()
{
    return this->output_tm;
}

void NNTaylor::get_output_tmv(TaylorModelVec<Real> &tmv_output, TaylorModelVec<Real> &tmv_input, TaylorInfo ti, vector<Interval> &tmv_domain)
{
    time_t start_timer;
    time_t end_timer;
    double seconds;

    TaylorModelVec<Real> tmvTemp;
    vector<TaylorModelVec<Real>> tmv_all_layer;
    tmv_all_layer.push_back(tmv_input);
    for (int s = 0; s < this->nn.get_num_of_hidden_layers() + 1; s++)
    {
        cout << "-------------------  Layer " << s << " starts. ------------------- " << endl;
        Layer layer = this->nn.get_layers()[s];
        Matrix<Interval> weight = layer.get_weight();
        Matrix<Interval> bias = layer.get_bias();

        Matrix<Real> weight_value(weight.rows(), weight.cols());
        for (int i = 0; i < weight.rows(); i++)
        {
            for (int j = 0; j < weight.cols(); j++)
            {
                weight_value[i][j] = weight[i][j].sup();
            }
        }

        Matrix<Real> bias_value(bias.rows(), bias.cols());
        for (int i = 0; i < bias.rows(); i++)
        {
            for (int j = 0; j < bias.cols(); j++)
            {
                bias_value[i][j] = bias[i][j].sup();
            }
        }

        // cout << "Layer " << s << " :" << endl;
        // time(&start_timer);
        TaylorModelVec<Real> tmv_layer_temp = weight_value * tmv_all_layer[s];
        // time(&end_timer);
        // cout << "weight: " << endl;
        // cout << weight_value << endl;
        // cout << "bias: " << endl;
        // cout << bias_value << endl;
        // seconds = -difftime(start_timer, end_timer);
        // cout << "Taylor model matrix mul: " << seconds << " seconds" << endl;
        // cout << "11111111" << endl;
        // if (s == 3)
        // {
        //     cout << tmv_layer_temp.tms[0].expansion.terms.size() << endl;
        // }
        // cout << tmv_layer_temp.tms.size() << endl;

        for (int i = 0; i < bias.rows(); i++)
        {
            Polynomial<Real> poly_temp(bias_value[i][0], tmv_domain.size());
            tmv_layer_temp.tms[i].expansion += poly_temp;
        }

        tmv_layer_temp.activate(tmvTemp, tmv_domain, layer.get_activation(), ti.order, ti.bernstein_order, ti.partition_num, ti.cutoff_threshold, ti.g_setting, 3);
        tmv_layer_temp = tmvTemp;

        tmv_all_layer.push_back(tmv_layer_temp);
    }

    tmv_output = tmv_all_layer.back();

    Matrix<Real> offset(nn.get_num_of_outputs(), 1);
    for (int i = 0; i < nn.get_num_of_outputs(); i++)
    {
        offset[i][0] = -nn.get_offset().sup();
    }
    // cout << "offset: " << offset << endl;
    tmv_output += offset;

    Matrix<Real> scalar(nn.get_num_of_outputs(), nn.get_num_of_outputs());
    for (int i = 0; i < nn.get_num_of_outputs(); i++)
    {
        scalar[i][i] = nn.get_scale_factor().sup();
    }
    // cout << "scalar: " << scalar << endl;
    tmv_output = scalar * tmv_output;
    // cout << "1111111111111111111111" << endl;
    tmv_all_layer.push_back(tmv_output);

    Interval box;
    tmv_output.tms[0].intEval(box, tmv_domain);
    cout << "neural network output range by TMP: " << box << endl;
}

void NNTaylor::NN_Reach(TaylorModelVec<Real> &tmv_output, TaylorModelVec<Real> &tmv_input, TaylorInfo ti, vector<Interval> &tmv_domain)
{
    Interval intUnit(-1, 1);

    TaylorModelVec<Real> tmv_layer_input = tmv_input;

    Flowpipe fp_layer_input(tmv_layer_input, tmv_domain, ti.cutoff_threshold);

    Symbolic_Remainder symbolic_remainder(fp_layer_input);

    unsigned int numOfLayers = nn.get_num_of_hidden_layers() + 1;

    unsigned int layer_input_dim = tmv_domain.size() - 1;

    for (unsigned int K = 0; true; ++K)
    {
        cout << "-------------------  Layer " << K << " starts. ------------------- " << endl;

        Flowpipe fp_layer_output;

        // evaluate the the initial set x0
        TaylorModelVec<Real> tmv_of_x0;

        if (K == numOfLayers)
        {
            tmv_of_x0 = fp_layer_input.tmvPre;
        }
        else
        {
            Layer layer = this->nn.get_layers()[K];
            Matrix<Interval> weight = layer.get_weight();

            Matrix<Real> weight_value(weight.rows(), weight.cols());
            for (int i = 0; i < weight.rows(); i++)
            {
                for (int j = 0; j < weight.cols(); j++)
                {
                    weight_value[i][j] = weight[i][j].sup();
                }
            }

            //cout << weight_value << endl;
            //cout << fp_layer_input.tmvPre.tms.size() << endl;
            tmv_of_x0 = weight_value * fp_layer_input.tmvPre;
        }

        // the center point of x0's polynomial part
        std::vector<Real> const_of_x0;
        tmv_of_x0.constant(const_of_x0);

        unsigned int rangeDim = tmv_of_x0.tms.size();
        unsigned int rangeDimExt = rangeDim + 1;

        for (unsigned int j = 0; j < rangeDim; ++j)
        {
            Real c;
            tmv_of_x0.tms[j].remainder.remove_midpoint(c);
            const_of_x0[j] += c;

            if (K < numOfLayers)
            {
                Layer layer = this->nn.get_layers()[K];
                Matrix<Interval> bias = layer.get_bias();

                Matrix<Real> bias_value(bias.rows(), bias.cols());
                for (int i = 0; i < bias.rows(); i++)
                {
                    for (int j = 0; j < bias.cols(); j++)
                    {
                        bias_value[i][j] = bias[i][j].sup();
                    }
                }

                const_of_x0[j] += bias_value[j][0];
            }
        }

        // introduce a new variable r0 such that x0 = c0 + A*r0, then r0 is origin-centered
        tmv_of_x0.rmConstant();

        // decompose the linear and nonlinear part
        TaylorModelVec<Real> x0_linear, x0_other;
        tmv_of_x0.decompose(x0_linear, x0_other);

        Matrix<Real> Phi_L_i(rangeDim, layer_input_dim);

        x0_linear.linearCoefficients(Phi_L_i);

        Matrix<Real> local_trans_linear = Phi_L_i;
        Phi_L_i.right_scale_assign(symbolic_remainder.scalars);
        // compute the remainder part under the linear transformation
        Matrix<Interval> J_i(rangeDim, 1);

        for (unsigned int i = 0; i < symbolic_remainder.Phi_L.size(); ++i)
        {
            symbolic_remainder.Phi_L[i] = Phi_L_i * symbolic_remainder.Phi_L[i];
        }

        symbolic_remainder.Phi_L.push_back(Phi_L_i);

        for (unsigned int i = 1; i < symbolic_remainder.Phi_L.size(); ++i)
        {
            J_i += symbolic_remainder.Phi_L[i] * symbolic_remainder.J[i - 1];
        }

        Matrix<Interval> J_ip1(rangeDim, 1);

        std::vector<Interval> range_of_x0;

        // compute the local initial set
        if (symbolic_remainder.J.size() > 0)
        {
            // cout << symbolic_remainder.Phi_L[0].cols() << endl;
            // cout << symbolic_remainder.polynomial_of_initial_set.size() << endl;
            // compute the polynomial part under the linear transformation
            std::vector<Polynomial<Real>> initial_linear = symbolic_remainder.Phi_L[0] * symbolic_remainder.polynomial_of_initial_set;

            // compute the other part
            std::vector<Interval> tmvPolyRange;
            fp_layer_input.tmv.polyRange(tmvPolyRange, fp_layer_input.domain);
            x0_other.insert_ctrunc(fp_layer_output.tmv, fp_layer_input.tmv, tmvPolyRange, fp_layer_input.domain, ti.order, ti.cutoff_threshold);

            fp_layer_output.tmv.Remainder(J_ip1);

            Matrix<Interval> x0_rem(rangeDim, 1);
            tmv_of_x0.Remainder(x0_rem);
            J_ip1 += x0_rem;

            for (int i = 0; i < rangeDim; ++i)
            {
                fp_layer_output.tmv.tms[i].expansion += initial_linear[i];
            }

            for (int i = 0; i < rangeDim; ++i)
            {
                fp_layer_output.tmv.tms[i].remainder = J_ip1[i][0] + J_i[i][0];
            }

            fp_layer_output.tmv.intEval(range_of_x0, fp_layer_input.domain);
        }
        else
        {
            std::vector<Interval> tmvPolyRange;
            fp_layer_input.tmv.polyRange(tmvPolyRange, fp_layer_input.domain);
            tmv_of_x0.insert_ctrunc(fp_layer_output.tmv, fp_layer_input.tmv, tmvPolyRange, fp_layer_input.domain, ti.order, ti.cutoff_threshold);

            fp_layer_output.tmv.intEval(range_of_x0, fp_layer_input.domain);

            fp_layer_output.tmv.Remainder(J_ip1);
        }

        symbolic_remainder.J.push_back(J_ip1);

        if (K == numOfLayers)
        {
            tmv_output = fp_layer_output.tmv;

            for (int i = 0; i < tmv_output.tms.size(); ++i)
            {
                tmv_output.tms[i] += const_of_x0[i];
            }

            break;
        }

        // Compute the scaling matrix S.
        std::vector<Real> S, invS;

        if (symbolic_remainder.scalars.size() != rangeDim)
        {
            symbolic_remainder.scalars.resize(rangeDim, 0);
        }

        for (int i = 0; i < rangeDim; ++i)
        {
            Real sup;
            range_of_x0[i].mag(sup);

            if (sup == 0)
            {
                S.push_back(0);
                invS.push_back(1);
                symbolic_remainder.scalars[i] = 0;
            }
            else
            {
                S.push_back(sup);
                Real tmp = 1 / sup;
                invS.push_back(tmp);
                symbolic_remainder.scalars[i] = tmp;
                // range_of_x0[i] = intUnit;
            }
        }

        fp_layer_output.tmv.scale_assign(invS);

        for (int i = 0; i < rangeDim; ++i)
        {
            range_of_x0[i] += const_of_x0[i];
        }

        // Computing a TM overapproximation of the activation function sigmoid(c + z) such that z in I
        std::vector<Interval> newDomain;
        TaylorModelVec<Real> tmv_simple_layer_input(range_of_x0, newDomain);

        //		tmv_simple_layer_input.output(std::cout, stateVars, tmVars);
        //		std::cout << std::endl << std::endl;
        Layer layer = this->nn.get_layers()[K];
        tmv_simple_layer_input.activate(fp_layer_output.tmvPre, newDomain, layer.get_activation(), ti.order, ti.bernstein_order, ti.partition_num, ti.cutoff_threshold, ti.g_setting, 2);

        //		tmv_simple_layer_output.output(std::cout, stateVars, tmVars);
        //		std::cout << std::endl << std::endl;

        fp_layer_input.tmv = fp_layer_output.tmv;
        fp_layer_input.tmvPre = fp_layer_output.tmvPre;

        layer_input_dim = layer.get_neuron_number_this_layer();
    }

    cout << tmv_output.tms.size() << endl;

    Matrix<Real> offset(nn.get_num_of_outputs(), 1);
    for (int i = 0; i < nn.get_num_of_outputs(); i++)
    {
        offset[i][0] = -nn.get_offset().sup();
    }
    //cout << tmv_output.tms.size() << endl;
    //cout << offset.rows() << endl;

    tmv_output += offset;

    Matrix<Real> scalar(nn.get_num_of_outputs(), nn.get_num_of_outputs());
    for (int i = 0; i < nn.get_num_of_outputs(); i++)
    {
        scalar[i][i] = nn.get_scale_factor().sup();
    }
    tmv_output = scalar * tmv_output;
    // cout << "1111111111111111111111" << endl;

    Interval box;
    tmv_output.tms[0].intEval(box, tmv_domain);
    cout << "neural network output range by TMP_symbolic_remainder: " << box << endl;
}

double remainder_interval_arithmetic(vector<Interval> network_input_box, Matrix<Interval> hessian_range)
{
    // Interval c(0.5, 0.5);
    Matrix<double> center(network_input_box.size(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        center[j][0] = network_input_box[j].midpoint();
    }

    Matrix<Interval> input_box(network_input_box.size(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        input_box[j][0] = network_input_box[j];
    }

    Matrix<Interval> state_inter = input_box - center;

    Matrix<Interval> state_inter_trans(1, network_input_box.size());
    state_inter.transpose(state_inter_trans);

    //cout << "state_inter_trans size: " << state_inter_trans.rows() << state_inter_trans.cols() << endl;
    //cout << "hessian_range size: " << hessian_range.rows() << hessian_range.cols() << endl;
    //cout << "state_inter size: " << state_inter.rows() << state_inter.cols() << endl;
    Matrix<Interval> remainder = state_inter_trans * hessian_range * state_inter * 0.5;
    return remainder[0][0].sup();
}

double remainder_norm_based(vector<Interval> network_input_box, Matrix<Interval> hessian_range)
{
    Matrix<double> center(network_input_box.size(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        center[j][0] = network_input_box[j].midpoint();
    }

    Matrix<double> half_len(network_input_box.size(), 1);
    for (int j = 0; j < network_input_box.size(); j++)
    {
        half_len[j][0] = network_input_box[j].width() / 2.0;
    }

    Matrix<double> hessian_max(network_input_box.size(), network_input_box.size());
    for (int i = 0; i < hessian_max.rows(); i++)
    {
        for (int j = 0; j < hessian_max.cols(); j++)
        {
            hessian_max[i][j] = max(abs(hessian_range[i][j].inf()), abs(hessian_range[i][j].sup()));
        }
    }
    // cout << inf_norm(half_len) << endl;
    double error = 0.5 * NNTaylor::inf_norm(half_len) * NNTaylor::inf_norm(hessian_max);
    return error;
}