#include "stdafx.h"
#include "AlgorithmP.h"


AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

void AlgorithmP::replaceInstanceOfPair(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolNext,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	Conditions& c)
{
	////Decrement count of xa
	//decrementCountLeft()
	//{

	//}
	////Decrement count of by
	//decrementCountRight()
	//{

	//}
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

void AlgorithmP::establishContext(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolBeforePrevious,
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

	//BeforePrevious
	if (indexSymbolPrevious > 0)
	{
		if (sequenceArray[indexSymbolPrevious - 1]->symbol != 0)
			indexSymbolBeforePrevious = sequenceArray[indexSymbolPrevious - 1]->index;
		else
			indexSymbolBeforePrevious = sequenceArray[indexSymbolPrevious - 1]->previous->index;
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

void AlgorithmP::findAllPairs(
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int& Symbols, //The symbol we are adding
	Conditions& c)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolBeforePrevious = -1;
	long indexSymbolNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];

	bool pairSequence = false;

	do
	{
		sequenceIndex = nextSymbol->index; //The current index in the seq array
		nextSymbol = nextSymbol->next;     //Pointer to the next place in the seq array

		establishContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolBeforePrevious,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceIndex,
			sequenceArray);

		//Symbols
		unsigned int symbolBeforePrevious = sequenceArray[indexSymbolBeforePrevious]->symbol;
		unsigned int symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;
		unsigned int symbolLeft = sequenceArray[indexSymbolLeft]->symbol;
		unsigned int symbolRight = sequenceArray[indexSymbolRight]->symbol;
		unsigned int symbolNext = sequenceArray[indexSymbolNext]->symbol;

		//Check if the last symbol will have been changed
		if (symbolBeforePrevious == symbolLeft && symbolPrevious == symbolRight)
			symbolPrevious = Symbols;
		

		//Add new pairs:

		if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord == NULL)
		//This is exactly the first time we see this
			activePairs[symbolPrevious][Symbols].seenOnce = true;

		else if (activePairs[symbolPrevious][Symbols].seenOnce) 
		//This is exactly the second time we see this
		{
			activePairs[symbolPrevious][Symbols].seenOnce = false;
			activePairs[symbolPrevious][Symbols].pairRecord = new PairRecord();
		}

		if (!activePairs[Symbols][symbolNext].seenOnce && activePairs[Symbols][symbolNext].pairRecord == NULL) 
		//This is exactly the first time we see this
			activePairs[Symbols][symbolNext].seenOnce = true;

		else if (activePairs[Symbols][symbolNext].seenOnce) 
		//This is exactly the second time we see this
		{
			activePairs[Symbols][symbolNext].seenOnce = false;
			activePairs[Symbols][symbolNext].pairRecord = new PairRecord();
		}		
		
	} while (nextSymbol);
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