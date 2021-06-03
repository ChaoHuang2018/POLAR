#include "dynamics_linearization.h"
#include <cmath>

using namespace flowstar;
using namespace std;

// Benchmark 1
void remainder_linear_taylor_benchmark1(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 2;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(-6);

	remainder[0][0] = 0.5 * c1 * domain[0][0] * (domain[0][0] - center[0][0]) * (domain[0][0] - center[0][0]);
	remainder[1][0] = 0;
}

void dynamics_linear_taylor_benchmark1(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 2;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	// const terms consists of two parts
	double const_term_ode1 = (center[1][0] - pow(center[0][0], 3.0)) + (3 * pow(center[0][0], 3.0) - center[1][0]);
	vector<double> jacobian;
	jacobian.push_back(-3 * pow(center[0][0], 2.0));
	jacobian.push_back(1);

	coeff[0][0] = jacobian[0];
	coeff[0][1] = jacobian[1];
	coeff[1][0] = 0;
	coeff[1][1] = 0;

	const_term[0][0] = const_term_ode1;
	const_term[1][0] = 0;

	// need to revise, forgot to consider the approximation error

	// string ode1_linear = to_string(const_term_ode1) + " + (" + to_string(jacobian[0]) + ") * " + "x0" + " + (" + to_string(jacobian[1]) + ") * " + "x1";
	// string ode2_linear = "0";

	// dynamics[0][0] = ode1_linear;
	// dynamics[1][0] = ode2_linear;
}

// Benchmark 2
void remainder_linear_taylor_benchmark2(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(1);

	remainder[0][0] = 0.5 * c1 * domain[0][0] * (domain[2][0] - center[2][0]) * (domain[2][0] - center[2][0]);
	remainder[1][0] = 0;
	remainder[2][0] = 0;
}

void dynamics_linear_taylor_benchmark2(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	double const_term_ode0 = (center[1][0] + 0.5 * pow(center[2][0], 2.0)) + (-center[1][0] - pow(center[2][0], 2.0));
	vector<double> jacobian0;
	jacobian0.push_back(0);
	jacobian0.push_back(1);
	jacobian0.push_back(center[2][0]);

	double const_term_ode1 = 0;
	vector<double> jacobian1;
	jacobian1.push_back(0);
	jacobian1.push_back(0);
	jacobian1.push_back(1);

	double const_term_ode2 = 0;
	vector<double> jacobian2;
	jacobian2.push_back(0);
	jacobian2.push_back(0);
	jacobian2.push_back(0);

	coeff[0][0] = jacobian0[0];
	coeff[0][1] = jacobian0[1];
	coeff[0][2] = jacobian0[2];
	coeff[1][0] = jacobian1[0];
	coeff[1][1] = jacobian1[1];
	coeff[1][2] = jacobian1[2];
	coeff[2][0] = jacobian2[0];
	coeff[2][1] = jacobian2[1];
	coeff[2][2] = jacobian2[2];

	const_term[0][0] = const_term_ode0;
	const_term[1][0] = const_term_ode1;
	const_term[2][0] = const_term_ode2;

	// string ode0_linear = to_string(const_term_ode0) + " + (" + to_string(jacobian0[0]) + ") * " + "x0" + " + (" + to_string(jacobian1[1]) + ") * " + "x1";
	// string ode1_linear = "0";

	// dynamics[0][0] = ode0_linear;
	// dynamics[1][0] = ode1_linear;
}

// Benchmark 3
void remainder_linear_taylor_benchmark3(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(2);

	remainder[0][0] = 0;
	remainder[1][0] = 0.5 * c1 * (domain[0][0] - center[0][0]) * (domain[2][0] - center[2][0]);
	remainder[2][0] = 0;
}

