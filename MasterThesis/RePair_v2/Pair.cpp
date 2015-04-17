#include "stdafx.h"
#include "Pair.h"


Pair::Pair()
{
}

Pair::Pair(unsigned long  left, unsigned long  right, unsigned long  gen)
{
	leftSymbol = left;
	rightSymbol = right;
	generation = gen;
}

Pair::~Pair()
{
}
