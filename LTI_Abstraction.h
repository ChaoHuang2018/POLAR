#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

class LTI_Abstraction
{
protected:
	Matrix<Real> Ac;
	Matrix<UnivariateTaylorModel<Real>> Bc;
	Matrix<Interval> Uc;
	Matrix<UnivariateTaylorModel<Real>> Ux;
	Matrix<bool> connectivity;

public:
	LTI_Abstraction(Matrix<Real> &A, Matrix<Real> &B, Matrix<Real> &a, Matrix<Real> &C,
					Matrix<Interval> &range_of_Ux, Matrix<Interval> &range_of_Uu);

	int reach_LTI(std::list<LinearFlowpipe> &flowpipes, std::list<unsigned int> &flowpipe_orders, std::list<int> &flowpipes_safety,
				  unsigned long &num_of_flowpipes, const double time, const std::vector<Flowpipe> &initialSets, const Taylor_Model_Computation_Setting &tm_setting,
				  const Global_Computation_Setting &g_setting, const bool bPrint, const std::vector<Constraint> &unsafeSet, const bool bSafetyChecking,
				  const bool bPlot, const bool bTMOutput);

	void reach(Result_of_Reachability &result, Computational_Setting &setting, const Flowpipe &initialSet, const std::vector<Constraint> &unsafeSet);
};
