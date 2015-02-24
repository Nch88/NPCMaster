#pragma once
class Pair
{
public:
	unsigned int leftSymbol;
	unsigned int rightSymbol;
	unsigned int generation;

	Pair();
	Pair(unsigned int leftSymbol, unsigned int rightSymbol, unsigned int gen);
	~Pair();
};

