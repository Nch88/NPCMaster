#pragma once
class Pair
{
public:
	long leftSymbol;
	long rightSymbol;
	long generation;

	Pair();
	Pair(long leftSymbol, long rightSymbol, long gen);
	~Pair();
};

