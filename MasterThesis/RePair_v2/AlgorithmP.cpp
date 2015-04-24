#include "stdafx.h"
#include "AlgorithmP.h"


AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

long AlgorithmP::findGeneration(
	dense_hash_map<long, Pair>& dictionary, 
	long left, 
	long right
	)
{
	if (left < initialSymbolValue)
		if (right < initialSymbolValue)
			//Both left & right are terminals
			return 1;
		else
			//Left is a terminal, right is not
			return dictionary[right].generation + 1;
	else if (right < initialSymbolValue)
		//Right is a terminal, left is not
		return dictionary[left].generation + 1;
	else
	{
		//Neither are terminals, so we need to compare them
		long genLeft = dictionary[left].generation;
		long genRight = dictionary[right].generation;
		return (genLeft > genRight ? genLeft : genRight) + 1;
	}
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
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue)
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
				long s1 = sequenceArray[i]->symbol;
				long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;

				if (activePairs[s1].empty())
				{
					activePairs[s1].set_empty_key(-1);
					activePairs[s1].set_deleted_key(-2);
				}
				if (activePairs[s1][s2].pairRecord->arrayIndexFirst == i)
					activePairs[s1][s2].pairRecord->arrayIndexFirst = empty->index;
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
	}
	sequenceArray.resize(index);
}

bool AlgorithmP::sameContext(long & indexSymbolLeft, vector<SymbolRecord*> & sequenceArray)
{
	bool same = true;

	long indexHerePrevious;
	long indexHereLeft;
	long indexHereRight;
	long indexHereNext;

	long indexTherePrevious;
	long indexThereLeft;
	long indexThereRight;
	long indexThereNext;
	
	establishContext(indexHereLeft, indexHereRight, indexHerePrevious, indexHereNext, indexSymbolLeft, sequenceArray);
	establishContext(indexThereLeft, indexThereRight, indexTherePrevious, indexThereNext, sequenceArray[indexSymbolLeft]->next->index, sequenceArray);

	if (indexThereNext == -1)
		return false;

	same = same && sequenceArray[indexHereLeft]->symbol == sequenceArray[indexThereLeft]->symbol && sequenceArray[indexHereLeft]->symbol != 0;

	same = same && sequenceArray[indexHereRight]->symbol == sequenceArray[indexThereRight]->symbol && sequenceArray[indexHereRight]->symbol != 0;

	same = same && sequenceArray[indexHereNext]->symbol == sequenceArray[indexThereNext]->symbol && sequenceArray[indexHereNext]->symbol != 0;

	return same;
}

void AlgorithmP::removeSymbolThreadingPointers(
	long & indexSymbolLeft,
	vector<SymbolRecord*> & sequenceArray,
	bool left)
{
	
	//Middle of sequence, connect the remaining parts
	if (sequenceArray[indexSymbolLeft]->previous &&
		sequenceArray[indexSymbolLeft]->next)
	{
		sequenceArray[indexSymbolLeft]->previous->next =
			sequenceArray[indexSymbolLeft]->next;

		//DEBUG
		if (sequenceArray[indexSymbolLeft]->previous->index == 136963 &&
			sequenceArray[indexSymbolLeft]->previous->next->index == 142806)
		{
			int x = 0;
		}
		
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
		//We cannot remove pointers from last left pair in a sequence if it has the same context, as it will not seem active later
		if (!(left &&
			sequenceArray[indexSymbolLeft]->next &&
			!sequenceArray[indexSymbolLeft]->next->next &&
			sameContext(indexSymbolLeft, sequenceArray)))
		{
			sequenceArray[indexSymbolLeft]->next->previous = nullptr;
		}
	}
	
	
	sequenceArray[indexSymbolLeft]->next = nullptr;
	sequenceArray[indexSymbolLeft]->previous = nullptr;
}

