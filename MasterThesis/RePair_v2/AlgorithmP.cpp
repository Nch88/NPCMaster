#include "stdafx.h"
#include "AlgorithmP.h"

AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

SymbolRecord* AlgorithmP::findNextEmpty(vector<SymbolRecord*> & sequenceArray,  SymbolRecord* current)
{
	SymbolRecord* result = current;
	int index = current->index;
	do
	{
		if ((index + 2) > sequenceArray.size())
			return nullptr;
		result = sequenceArray[++index];
	} while (result->symbol != 0);
	return result;
}

void AlgorithmP::compact(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	Conditions &c)
{
	SymbolRecord *empty = nullptr;// , *tmpnxt = nullptr, *tmppre = nullptr;
	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i]->symbol == 0 && !empty)
			empty = sequenceArray[i];
		else if (sequenceArray[i]->symbol != 0 && empty && i > empty->index)
		//If we are at a non-empty record and an empty record exists before it
		{
			//Transfer data to next
			empty->symbol = sequenceArray[i]->symbol;
			empty->previous = sequenceArray[i]->previous;
			empty->next = sequenceArray[i]->next;

			//Update our previous and next if they exist
			if (sequenceArray[i]->next)
				sequenceArray[i]->next->previous = empty;
			if (sequenceArray[i]->previous)
				sequenceArray[i]->previous->next = empty;

			//Update pair-record if needed
			if ((sequenceArray[i]->next || sequenceArray[i]->previous) && i < (sequenceArray.size() - 1))
			{
				//Figure out the pair
				unsigned long s1 = sequenceArray[i]->symbol;
				unsigned long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;

				if (activePairs[s1].empty())
				{
					activePairs[s1].set_empty_key(-1);
					activePairs[s1].set_deleted_key(-2);
				}
				if (activePairs[s1][s2].pairRecord->arrayIndexFirst == i)
					activePairs[s1][s2].pairRecord->arrayIndexFirst = empty->index;

				if (activePairs[s1][s2].pairRecord->arrayIndexLast == i)
					activePairs[s1][s2].pairRecord->arrayIndexLast = empty->index;
			}

			//Clear this record
			sequenceArray[i]->next = nullptr;
			sequenceArray[i]->previous = nullptr;
			sequenceArray[i]->symbol = 0;

			//Update empty
			empty = findNextEmpty(sequenceArray, empty);
		}
	}

	//Resize the sequence array
	int index = empty->index;
	for (int i = empty->index; i < sequenceArray.size(); i++)
	{
		delete sequenceArray[i];

		if (c.test)
			c.ts->addMemory("repairSeq", -c.ts->symbolRecordWords);
	}
	sequenceArray.resize(index);
}

void AlgorithmP::removeSymbolThreadingPointers(
	long & indexSymbolLeft,
	vector<SymbolRecord*> & sequenceArray)
{
	//Middle of sequence, connect the remaining parts
	if (sequenceArray[indexSymbolLeft]->previous &&
		sequenceArray[indexSymbolLeft]->next)
	{
		sequenceArray[indexSymbolLeft]->previous->next =
			sequenceArray[indexSymbolLeft]->next;
		sequenceArray[indexSymbolLeft]->next->previous =
			sequenceArray[indexSymbolLeft]->previous;
	}
	//Last in sequence
	else if (sequenceArray[indexSymbolLeft]->previous)
	{
		sequenceArray[indexSymbolLeft]->previous->next = nullptr;
	}
	//First in sequence
	else if (sequenceArray[indexSymbolLeft]->next)
	{
		sequenceArray[indexSymbolLeft]->next->previous = nullptr;
	}
	sequenceArray[indexSymbolLeft]->previous = nullptr;
	sequenceArray[indexSymbolLeft]->next = nullptr;
}

void AlgorithmP::deletePairRecord(
	unsigned long & symbolLeft,
	unsigned long & symbolRight,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs)
{
	delete activePairs[symbolLeft][symbolRight].pairRecord;
	activePairs[symbolLeft][symbolRight].pairRecord = nullptr;
	activePairs[symbolLeft][symbolRight].seenOnce = false;
	activePairs[symbolLeft][symbolRight].indexFirst = -1;
}

