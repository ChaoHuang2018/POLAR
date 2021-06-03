#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

// Benchmark 1
void remainderEval_benchmark1(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time);

void linearizationDomainEval_benchmark1(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time);

// Benchmark 2
void remainderEval_benchmark2(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time);

void linearizationDomainEval_benchmark2(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time);

// Benchmark 5
void remainderEval_benchmark5(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time);

void linearizationDomainEval_benchmark5(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time);

// Benchmark 6
void remainderEval_benchmark6(Matrix<Interval> &remainder, Matrix<Interval> &stateSpace, Matrix<Interval> &u, Matrix<Interval> &d, double time);

void linearizationDomainEval_benchmark6(Matrix<Interval> &domain, Matrix<Interval> &x0, Matrix<Interval> &remainder, Matrix<Interval> &u, Matrix<Interval> &d, double time);

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
