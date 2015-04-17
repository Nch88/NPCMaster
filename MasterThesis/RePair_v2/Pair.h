#pragma once
class Pair
{
public:
	unsigned long  leftSymbol;
	unsigned long  rightSymbol;
	unsigned long  generation;

	Pair();
	Pair(unsigned long  leftSymbol, unsigned long  rightSymbol, unsigned long  gen);
	~Pair();
};

