#include "stdafx.h"
#include "Conditions.h"


Conditions::Conditions()
{
}

Conditions::Conditions(bool v, bool eV, bool t, bool c, bool test)
{
	verbose = v;
	extraVerbose = eV;
	timing = t;
	compact = c;
	this->test = test;
}

Conditions::~Conditions()
{
}

long double Conditions::estimatedResultSize()
{
	double base = 100.0;
	double baseFactor = 0.25;
	double terminalFactor = (abs(base - offset_terminals) / base / 4.4);
	double sequenceFactor = baseFactor - terminalFactor;
	if (sequenceFactor <= 0)
	{
		sequenceFactor = 0.02;
	}
	return offset_dictionaryEntries + (sequenceFactor * offset_sequenceSize);
}