void dynamics_linear_taylor_benchmark3(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	double const_term_ode0 = 0;
	vector<double> jacobian0;
	jacobian0.push_back(-1);
	jacobian0.push_back(1);
	jacobian0.push_back(-1);

	double const_term_ode1 = (-center[0][0] * (center[2][0] + 1) - center[1][0]) + (-(center[2][0] + 1) * (-center[0][0]) + (-1) * (-center[1][0]) + (-center[0][0]) * (-center[2][0]));
	vector<double> jacobian1;
	jacobian1.push_back(-(center[2][0] + 1));
	jacobian1.push_back(-1);
	jacobian1.push_back((-center[0][0]));

	double const_term_ode2 = 0;
	vector<double> jacobian2;
	jacobian2.push_back(-1);
	jacobian2.push_back(0);
	jacobian2.push_back(0);

	coeff[0][0] = jacobian0[0];
	coeff[0][1] = jacobian0[1];
	coeff[0][2] = jacobian0[2];
	coeff[1][0] = jacobian1[0];
	coeff[1][1] = jacobian1[1];
	coeff[1][2] = jacobian1[2];
	coeff[2][0] = jacobian2[0];
	coeff[2][1] = jacobian2[1];
	coeff[2][2] = jacobian2[2];

	const_term[0][0] = const_term_ode0;
	const_term[1][0] = const_term_ode1;
	const_term[2][0] = const_term_ode2;

	// string ode0_linear = to_string(const_term_ode0) + " + (" + to_string(jacobian0[0]) + ") * " + "x0" + " + (" + to_string(jacobian1[1]) + ") * " + "x1";
	// string ode1_linear = "0";

	// dynamics[0][0] = ode0_linear;
	// dynamics[1][0] = ode1_linear;
}

// Benchmark 4
void remainder_linear_taylor_benchmark4(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(-6);
	Real c2(6);

	remainder[0][0] = 0.5 * c1 * domain[0][0] * (domain[0][0] - center[0][0]) * (domain[0][0] - center[0][0]);
	remainder[1][0] = 0.5 * c2 * domain[1][0] * (domain[1][0] - center[1][0]) * (domain[1][0] - center[1][0]);
	remainder[2][0] = 0;
}

void dynamics_linear_taylor_benchmark4(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	double const_term_ode0 = (-pow(center[0][0], 3.0) + center[1][0]) + (3 * pow(center[0][0], 3.0) - center[1][0]);
	vector<double> jacobian0;
	jacobian0.push_back(-3 * pow(center[0][0], 2.0));
	jacobian0.push_back(1);
	jacobian0.push_back(0);

	double const_term_ode1 = (pow(center[1][0], 3.0) + center[2][0]) + (-3 * pow(center[0][0], 3.0) - center[2][0]);
	vector<double> jacobian1;
	jacobian1.push_back(0);
	jacobian1.push_back(3 * pow(center[1][0], 2.0));
	jacobian1.push_back(1);

	double const_term_ode2 = 0;
	vector<double> jacobian2;
	jacobian2.push_back(0);
	jacobian2.push_back(0);
	jacobian2.push_back(0);

	coeff[0][0] = jacobian0[0];
	coeff[0][1] = jacobian0[1];
	coeff[0][2] = jacobian0[2];
	coeff[1][0] = jacobian1[0];
	coeff[1][1] = jacobian1[1];
	coeff[1][2] = jacobian1[2];
	coeff[2][0] = jacobian2[0];
	coeff[2][1] = jacobian2[1];
	coeff[2][2] = jacobian2[2];

	const_term[0][0] = const_term_ode0;
	const_term[1][0] = const_term_ode1;
	const_term[2][0] = const_term_ode2;

	// string ode0_linear = to_string(const_term_ode0) + " + (" + to_string(jacobian0[0]) + ") * " + "x0" + " + (" + to_string(jacobian1[1]) + ") * " + "x1";
	// string ode1_linear = "0";

	// dynamics[0][0] = ode0_linear;
	// dynamics[1][0] = ode1_linear;
}

// Benchmark 5
void remainder_linear_taylor_benchmark5(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(6);

	remainder[0][0] = 0.5 * c1 * domain[2][0] * (domain[2][0] - center[2][0]) * (domain[2][0] - center[2][0]);
	remainder[1][0] = 0;
	remainder[2][0] = 0;
}

void dynamics_linear_taylor_benchmark5(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 3;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	double const_term_ode0 = (pow(center[2][0], 3.0) - center[1][0]) + (-3 * pow(center[2][0], 3.0) + center[1][0]);
	vector<double> jacobian0;
	jacobian0.push_back(0);
	jacobian0.push_back(-1);
	jacobian0.push_back(3 * pow(center[2][0], 2.0));

	double const_term_ode1 = 0;
	vector<double> jacobian1;
	jacobian1.push_back(0);
	jacobian1.push_back(0);
	jacobian1.push_back(1);

	double const_term_ode2 = 0;
	vector<double> jacobian2;
	jacobian2.push_back(0);
	jacobian2.push_back(0);
	jacobian2.push_back(0);

	coeff[0][0] = jacobian0[0];
	coeff[0][1] = jacobian0[1];
	coeff[0][2] = jacobian0[2];
	coeff[1][0] = jacobian1[0];
	coeff[1][1] = jacobian1[1];
	coeff[1][2] = jacobian1[2];
	coeff[2][0] = jacobian2[0];
	coeff[2][1] = jacobian2[1];
	coeff[2][2] = jacobian2[2];

	const_term[0][0] = const_term_ode0;
	const_term[1][0] = const_term_ode1;
	const_term[2][0] = const_term_ode2;

	// string ode0_linear = to_string(const_term_ode0) + " + (" + to_string(jacobian0[0]) + ") * " + "x0" + " + (" + to_string(jacobian1[1]) + ") * " + "x1";
	// string ode1_linear = "0";

	// dynamics[0][0] = ode0_linear;
	// dynamics[1][0] = ode1_linear;
}

