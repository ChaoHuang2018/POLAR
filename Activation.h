#include "POLAR/Continuous.h"
#include "TaylorInfo.h"

using namespace flowstar;
using namespace std;

class Activation
{

    //
public:
    string activation;
    Interval input;
    Interval input_bound;

    Interval value;
    Interval de;
    Interval de2;
    Interval output_range;
    Interval de_range;
    Interval de2_range;

    TaylorModel<Real> tm;

public:
    Activation();
    Activation(string act, Interval in, Interval in_bound, string approach = "taylor");

    Activation(string act, TaylorModel<Real> tm_in, TaylorInfo ti, vector<Interval> tmv_domain);

    string get_activation();
    Interval get_input();
    Interval get_input_bound();
    Interval get_value();
    Interval get_de();
    Interval get_de2();
    Interval get_output_range();
    Interval get_de_range();
    Interval get_de2_range();

    TaylorModel<Real> get_taylor_model();

    static Real softplus(Real x);
    static Real softplus_de(Real x);
    static Real softplus_de2(Real x);
    static double softplus(double x);
    static double softplus_de(double x);
    static double softplus_de2(double x);
    static Interval softplus(Interval x);
    static Interval softplus_de(Interval x);
    static Interval softplus_de2(Interval x);
    void softplus(Interval &x_assign, Interval &x);
    void softplus_de(Interval &x_assign, Interval &x);
    void softplus_de2(Interval &x_assign, Interval &x);

    static Real tanh(Real x);
    static Real tanh_de(Real x);
    static Real tanh_de2(Real x);
    static double tanh(double x);
    static double tanh_de(double x);
    static double tanh_de2(double x);
    static Interval tanh(Interval x);
    static Interval tanh_de(Interval x);
    static Interval tanh_de2(Interval x);
    void tanh(Interval &x_assign, Interval &x);
    void tanh_de(Interval &x_assign, Interval &x);
    void tanh_de2(Interval &x_assign, Interval &x);

    static Real sigmoid(Real x);
    static Real sigmoid_de(Real x);
    static Real sigmoid_de2(Real x);
    static double sigmoid(double x);
    static double sigmoid_de(double x);
    static double sigmoid_de2(double x);
    static Interval sigmoid(Interval x);
    static Interval sigmoid_de(Interval x);
    static Interval sigmoid_de2(Interval x);
    void sigmoid(Interval &x_assign, Interval &x);
    void sigmoid_de(Interval &x_assign, Interval &x);
    void sigmoid_de2(Interval &x_assign, Interval &x);

    static Real affine(Real x);
    static Real affine_de(Real x);
    static Real affine_de2(Real x);
    static double affine(double x);
    static double affine_de(double x);
    static double affine_de2(double x);
    static Interval affine(Interval x);
    static Interval affine_de(Interval x);
    static Interval affine_de2(Interval x);
    void affine(Interval &x_assign, Interval &x);
    void affine_de(Interval &x_assign, Interval &x);
    void affine_de2(Interval &x_assign, Interval &x);
};