void AlgorithmP::deletePairRecord(
	long & symbolLeft,
	long & symbolRight,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs)
{
	delete activePairs[symbolLeft][symbolRight].pairRecord;
	activePairs[symbolLeft][symbolRight].pairRecord = nullptr;
	activePairs[symbolLeft][symbolRight].seenOnce = false;
}

void AlgorithmP::updatePairRecord(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	PairTracker *& tracker)
{
	tracker->pairRecord->count--;
	
	long symbolLeft = sequenceArray[indexSymbolLeft]->symbol;
	long symbolRight = sequenceArray[indexSymbolRight]->symbol;

	//Delete pair record if the pair is no longer active
	if (tracker->pairRecord->count < 2) 
	{
		deletePairRecord(
			symbolLeft,
			symbolRight,
			activePairs);
		tracker->pairRecord = nullptr;
		tracker = nullptr;
	}
	//If we are removing the first symbol in the sequence update the pair record to reflect this
	else
	{
		if (indexSymbolLeft == tracker->pairRecord->arrayIndexFirst)
		{
			tracker->pairRecord->arrayIndexFirst = sequenceArray[indexSymbolLeft]->next->index;
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
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	PairTracker *& tracker,
	bool left,
	Conditions& c)
{
	moveDownInPriorityQueue(tracker, priorityQueue);

	updatePairRecord(
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		tracker);

	removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray, left);	
}

void AlgorithmP::decrementCountLeft(
	long & indexSymbolPrevious, 
	long & indexSymbolLeft, 
	long & indexSymbolRight,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray, 
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
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
				true,
				c);
		}
	}
}

void AlgorithmP::decrementCountRight(
	long & indexSymbolRight,
	long & indexSymbolNext,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
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
				false,
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
	//DEBUG
	if (leftSymbolRecord->index == 136963 && nextSymbolRecord->index == 142806)
	{
		int x = 0;
	}

	SymbolRecord * firstEmptyRecord =
		sequenceArray[leftSymbolRecord->index + 1];

	firstEmptyRecord->previous = leftSymbolRecord;
	firstEmptyRecord->next = nextSymbolRecord;

	//DEBUG
	if (firstEmptyRecord->index == 136963 &&
		firstEmptyRecord->next->index == 142806)
	{
		int x = 0;
	}

	//Thread both ends of a sequence of empty symbols unless they are the same
	if (nextSymbolRecord &&
		nextSymbolRecord->index - 1 != firstEmptyRecord->index)
	{
		SymbolRecord * lastEmptyRecord =
			sequenceArray[nextSymbolRecord->index - 1];
		lastEmptyRecord->previous = leftSymbolRecord;
		lastEmptyRecord->next = nextSymbolRecord;
		//DEBUG
		if (lastEmptyRecord->index == 136963 &&
			lastEmptyRecord->next->index == 142806)
		{
			int x = 0;
		}
	}
}

void AlgorithmP::replacePair(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolNext,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	long & Symbols,
	Conditions& c)
{
	SymbolRecord * leftSymbolRecord = nullptr;
	SymbolRecord * rightSymbolRecord = nullptr;
	SymbolRecord * nextSymbolRecord = nullptr;
	PairRecord * oldPair = nullptr;

	leftSymbolRecord = sequenceArray[indexSymbolLeft];
	rightSymbolRecord = sequenceArray[indexSymbolRight];

	oldPair = activePairs[leftSymbolRecord->symbol][rightSymbolRecord->symbol].pairRecord;

	//DEBUG
	if (!oldPair)
	{
		int x = 0;
	}
	
	oldPair->count--;

	//The pair is no longer active and can be deleted
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

	//The dictionary generation of the pair is determined and the replacement is stored in our dictionary
	Pair pairToReplace(
		leftSymbolRecord->symbol, 
		rightSymbolRecord->symbol,
		findGeneration(dictionary, leftSymbolRecord->symbol, rightSymbolRecord->symbol));
	
	dictionary[Symbols] = pairToReplace;

	leftSymbolRecord->symbol = Symbols;
	rightSymbolRecord->symbol = 0;

	//The right symbol of the old pair is now empty and must be threaded
	threadEmptySymbols(
		leftSymbolRecord,
		rightSymbolRecord,
		nextSymbolRecord,
		sequenceArray);

	leftSymbolRecord->next = nullptr;
}

