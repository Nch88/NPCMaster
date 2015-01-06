#include "stdafx.h"

#pragma once
class SymbolRecord
{	char symbol;
	SymbolRecord* previous;
	SymbolRecord* next;

public:
	SymbolRecord();
	SymbolRecord(char s);
	SymbolRecord(char s, SymbolRecord* p, SymbolRecord* n);
	~SymbolRecord();

	void setPrevious(SymbolRecord* p);
	void setNext(SymbolRecord* n);

	char getSymbol();
	SymbolRecord* getPrevious();
	SymbolRecord* getNext();
};

