#include "../POLAR/Continuous.h"
#include "../NNTaylor.h"
#include "../domain_computation.h"
#include "../dynamics_linearization.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
    intervalNumPrecision = 800;

    unsigned int maxOrder = 15;
    Global_Computation_Setting g_setting;
    g_setting.prepareForReachability(maxOrder);

    Interval cutoff_threshold(-1e-8, 1e-8);
    unsigned int order = 2;
    unsigned int bernstein_order = 4;
    unsigned int partition_num = 1000;

    unsigned int if_symbo = 0;

    string nn_name = "systems_with_networks/motivating_example/motivating_nn";
    NeuralNetwork nn(nn_name);

    // Declaration of the state variables.
    unsigned int numVars = 3;

    stateVars.declareVar("z1");
    stateVars.declareVar("z2");

    vector<Interval> domain;
    Interval I(-1, 1);

    domain.push_back(I);
    domain.push_back(I);
    domain.push_back(I);
    
    Interval r(0);
    
    Polynomial<Real> p1("1 - 0.5 * z1 + z2 - 0.3 * z1 * z2");
//    Polynomial<Real> p1("1 + 0.1 * z1");
    Interval r1(-0.1, 0.1);
    TaylorModel<Real> tm1(p1, r1);
    
    Polynomial<Real> p2("- 2 + z2 - 0.1 * z1 * z2");
//    Polynomial<Real> p2("- 2 + 0.1 * z2");
    Interval r2(-0.2, 0.2);
    TaylorModel<Real> tm2(p2, r2);
    
    int t_id = tmVars.declareVar("t");
    int z1_id = tmVars.declareVar("z1");
    int z2_id = tmVars.declareVar("z2");

    TaylorModelVec<Real> tmv_input;

    tmv_input.tms.push_back(tm1);
    tmv_input.tms.push_back(tm2);
    
    cout << "------------- Layer " << 1 << " starts. -------------" << endl;

    NNTaylor nn_taylor(nn);
    TaylorInfo ti(g_setting, order, bernstein_order, partition_num, cutoff_threshold);
    TaylorModelVec<Real> tmv_output;
    nn_taylor.NN_Reach(tmv_output, tmv_input, ti, domain);
    
    
    tmv_output.output(cout, stateVars, tmVars);

    // TaylorModel<Real> tm11_after;
    // tm11_before.activate(tm11_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);

    // TaylorModel<Real> tm12_after;

    cout << endl;

    return 0;
}
