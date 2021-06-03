/*
 * Symbolic_Remainder_NN.cpp
 *
 *  Created on: May 17, 2021
 *      Author: xchen4
 */

#include "Symbolic_Remainder_NN.h"

using namespace flowstar;

Symbolic_Remainder_NN::Symbolic_Remainder_NN()
{
}

Symbolic_Remainder_NN::Symbolic_Remainder_NN(const Symbolic_Remainder_NN & symbolic_remainder_nn)
{
	R = symbolic_remainder_nn.R;
	Q = symbolic_remainder_nn.Q;
	scalars = symbolic_remainder_nn.scalars;
}

Symbolic_Remainder_NN::~Symbolic_Remainder_NN()
{
}

Symbolic_Remainder_NN & Symbolic_Remainder_NN::operator = (const Symbolic_Remainder_NN & symbolic_remainder_nn)
{
	if(this == &symbolic_remainder_nn)
		return *this;

	R = symbolic_remainder_nn.R;
	Q = symbolic_remainder_nn.Q;
	scalars = symbolic_remainder_nn.scalars;

	return *this;
}




