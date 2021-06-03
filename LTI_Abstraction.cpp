#include "LTI_Abstraction.h"


LTI_Abstraction::LTI_Abstraction(Matrix<Real> & A, Matrix<Real> & B, Matrix<Real> & a, Matrix<Real> & C,
		Matrix<Interval> & range_of_Ux, Matrix<Interval> & range_of_Uu)
{
	Ac = A + B * C;

	Uc = range_of_Uu + a;

	Bc = B * Uc;

	Ux = range_of_Ux;

	unsigned int n = Ac.rows();
	Matrix<bool> conMatrix(n, n), adjMatrix(n, n);

	for(unsigned int i=0; i<n; ++i)
	{
		for(unsigned int j=0; j<n; ++j)
		{
			if(Ac[i][j] != 0)
			{
				adjMatrix[i][j] = true;
			}
		}
	}

	check_connectivities(conMatrix, adjMatrix);
	connectivity = conMatrix;
}

int LTI_Abstraction::reach_LTI(std::list<LinearFlowpipe> & flowpipes, std::list<unsigned int> & flowpipe_orders, std::list<int> & flowpipes_safety,
		unsigned long & num_of_flowpipes, const double time, const std::vector<Flowpipe> & initialSets, const Taylor_Model_Computation_Setting & tm_setting,
		const Global_Computation_Setting & g_setting, const bool bPrint, const std::vector<Constraint> & unsafeSet, const bool bSafetyChecking,
		const bool bPlot, const bool bTMOutput)
{
	// find a proper parameter r = 2^n such that |A*delta/r| < 0.1
	Real A_max = Ac.max_norm();
	Real threshold = 0.1;
	double step = tm_setting.step_exp_table[1].sup();
	Real rStep = step;

	unsigned int r = 1, n = 0;
	while(A_max >= threshold)
	{
		r *= 2;
		++n;
		A_max /= r;
	}

	// find the proper order
	Real A_min = Ac.min_entry();
	A_min /= r;
	Real tolerance = APPROX_TOLERANCE;
	Real error;

	unsigned int approx_order = findProperOrder(error, A_max, A_min, tolerance, tm_setting.order);


	unsigned int nec_order = 2*approx_order + 1;
	std::vector<Real> step_end_exp_table(nec_order + 1, 1);
	step_end_exp_table[1] = step;

	for(unsigned int i=2; i<=nec_order; ++i)
	{
		step_end_exp_table[i] = step_end_exp_table[i-1] * rStep;
	}


	Interval intStep(0, step);
	interval_utm_setting.setValue(intStep, approx_order);

	int rangeDim = Ac.rows();

	// identity matrix
	Matrix<Real> identity(rangeDim);

	Matrix<Real> A_scaled = Ac / r;

	// compute the Taylor series to the order of approx_order
	std::vector<Matrix<Real> > A_exp_table;
	compute_mat_pow(A_exp_table, A_scaled, approx_order);

	Matrix<UnivariatePolynomial<Real> > expansion_exp_A_t_k = (Matrix<UnivariatePolynomial<Real> >)identity;

	Real tmp = 1;

	for(unsigned int i=1; i<=approx_order; ++i)
	{
		Matrix<UnivariatePolynomial<Real> > A_t_i = (Matrix<UnivariatePolynomial<Real> >)A_exp_table[i];
		A_t_i.times_x(i);

		tmp *= i;
		A_t_i /= tmp;

		expansion_exp_A_t_k += A_t_i;
	}

	Matrix<UnivariateTaylorModel<Real> > utm_Phi_0 = expansion_exp_A_t_k;


	// compute a proper remainder
	Interval intErr;
	error.to_sym_int(intErr);

	Matrix<Interval> im_error(rangeDim, rangeDim);
	for(int i=0; i<rangeDim; ++i)
	{
		for(int j=0; j<rangeDim; ++j)
		{
			if(connectivity[i][j])
			{
				im_error[i][j] = intErr;
			}
		}
	}

	utm_Phi_0.setRemainder(im_error);

	for(unsigned int i=0; i<n; ++i)
	{
		utm_Phi_0 *= utm_Phi_0;
	}

	// evaluate the one-step mapping matrix
	Matrix<Real> rm_Phi(rangeDim, rangeDim);
	utm_Phi_0.evaluate(rm_Phi, step_end_exp_table);


	// compute the linear mapping for the constant part
	Matrix<UnivariateTaylorModel<Real> > utm_Psi_u_0;
	Matrix<UnivariateTaylorModel<Real> > utm_Psi_u(rangeDim, 1);

	LinearFlowpipe flowpipe;

	utm_Psi_u_0 = utm_Phi_0 * Bc;
	utm_Psi_u_0.integral(intStep);
	utm_Psi_u_0.evaluate(utm_Psi_u, step_end_exp_table);
	utm_Psi_u_0.ctrunc(tm_setting.order);
	flowpipe.Psi = utm_Psi_u_0;


	Matrix<UnivariateTaylorModel<Real> > utm_Psi_x_0;
	Matrix<UnivariateTaylorModel<Real> > utm_Psi_x(rangeDim, 1);
	utm_Psi_x_0 = utm_Phi_0 * Ux;
	utm_Psi_x_0.integral(intStep);
	utm_Psi_x_0.evaluate(utm_Psi_x, step_end_exp_table);
	utm_Psi_x_0.ctrunc(tm_setting.order);
	flowpipe.Psi = flowpipe.Psi + utm_Psi_x_0;


	utm_Phi_0.ctrunc(tm_setting.order);
	flowpipe.Phi = utm_Phi_0;

	interval_utm_setting.setOrder(tm_setting.order);


	flowpipes.clear();
	flowpipes_safety.clear();

	num_of_flowpipes = 1;


	// perform the safety checking on the first flowpipe
	int checking_result = COMPLETED_SAFE;
	std::vector<std::vector<Interval> > polyRangeX0;
	std::vector<std::vector<Interval> > range_of_X0;

	std::vector<Interval> domain = initialSets[0].domain;
	domain[0] = intStep;


	if(bSafetyChecking)
	{
		for(int m=0; m<initialSets.size(); ++m)
		{
			std::vector<Interval> intVecTemp;
			initialSets[m].tmvPre.polyRangeNormal(intVecTemp, interval_utm_setting.val_exp_table);
			polyRangeX0.push_back(intVecTemp);

			std::vector<Interval> rangeX0(rangeDim);
			for(int k=0; k<rangeDim; ++k)
			{
				rangeX0[k] = intVecTemp[k] + initialSets[m].tmvPre.tms[k].remainder;
			}

			range_of_X0.push_back(rangeX0);
		}

		if(bTMOutput || bPlot)
		{
			flowpipes.push_back(flowpipe);
		}

		for(int m=0; m<initialSets.size(); ++m)
		{
			int safety;

			safety = flowpipe.safetyChecking(unsafeSet, tm_setting, g_setting, initialSets[m].tmvPre, polyRangeX0[m], range_of_X0[m], domain);

			if(bTMOutput || bPlot)
			{
				flowpipes_safety.push_back(safety);
			}

			if(safety == UNSAFE)
			{
				return COMPLETED_UNSAFE;
			}
			else if(safety == UNKNOWN && checking_result == COMPLETED_SAFE)
			{
				checking_result = COMPLETED_UNKNOWN;
			}
		}
	}
	else
	{
		if(bTMOutput || bPlot)
		{
			flowpipes.push_back(flowpipe);

			for(int m=0; m<initialSets.size(); ++m)
			{
				flowpipes_safety.push_back(SAFE);
			}
		}
	}


	Matrix<UnivariateTaylorModel<Real> > utm_global_Psi_u = utm_Psi_u;
	Matrix<UnivariateTaylorModel<Real> > utm_global_Psi_x = utm_Psi_x;
	Matrix<Real> rm_global_Phi(rangeDim);

	int N = (int)ceil(time/step);

	if(bPrint)
	{
		printf("time = %f,\t", step);
		printf("step = %f,\t", step);
		printf("order = %d\n", tm_setting.order);
	}


	for(int i=1; i<N; ++i)
	{
		LinearFlowpipe newFlowpipe;

//		rm_global_Phi = rm_Phi * rm_global_Phi;
		newFlowpipe.Phi = rm_global_Phi * utm_Phi_0;
		newFlowpipe.Phi.evaluate(rm_global_Phi, step_end_exp_table);

		newFlowpipe.Psi = utm_Phi_0 * utm_global_Psi_u + utm_Psi_u_0;
		utm_global_Psi_u += rm_global_Phi * utm_Psi_u;

		newFlowpipe.Psi += utm_Phi_0 * utm_global_Psi_x + utm_Psi_x_0;
		utm_global_Psi_x += rm_global_Phi * utm_Psi_x;

		++num_of_flowpipes;

		if(bSafetyChecking)
		{
			if(bTMOutput || bPlot)
			{
				flowpipes.push_back(newFlowpipe);
			}

			for(int m=0; m<initialSets.size(); ++m)
			{
				int safety;

				safety = newFlowpipe.safetyChecking(unsafeSet, tm_setting, g_setting, initialSets[m].tmvPre, polyRangeX0[m], range_of_X0[m], domain);

				if(bTMOutput || bPlot)
				{
					flowpipes_safety.push_back(safety);
				}

				if(safety == UNSAFE)
				{
					if(true)
					{
						printf("time = %f,\t", (i+1)*step);
						printf("step = %f,\t", step);
						printf("order = %d\n", tm_setting.order);
					}

					return COMPLETED_UNSAFE;
				}
				else if(safety == UNKNOWN && checking_result == COMPLETED_SAFE)
				{
					checking_result = COMPLETED_UNKNOWN;
				}
			}
		}
		else
		{
			if(bTMOutput || bPlot)
			{
				flowpipes.push_back(newFlowpipe);

				for(int m=0; m<initialSets.size(); ++m)
				{
					flowpipes_safety.push_back(SAFE);
				}
			}
		}

		if(bPrint)
		{
			printf("time = %f,\t", (i+1)*step);
			printf("step = %f,\t", step);
			printf("order = %d\n", tm_setting.order);
		}
	}

	return checking_result;
}

void LTI_Abstraction::reach(Result_of_Reachability & result, Computational_Setting & setting, const Flowpipe & initialSet, const std::vector<Constraint> & unsafeSet)
{
	std::vector<Flowpipe> initialSets;
	initialSets.push_back(initialSet);

	bool bSafetyChecking = false;

	if(unsafeSet.size() > 0)
	{
		bSafetyChecking = true;
	}

	result.status = reach_LTI(result.linear_flowpipes, result.orders_of_flowpipes, result.safety_of_flowpipes,
			result.num_of_flowpipes, setting.time, initialSets, setting.tm_setting,
			setting.g_setting, setting.bPrint, unsafeSet, bSafetyChecking, true, true);
}



