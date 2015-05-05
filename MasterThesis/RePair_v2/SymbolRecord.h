#pragma once
class SymbolRecord
{
public:
	unsigned long symbol;
	long index;
	SymbolRecord* previous;
	SymbolRecord* next;

	SymbolRecord();
	SymbolRecord(unsigned long s);
	SymbolRecord(unsigned long s, long index);
	SymbolRecord(unsigned long s, SymbolRecord * p, SymbolRecord * n);
	SymbolRecord(unsigned long s, long index, SymbolRecord * p, SymbolRecord * n);
	~SymbolRecord();
};

