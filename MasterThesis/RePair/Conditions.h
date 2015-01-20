#include "stdafx.h"

#pragma once
class Conditions
{
public:
	Conditions();
	Conditions(bool v, bool eV, bool t);
	~Conditions();

	bool verbose = false;
	bool extraVerbose = false;
	bool timing = false;
};

