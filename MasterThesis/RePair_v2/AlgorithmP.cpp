#include "stdafx.h"
#include "AlgorithmP.h"


AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

void AlgorithmP::establishContext(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolNext,
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray)
{
	indexSymbolLeft = sequenceIndex;

	//Right
	indexSymbolRight = sequenceArray[sequenceIndex + 1]->index;

	if (sequenceArray[indexSymbolRight]->symbol == 0)
	{
		indexSymbolRight = sequenceArray[indexSymbolRight]->next->index;
	}

	//Previous
	if (sequenceIndex > 0)
	{
		if (sequenceArray[indexSymbolLeft - 1]->symbol != 0)		
			indexSymbolPrevious = sequenceArray[indexSymbolLeft - 1]->index;
		else
			indexSymbolPrevious = sequenceArray[indexSymbolLeft - 1]->previous->index;		
	}

	//Next
	if (indexSymbolRight < sequenceArray.size() - 1)
	{
		if (sequenceArray[indexSymbolRight + 1]->symbol != 0)
			indexSymbolNext = sequenceArray[indexSymbolRight + 1]->index;
		else if (sequenceArray[indexSymbolRight + 1]->next)
			indexSymbolNext = sequenceArray[indexSymbolRight + 1]->next->index;
	}
}

void AlgorithmP::replaceAllPairs(
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	Conditions& c)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex]->next;

	do
	{
		establishContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceIndex,
			sequenceArray);


		nextSymbol = nextSymbol->next;
	} while (nextSymbol);
}