#include "stdafx.h"
#include "SymbolRecord.h"


SymbolRecord::SymbolRecord()
{
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(unsigned int s)
{
	symbol = s;
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(unsigned int s, long i)
{
	symbol = s;
	index = i;
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(unsigned int s, SymbolRecord * p, SymbolRecord * n)
{
	symbol = s;
	previous = p;
	next = n;
}

SymbolRecord::SymbolRecord(unsigned int s, long i, SymbolRecord * p, SymbolRecord * n)
{
	symbol = s;
	previous = p;
	next = n;
	index = i;
}


SymbolRecord::~SymbolRecord()
{
}
