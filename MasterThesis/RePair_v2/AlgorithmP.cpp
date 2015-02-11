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

void AlgorithmP::deletePairRecord(
	unsigned int & symbolLeft,
	unsigned int & symbolRight,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs)
{
	delete activePairs[symbolLeft][symbolRight].pairRecord;
	activePairs[symbolLeft][symbolRight].pairRecord = nullptr;
	activePairs[symbolLeft][symbolRight].seenOnce = false;
	activePairs[symbolLeft][symbolRight].indexFirst = -1;
}

void AlgorithmP::updatePairRecord(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	PairTracker *& tracker)
{
	tracker->pairRecord->count--;

	unsigned int symbolLeft = sequenceArray[indexSymbolLeft]->symbol;
	unsigned int symbolRight = sequenceArray[indexSymbolRight]->symbol;

	if (tracker->pairRecord->count < 2) //Delete pair record
	{
		deletePairRecord(
			symbolLeft,
			symbolRight,
			activePairs);
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

void AlgorithmP::moveUpInPriorityQueue(
	PairTracker *& tracker,
	vector<PairRecord*>& priorityQueue)
{
	if (tracker->pairRecord->count - 1 < priorityQueue.size())
	{
		removeFromPriorityQueueList(
			tracker->pairRecord->count - 2,
			tracker,
			priorityQueue);
		addToPriorityQueueList(
			tracker->pairRecord->count - 1,
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
	moveDownInPriorityQueue(tracker, priorityQueue);

	updatePairRecord(
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		tracker);

	removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);	
}

void AlgorithmP::decrementCountLeft(
	long & indexSymbolPrevious, 
	long & indexSymbolLeft, 
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
		else
		{
			tracker->seenOnce = false;
			tracker->indexFirst = -1;
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
	if (indexSymbolNext >= 0)
	{
		PairTracker * tracker;
		tracker =
			&activePairs[sequenceArray[indexSymbolRight]->symbol]
			[sequenceArray[indexSymbolNext]->symbol];

		if (tracker &&
			tracker->pairRecord &&
			(sequenceArray[indexSymbolRight]->next ||
			sequenceArray[indexSymbolRight]->previous))
		{
			decrementCount(
				indexSymbolRight,
				indexSymbolNext,
				activePairs,
				sequenceArray,
				priorityQueue,
				tracker,
				c);
		}
	}
}

void AlgorithmP::threadEmptySymbols(
	SymbolRecord *& leftSymbolRecord,
	SymbolRecord *& rightSymbolRecord,
	SymbolRecord *& nextSymbolRecord,
	vector<SymbolRecord*> & sequenceArray)
{
	SymbolRecord * firstEmptyRecord =
		sequenceArray[leftSymbolRecord->index + 1];

	firstEmptyRecord->previous = leftSymbolRecord;
	firstEmptyRecord->next = nextSymbolRecord;

	if (nextSymbolRecord &&
		nextSymbolRecord->index - 1 != firstEmptyRecord->index)
	{
		SymbolRecord * lastEmptyRecord =
			sequenceArray[nextSymbolRecord->index - 1];
		lastEmptyRecord->previous = leftSymbolRecord;
		lastEmptyRecord->next = nextSymbolRecord;
	}
}

void AlgorithmP::replacePair(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolNext,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unsigned int & Symbols,
	Conditions& c)
{
	SymbolRecord * leftSymbolRecord;
	SymbolRecord * rightSymbolRecord;
	SymbolRecord * nextSymbolRecord;
	PairRecord * oldPair;

	leftSymbolRecord = sequenceArray[indexSymbolLeft];
	rightSymbolRecord = sequenceArray[indexSymbolRight];

	oldPair = activePairs[leftSymbolRecord->symbol][rightSymbolRecord->symbol].pairRecord;
	
	oldPair->count--;

	if (oldPair->count == 0)
	{
		deletePairRecord(
			leftSymbolRecord->symbol,
			rightSymbolRecord->symbol,
			activePairs);
	}

	if (indexSymbolNext >= 0)
		nextSymbolRecord = sequenceArray[indexSymbolNext];
	else
		nextSymbolRecord = nullptr;

	Pair pairToReplace(
		leftSymbolRecord->symbol, 
		rightSymbolRecord->symbol);
	
	dictionary[Symbols] = pairToReplace;
	leftSymbolRecord->symbol = Symbols;
	rightSymbolRecord->symbol = 0;

	threadEmptySymbols(
		leftSymbolRecord,
		rightSymbolRecord,
		nextSymbolRecord,
		sequenceArray);

	leftSymbolRecord->next = nullptr;
	leftSymbolRecord->previous = nullptr;
}

void AlgorithmP::incrementCountLeft(
	long & indexSymbolPrevious,
	long & indexSymbolLeft,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	bool &skip,
	Conditions& c)
{
	if (indexSymbolPrevious > -1)
	{
		unsigned int symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;

		//Check if we need to skip
		if (symbolPrevious != Symbols)
			skip = false;

		if (!skip)
			//Don't do this for the first pair, or if we need to skip a pair
		{
			if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord == NULL)
				//This is exactly the first time we see this
			{
				activePairs[symbolPrevious][Symbols].seenOnce = true;
				activePairs[symbolPrevious][Symbols].indexFirst = indexSymbolPrevious;
			}

			else if (activePairs[symbolPrevious][Symbols].seenOnce)
				//This is if we se it the second time
			{
				activePairs[symbolPrevious][Symbols].seenOnce = false;
				activePairs[symbolPrevious][Symbols].pairRecord = new PairRecord(activePairs[symbolPrevious][Symbols].indexFirst, indexSymbolPrevious);
				activePairs[symbolPrevious][Symbols].pairRecord->count = 2;

				//Add to priority queue
				PairTracker* tracker = &activePairs[symbolPrevious][Symbols];
				addToPriorityQueueList(0, tracker, priorityQueue);

				//Update threading pointers
				sequenceArray[activePairs[symbolPrevious][Symbols].indexFirst]->next = sequenceArray[indexSymbolPrevious];
				sequenceArray[indexSymbolPrevious]->previous = sequenceArray[activePairs[symbolPrevious][Symbols].indexFirst];
			}

			else if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord)
				//This is if we see it after the second time
			{
				//Raise priority
				PairTracker* tracker = &activePairs[symbolPrevious][Symbols];
				moveUpInPriorityQueue(tracker, priorityQueue);

				//Update count
				activePairs[symbolPrevious][Symbols].pairRecord->count++;

				//Update threading pointers
				sequenceArray[activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexLast]->next = sequenceArray[indexSymbolPrevious];
				sequenceArray[indexSymbolPrevious]->previous = sequenceArray[activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexLast];

				//Update arrayIndexLast
				activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexLast = indexSymbolPrevious;
			}
		}

		//Update skip flag
		if (symbolPrevious == Symbols)
			skip = !skip;
	}
}

void AlgorithmP::incrementCountRight(
	long & indexSymbolLeft,
	long & indexSymbolNext,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	
	if (indexSymbolNext > -1)
	//Only do this if there is a next symbol
	{
		unsigned int symbolNext = sequenceArray[indexSymbolNext]->symbol;

		if (!activePairs[Symbols][symbolNext].seenOnce && activePairs[Symbols][symbolNext].pairRecord == NULL)
			//This is exactly the first time we see this
		{
			activePairs[Symbols][symbolNext].seenOnce = true;
			activePairs[Symbols][symbolNext].indexFirst = indexSymbolLeft;
		}

		else if (activePairs[Symbols][symbolNext].seenOnce)
			//This is if we se it the second time
		{
			activePairs[Symbols][symbolNext].seenOnce = false;
			activePairs[Symbols][symbolNext].pairRecord = new PairRecord(activePairs[Symbols][symbolNext].indexFirst, indexSymbolLeft);
			activePairs[Symbols][symbolNext].pairRecord->count = 2;

			//Add to priority queue
			PairTracker* tracker = &activePairs[Symbols][symbolNext];
			addToPriorityQueueList(0, tracker, priorityQueue);

			//Update threading pointers
			sequenceArray[activePairs[Symbols][symbolNext].indexFirst]->next = sequenceArray[indexSymbolLeft];
			sequenceArray[indexSymbolLeft]->previous = sequenceArray[activePairs[Symbols][symbolNext].indexFirst];
		}

		else if (!activePairs[Symbols][symbolNext].seenOnce && activePairs[Symbols][symbolNext].pairRecord)
			//This is if we see it after the second time
		{
			//Raise priority
			PairTracker* tracker = &activePairs[Symbols][symbolNext];
			moveUpInPriorityQueue(tracker, priorityQueue);

			//Update count
			activePairs[Symbols][symbolNext].pairRecord->count++;

			//Update threading pointers
			sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexLast]->next = sequenceArray[indexSymbolLeft];
			sequenceArray[indexSymbolLeft]->previous = sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexLast];
			
			//Update arrayIndexLast
			activePairs[Symbols][symbolNext].pairRecord->arrayIndexLast = indexSymbolLeft;
		}
	}
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
	bool& skip,
	Conditions& c)
{
	//Decrement count of xa
	decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);

	//Decrement count of by
	decrementCountRight(
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);

	//Replace xaby with xA_y
	replacePair(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		dictionary,
		Symbols,
		c);

	//Increment count of xA
	incrementCountLeft(
		indexSymbolPrevious, 
		indexSymbolLeft, 
		activePairs, 
		sequenceArray, 
		priorityQueue, 
		Symbols, 
		skip, 
		c);

	//Increment count of Ay
	incrementCountRight(
		indexSymbolLeft, 
		indexSymbolNext, 
		activePairs, 
		sequenceArray, 
		priorityQueue, 
		Symbols, 
		c);
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
	else
		indexSymbolPrevious = -1;

	//Next
	if (indexSymbolRight < sequenceArray.size() - 1)
	{
		if (sequenceArray[indexSymbolRight + 1]->symbol != 0)
			indexSymbolNext = sequenceArray[indexSymbolRight + 1]->index;
		else if (sequenceArray[indexSymbolRight + 1]->next)
			indexSymbolNext = sequenceArray[indexSymbolRight + 1]->next->index;
	}
	else
		indexSymbolNext = -1;
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
	bool skip = false;

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

		replaceInstanceOfPair(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			skip,
			c);
		
	} while (nextSymbol);
}

