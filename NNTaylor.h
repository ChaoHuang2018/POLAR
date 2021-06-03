#include "POLAR/Continuous.h"
#include "POLAR/Symbolic_Remainder_NN.h"
#include "Neuron.h"
#include "NeuralNetwork.h"

using namespace flowstar;
using namespace std;

class NNTaylor
{
protected:
    NeuralNetwork nn;
    string taylor_linear_expression;
    Interval taylor_linear_remainder;
    double output;
    vector<double> jacobian;
    Interval output_range_IBP;
    TaylorModelVec<Real> input_tmv;
    TaylorModel<Real> output_tm;

public:
    NNTaylor();
    NNTaylor(NeuralNetwork nn);

    void set_taylor_linear(vector<string> state_vars, vector<Interval> network_input_box);
    void set_range_by_IBP(vector<Interval> network_input_box);
    void set_tm_by_TMP(vector<string> state_vars, vector<Interval> network_input_box, TaylorInfo ti, vector<Interval> tmv_domain);

    string get_taylor_expression();
    Interval get_taylor_remainder();
    double get_output();
    vector<double> get_jacobian();
    Interval get_range_by_IBP();
    TaylorModelVec<Real> get_input_tmv();
    TaylorModel<Real> get_output_tm();

    void get_output_tmv(TaylorModelVec<Real> &tmv_output, TaylorModelVec<Real> &tmv_input, TaylorInfo ti, vector<Interval> &tmv_domain);

    void NN_Reach(TaylorModelVec<Real> &tmv_output, TaylorModelVec<Real> &tmv_input, TaylorInfo ti, vector<Interval> &tmv_domain);

    static double inf_norm(Matrix<double> m)
    {
        double norm = 0;
        for (int i = 0; i < m.rows(); i++)
        {
            double row_abs_sum = 0;
            for (int j = 0; j < m.cols(); j++)
            {
                row_abs_sum = row_abs_sum + abs(m[i][j]);
            }
            if (norm <= row_abs_sum)
            {
                norm = row_abs_sum;
            }
        }
        return norm;
    }
};

double remainder_interval_arithmetic(vector<Interval> network_input_box, Matrix<Interval> hessian_range);

double remainder_norm_based(vector<Interval> network_input_box, Matrix<Interval> hessian_range);