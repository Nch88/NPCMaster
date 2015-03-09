#include "stdafx.h"
#include "Pair.h"


Pair::Pair()
{
}

Pair::Pair(long left, long right, long gen)
{
	leftSymbol = left;
	rightSymbol = right;
	generation = gen;
}

Pair::~Pair()
{
}
