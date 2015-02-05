#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(establishContext, adjacentSymbols)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex;

	vector<SymbolRecord*> sequenceArray;
	unsigned int symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);
}