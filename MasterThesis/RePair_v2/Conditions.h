#pragma once
class Conditions
{
public:
	bool verbose = false;
	bool extraVerbose = false;
	bool timing = false;
	bool compact = false;

	Conditions();
	Conditions(bool v, bool eV, bool t, bool c);
	~Conditions();
};