void AlgorithmP::incrementCountLeft(
	long & indexSymbolPrevious,
	long & indexSymbolLeft,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	bool &skip,
	Conditions& c)
{
	if (indexSymbolPrevious > -1)
	{
		long symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;

		//Check for when we have duplicates

		if (sequenceArray[indexSymbolPrevious]->symbol == Symbols &&
			activePairs[Symbols][Symbols].pairRecord &&
			!skip)
		{
			skip = true;

			if (activePairs[symbolPrevious].empty())
			{
				activePairs[symbolPrevious].set_empty_key(-1);
				activePairs[symbolPrevious].set_deleted_key(-2);
			}

			PairTracker* tracker = &activePairs[symbolPrevious][Symbols];
			PairRecord* record = tracker->pairRecord;

			//If this is the first occurrence, update index first
			if (record->arrayIndexFirst > indexSymbolPrevious)
			{
				record->arrayIndexFirst = indexSymbolPrevious;
				addToPriorityQueueList(record->count - 2, tracker, priorityQueue);
			}
			//For second occurrence we thread the sequence to the first occ.
			else if (!sequenceArray[indexSymbolPrevious]->previous)
			{
				sequenceArray[indexSymbolPrevious]->previous = sequenceArray[record->arrayIndexFirst];
				sequenceArray[record->arrayIndexFirst]->next = sequenceArray[indexSymbolPrevious];
				//DEBUG
				if (sequenceArray[record->arrayIndexFirst]->index == 136963 &&
					sequenceArray[record->arrayIndexFirst]->next->index == 142806)
				{
					int x = 0;
				}
			}
			//Else we update the next pointer based on the previous pointer set in first pass
			else
			{
				sequenceArray[indexSymbolPrevious]->previous->next = sequenceArray[indexSymbolPrevious];
				//DEBUG
				if (sequenceArray[indexSymbolPrevious]->previous->index == 136963 &&
					sequenceArray[indexSymbolPrevious]->previous->next->index == 142806)
				{
					int x = 0;
				}
			}
		}
		//Check for normal pairs
		else if (activePairs[symbolPrevious][Symbols].pairRecord &&
				symbolPrevious != Symbols)
		{
			skip = false;

			PairTracker* tracker = &activePairs[symbolPrevious][Symbols];
			PairRecord* record = tracker->pairRecord;

			//If this is the first occurrence, update index first
			if (record->arrayIndexFirst > indexSymbolPrevious)
			{
				record->arrayIndexFirst = indexSymbolPrevious;
				addToPriorityQueueList(record->count - 2, tracker, priorityQueue);
			}
			//For second occurrence we thread the sequence to the first occ.
			else if (!sequenceArray[indexSymbolPrevious]->previous)
			{
				sequenceArray[indexSymbolPrevious]->previous = sequenceArray[record->arrayIndexFirst];
				sequenceArray[record->arrayIndexFirst]->next = sequenceArray[indexSymbolPrevious];
				//DEBUG
				if (sequenceArray[record->arrayIndexFirst]->index == 136963 &&
					sequenceArray[record->arrayIndexFirst]->next->index == 142806)
				{
					int x = 0;
				}

			}
			//Else we update the next pointer based on the previous pointer set in first pass
			else
			{
				sequenceArray[indexSymbolPrevious]->previous->next = sequenceArray[indexSymbolPrevious];
				//DEBUG
				if (sequenceArray[indexSymbolPrevious]->previous->index == 136963 &&
					sequenceArray[indexSymbolPrevious]->previous->next->index == 142806)
				{
					int x = 0;
				}
			}
		}
		else if (activePairs[symbolPrevious][Symbols].seenOnce &&
				symbolPrevious != Symbols)
		{
			skip = false;

			activePairs[symbolPrevious][Symbols].seenOnce = false;
		}			

		else
			skip = false;
	}
}

