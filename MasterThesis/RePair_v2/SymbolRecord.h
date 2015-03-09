#pragma once
class SymbolRecord
{
public:
	long symbol;
	long index;
	SymbolRecord* previous;
	SymbolRecord* next;

	SymbolRecord();
	SymbolRecord(long s);
	SymbolRecord(long s, long index);
	SymbolRecord(long s, SymbolRecord * p, SymbolRecord * n);
	SymbolRecord(long s, long index, SymbolRecord * p, SymbolRecord * n);
	~SymbolRecord();
};

