#include "stdafx.h"
#include "CompactPair.h"

CompactPair::CompactPair()
{
}

CompactPair::CompactPair(long left, long right)
{
	leftSymbol = left;
	rightSymbol = right;
}

CompactPair::CompactPair(Pair &p)
{
	leftSymbol = p.leftSymbol;
	rightSymbol = p.rightSymbol;
}

CompactPair::~CompactPair()
{
}