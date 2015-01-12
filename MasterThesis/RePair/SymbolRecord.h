#include "stdafx.h"

#pragma once
class SymbolRecord
{	
public:
	char symbol;
	int index;
	SymbolRecord* previous;
	SymbolRecord* next;


	SymbolRecord();
	SymbolRecord(char s);
	SymbolRecord(char s, int index);
	SymbolRecord(char s, SymbolRecord* p, SymbolRecord* n);
	SymbolRecord(char s, int index, SymbolRecord* p, SymbolRecord* n);
	~SymbolRecord();

	void setPrevious(SymbolRecord* p);
	void setNext(SymbolRecord* n);

	char getSymbol();
	SymbolRecord* getPrevious();
	SymbolRecord* getNext();
};

