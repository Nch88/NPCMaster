#pragma once
class Conditions
{
public:
	bool verbose = false;
	bool extraVerbose = false;
	bool timing = false;
	bool compact = false;

	//Testing
	long long checkCountRight = 0;
	long long checkCountLeft = 0;
	long long replacePair = 0;
	long long incrementCountRight = 0;
	long long incrementCountLeft = 0;
	long long decrementCountRight = 0;
	long long decrementCountLeft = 0;
	long long pairCount = 0;

	Conditions();
	Conditions(bool v, bool eV, bool t, bool c);
	~Conditions();
};

