#include "stdafx.h"

using namespace std;
#pragma once
class SymbolRecord
{	
public:
	long symbol;
	long index;
	shared_ptr<SymbolRecord> previous;
	shared_ptr<SymbolRecord> next;


	SymbolRecord();
	SymbolRecord(long s);
	SymbolRecord(long s, long index);
	SymbolRecord(long s, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	SymbolRecord(long s, long index, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	~SymbolRecord();

	void setPrevious(shared_ptr<SymbolRecord> p);
	void setNext(shared_ptr<SymbolRecord> n);

	long getSymbol();
	shared_ptr<SymbolRecord> getPrevious();
	shared_ptr<SymbolRecord> getNext();
};

