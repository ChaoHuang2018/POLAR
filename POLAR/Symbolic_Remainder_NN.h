/*
 * Symbolic_Remainder_NN.h
 *
 *  Created on: May 17, 2021
 *      Author: xchen4
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include "Continuous.h"

namespace flowstar
{

	class Symbolic_Remainder_NN
	{
	public:
		std::vector<Matrix<Interval>> R;
		std::vector<Matrix<Real>> Q;
		std::vector<Real> scalars;

	public:
		Symbolic_Remainder_NN();
		Symbolic_Remainder_NN(const Symbolic_Remainder_NN &symbolic_remainder_nn);
		~Symbolic_Remainder_NN();

		Symbolic_Remainder_NN &operator=(const Symbolic_Remainder_NN &symbolic_remainder_nn);
	};

	// example to compute the TM overapproximation for a feedforward NN with sigmoid activation functions
	// Parameters:
	// tmv_input: input TM.
	// domain: the domain of the input TM.
	// result: Resulting TM overapproximation.
	// W: Weight matrices in the NN. W[i] denotes the weight matrix to the (i+1)-st hidden layer.
	// B: Bias vectors in the NN. B[i] denotes the bias used in the neurons in the (i+1)-st hidden layer.
}

#endif /* NEURALNETWORK_H_ */