void AlgorithmP::incrementCountRight(
	long & indexSymbolLeft,
	long & indexSymbolNext,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	Conditions& c,
	bool & skipright)
{	
	if (indexSymbolNext > -1 && !skipright)
	//Only do this if there is a next symbol
	{
		long symbolNext = sequenceArray[indexSymbolNext]->symbol;

		if (activePairs[Symbols].empty())
		{
			activePairs[Symbols].set_empty_key(-1);
			activePairs[Symbols].set_deleted_key(-2);
		}

		if (activePairs[Symbols][symbolNext].pairRecord)
			//This is if we se it the second time
		{
			//Add to priority queue
			PairTracker* tracker = &activePairs[Symbols][symbolNext];
			PairRecord* record = tracker->pairRecord;

			//Update threading pointers
			//First occurrence
			if (record->arrayIndexFirst > indexSymbolLeft)
			{
				record->arrayIndexFirst = indexSymbolLeft;
				addToPriorityQueueList(record->count - 2, tracker, priorityQueue);
			}

			//Second occurrence
			else if (!sequenceArray[indexSymbolLeft]->previous)
			{
				sequenceArray[record->arrayIndexFirst]->next = sequenceArray[indexSymbolLeft];
				//DEBUG
				if (sequenceArray[record->arrayIndexFirst]->index == 136963 &&
					sequenceArray[record->arrayIndexFirst]->next->index == 142806)
				{
					int x = 0;
				}
				sequenceArray[indexSymbolLeft]->previous = sequenceArray[record->arrayIndexFirst];
			}
			else
			{
				sequenceArray[indexSymbolLeft]->previous->next = sequenceArray[indexSymbolLeft];
				//DEBUG
				if (sequenceArray[indexSymbolLeft]->previous->index == 136963 &&
					sequenceArray[indexSymbolLeft]->previous->next->index == 142806)
				{
					int x = 0;
				}
			}
		}
		else
			activePairs[Symbols][symbolNext].seenOnce = false;
	}
}

void AlgorithmP::replaceInstanceOfPair(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolNext,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	bool& skip,
	Conditions& c)
{
	//We must not increment a temporary pair
	//aaaa -> Aaa, Aa is about to disappear so we must not count it
	bool skipright = false;
	if (sequenceArray[indexSymbolLeft]->next &&
		sequenceArray[indexSymbolLeft]->next == sequenceArray[indexSymbolNext])
		skipright = true;


	

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
		c,
		skipright);
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

void AlgorithmP::establishExtendedContext(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolPreviousPrevious,
	long & indexSymbolNext,
	long & indexSymbolNextNext,
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

	//PreviousPrevious
	if (sequenceIndex > 1 && indexSymbolPrevious > 0)
	{
		if (sequenceArray[indexSymbolPrevious - 1]->symbol != 0)
			indexSymbolPreviousPrevious = sequenceArray[indexSymbolPrevious - 1]->index;
		else
			indexSymbolPreviousPrevious = sequenceArray[indexSymbolPrevious - 1]->previous->index;
	}
	else
		indexSymbolPreviousPrevious = -1;

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

	//NextNext
	if (indexSymbolNext > -1 && indexSymbolNext < sequenceArray.size() - 1)
	{
		if (sequenceArray[indexSymbolNext + 1]->symbol != 0)
			indexSymbolNextNext = sequenceArray[indexSymbolNext + 1]->index;
		else if (sequenceArray[indexSymbolNext + 1]->next)
			indexSymbolNextNext = sequenceArray[indexSymbolNext + 1]->next->index;
		else
			indexSymbolNextNext = -1;
	}
	else
		indexSymbolNextNext = -1;
}

