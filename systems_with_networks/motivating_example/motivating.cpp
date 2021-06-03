#include "../flowstar-template/Continuous.h"
#include "../NNTaylor.h"
#include "../domain_computation.h"
#include "../dynamics_linearization.h"

using namespace std;
using namespace flowstar;

int main(int argc, char *argv[])
{
	intervalNumPrecision = 600;

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

	stateVars.declareVar("y1");
	tm1.output(cout, tmVars);

	return 0;
}
