#include "stdafx.h"

#pragma once
class Pair
{
public:
	Pair();
	Pair(unsigned int leftSymbol, unsigned int rightSymbol);
	~Pair();

	unsigned int leftSymbol;
	unsigned int rightSymbol;
};

