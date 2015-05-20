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
