#include "stdafx.h"

using namespace std;
#pragma once
class SymbolRecord
{	
public:
	unsigned int symbol;
	int index;
	shared_ptr<SymbolRecord> previous;
	shared_ptr<SymbolRecord> next;


	SymbolRecord();
	SymbolRecord(unsigned int s);
	SymbolRecord(unsigned int s, int index);
	SymbolRecord(unsigned int s, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	SymbolRecord(unsigned int s, int index, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	~SymbolRecord();

	void setPrevious(shared_ptr<SymbolRecord> p);
	void setNext(shared_ptr<SymbolRecord> n);

	unsigned int getSymbol();
	shared_ptr<SymbolRecord> getPrevious();
	shared_ptr<SymbolRecord> getNext();
};

