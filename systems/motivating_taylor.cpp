#include "../POLAR/Continuous.h"
#include "../NNTaylor.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
	intervalNumPrecision = 1000;

	unsigned int maxOrder = 15;
	Global_Computation_Setting g_setting;
	g_setting.prepareForReachability(maxOrder);

	Interval cutoff_threshold(-1e-8, 1e-8);
	unsigned int order = 2;
	unsigned int bernstein_order = 4;
	unsigned int partition_num = 1000;

	unsigned int if_symbo = 0;

	// input layer -> 1st hidden layer
	Matrix<Real> W1(2, 2), b1(2, 1);

	W1[0][0] = 1.5;
	W1[1][0] = -1;
	W1[0][1] = 0.5;
	W1[1][1] = 2;

	b1[0][0] = 0.3;
	b1[1][0] = 0;

	// 1st hidden layer -> 2nd hidden layer
	Matrix<Real> W2(2, 2), b2(2, 1);

	W2[0][0] = -0.8;
	W2[1][0] = 1.2;
	W2[0][1] = 3;
	W2[1][1] = 0.1;

	b2[0][0] = -1;
	b2[1][0] = 2;

	// 2nd hidden layer -> output layer
	Matrix<Real> W3(1, 2), b3(1, 1);

	W3[0][0] = 2;
	W3[0][1] = 1;

	b3[0][0] = 0;

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

	TaylorModelVec<Real> tmv_layer1;
	tmv_layer1 = W1 * tmv_input;
	tmv_layer1 += b1;

	stateVars.declareVar("y1");
	stateVars.declareVar("y2");
	// tmv_layer1.output(cout, stateVars, tmVars);

	TaylorModelVec<Real> tmv_layer1_after;
    tmv_layer1.output(cout, stateVars, tmVars);
	tmv_layer1.activate(tmv_layer1_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);

	tmv_layer1_after.output(cout, stateVars, tmVars);
	
	cout << "------------- Layer " << 2 << " starts. -------------" << endl;

	TaylorModelVec<Real> tmv_layer2;
	tmv_layer2 = W2 * tmv_layer1_after;
	tmv_layer2 += b2;

	TaylorModelVec<Real> tmv_layer2_after;
	tmv_layer2.activate(tmv_layer2_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);
	tmv_layer2_after.output(cout, stateVars, tmVars);
	
	cout << "------------- Output Layer starts. -------------" << endl;

	TaylorModelVec<Real> tmv_output;
	tmv_output = W3 * tmv_layer2_after;
//    tmv_output = W3 * tmv_input;
	tmv_output += b3;

	TaylorModelVec<Real> tmv_output_after;
	tmv_output.activate(tmv_output_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);
    
    Interval tmRange;
    tmv_output_after.tms[0].intEval(tmRange, domain);
    cout << "neural network output range with only TM Arithmetic:" << tmRange << endl;
    cout << "Ouput TM with only TM Arithmetic:" << endl;
	tmv_output_after.output(cout, stateVars, tmVars);

	// TaylorModel<Real> tm11_after;
	// tm11_before.activate(tm11_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);

	// TaylorModel<Real> tm12_after;

	cout << endl;

	return 0;
}
