#include "stdafx.h"
#include "AlgorithmP.h"


AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

void AlgorithmP::removeSymbolThreadingPointers(
	long & indexSymbolLeft,
	vector<SymbolRecord*> & sequenceArray)
{
	if (sequenceArray[indexSymbolLeft]->previous &&
		sequenceArray[indexSymbolLeft]->next)
	{
		sequenceArray[indexSymbolLeft]->previous->next =
			sequenceArray[indexSymbolLeft]->next;
		sequenceArray[indexSymbolLeft]->next->previous =
			sequenceArray[indexSymbolLeft]->previous;
	}
	else if (sequenceArray[indexSymbolLeft]->previous)
	{
		sequenceArray[indexSymbolLeft]->previous->next = nullptr;
	}
	else if (sequenceArray[indexSymbolLeft]->next)
	{
		sequenceArray[indexSymbolLeft]->next->previous = nullptr;
	}
	sequenceArray[indexSymbolLeft]->previous = nullptr;
	sequenceArray[indexSymbolLeft]->next = nullptr;
}

void AlgorithmP::updatePairRecord(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	PairTracker *& tracker)
{
	tracker->pairRecord->count--;

	long symbolleft = sequenceArray[indexSymbolLeft]->symbol;
	long symbolRight = sequenceArray[indexSymbolRight]->symbol;

	if (tracker->pairRecord->count < 2) //Delete pair record
	{
		delete activePairs[symbolleft][symbolRight].pairRecord;
		activePairs[symbolleft][symbolRight].pairRecord = nullptr;
		activePairs[symbolleft][symbolRight].seenOnce = false;
		activePairs[symbolleft][symbolRight].indexFirst = -1;
		tracker->pairRecord = nullptr;
		tracker = nullptr;
	}
	else
	{
		if (indexSymbolLeft == tracker->pairRecord->arrayIndexFirst)
		{
			tracker->pairRecord->arrayIndexFirst = sequenceArray[indexSymbolLeft]->next->index;
		}
		else if (indexSymbolLeft == tracker->pairRecord->arrayIndexLast)
		{
			tracker->pairRecord->arrayIndexLast = sequenceArray[indexSymbolLeft]->previous->index;
		}
	}	
}

void AlgorithmP::removeFromPriorityQueueList(
	long index,
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (tracker->pairRecord->nextPair && tracker->pairRecord->previousPair)
	{
		tracker->pairRecord->nextPair->previousPair = 
			tracker->pairRecord->previousPair;
		tracker->pairRecord->previousPair->nextPair =
			tracker->pairRecord->nextPair;
	}
	else if (tracker->pairRecord->nextPair)
	{
		priorityQueue[index] = tracker->pairRecord->nextPair;
		tracker->pairRecord->nextPair->previousPair = nullptr;		
	}
	else if (tracker->pairRecord->previousPair)
	{
		tracker->pairRecord->previousPair->nextPair = nullptr;
	}
	else
		priorityQueue[index] = nullptr;

	tracker->pairRecord->previousPair = nullptr;
	tracker->pairRecord->nextPair = nullptr;
}

void AlgorithmP::addToPriorityQueueList(
	long index,
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (index > priorityQueue.size() - 1)
		index = priorityQueue.size() - 1;

	if (priorityQueue[index])
	{
		tracker->pairRecord->nextPair =
			priorityQueue[index];
		priorityQueue[index]->previousPair =
			tracker->pairRecord;		
	}
	priorityQueue[index] =
		tracker->pairRecord;
}

void AlgorithmP::moveDownInPriorityQueue(
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (tracker->pairRecord->count == 2)
	{
		removeFromPriorityQueueList(0, tracker, priorityQueue);
	}
	else if (tracker->pairRecord->count - 1 <= priorityQueue.size())
	{
		removeFromPriorityQueueList(
			tracker->pairRecord->count - 2,
			tracker, 
			priorityQueue);
		addToPriorityQueueList(
			tracker->pairRecord->count - 3, 
			tracker, 
			priorityQueue);
	}
}

void AlgorithmP::decrementCount(
	long & indexSymbolLeft,
	long & indexSymbolRight, 
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	PairTracker *& tracker,
	Conditions& c)
{
	
	removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	moveDownInPriorityQueue(tracker, priorityQueue);

	updatePairRecord(
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		tracker);
}

void AlgorithmP::decrementCountLeft(
	long & indexSymbolPrevious, 
	long & indexSymbolLeft, 
	long & indexSymbolRight,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray, 
	vector<PairRecord*>& priorityQueue,
	Conditions& c)
{	
	if (indexSymbolPrevious >= 0)
	{
		PairTracker * tracker;
		tracker = 
			&activePairs[sequenceArray[indexSymbolPrevious]->symbol]
						[sequenceArray[indexSymbolLeft]->symbol];
		if (tracker && 
			tracker->pairRecord &&
			(sequenceArray[indexSymbolPrevious]->next ||
			sequenceArray[indexSymbolPrevious]->previous))
		{
			decrementCount(
				indexSymbolPrevious,
				indexSymbolLeft,
				activePairs,
				sequenceArray,
				priorityQueue,
				tracker,
				c);
		}
	}
}

void AlgorithmP::decrementCountRight(
	long & indexSymbolRight,
	long & indexSymbolNext,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray, 
	vector<PairRecord*>& priorityQueue,
	Conditions& c)
{

}

void AlgorithmP::incrementCountLeft(
	long & indexSymbolPrevious,
	long & indexSymbolLeft,
	long & indexSymbolRight,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	unsigned int symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;

	if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord == NULL)
		//This is exactly the first time we see this
	{
		activePairs[symbolPrevious][Symbols].seenOnce = true;
		activePairs[symbolPrevious][Symbols].indexFirst = indexSymbolLeft;
	}

	else if (activePairs[symbolPrevious][Symbols].seenOnce)
		//This is if we se it the second time
	{
		activePairs[symbolPrevious][Symbols].seenOnce = false;
		activePairs[symbolPrevious][Symbols].pairRecord = new PairRecord(activePairs[symbolPrevious][Symbols].indexFirst,indexSymbolLeft);
		activePairs[symbolPrevious][Symbols].pairRecord->count = 2;
	}

	else if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord)
		//This is if we see it after the second time
	{
		activePairs[symbolPrevious][Symbols].pairRecord->count++;
	}
}

void AlgorithmP::incrementCountRight(
	long & indexSymbolRight,
	long & indexSymbolNext,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
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
	unsigned int & Symbols,
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
	unsigned int & Symbols,
	Conditions& c)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];

	do
	{
		sequenceIndex = nextSymbol->index;
		nextSymbol = nextSymbol->next;

		establishContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceIndex,
			sequenceArray);		
		
	} while (nextSymbol);
}