void AlgorithmP::checkCountLeft(
	long & indexSymbolPreviousPrevious,
	long & indexSymbolPrevious,
	long & indexSymbolLeft,
	long & indexSymbolRight,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	long & Symbols,
	bool activeLeft,
	bool &skip,
	Conditions& c)
{
	if (indexSymbolPrevious > -1)
	{
		if (activeLeft)
			//Only do this for symbols that are left parts of pairs
		{
			skip = false;

			//In this case the underlying pair will be consumed by the replacements
			if (indexSymbolPreviousPrevious > -1 &&
				sequenceArray[indexSymbolPreviousPrevious]->symbol == sequenceArray[indexSymbolLeft]->symbol &&
				sequenceArray[indexSymbolPrevious]->symbol == sequenceArray[indexSymbolRight]->symbol)
				return;

			

			long symbolPrevious = sequenceArray[indexSymbolPrevious]->symbol;

			if (activePairs[symbolPrevious].empty())
			{
				activePairs[symbolPrevious].set_empty_key(-1);
				activePairs[symbolPrevious].set_deleted_key(-2);
			}

			if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord == NULL)
				//This is exactly the first time we see this
			{
				activePairs[symbolPrevious][Symbols].seenOnce = true;
			}

			else if (activePairs[symbolPrevious][Symbols].seenOnce)
				//This is if we se it the second time
			{
				activePairs[symbolPrevious][Symbols].seenOnce = false;
				activePairs[symbolPrevious][Symbols].pairRecord = new PairRecord();
				activePairs[symbolPrevious][Symbols].pairRecord->count = 2;
				activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexFirst = indexSymbolPrevious;
			}

			else if (!activePairs[symbolPrevious][Symbols].seenOnce && activePairs[symbolPrevious][Symbols].pairRecord)
				//This is if we see it after the second time
			{
				//Update count
				activePairs[symbolPrevious][Symbols].pairRecord->count++;

				//Update threading pointers
				sequenceArray[indexSymbolPrevious]->previous = sequenceArray[activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexFirst];

				//Update arrayIndexLast
				activePairs[symbolPrevious][Symbols].pairRecord->arrayIndexFirst = indexSymbolPrevious;
			}
		}
		else if (indexSymbolPreviousPrevious >= 0 &&
				sequenceArray[indexSymbolPreviousPrevious]->symbol == sequenceArray[indexSymbolLeft]->symbol &&
				sequenceArray[indexSymbolPrevious]->symbol == sequenceArray[indexSymbolRight]->symbol &&
				!skip)
		{
			skip = true;

			if (activePairs[Symbols].empty())
			{
				activePairs[Symbols].set_empty_key(-1);
				activePairs[Symbols].set_deleted_key(-2);
			}

			if (!activePairs[Symbols][Symbols].seenOnce && activePairs[Symbols][Symbols].pairRecord == NULL)
				//This is exactly the first time we see this
			{
				activePairs[Symbols][Symbols].seenOnce = true;
			}

			else if (activePairs[Symbols][Symbols].seenOnce)
				//This is if we se it the second time
			{
				activePairs[Symbols][Symbols].seenOnce = false;
				activePairs[Symbols][Symbols].pairRecord = new PairRecord();
				activePairs[Symbols][Symbols].pairRecord->count = 2;
				activePairs[Symbols][Symbols].pairRecord->arrayIndexFirst = indexSymbolPreviousPrevious;
			}

			else if (!activePairs[Symbols][Symbols].seenOnce && activePairs[Symbols][Symbols].pairRecord)
				//This is if we see it after the second time
			{
				//Update count
				activePairs[Symbols][Symbols].pairRecord->count++;

				//Update threading pointers
				sequenceArray[indexSymbolPreviousPrevious]->previous = sequenceArray[activePairs[Symbols][Symbols].pairRecord->arrayIndexFirst];

				//DEBUG
				if (sequenceArray[activePairs[Symbols][Symbols].pairRecord->arrayIndexFirst]->symbol == 0)
				{
					int x = 0;
				}

				//Update arrayIndexLast
				activePairs[Symbols][Symbols].pairRecord->arrayIndexFirst = indexSymbolPreviousPrevious;
			}
		}
		else
			skip = false;
	}
}