void AlgorithmP::updatePairRecord(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	PairTracker *& tracker,
	Conditions &c)
{
	tracker->pairRecord->count--;
	
	unsigned long symbolLeft = sequenceArray[indexSymbolLeft]->symbol;
	unsigned long symbolRight = sequenceArray[indexSymbolRight]->symbol;

	//Delete pair record if the pair is no longer active
	if (tracker->pairRecord->count < 2) 
	{
		deletePairRecord(
			symbolLeft,
			symbolRight,
			activePairs);
		tracker->pairRecord = nullptr;
		tracker = nullptr;

		if (c.test)
			c.ts->addMemory("repairPair", c.ts->pairRecordSubtractWords);
	}
	//If we are removing the first or last symbol in the sequence update the pair record to reflect this
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
	//Middle of list, connect the remaining parts
	if (tracker->pairRecord->nextPair && tracker->pairRecord->previousPair)
	{
		tracker->pairRecord->nextPair->previousPair = 
			tracker->pairRecord->previousPair;
		tracker->pairRecord->previousPair->nextPair =
			tracker->pairRecord->nextPair;
	}
	//First in list
	else if (tracker->pairRecord->nextPair)
	{
		priorityQueue[index] = tracker->pairRecord->nextPair;
		tracker->pairRecord->nextPair->previousPair = nullptr;		
	}
	//Last in list
	else if (tracker->pairRecord->previousPair)
	{
		tracker->pairRecord->previousPair->nextPair = nullptr;
	}
	//Only in list
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
	//Put pairs with large frequencies in the last PQ entry
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
	//Pairs is no longer active as count will be decremented to 1
	if (tracker->pairRecord->count == 2)
	{
		removeFromPriorityQueueList(0, tracker, priorityQueue);
	}
	//Unless we still belong in the entry for very large frequency pairs move down one entry
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
	//Move up unless we are already in entry for large frequencies
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
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
		tracker,
		c);

	removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);	
}

