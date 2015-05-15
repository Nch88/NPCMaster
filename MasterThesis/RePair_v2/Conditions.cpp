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
	if (this->ts)
	{
		delete ts;
	}
}

long double Conditions::estimatedResultSize()
{
	//+ (100.0 - offset_terminals) / 2.0
	return (1.0 / ((offset_terminals + (100.0 - offset_terminals) / 8.0) / 100.0)) * offset_dictionaryEntries + 0.25 * offset_sequenceSize;
}