void AlgorithmP::checkCountRight(
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolNext,
	long & indexSymbolNextNext,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<SymbolRecord*> & sequenceArray,
	long & Symbols,
	Conditions& c)
{
	if (indexSymbolNext > -1 && indexSymbolNextNext > -1 &&
		sequenceArray[indexSymbolLeft]->symbol == sequenceArray[indexSymbolNext]->symbol &&
		sequenceArray[indexSymbolRight]->symbol == sequenceArray[indexSymbolNextNext]->symbol)
		return;	//This makes sure we do not count pairs that are going to be removed in the next iteration
	else if (indexSymbolNext > -1)
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
		}

		else if (activePairs[Symbols][symbolNext].seenOnce)
			//This is if we se it the second time
		{
			activePairs[Symbols][symbolNext].seenOnce = false;
			activePairs[Symbols][symbolNext].pairRecord = new PairRecord();
			activePairs[Symbols][symbolNext].pairRecord->count = 2;
			activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst = indexSymbolLeft;
		}

		else if (!activePairs[Symbols][symbolNext].seenOnce && activePairs[Symbols][symbolNext].pairRecord)
			//This is if we see it after the second time
		{
			//Update count
			activePairs[Symbols][symbolNext].pairRecord->count++;

			//Update threading pointers
			sequenceArray[indexSymbolLeft]->previous = sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst];

			//DEBUG
			if (sequenceArray[activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst]->symbol == 0)
			{
				int x = 0;
			}

			//Update arrayIndexLast
			activePairs[Symbols][symbolNext].pairRecord->arrayIndexFirst = indexSymbolLeft;
		}
	}
}

void AlgorithmP::firstPass(
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	Conditions& c)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;
	long indexSymbolNextNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
	bool skip = false;

	do
	{
		indexSymbolLeft = -1;
		indexSymbolRight = -1;
		indexSymbolPrevious = -1;
		indexSymbolPreviousPrevious = -1;
		indexSymbolNext = -1;
		indexSymbolNextNext = -1;

		sequenceIndex = nextSymbol->index;
		//Store the pointer to the next symbol now, as the current symbol is changed as we go
		nextSymbol = nextSymbol->next;

		establishExtendedContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolPreviousPrevious,
			indexSymbolNext,
			indexSymbolNextNext,
			sequenceIndex,
			sequenceArray);

		bool activeLeft = false;
		if (indexSymbolPrevious >= 0)
			activeLeft = sequenceArray[indexSymbolPrevious]->next ||
			sequenceArray[indexSymbolPrevious]->previous;
		
		//Decrement count of xa
		decrementCountLeft(
			indexSymbolPrevious,
			indexSymbolLeft,
			indexSymbolRight,
			activePairs,
			sequenceArray,
			priorityQueue,
			Symbols,
			c);

		//We need to reset this as we no longer do it while replacing the pair. This is because we need to set this previous pointer in the first pass.
		sequenceArray[indexSymbolLeft]->previous = nullptr;

		//Left pair
		checkCountLeft(
			indexSymbolPreviousPrevious,
			indexSymbolPrevious,
			indexSymbolLeft,
			indexSymbolRight,
			activePairs,
			sequenceArray,
			Symbols,
			activeLeft,
			skip,
			c);

		//Right pair
		checkCountRight(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolNext,
			indexSymbolNextNext,
			activePairs,
			sequenceArray,
			Symbols,
			c);

	} while (nextSymbol);
}