void AlgorithmP::decrementCountLeft(
	long & indexSymbolPrevious, 
	long & indexSymbolLeft, 
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray, 
	vector<PairRecord*>& priorityQueue,
	Conditions& c)
{	
	//Check that a pair exists
	if (indexSymbolPrevious >= 0)
	{
		PairTracker * tracker = nullptr;
		tracker = 
			&activePairs[sequenceArray[indexSymbolPrevious]->symbol]
						[sequenceArray[indexSymbolLeft]->symbol];

		//Check that the pair is active and 
		//for the sake of identical symbols that this left is the left part of a pair we have counted
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
		//Reset the seenOnce bool such that temporary pairs which are destroyed in the subsequent 
		//iteration are never considered active by mistake
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray, 
	vector<PairRecord*>& priorityQueue,
	Conditions& c)
{
	//Check that a pair exists
	if (indexSymbolNext >= 0)
	{
		PairTracker * tracker = nullptr;
		tracker =
			&activePairs[sequenceArray[indexSymbolRight]->symbol]
			[sequenceArray[indexSymbolNext]->symbol];

		//Check that the pair is active and 
		//for the sake of identical symbols that this left is the left part of a pair we have counted
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

	//Thread both ends of a sequence of empty symbols unless they are the same
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	unsigned long & Symbols,
	Conditions& c)
{
	SymbolRecord * leftSymbolRecord = nullptr;
	SymbolRecord * rightSymbolRecord = nullptr;
	SymbolRecord * nextSymbolRecord = nullptr;
	PairRecord * oldPair = nullptr;

	leftSymbolRecord = sequenceArray[indexSymbolLeft];
	rightSymbolRecord = sequenceArray[indexSymbolRight];

	oldPair = activePairs[leftSymbolRecord->symbol][rightSymbolRecord->symbol].pairRecord;
	
	oldPair->count--;

	//The pair is no longer active and can be deleted
	if (oldPair->count == 0)
	{
		deletePairRecord(
			leftSymbolRecord->symbol,
			rightSymbolRecord->symbol,
			activePairs);

		if (c.test)
			c.ts->addMemory("repairPair", c.ts->pairRecordSubtractWords);
	}

	if (indexSymbolNext >= 0)
		nextSymbolRecord = sequenceArray[indexSymbolNext];
	else
		nextSymbolRecord = nullptr;

	leftSymbolRecord->symbol = Symbols;
	rightSymbolRecord->symbol = 0;

	//The right symbol of the old pair is now empty and must be threaded
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
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	bool &skip,
	Conditions& c)
{
	if (indexSymbolPrevious > -1)
	{
		long symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;

		if (activePairs[symbolPrevious].empty())
		{
			activePairs[symbolPrevious].set_empty_key(-1);
			activePairs[symbolPrevious].set_deleted_key(-2);
		}

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

				if (c.test)
				{
					c.ts->addMemory("repairTracker", c.ts->pairTrackerWords); //Dense hash map uses extra memory
				}
			}

			else if (activePairs[symbolPrevious][Symbols].seenOnce)
				//This is if we se it the second time
			{
				activePairs[symbolPrevious][Symbols].seenOnce = false;
				activePairs[symbolPrevious][Symbols].pairRecord = new PairRecord(activePairs[symbolPrevious][Symbols].indexFirst, indexSymbolPrevious);
				activePairs[symbolPrevious][Symbols].pairRecord->count = 2;

				if (c.test)
				{
					c.ts->addMemory("repairPair", c.ts->pairRecordWords); //Dense hash map uses double memory
					if (c.ts->firstBlock)
						c.ts->s_maxPairs++;
				}
					

				//Add to priority queue
				PairTracker* tracker = &activePairs[symbolPrevious][Symbols];
				addToPriorityQueueList(0, tracker, priorityQueue);

			//Update threading pointers
			sequenceArray[activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexFirst]->next = sequenceArray[indexSymbolPrevious];
			sequenceArray[indexSymbolPrevious]->previous = sequenceArray[activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexFirst];
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	Conditions& c)
{
	
	if (indexSymbolNext > -1)
	//Only do this if there is a next symbol
	{
		long symbolNext = sequenceArray[indexSymbolNext]->symbol;

		if (activePairs[Symbols].empty())
		{
			activePairs[Symbols].set_empty_key(-1);
			activePairs[Symbols].set_deleted_key(-2);
		}
		if (!activePairs[Symbols][symbolNext].seenOnce && activePairs[Symbols][symbolNext].pairRecord == NULL)
			//This is exactly the first time we see this
		{
			activePairs[Symbols][symbolNext].seenOnce = true;
			activePairs[Symbols][symbolNext].indexFirst = indexSymbolLeft;

			if (c.test)
			{
				c.ts->addMemory("repairTracker", c.ts->pairTrackerWords); //Dense hash map uses extra memory
			}
		}

		else if (activePairs[Symbols][symbolNext].seenOnce)
			//This is if we se it the second time
		{
			activePairs[Symbols][symbolNext].seenOnce = false;
			activePairs[Symbols][symbolNext].pairRecord = new PairRecord(activePairs[Symbols][symbolNext].indexFirst, indexSymbolLeft);
			activePairs[Symbols][symbolNext].pairRecord->count = 2;

			if (c.test)
			{				
				c.ts->addMemory("repairPair", c.ts->pairRecordWords); //Dense hash map uses double memory
				c.ts->s_maxPairs++;
			}
				

			//Add to priority queue
			PairTracker* tracker = &activePairs[Symbols][symbolNext];
			addToPriorityQueueList(0, tracker, priorityQueue);

			//Update threading pointers
			sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst]->next = sequenceArray[indexSymbolLeft];
			sequenceArray[indexSymbolLeft]->previous = sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst];
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
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
		else
			indexSymbolNext = -1;
	}
	else
		indexSymbolNext = -1;
}

void AlgorithmP::replaceAllPairs(
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	Conditions& c)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
	bool skip = false;

	//Create the new dictionary pair and set Symbols to its address
	unsigned long * newPair = new unsigned long[2];
	newPair[0] = sequenceArray[sequenceIndex]->symbol;
	if (sequenceArray[sequenceIndex + 1]->symbol != 0)
		newPair[1] = sequenceArray[sequenceIndex + 1]->symbol;
	else
		newPair[1] = sequenceArray[sequenceIndex + 1]->next->symbol;
	Symbols = (unsigned long)newPair;

	if (Symbols < initialSymbolValue)
	{
		while (true)
		{
			cout << " (T_T) ";
		}
	}

	if (c.test)
		c.ts->addMemory("repairPhrase", 2);

	do
	{
		indexSymbolLeft = -1;
		indexSymbolRight = -1;
		indexSymbolPrevious = -1;
		indexSymbolNext = -1;

		sequenceIndex = nextSymbol->index;
		//Store the pointer to the next symbol now, as the current symbol is changed as we go
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
			activePairs,
			priorityQueue,
			Symbols,
			skip,
			c);
		
	} while (nextSymbol);
}