void AlgorithmP::newSymbol(unsigned int & Symbols)
{
	if (Symbols == UINT_MAX - 1)
	{
		cout << "Ran out of symbols, aborting compression" << endl;
		exit;
	}
	Symbols++;
}

void AlgorithmP::manageOneEntryOnList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	PairRecord * tmpPairRecord;
	long sequenceIndex;

	tmpPairRecord = priorityQueue[i];
	sequenceIndex = tmpPairRecord->arrayIndexFirst;

	//Remove current pair from priority queue
	if (tmpPairRecord->nextPair)
	{
		priorityQueue[i] = tmpPairRecord->nextPair;
		priorityQueue[i]->previousPair = nullptr;
	}
	else
		priorityQueue[i] = nullptr;
	tmpPairRecord->previousPair = nullptr;
	tmpPairRecord->nextPair = nullptr;
	
	replaceAllPairs(
		sequenceIndex,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);

	//Pick new symbol
	newSymbol(Symbols);
}

void AlgorithmP::manageOneList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	while (priorityQueue[i])
	{
		manageOneEntryOnList(
			i,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			c);
	}
}

void AlgorithmP::manageLowerPriorityLists(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{		
		manageOneList(
			i,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			c);
	}
}

void AlgorithmP::manageHighPriorityList(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	PairRecord * tmpPairRecord;
	PairRecord * tmpPairRecordSelected;
	long sequenceIndex = 0;
	long last = priorityQueue.size() - 1;

	while (priorityQueue[last])
	{
		tmpPairRecordSelected = priorityQueue[last];
		tmpPairRecord = priorityQueue[last];

		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		}
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (tmpPairRecordSelected->previousPair && tmpPairRecordSelected->nextPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		else if (tmpPairRecordSelected->previousPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = nullptr;
		}
		else if (tmpPairRecordSelected->nextPair)
		{
			priorityQueue[last] = tmpPairRecordSelected->nextPair;
			priorityQueue[last]->previousPair = nullptr;
		}
		else
			priorityQueue[last] = nullptr;
		tmpPairRecordSelected->previousPair = nullptr;
		tmpPairRecordSelected->nextPair = nullptr;

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			c);

		//Pick new symbol
		newSymbol(Symbols);
	}
}

void AlgorithmP::run(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	Conditions& c)
{
	manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);

	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);
}