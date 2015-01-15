#include "stdafx.h"

using namespace std;
#pragma once
class SymbolRecord
{	
public:
	char symbol;
	int index;
	shared_ptr<SymbolRecord> previous;
	shared_ptr<SymbolRecord> next;


	SymbolRecord();
	SymbolRecord(char s);
	SymbolRecord(char s, int index);
	SymbolRecord(char s, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	SymbolRecord(char s, int index, shared_ptr<SymbolRecord> p, shared_ptr<SymbolRecord> n);
	~SymbolRecord();

	void setPrevious(shared_ptr<SymbolRecord> p);
	void setNext(shared_ptr<SymbolRecord> n);

	char getSymbol();
	shared_ptr<SymbolRecord> getPrevious();
	shared_ptr<SymbolRecord> getNext();
};

