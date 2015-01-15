#include "stdafx.h"
#include "AlgorithmP.h"

using namespace std;

AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}


void AlgorithmP::removeFromListInPriorityQueue(int index, PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue)
{
	if (index > priorityQueue->size() - 1)
		index = priorityQueue->size() - 1;


	if (tmpPairRecordAdjacent->previousPair == NULL && tmpPairRecordAdjacent->nextPair == NULL) //Only in the list	
		(*priorityQueue)[index] = NULL;

	else if (tmpPairRecordAdjacent->previousPair == NULL) //First in the list
	{
		(*priorityQueue)[index] = tmpPairRecordAdjacent->nextPair;
		tmpPairRecordAdjacent->nextPair->previousPair = NULL;
	}
	else if (tmpPairRecordAdjacent->nextPair == NULL) //Last in the list	
		tmpPairRecordAdjacent->previousPair->nextPair = NULL;
	else //Middle of the list
	{
		tmpPairRecordAdjacent->previousPair->nextPair = tmpPairRecordAdjacent->nextPair;
		tmpPairRecordAdjacent->nextPair->previousPair = tmpPairRecordAdjacent->previousPair;
	}
}

void AlgorithmP::insertIntoListInPriorityQueue(int index, PairRecord * tmpPairRecord, vector<PairRecord*> * priorityQueue)
{
	int pQIndex = index;

	if ((*priorityQueue)[pQIndex] == NULL)
	{
		(*priorityQueue)[pQIndex] = tmpPairRecord;
		tmpPairRecord->previousPair = NULL;
		tmpPairRecord->nextPair = NULL;
	}
		
	else
	{
		(*priorityQueue)[pQIndex]->previousPair = tmpPairRecord;
		tmpPairRecord->nextPair = (*priorityQueue)[pQIndex];
		(*priorityQueue)[pQIndex] = tmpPairRecord;
		tmpPairRecord->previousPair = NULL;
	}
}

void AlgorithmP::managePriorityQueueDecrement(PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue)
{

	if (tmpPairRecordAdjacent->count == 1) //Remove from priority queue
	{
		removeFromListInPriorityQueue(0, tmpPairRecordAdjacent, priorityQueue);
	}
	//Remove from current priority queue entry and add to one lower
	else if (tmpPairRecordAdjacent->count > 1 && tmpPairRecordAdjacent->count <= priorityQueue->size() - 1)
	{
		removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, priorityQueue);

		insertIntoListInPriorityQueue(
			tmpPairRecordAdjacent->count - 2,
			tmpPairRecordAdjacent,
			priorityQueue);
	}
}

void AlgorithmP::decrementCount(
	SymbolRecord* symbolLeft, 
	SymbolRecord* symbolRight,
	unordered_map<string, 
	PairRecord> * activePairs,
	PairRecord * tmpPairRecordAdjacent,
	vector<PairRecord*> * priorityQueue)
{
	tmpPairRecordAdjacent->count--;

	managePriorityQueueDecrement(tmpPairRecordAdjacent, priorityQueue);
	if (tmpPairRecordAdjacent->count == 0)
		activePairs->erase(tmpPairRecordAdjacent->pair);
}

void AlgorithmP::replacePair(
	SymbolRecord* symbolLeft,
	SymbolRecord* symbolRight,
	SymbolRecord* symbolNext,
	int * Symbols,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs)
{
	stringstream ss;
	string tmpPair;
	char newSymbol = (char)(*Symbols);
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();

	(*dictionary)[newSymbol] = tmpPair;
	symbolLeft->symbol = newSymbol;
	symbolRight->symbol = (char)0;

	symbolRight->next = symbolNext;
	symbolRight->previous = symbolLeft;

	(*activePairs)[tmpPair].count--;

	if ((*activePairs)[tmpPair].count == 0)	
		(*activePairs).erase(tmpPair);	
}

void AlgorithmP::increaseCount(
	SymbolRecord* symbolLeft,
	SymbolRecord* symbolRight,
	PairRecord * tmpPairRecord,
	unordered_map<string, PairRecord> * activePairs)
{
	stringstream ss;
	string tmpPair;
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();
	tmpPairRecord = &(*activePairs)[tmpPair];
	tmpPairRecord->count++;	
}

