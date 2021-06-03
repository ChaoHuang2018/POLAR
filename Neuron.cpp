#include "Neuron.h"

using namespace flowstar;
using namespace std;

Neuron::Neuron()
{
}

Neuron::Neuron(int nn_input_dim)
{
    this->nn_input_dim = nn_input_dim;
}

int Neuron::get_nn_input_dim()
{
    return this->nn_input_dim;
}

Activation Neuron::get_activation_info()
{
    return this->activation_info;
}

const Interval &Neuron::get_input_value() const
{
    return this->input_value;
}

Interval Neuron::get_input_range()
{
    return Interval(this->input_range);
}

Matrix<Interval> Neuron::get_first_order_der_value()
{
    return this->first_order_der_value;
}

Matrix<Interval> Neuron::get_first_order_der_range()
{
    return Matrix<Interval>(this->first_order_der_range);
}

Matrix<Interval> Neuron::get_second_order_der_value()
{
    return Matrix<Interval>(this->second_order_der_value);
}

Matrix<Interval> Neuron::get_second_order_der_range()
{
    return Matrix<Interval>(this->second_order_der_range);
}

TaylorModel<Real> Neuron::get_taylor_model()
{
    return this->tm;
}

void Neuron::set_input_value(Interval input_value)
{
    this->input_value = Interval(input_value);
}

void Neuron::set_input_range(Interval input_range)
{
    this->input_range = Interval(input_range);
}

void Neuron::set_first_order_der_value(Matrix<Interval> first_order_der_value)
{
    this->first_order_der_value = Matrix<Interval>(first_order_der_value);
}

void Neuron::set_first_order_der_range(Matrix<Interval> first_order_der_range)
{
    this->first_order_der_range = Matrix<Interval>(first_order_der_range);
}

void Neuron::set_second_order_der_value(Matrix<Interval> second_order_der_value)
{
    this->second_order_der_value = Matrix<Interval>(second_order_der_value);
}

void Neuron::set_second_order_der_range(Matrix<Interval> second_order_der_range)
{
    this->second_order_der_range = Matrix<Interval>(second_order_der_range);
}

void Neuron::set_input_value(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias)
{
    this->input_value = Interval(bias);
    for (int j = 0; j < last_layer_info.size(); j++)
    {
        // cout << weight[0][j] << endl;
        // cout << last_layer_info[j].activation_info.get_value() << endl;
        this->input_value = this->input_value + weight[0][j] * last_layer_info[j].activation_info.value;
        // cout << "iterative value: " << input_value << endl;
    }
}

void Neuron::set_input_range(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias)
{
    this->input_range = Interval(bias);
    for (int j = 0; j < last_layer_info.size(); j++)
    {
        // cout << weight[0][j] << endl;
        this->input_range = this->input_range + weight[0][j] * last_layer_info[j].activation_info.output_range;
        // cout << "iterative range: " << input_range << endl;
    }
}

void Neuron::set_first_order_der_value(vector<Neuron> last_layer_info, Matrix<Interval> weight)
{
    this->first_order_der_value = Matrix<Interval>(this->nn_input_dim, 1);
    for (int i = 0; i < this->nn_input_dim; i++)
    {
        for (int j = 0; j < last_layer_info.size(); j++)
        {
            this->first_order_der_value[i][0] = this->first_order_der_value[i][0] + weight[0][j] * last_layer_info[j].activation_info.de * last_layer_info[j].first_order_der_value[i][0];
        }
    }
}

void Neuron::set_first_order_der_range(vector<Neuron> last_layer_info, Matrix<Interval> weight)
{
    this->first_order_der_range = Matrix<Interval>(this->nn_input_dim, 1);
    for (int i = 0; i < this->nn_input_dim; i++)
    {
        for (int j = 0; j < last_layer_info.size(); j++)
        {
            this->first_order_der_range[i][0] = this->first_order_der_range[i][0] + weight[0][j] * last_layer_info[j].activation_info.de_range * last_layer_info[j].first_order_der_range[i][0];
        }
    }
}

void Neuron::set_second_order_der_value(vector<Neuron> last_layer_info, Matrix<Interval> weight)
{
    this->second_order_der_value = Matrix<Interval>(this->nn_input_dim, this->nn_input_dim);
    for (int i = 0; i < this->nn_input_dim; i++)
    {
        for (int s = i; s < this->nn_input_dim; s++)
        {
            for (int j = 0; j < last_layer_info.size(); j++)
            {
                this->second_order_der_value[i][s] = this->second_order_der_value[i][s] + weight[0][j] * (last_layer_info[j].activation_info.de2 * *(last_layer_info[j].first_order_der_value[i]) * *(last_layer_info[j].first_order_der_value[s]) + last_layer_info[j].get_activation_info().de * (last_layer_info[j].second_order_der_value[i][s]));
            }
            second_order_der_value[s][i] = second_order_der_value[i][s];
        }
    }
}

void Neuron::set_second_order_der_range(vector<Neuron> last_layer_info, Matrix<Interval> weight)
{
    this->second_order_der_range = Matrix<Interval>(this->nn_input_dim, this->nn_input_dim);
    for (int i = 0; i < this->nn_input_dim; i++)
    {
        for (int s = i; s < this->nn_input_dim; s++)
        {
            for (int j = 0; j < last_layer_info.size(); j++)
            {
                // cout << "111111" << endl;
                // cout << weight[0][j] << endl;
                // cout << "222222" << endl;
                // cout << last_layer_info[j].activation_info.get_de2_range() << endl;
                // cout << "333333" << endl;
                // cout << *(last_layer_info[j].get_first_order_der_range()[i]) << endl;
                // cout << "444444" << endl;
                // cout << *(last_layer_info[j].get_first_order_der_range()[s]) << endl;
                // cout << "555555" << endl;
                // cout << last_layer_info[j].get_activation_info().get_de_range() << endl;
                // cout << "666666" << endl;
                // cout << (last_layer_info[j].get_second_order_der_range()[i][s]) << endl;
                // cout << "777777" << endl;
                this->second_order_der_range[i][s] = this->second_order_der_range[i][s] + weight[0][j] * (last_layer_info[j].activation_info.de2_range * *(last_layer_info[j].first_order_der_range[i]) * *(last_layer_info[j].first_order_der_range[s]) + last_layer_info[j].get_activation_info().de_range * (last_layer_info[j].second_order_der_range[i][s]));
            }
            second_order_der_range[s][i] = second_order_der_range[i][s];
        }
    }
}

void Neuron::set_activation_info(string activation_type, string approach)
{
    this->activation_info = Activation(activation_type, this->input_value, this->input_range, approach);
}

void Neuron::set_activation_info(string activation_type, TaylorInfo ti, vector<Interval> tmv_domain)
{
    this->activation_info = Activation(activation_type, this->tm, ti, tmv_domain);
}

void Neuron::set_taylor_model(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias)
{
    //this->tmv = 0;
    for (int j = 0; j < last_layer_info.size(); j++)
    {
        this->tm = this->tm + last_layer_info[j].activation_info.tm * weight[0][j].sup();
    }
    this->tm += Real(bias.sup());
}

void Neuron::set_taylor_model(TaylorModel<Real> tm)
{
    this->tm = tm;
}
