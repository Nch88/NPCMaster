#include "stdafx.h"
#include "AlgorithmP.h"


AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}

bool comPair(CompactPair fst, CompactPair snd)
{
	//compare two pairs by comparing left symbols, then right symbols
	if (fst.leftSymbol < snd.leftSymbol)
		return true;
	else if (fst.leftSymbol == snd.leftSymbol)
		return fst.rightSymbol < snd.rightSymbol;
	else
		return false;
}

//This is the main dictionary function. It fills the pair vector based on dictionary + terminals.
void AlgorithmP::generateCompactDictionary(
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_set<unsigned int>& terminals,
	vector<CompactPair>& pairVector)
{
	vector<unsigned int> terminalVector;
	terminalVector.assign(terminals.begin(), terminals.end());

	//Split dictionary by generation
	vector<vector<CompactPair>> generationVectors;
	createGenerationVectors(dictionary, generationVectors);

	createFinalPairVector(dictionary, generationVectors, pairVector, terminalVector);
}

void AlgorithmP::createFinalPairVector(
	unordered_map<unsigned int, Pair>& dictionary,
	vector<vector<CompactPair>>& generationVectors,
	vector<CompactPair>& pairVector,
	vector<unsigned int>& terminals)
{
	//Find the indices of the terminals
	unordered_map<unsigned int, unsigned int> terminalIndices;
	for (int i = 0; i < terminals.size(); ++i)
	{
		terminalIndices[terminals[i]] = i;
	}
	unordered_map<unsigned int,unordered_map<unsigned int, unsigned int>> indices;

	//Generation 1
	for (int xyz = 0; xyz < generationVectors[0].size(); ++xyz)
	{
		//Find the new indices of the two symbols in this pair
		unsigned int left = terminalIndices[generationVectors[0][xyz].leftSymbol];
		unsigned int right = terminalIndices[generationVectors[0][xyz].rightSymbol];

		//Make a pair out of the indices we found, then push it to the vector
		CompactPair p(left,right);
		pairVector.push_back(p);

		//Record the index of this symbol
		indices[p.leftSymbol][p.rightSymbol] = xyz + terminals.size();
	}

	int x = 0;

	//Generation 2+
	int offset = terminals.size() + generationVectors[0].size();
	//if (generationVectors.size() > 1)
	//{
		for (int i = 1; i < generationVectors.size(); ++i)
		{
			for (int j = 0; j < generationVectors[i].size(); ++j)
			{
				//Find the new indices of the two symbols in this pair
				unsigned int left = indices[dictionary[generationVectors[i][j].leftSymbol].leftSymbol][dictionary[generationVectors[i][j].leftSymbol].rightSymbol];
				unsigned int right = indices[dictionary[generationVectors[i][j].rightSymbol].leftSymbol][dictionary[generationVectors[i][j].rightSymbol].rightSymbol];

				//Make a pair out of the indices we found, then push it to the vector
				CompactPair p(left, right);
				pairVector.push_back(p);

				//Record the index of this symbol
				indices[p.leftSymbol][p.rightSymbol] = offset + j;
			}
			//Update the offset
			offset += generationVectors[i].size();
		}
	//}
}

void AlgorithmP::createGenerationVectors(
	unordered_map<unsigned int, Pair>& dictionary, 
	vector<vector<CompactPair>>& generationVectors)
{
	//Distribute pairs in vectors
	for each (std::pair<unsigned int, Pair> p in dictionary)
	{
		//Expand the outer vector if necessary
		while (p.second.generation >= generationVectors.size())
		{
			vector<CompactPair> v;
			generationVectors.push_back(v);
		}

		//Add this pair to a vector
		CompactPair cp(p.second.leftSymbol,p.second.rightSymbol);
		generationVectors[p.second.generation - 1].push_back(cp);
	}

	//Sort the vectors
	for each (vector<CompactPair> v in generationVectors)
	{
		sort(v.begin(), v.end(), comPair);
	}
}

unsigned int AlgorithmP::findGeneration(
	unordered_map<unsigned int, Pair>& dictionary, 
	unsigned int left, 
	unsigned int right
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
		unsigned int genLeft = dictionary[left].generation;
		unsigned int genRight = dictionary[right].generation;
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
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
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
				unsigned int s1 = sequenceArray[i]->symbol;
				unsigned int s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;

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
	}
	sequenceArray.resize(index);
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
	if (tracker->pairRecord->count < 2)
		//DEBUG
	{
		int x = 0;
	}
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
	if (tracker->pairRecord->count < 2)
		//DEBUG
	{
		int x = 0;
	}
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
			if (tracker->pairRecord->count < 2)
				//DEBUG
			{
				int x = 0;
			}
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
			if (tracker->pairRecord->count < 2)
				//DEBUG
			{
				int x = 0;
			}
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
		rightSymbolRecord->symbol,
		findGeneration(dictionary, leftSymbolRecord->symbol, rightSymbolRecord->symbol));
	
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
		else
			indexSymbolNext = -1;
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
		indexSymbolLeft = -1;
		indexSymbolRight = -1;
		indexSymbolPrevious = -1;
		indexSymbolNext = -1;

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
	CompactionData &cData,
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
	
	//Find the count of the pair to be replaced and update counter for compaction
	if (c.compact)
	{
		long idx = sequenceIndex;
		unsigned int s1 = sequenceArray[idx]->symbol;
		unsigned int s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
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
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
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
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	CompactionData &cData,
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
			cData,
			c);
	}
}

void AlgorithmP::manageHighPriorityList(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unsigned int & Symbols,
	CompactionData &cData,
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

		//Find the count of the pair to be replaced and update counter for compaction
		if (c.compact)
		{
			long i = sequenceIndex;
			unsigned int s1 = sequenceArray[i]->symbol;
			unsigned int s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;
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
}

void AlgorithmP::run(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unordered_set<unsigned int>& terminals,
	unsigned int & Symbols,
	Conditions& c)
{
	CompactionData cData(sequenceArray.size());

	manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);

	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		cData,
		c);
}