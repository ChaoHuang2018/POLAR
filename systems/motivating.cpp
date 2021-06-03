#include "../POLAR/Continuous.h"
#include "../NNTaylor.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
	intervalNumPrecision = 600;

	unsigned int maxOrder = 15;
	Global_Computation_Setting g_setting;
	g_setting.prepareForReachability(maxOrder);

	Interval cutoff_threshold(-1e-8, 1e-8);
	unsigned int order = 2;
	unsigned int bernstein_order = 2;
	unsigned int partition_num = 4000;

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

	int t_id = tmVars.declareVar("t");
	int z1_id = tmVars.declareVar("z1");
	int z2_id = tmVars.declareVar("z2");

	vector<Interval> domain;
	Interval I(-1, 1);

	domain.push_back(I);
	domain.push_back(I);
	domain.push_back(I);

	Term<Real> c1(1, 3);
	vector<unsigned int> D1(3, 0);
	D1[1] = 1;
	Term<Real> t1(-0.5, D1);

	vector<unsigned int> D2(3, 0);
	D2[2] = 1;
	Term<Real> t2(1, D2);

	vector<unsigned int> D3(3, 0);
	D3[1] = 1;
	D3[2] = 1;
	Term<Real> t3(-0.3, D3);

	list<Term<Real>> tl;
	tl.push_back(c1);
	tl.push_back(t2);
	tl.push_back(t1);
	tl.push_back(t3);

	Polynomial<Real> p1(tl);

	Interval r1(-0.1, 0.1);

	TaylorModel<Real> tm1(p1, r1);

	Term<Real> c2(-2, 3);
	vector<unsigned int> D11(3, 0);
	D11[2] = 1;
	Term<Real> t11(1, D11);

	vector<unsigned int> D12(3, 0);
	D12[1] = 2;
	Term<Real> t12(-0.1, D12);

	list<Term<Real>> tl1;
	tl1.push_back(c2);
	tl1.push_back(t11);
	tl1.push_back(t12);

	Polynomial<Real> p2(tl1);

	Interval r2(-0.2, 0.2);

	TaylorModel<Real> tm2(p2, r2);

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
	tmv_layer1.activate(tmv_layer1_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 0);

	tmv_layer1_after.output(cout, stateVars, tmVars);
	
	cout << "------------- Layer " << 2 << " starts. -------------" << endl;

	TaylorModelVec<Real> tmv_layer2;
	tmv_layer2 = W2 * tmv_layer1_after;
	tmv_layer2 += b2;

	TaylorModelVec<Real> tmv_layer2_after;
	tmv_layer2.activate(tmv_layer2_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 0);
	tmv_layer2_after.output(cout, stateVars, tmVars);
	
	cout << "------------- Output Layer starts. -------------" << endl;

	TaylorModelVec<Real> tmv_output;
	tmv_output = W3 * tmv_layer2_after;
	tmv_output += b3;

	TaylorModelVec<Real> tmv_output_after;
	tmv_output.activate(tmv_output_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 0);
	tmv_output_after.output(cout, stateVars, tmVars);

	// TaylorModel<Real> tm11_after;
	// tm11_before.activate(tm11_after, domain, "sigmoid", order, bernstein_order, partition_num, cutoff_threshold, g_setting, 1);

	// TaylorModel<Real> tm12_after;

	cout << endl;

	return 0;
}
