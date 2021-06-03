#include "POLAR/Continuous.h"
#include "Activation.h"

using namespace flowstar;
using namespace std;

class Neuron
{
public:
    int nn_input_dim;
    Activation activation_info;
    Interval input_value;
    Interval input_range;
    Matrix<Interval> first_order_der_value;
    Matrix<Interval> first_order_der_range;
    Matrix<Interval> second_order_der_value;
    Matrix<Interval> second_order_der_range;

    // taylor model propagation
    TaylorModel<Real> tm;

public:
    Neuron();
    Neuron(int nn_input_dim);

    int get_nn_input_dim();
    Activation get_activation_info();
    const Interval &get_input_value() const;
    Interval get_input_range();
    Matrix<Interval> get_first_order_der_value();
    Matrix<Interval> get_first_order_der_range();
    Matrix<Interval> get_second_order_der_value();
    Matrix<Interval> get_second_order_der_range();
    TaylorModel<Real> get_taylor_model();

    void set_input_value(Interval input_value);
    void set_input_range(Interval input_range);

    void set_first_order_der_value(Matrix<Interval> first_order_der_value);
    void set_first_order_der_range(Matrix<Interval> first_order_der_range);

    void set_second_order_der_value(Matrix<Interval> second_order_der_value);
    void set_second_order_der_range(Matrix<Interval> second_order_der_range);

    void set_input_value(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias);
    void set_input_range(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias);

    void set_first_order_der_value(vector<Neuron> last_layer_info, Matrix<Interval> weight);
    void set_first_order_der_range(vector<Neuron> last_layer_info, Matrix<Interval> weight);

    void set_second_order_der_value(vector<Neuron> last_layer_info, Matrix<Interval> weight);
    void set_second_order_der_range(vector<Neuron> last_layer_info, Matrix<Interval> weight);

    void set_activation_info(string activation_type, string approach);
    void set_activation_info(string activation_type, TaylorInfo ti, vector<Interval> tmv_domain);

    void set_taylor_model(vector<Neuron> last_layer_info, Matrix<Interval> weight, Interval bias);
    void set_taylor_model(TaylorModel<Real> tm);
};