void AlgorithmP::setupPairRecord(
	SymbolRecord* symbolLeft,
	SymbolRecord* symbolRight,
	PairRecord * tmpPairRecord)
{
	stringstream ss;
	string tmpPair;
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();
	tmpPairRecord->previousPair = NULL;
	tmpPairRecord->nextPair = NULL;
	tmpPairRecord->arrayIndexFirst = symbolLeft->index;
	tmpPairRecord->arrayIndexLast = symbolLeft->index;
	tmpPairRecord->pair = tmpPair;
}

void AlgorithmP::setupPairSequence(
	vector<SymbolRecord*> * sequenceArray,
	PairRecord * tmpPairRecord)
{
	(*sequenceArray)[tmpPairRecord->arrayIndexFirst]->next = NULL;
	(*sequenceArray)[tmpPairRecord->arrayIndexFirst]->previous = NULL;
}

void AlgorithmP::updatePairRecord(
	SymbolRecord* symbolLeft,
	PairRecord * tmpPairRecord)
{
	tmpPairRecord->arrayIndexLast = symbolLeft->index;
}

void AlgorithmP::updatePairSequence(
	SymbolRecord* symbolLeft,
	vector<SymbolRecord*> * sequenceArray,
	PairRecord * tmpPairRecord)
{
	(*sequenceArray)[tmpPairRecord->arrayIndexLast]->next =
		(*sequenceArray)[symbolLeft->index];
	(*sequenceArray)[symbolLeft->index]->previous =
		(*sequenceArray)[tmpPairRecord->arrayIndexLast];
}

