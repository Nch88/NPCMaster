#pragma once
class SymbolRecord
{
public:
	unsigned int symbol;
	long index;
	SymbolRecord* previous;
	SymbolRecord* next;

	SymbolRecord();
	SymbolRecord(unsigned int s);
	SymbolRecord(unsigned int s, long index);
	SymbolRecord(unsigned int s, SymbolRecord * p, SymbolRecord * n);
	SymbolRecord(unsigned int s, long index, SymbolRecord * p, SymbolRecord * n);
	~SymbolRecord();
};