void AlgorithmP::manageOneEntryOnList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	CompactionData &cData,
	Conditions& c)
{
	PairRecord * tmpPairRecord = nullptr;
	long sequenceIndex = -1;

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
	
	//Find the count of the pair to be replaced and update counter for compaction
	if (c.compact)
	{
		long idx = sequenceIndex;
		long s1 = sequenceArray[idx]->symbol;
		long s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
		cData.replaceCount += activePairs[s1][s2].pairRecord->count;
	}

	replaceAllPairs(
		sequenceIndex,
		sequenceArray,
		activePairs,
		priorityQueue,
		Symbols,
		c);

	//Compaction
	if (c.compact)
	{
		if (cData.replaceCount > cData.compactTotal)
		{
			compact(sequenceArray, activePairs, priorityQueue, c);
			cData.updateCompactTotal();
		}
	}
}

void AlgorithmP::manageOneList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	CompactionData &cData,
	Conditions& c)
{
	while (priorityQueue[i])
	{
		manageOneEntryOnList(
			i,
			sequenceArray,
			activePairs,
			priorityQueue,
			Symbols,
			cData,
			c);
	}
}

void AlgorithmP::manageLowerPriorityLists(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	CompactionData &cData,
	Conditions& c)
{
	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= cutoffValue - 2; i--)
	{		
		manageOneList(
			i,
			sequenceArray,
			activePairs,
			priorityQueue,
			Symbols,
			cData,
			c);
	}
	//DEBUG
	int count = 0;
	for (int i = 0; i < cutoffValue - 2; i++)
	{
		PairRecord *p = priorityQueue[i];
		while (p)
		{
			count++;
			p = p->nextPair;
		}
		cout << "# of pairs with freq " << i + 2 << " is " << count << endl;
		count = 0;
	}
}

//Manages active pairs with frequencies greater than sqrt(n)
void AlgorithmP::manageHighPriorityList(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long, dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	CompactionData &cData,
	Conditions& c)
{
	PairRecord * tmpPairRecord = nullptr;
	PairRecord * tmpPairRecordSelected = nullptr;
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

		//Find the count of the pair to be replaced and update counter for compaction
		if (c.compact)
		{
			long i = sequenceIndex;
			long s1 = sequenceArray[i]->symbol;
			long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;
			cData.replaceCount += activePairs[s1][s2].pairRecord->count;
		}

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			activePairs,
			priorityQueue,
			Symbols,
			c);

		//Compaction
		if (c.compact)
		{
			if (cData.replaceCount > cData.compactTotal)
			{
				compact(sequenceArray, activePairs, priorityQueue, c);
				cData.updateCompactTotal();
			}
		}
	}
}

void AlgorithmP::run(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned long & Symbols,
	Conditions& c)
{
	CompactionData cData(sequenceArray.size());

	if (c.test)
	{
		c.ts->addMemory("repairSeq", c.ts->m_init_sequenceArray_current);
		c.ts->addMemory("repairPair", c.ts->m_init_pairRecord_current);
		c.ts->addMemory("repairPrio", c.ts->m_init_priorityQueue_max);
	}

	manageHighPriorityList(
		sequenceArray,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);

	manageLowerPriorityLists(
		sequenceArray,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);
}