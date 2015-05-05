#include "stdafx.h"
#include "SymbolRecord.h"


SymbolRecord::SymbolRecord()
{
	previous = nullptr;
	next = nullptr;
}

SymbolRecord::SymbolRecord(unsigned long s)
{
	symbol = s;
	previous = nullptr;
	next = nullptr;
}

SymbolRecord::SymbolRecord(unsigned long s, long i)
{
	symbol = s;
	index = i;
	previous = nullptr;
	next = nullptr;
}

SymbolRecord::SymbolRecord(unsigned long s, SymbolRecord * p, SymbolRecord * n)
{
	symbol = s;
	previous = p;
	next = n;
}

SymbolRecord::SymbolRecord(unsigned long s, long i, SymbolRecord * p, SymbolRecord * n)
{
	symbol = s;
	previous = p;
	next = n;
	index = i;
}


SymbolRecord::~SymbolRecord()
{
	previous = nullptr;
	next = nullptr;
}
