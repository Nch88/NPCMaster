#include "stdafx.h"
#include "SymbolRecord.h"


SymbolRecord::SymbolRecord()
{
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(long s)
{
	symbol = s;
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(long s, long i)
{
	symbol = s;
	index = i;
	previous = NULL;
	next = NULL;
}

SymbolRecord::SymbolRecord(long s, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n)
{
	symbol = s;
	previous = p;
	next = n;
}

SymbolRecord::SymbolRecord(long s, long i, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n)
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

long SymbolRecord::getSymbol()
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