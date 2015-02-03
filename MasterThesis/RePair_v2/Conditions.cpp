#include "stdafx.h"
#include "Conditions.h"


Conditions::Conditions()
{
}

Conditions::Conditions(bool v, bool eV, bool t)
{
	verbose = v;
	extraVerbose = eV;
	timing = t;
}

Conditions::~Conditions()
{
}
