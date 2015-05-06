#pragma once
class Conditions
{
public:
	bool verbose = false;
	bool extraVerbose = false;
	bool timing = false;
	bool compact = false;
	bool test = false;

	int runs = 1;
	int blocksizemb = 1;

	TestSuite *ts = nullptr;

	Conditions();
	Conditions(bool v, bool eV, bool t, bool c, bool test);
	~Conditions();
};

