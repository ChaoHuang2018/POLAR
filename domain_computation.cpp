#include "domain_computation.h"

using namespace flowstar;
using namespace std;

// Benchmark 1
void remainderEval_benchmark1(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Real factor(1.0 / 24.0), c1(-6), c2(84), c3(-105), c4(-12), c5(21);

	remainder[0][0] = (c1 * stateSpace[1][0] * stateSpace[1][0] + c2 * stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] * stateSpace[1][0] + c1 * stateSpace[0][0] * (u[0][0] + d[1][0]) + c3 * stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] * (stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] + d[0][0])) * (stateSpace[1][0] - stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] + d[0][0]) + c4 * stateSpace[0][0] * stateSpace[1][0] * (u[0][0] + d[1][0]) + c5 * stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] * (u[0][0] + d[1][0]);
	remainder[1][0] = 0;

	remainder[0][0] = factor * remainder[0][0] * pow(time, 4);
}

void linearizationDomainEval_benchmark1(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Real factor2(0.5), factor3(1.0 / 6.0), c1(3), c2(-6), c3(21), c4(-15);
	Interval delta(0, time);

	domain[0][0] = x0[0][0] + delta * (x0[1][0] - x0[0][0] * x0[0][0] * x0[0][0] + d[0][0]) + factor2 * delta * delta * (u[0][0] + d[1][0] - c1 * x0[0][0] * x0[0][0] * (x0[1][0] + d[0][0]) + c1 * x0[0][0] * x0[0][0] * (x0[0][0] * x0[0][0] * x0[0][0] + d[0][0])) + factor3 * delta * delta * delta * (c2 * x0[0][0] * x0[1][0] * (x0[1][0] + d[0][0]) + c3 * x0[0][0] * x0[0][0] * (x0[0][0] * x0[0][0] * x0[1][0] + d[0][0]) - c1 * x0[0][0] * x0[0][0] * (u[0][0] + d[1][0]) + c4 * x0[0][0] * x0[0][0] * x0[0][0] * x0[0][0] * (x0[0][0] * x0[0][0] * x0[0][0] + d[0][0]));
	domain[1][0] = x0[1][0] + delta * (u[0][0] + d[1][0]);

	domain[0][0] += remainder[0][0];
	domain[1][0] += remainder[1][0];
}

// Benchmark 2
void remainderEval_benchmark2(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	remainder[0][0] = 0;
	remainder[1][0] = 0;
	remainder[2][0] = 0;
}

void linearizationDomainEval_benchmark2(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Interval factor2(0.5), factor3(1.0 / 6.0);
	Interval delta(0, time), c1(0.5, 0.5);

	domain[0][0] = x0[0][0] + delta * (x0[1][0] + c1 * x0[2][0] * x0[2][0] + d[0][0]) + factor2 * delta * delta * (x0[2][0] + d[1][0] + x0[2][0] * (u[0][0] + d[2][0])) + factor3 * delta * delta * delta * (u[0][0] + d[1][0] + d[2][0] + (u[0][0] + d[2][0]) * (u[0][0] + d[2][0]));
	domain[1][0] = x0[1][0] + delta * (x0[2][0] + d[1][0]) + factor2 * delta * delta * (u[0][0] + d[1][0] + d[2][0]);
	domain[2][0] = x0[2][0] + delta * (u[0][0] + d[2][0]);

	// no need to add the zero remainder
}

// Benchmark 5
void remainderEval_benchmark5(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Interval factor(1.0 / 24.0), c1(36), c2(3), c3(12);

	remainder[0][0] = (c1 * stateSpace[1][0] * stateSpace[1][0] * (stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] - stateSpace[1][0] + d[0][0]) - c2 * (stateSpace[2][0] + d[1][0])) * (stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] - stateSpace[1][0] + d[0][0]) + (c3 * stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] - c2 * stateSpace[1][0] + c2 * d[0][0]) * (c2 * stateSpace[0][0] * stateSpace[0][0] * (stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] - stateSpace[1][0] + d[0][0]) - (stateSpace[2][0] + d[1][0])) - c2 * (stateSpace[0][0] * stateSpace[0][0] * stateSpace[0][0] - stateSpace[1][0] + d[0][0]);
	remainder[1][0] = 0;
	remainder[2][0] = 0;

	remainder[0][0] = factor * remainder[0][0] * pow(time, 4);
}

void linearizationDomainEval_benchmark5(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Interval factor2(0.5), factor3(1.0 / 6.0);
	Interval delta(0, time), c1(3), c2(12);

	domain[0][0] = x0[0][0] + delta * (x0[0][0] * x0[0][0] * x0[0][0] - x0[1][0] + d[0][0]) + factor2 * delta * delta * (c1 * x0[0][0] * x0[0][0] * x0[0][0] * x0[0][0] - c1 * x0[0][0] * x0[1][0] + c1 * x0[0][0] * d[0][0] - x0[2][0] - d[1][0]) + factor3 * delta * delta * delta * ((c2 * x0[0][0] * x0[0][0] * x0[0][0] - c1 * x0[1][0] + c1 * d[0][0]) * (x0[0][0] * x0[0][0] * x0[0][0] - x0[1][0] + d[0][0]) - c1 * x0[0][0] * (u[0][0] + d[2][0]) - u[0][0] - d[2][0]);
	domain[1][0] = x0[1][0] + delta * (x0[2][0] + d[2][0]) + factor2 * delta * delta * (u[0][0] + d[2][0]);
	domain[2][0] = x0[2][0] + delta * (u[0][0] + d[2][0]);

	domain[0][0] += remainder[0][0];
	domain[1][0] += remainder[1][0];
	domain[2][0] += remainder[2][0];
}

