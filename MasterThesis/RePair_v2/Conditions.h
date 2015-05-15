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
	bool firstblock = true;

	//Automatic offset
	long double offset_sequenceSize = 0;
	long double offset_dictionaryEntries = 0;
	long double offset_minCompressedSize = 0;
	long double offset_optimalCutoff = 2;
	long double offset_terminals = 0;

	int optimalCutoff = 2;

	TestSuite *ts = nullptr;

	Conditions();
	Conditions(bool v, bool eV, bool t, bool c, bool test);
	~Conditions();

	long double estimatedResultSize();
};

