#include "stdafx.h"

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
	SymbolRecord(char s, unique_ptr<SymbolRecord>& p, unique_ptr<SymbolRecord>& n);
	SymbolRecord(char s, int index, unique_ptr<SymbolRecord>& p, unique_ptr<SymbolRecord>& n);
	~SymbolRecord();

	void setPrevious(unique_ptr<SymbolRecord>& p);
	void setNext(unique_ptr<SymbolRecord>& n);

	char getSymbol();
	unique_ptr<SymbolRecord> getPrevious();
	unique_ptr<SymbolRecord> getNext();
};