// Benchmark 6
void remainderEval_benchmark6(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Interval factor(1.0 / 24.0), c1(0.1), c2(0.2), c3(0.3);

	remainder[0][0] = stateSpace[0][0] - c1 * stateSpace[2][0].sin() - d[1][0] - c1 * stateSpace[2][0].sin() * (stateSpace[3][0] + d[2][0]) * (stateSpace[3][0] + d[2][0]) + c1 * stateSpace[2][0].cos() * (u[0][0] + d[3][0]);
	remainder[1][0] = stateSpace[1][0] + d[0][0] - c1 * stateSpace[2][0].cos() * (stateSpace[3][0] + d[2][0]) - c1 * stateSpace[2][0].cos() * (stateSpace[3][0] + d[2][0]) * (stateSpace[3][0] + d[2][0]) * (stateSpace[3][0] + d[2][0]) * (stateSpace[3][0] + d[2][0]) - c3 * stateSpace[2][0].sin() * (stateSpace[3][0] + d[2][0]) * (u[0][0] + d[3][0]);
	remainder[2][0] = 0;
	remainder[3][0] = 0;

	remainder[0][0] = factor * remainder[0][0] * pow(time, 4);
	remainder[1][0] = factor * remainder[1][0] * pow(time, 4);
}

void linearizationDomainEval_benchmark6(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time)
{
	Interval factor2(0.5), factor3(1.0 / 6.0);
	Interval delta(0, time), c1(0.1);

	domain[0][0] = x0[0][0] + delta * (x0[1][0] + d[0][0]) + factor2 * delta * delta * (c1 * x0[2][0].sin() - x0[0][0] + d[1][0]) + factor3 * delta * delta * delta * (c1 * x0[2][0].cos() * (x0[3][0] + d[2][0]) - x0[1][0] - d[0][0]);
	domain[1][0] = x0[1][0] + delta * (c1 * x0[2][0].sin() - x0[0][0] + d[1][0]) + factor2 * delta * delta * (c1 * x0[2][0].cos() * (x0[3][0] + d[2][0]) - x0[1][0] - d[0][0]) + factor3 * delta * delta * delta * (x0[0][0] - c1 * x0[2][0].sin() - d[1][0] - c1 * x0[2][0].sin() * (x0[3][0] + d[2][0]) * (x0[3][0] + d[2][0]) + c1 * x0[2][0].cos() * (u[0][0] + d[3][0]));
	domain[2][0] = x0[2][0] + delta * (x0[3][0] + d[2][0]) + factor2 * delta * delta * (u[0][0] + d[3][0]);
	domain[3][0] = x0[3][0] + delta * (u[0][0] + d[3][0]);

	domain[0][0] += remainder[0][0];
	domain[1][0] += remainder[1][0];
	domain[2][0] += remainder[2][0];
	domain[3][0] += remainder[3][0];
}

// int main()
// {

// 	// run the reachability computation
// 	clock_t begin, end;
// 	begin = clock();

// 	Matrix<Interval> remainder(4, 1), stateSpace(4, 1), u(1, 1), d(4, 1);
// 	Interval x(-2, 2), y(-2, 2), z(-2, 2), s(-2, 2), control(-1, 1), disturbance(-0.1, 0.1);
// 	stateSpace[0][0] = x;
// 	stateSpace[1][0] = y;
// 	stateSpace[2][0] = z;
// 	stateSpace[3][0] = s;

// 	u[0][0] = control;

// 	d[0][0] = d[1][0] = d[2][0] = d[3][0] = disturbance;

// 	remainderEval_benchmark6(remainder, stateSpace, u, d, 0.1);

// 	cout << "Initial:\n"
// 		 << remainder << endl;

// 	Matrix<Interval> x0(4, 1);
// 	x0[0][0] = 0.5;
// 	x0[1][0] = 0.2;
// 	x0[2][0] = 0.4;
// 	x0[3][0] = 0.8;

// 	Matrix<Interval> domain(4, 1);

// 	linearizationDomainEval_benchmark6(domain, x0, remainder, u, d, 0.1);

// 	cout << domain << endl;

// 	int N = 5;

// 	for (int i = 0; i < N; ++i)
// 	{
// 		stateSpace = domain;

// 		remainderEval_benchmark6(remainder, stateSpace, u, d, 0.1);

// 		linearizationDomainEval_benchmark6(domain, x0, remainder, u, d, 0.1);
// 	}

// 	cout << "\nAfter " << N << "-round refinement:\n"
// 		 << remainder << endl;
// 	cout << domain << endl;

// 	end = clock();
// 	printf("time cost: %lf\n", (double)(end - begin) / CLOCKS_PER_SEC);

// 	return 0;
// }