// Benchmark 6
void remainder_linear_taylor_benchmark6(Matrix<Interval> &remainder, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 4;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	Real c1(-0.1);

	remainder[0][0] = 0;

	// treatment for sin
	const double PI = 3.141592653589793238463;
	double inf = min(sin(domain[2][0].inf()), sin(domain[2][0].sup()));
	double sup = max(sin(domain[2][0].inf()), sin(domain[2][0].sup()));
	int k_sup = floor((domain[2][0].sup() - PI / 2) / PI);
	int k_inf = ceil((domain[2][0].inf() - PI / 2) / PI);
	if (k_sup > k_inf)
	{
		if (k_sup % 2 == 1)
		{
			inf = -1;
		}
		if (k_inf % 2 == 0)
		{
			sup = 1;
		}
	}
	Interval I1(inf, sup);
	remainder[1][0] = 0.5 * c1 * I1 * (domain[2][0] - center[2][0]) * (domain[2][0] - center[2][0]);

	remainder[2][0] = 0;
	remainder[3][0] = 0;
}

void dynamics_linear_taylor_benchmark6(Matrix<string> &dynamics, Matrix<double> &coeff, Matrix<double> &const_term, Matrix<Interval> &domain)
{
	// declare the number of state variables
	unsigned int numVars = 4;

	Matrix<double> center(numVars, 1);
	for (int j = 0; j < numVars; j++)
	{
		center[j][0] = domain[j][0].midpoint();
	}

	double const_term_ode0 = 0;
	vector<double> jacobian0;
	jacobian0.push_back(0);
	jacobian0.push_back(1);
	jacobian0.push_back(0);
	jacobian0.push_back(0);

	double const_term_ode1 = -center[0][0] + 0.1 * sin(center[2][0]) + (-1) * (-center[0][0]) + 0.1 * cos(center[2][0]) * (-center[2][0]);
	vector<double> jacobian1;
	jacobian1.push_back(-1);
	jacobian1.push_back(0);
	jacobian1.push_back(1.1 * cos(center[2][0]));
	jacobian0.push_back(0);

	double const_term_ode2 = 0;
	vector<double> jacobian2;
	jacobian2.push_back(0);
	jacobian2.push_back(0);
	jacobian2.push_back(0);
	jacobian2.push_back(1);

	double const_term_ode3 = 0;
	vector<double> jacobian3;
	jacobian3.push_back(0);
	jacobian3.push_back(0);
	jacobian3.push_back(0);
	jacobian3.push_back(0);

	coeff[0][0] = jacobian0[0];
	coeff[0][1] = jacobian0[1];
	coeff[0][2] = jacobian0[2];
	coeff[0][3] = jacobian0[3];
	coeff[1][0] = jacobian1[0];
	coeff[1][1] = jacobian1[1];
	coeff[1][2] = jacobian1[2];
	coeff[1][3] = jacobian1[3];
	coeff[2][0] = jacobian2[0];
	coeff[2][1] = jacobian2[1];
	coeff[2][2] = jacobian2[2];
	coeff[2][3] = jacobian2[3];
	coeff[3][0] = jacobian3[0];
	coeff[3][1] = jacobian3[1];
	coeff[3][2] = jacobian3[2];
	coeff[3][3] = jacobian3[3];

	const_term[0][0] = const_term_ode0;
	const_term[1][0] = const_term_ode1;
	const_term[2][0] = const_term_ode2;
	const_term[3][0] = const_term_ode3;

	// string ode0_linear = to_string(const_term_ode0) + " + (" + to_string(jacobian0[0]) + ") * " + "x0" + " + (" + to_string(jacobian1[1]) + ") * " + "x1";
	// string ode1_linear = "0";

	// dynamics[0][0] = ode0_linear;
	// dynamics[1][0] = ode1_linear;
}