void AlgorithmP::replaceInstanceOfPair(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols,
	bool firstPair,
	bool lastPair,
	SymbolRecord* symbolLeft,
	SymbolRecord* symbolRight,
	SymbolRecord* symbolPrevious,
	SymbolRecord* symbolNext)
{
	
	PairRecord * tmpPairRecordAdjacent = NULL;
	PairRecord * tmpPairRecord = NULL;
	char newSymbol;

	stringstream ss;
	string tmpPair;

	

	//Step 2, decrement counts of xa and by
	if (!firstPair) //xa
		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecordAdjacent = &(*activePairs)[tmpPair];

		decrementCount(symbolPrevious, symbolLeft, activePairs, tmpPairRecordAdjacent, priorityQueue);
	
	if (!lastPair) //by
		ss << symbolRight->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecordAdjacent = &(*activePairs)[tmpPair];

		decrementCount(symbolRight, symbolNext, activePairs, tmpPairRecordAdjacent, priorityQueue);

	//Step 3, replace ab, leaving xAy

	replacePair(symbolLeft, symbolRight, symbolNext, Symbols, dictionary, activePairs);

	//Step 4, increase counts of xA and Ay
	if (!firstPair) //xA
	{
		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecord = &(*activePairs)[tmpPair];

		increaseCount(symbolPrevious, symbolLeft, tmpPairRecord, activePairs);

		if (tmpPairRecord->count == 1) //New pair
		{
			setupPairRecord(symbolPrevious, symbolLeft, tmpPairRecord);
			setupPairSequence(sequenceArray, tmpPairRecord);
		}
		else //Update link between  pair sequence
		{
			updatePairSequence(symbolPrevious, sequenceArray, tmpPairRecord);
			updatePairRecord(symbolPrevious, tmpPairRecord);
		}

		if (tmpPairRecord->count == 2) //Insert into priority queue					
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
	if (!lastPair) //Ay
	{
		ss << symbolLeft->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecord = &(*activePairs)[tmpPair];

		increaseCount(symbolLeft, symbolNext, tmpPairRecord, activePairs);

		if (tmpPairRecord->count == 1) //New pair
		{
			setupPairRecord(symbolLeft, symbolNext, tmpPairRecord);
			setupPairSequence(sequenceArray, tmpPairRecord);
		}
		else //Update link between  pair sequence
		{
			updatePairSequence(symbolLeft, sequenceArray, tmpPairRecord);
			updatePairRecord(symbolLeft, tmpPairRecord);
		}

		if (tmpPairRecord->count == 2) //Insert into priority queue					
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
	/*if (tmpPairRecord)
	{
		delete tmpPairRecord;
		tmpPairRecord = 0;
	}
	if (tmpPairRecordAdjacent)
	{
		delete tmpPairRecordAdjacent;
		tmpPairRecordAdjacent = 0;
	}*/
}

void AlgorithmP::establishContext(
SymbolRecord** symbolLeft,
SymbolRecord** symbolRight,
SymbolRecord** symbolPrevious,
SymbolRecord** symbolNext,
bool firstPair, 
bool lastPair,
vector<SymbolRecord*> * sequenceArray,
int sequenceIndex)
{
	*symbolLeft = (*sequenceArray)[sequenceIndex];
	*symbolRight = (*sequenceArray)[sequenceIndex + 1];
	if (!firstPair)
	{
		*symbolPrevious = (*sequenceArray)[sequenceIndex - 1];
		if ((*symbolPrevious)->symbol == (char)0)
			*symbolPrevious = (*symbolPrevious)->previous;
	}

	if (!lastPair)
	{
		*symbolNext = (*sequenceArray)[sequenceIndex + 2];
		if ((*symbolNext)->symbol == (char)0)
			*symbolNext = (*symbolNext)->next;
	}
}

void AlgorithmP::replaceAllPairs(
	int sequenceIndex,
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols)
{
	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
	SymbolRecord* symbolRight = NULL; //b
	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
	SymbolRecord* symbolNext = NULL; //y
	bool firstPair;
	bool lastPair;
	bool firstInstance = true;
	bool running = true;
	SymbolRecord symbolOld = *(*sequenceArray)[sequenceIndex];

	do
	{
		//Step 1, Establish context of xaby
		firstPair = sequenceIndex == 0;
		lastPair = sequenceIndex == sequenceArray->size() - 2;

		establishContext(&symbolLeft, &symbolRight, &symbolPrevious, &symbolNext, firstPair, lastPair, sequenceArray, sequenceIndex);

		replaceInstanceOfPair(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			firstPair,
			lastPair,
			symbolLeft,
			symbolRight,
			symbolPrevious,
			symbolNext);

		if (!symbolOld.next)
			break;

		if (!firstInstance)
		{
			sequenceIndex = (*symbolOld.next).index;
			symbolOld = *(*sequenceArray)[sequenceIndex];
		}

		firstInstance = false;


	} while (running);

	if (symbolLeft)
	{
		delete symbolLeft;
		symbolLeft = 0;
	}
	if (symbolRight)
	{
		delete symbolRight;
		symbolRight = 0;
	}
	if (symbolPrevious)
	{
		delete symbolPrevious;
		symbolPrevious = 0;
	}
	if (symbolNext)
	{
		delete symbolNext;
		symbolNext = 0;
	}
	if (&symbolOld)
	{
		delete &symbolOld;
	}
}

void AlgorithmP::manageHighPriorityList(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols)
{
	PairRecord* tmpPairRecord = NULL;
	PairRecord* tmpPairRecordSelected = NULL;
	int sequenceIndex = 0;

	while ((*priorityQueue)[priorityQueue->size() - 1])
	{
		tmpPairRecordSelected = (*priorityQueue)[priorityQueue->size() - 1];
		//Find pair with most occurences
		do
		{
			tmpPairRecord = (*priorityQueue)[priorityQueue->size() - 1];
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		} while (tmpPairRecord->nextPair != NULL);

		sequenceIndex = tmpPairRecord->arrayIndexFirst;

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols);
		Symbols++;
	}
	if (tmpPairRecord)
	{
		delete tmpPairRecord;
		tmpPairRecord = 0;
	}
	if (tmpPairRecordSelected)
	{
		delete tmpPairRecordSelected;
		tmpPairRecordSelected = 0;
	}
}

void AlgorithmP::manageOneEntryOnList(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols,
	int i)
{
	PairRecord* tmpPairRecord = NULL;
	int sequenceIndex;

	tmpPairRecord = (*priorityQueue)[i];

	sequenceIndex = tmpPairRecord->arrayIndexFirst;

	//Remove current pair from priority queue
	if (tmpPairRecord->nextPair)
		(*priorityQueue)[i] = tmpPairRecord->nextPair;
	else
		(*priorityQueue)[i] = NULL;

	replaceAllPairs(
		sequenceIndex,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	(*Symbols)++;

	if (tmpPairRecord)
	{
		delete tmpPairRecord;
		tmpPairRecord = 0;
	}
}

void AlgorithmP::manageOneList(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols,
	int i)
{
	while ((*priorityQueue)[i])
	{
		manageOneEntryOnList(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			i);
	}
}

void AlgorithmP::manageLowerPriorityLists(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols)
{

	for (int i = priorityQueue->size() - 2; i >= 0; i--)
	{		
		manageOneList(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			i);
	}
}

void AlgorithmP::run(
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<char, string> * dictionary,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue,
	int * Symbols)
{
	manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);
}