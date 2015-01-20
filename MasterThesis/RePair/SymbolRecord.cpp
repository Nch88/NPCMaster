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

SymbolRecord::SymbolRecord(unsigned int s, int i)
{
	symbol = s;
	index = i;
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(unsigned int s, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n)
{
	symbol = s;
	previous = p;
	next = n;
}

SymbolRecord::SymbolRecord(unsigned int s, int i, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n)
{
	symbol = s;
	previous = p;
	next = n;
	index = i;
}

SymbolRecord::~SymbolRecord()
{
}

void SymbolRecord::setPrevious(shared_ptr<SymbolRecord> p)
{
	previous = p;
}

void SymbolRecord::setNext(shared_ptr<SymbolRecord> n)
{
	next = n;
}

unsigned int SymbolRecord::getSymbol()
{
	return symbol;
}

shared_ptr<SymbolRecord> SymbolRecord::getPrevious()
{
	return previous;
}

shared_ptr<SymbolRecord> SymbolRecord::getNext()
{
	return next;
}