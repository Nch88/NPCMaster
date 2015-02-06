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
		priorityQueue[tracker->pairRecord->count - 2] = tracker->pairRecord->nextPair;
		tracker->pairRecord->nextPair->previousPair = nullptr;		
	}
	else if (tracker->pairRecord->previousPair)
	{
		tracker->pairRecord->previousPair->nextPair = nullptr;
	}

	tracker->pairRecord->previousPair = nullptr;
	tracker->pairRecord->nextPair = nullptr;
}

void AlgorithmP::addToPriorityQueueList(
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (priorityQueue[tracker->pairRecord->count - 2])
	{
		tracker->pairRecord->nextPair =
			priorityQueue[tracker->pairRecord->count - 2];
		priorityQueue[tracker->pairRecord->count - 2]->previousPair =
			tracker->pairRecord;		
	}
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;
}

void AlgorithmP::moveDownInPriorityQueue(
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (tracker->pairRecord->count == 2)
	{
		removeFromPriorityQueueList(tracker, priorityQueue);
	}
	else if (tracker->pairRecord->count - 1 <= priorityQueue.size())
	{
		removeFromPriorityQueueList(tracker, priorityQueue);
		addToPriorityQueueList(tracker, priorityQueue);
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