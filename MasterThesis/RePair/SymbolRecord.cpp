#include "stdafx.h"
#include "SymbolRecord.h"


SymbolRecord::SymbolRecord()
{
}

SymbolRecord::SymbolRecord(char s)
{
	symbol = s;
}

SymbolRecord::SymbolRecord(char s, SymbolRecord* p, SymbolRecord* n)
{
	symbol = s;
	previous = p;
	next = n;
}

SymbolRecord::~SymbolRecord()
{
}

void SymbolRecord::setPrevious(SymbolRecord* p)
{
	previous = p;
}

void SymbolRecord::setNext(SymbolRecord* n)
{
	next = n;
}

char SymbolRecord::getSymbol()
{
	return symbol;
}

SymbolRecord* SymbolRecord::getPrevious()
{
	return previous;
}

SymbolRecord* SymbolRecord::getNext()
{
	return next;
}