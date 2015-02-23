#include "stdafx.h"
#include "Pair.h"


Pair::Pair()
{
}

Pair::Pair(unsigned int left, unsigned int right, unsigned int gen)
{
	leftSymbol = left;
	rightSymbol = right;
	generation = gen;
}

Pair::~Pair()
{
}
