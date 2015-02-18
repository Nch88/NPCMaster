#include "stdafx.h"
#include "Conditions.h"


Conditions::Conditions()
{
}

Conditions::Conditions(bool v, bool eV, bool t, bool c)
{
	verbose = v;
	extraVerbose = eV;
	timing = t;
	compact = c;
}

Conditions::~Conditions()
{
}