void AlgorithmP::replaceAllPairs(
	long sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	Conditions& c)
{
	MyTimer clock;

	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];

	/*if (c.extraVerbose)
	{
		establishContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceIndex,
			sequenceArray);

		cout << "Compressing pair (" << sequenceArray[indexSymbolLeft]->symbol << ", " << sequenceArray[indexSymbolRight]->symbol << ") with count: "
			<< activePairs[sequenceArray[indexSymbolLeft]->symbol][sequenceArray[indexSymbolRight]->symbol].pairRecord->count << endl;
	}*/
	
	if (c.timing)
	{
		clock.start();
	}

	firstPass(
		sequenceIndex,
		sequenceArray,
		activePairs,
		priorityQueue,
		Symbols,
		c);

	if (c.timing)
	{
		clock.stop();
		cout << "	Timing first pass: " << clock.getTime() << endl;
	}

	bool skip = false;

	//DEBUG
	int count = 0;

	if (c.timing)
	{
		clock.start();
	}

	do
	{
		indexSymbolLeft = -1;
		indexSymbolRight = -1;
		indexSymbolPrevious = -1;
		indexSymbolNext = -1;

		//DEBUG
		
		if (count == 3140)
		{
			int x = 0;
		}

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
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			skip,
			c);

		
		
		//DEBUG
		count++;
	} while (nextSymbol);

	if (c.timing)
	{
		clock.stop();
		cout << "	Timing second pass: " << clock.getTime() << endl;
	}

	//DEBUG
	MyTest t;
	int insane = t.SanityCheck(sequenceArray, priorityQueue, activePairs);
	if (insane)
	{
		string test = t.SanityCheckThreadingPointersDetailed(sequenceArray);
		int x = 0;
	}
		
}

void AlgorithmP::newSymbol(long & Symbols)
{
	if (Symbols == LONG_MAX - 1)
	{
		cerr << "Ran out of symbols, aborting compression" << endl;
		exit;
	}
	Symbols++;
}

void AlgorithmP::manageOneEntryOnList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
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
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);

	//Compaction
	if (c.compact)
	{
		if (cData.replaceCount > cData.compactTotal)
		{
			compact(sequenceArray, activePairs, priorityQueue);
			cData.updateCompactTotal();
		}
	}

	//Pick new symbol
	newSymbol(Symbols);
}

void AlgorithmP::manageOneList(
	long i,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	CompactionData &cData,
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
			cData,
			c);
	}
}

void AlgorithmP::manageLowerPriorityLists(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
	CompactionData &cData,
	Conditions& c)
{
	//DEBUG
	MyTest t;
	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{		
		if (c.extraVerbose)
		{
			int c = t.entriesinPriorityQueueAtPosition(priorityQueue, i);
			cout << "Replacing " << c << " pairs with count " << i + 2 << endl;
		}
		//DEBUG
		if (i == 60)
		{
			int x = 0;
		}
		manageOneList(
			i,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			cData,
			c);
	}
}

//Manages active pairs with frequencies greater than sqrt(n)
void AlgorithmP::manageHighPriorityList(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	long & Symbols,
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

		//DEBUG
		if (Symbols == 297)
		{
			int x = 0;
		}
		if (Symbols == 298)
		{
			int x = 0;
		}

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			c);

		//Compaction
		if (c.compact)
		{
			if (cData.replaceCount > cData.compactTotal)
			{
				compact(sequenceArray, activePairs, priorityQueue);
				cData.updateCompactTotal();
			}
		}

		//Pick new symbol
		newSymbol(Symbols);
	}
}

void AlgorithmP::run(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unordered_set<long>& terminals,
	long & Symbols,
	Conditions& c)
{
	CompactionData cData(sequenceArray.size());
	if (c.extraVerbose)
	{
		cout << "Compressing high priority pairs" << endl;
	}
	manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);
	if (c.extraVerbose)
	{
		cout << "Compressing low priority pairs" << endl;
	}
	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);
}