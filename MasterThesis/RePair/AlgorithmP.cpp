#include "stdafx.h"
#include "AlgorithmP.h"

using namespace std;

AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}


void AlgorithmP::removeFromListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
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
	tmpPairRecordAdjacent->previousPair = NULL;
	tmpPairRecordAdjacent->nextPair = NULL;
}

void AlgorithmP::insertIntoListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecord, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
{
	int pQIndex = index;
	shared_ptr<PairRecord> tmpRecord;

	if ((*priorityQueue)[pQIndex] == NULL)
	{
		(*priorityQueue)[pQIndex] = tmpPairRecord;
		tmpPairRecord->previousPair = NULL;
		tmpPairRecord->nextPair = NULL;
	}
		
	else
	{
		tmpRecord = (*priorityQueue)[index];
		while (tmpRecord->nextPair)
		{
			tmpRecord = tmpRecord->nextPair;
		}
		tmpRecord->nextPair = tmpPairRecord;
		tmpPairRecord->previousPair = tmpRecord;
		tmpPairRecord->nextPair = NULL;
		/*(*priorityQueue)[pQIndex]->previousPair = tmpPairRecord;
		tmpPairRecord->nextPair = (*priorityQueue)[pQIndex];
		(*priorityQueue)[pQIndex] = tmpPairRecord;
		tmpPairRecord->previousPair = NULL;*/
	}
}

void AlgorithmP::managePriorityQueueDecrement(shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
{

	if (tmpPairRecordAdjacent->count == 1) //Remove from priority queue
	{
		removeFromListInPriorityQueue(0, tmpPairRecordAdjacent, priorityQueue);
	}
	//Remove from current priority queue entry and add to one lower
	else if (tmpPairRecordAdjacent->count > 1 && tmpPairRecordAdjacent->count <= priorityQueue->size())
	{
		removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, priorityQueue);

		insertIntoListInPriorityQueue(
			tmpPairRecordAdjacent->count - 2,
			tmpPairRecordAdjacent,
			priorityQueue);
	}
}

void AlgorithmP::decrementCount(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	shared_ptr<PairRecord>& tmpPairRecordAdjacent)
{
	tmpPairRecordAdjacent->count--;
	if (symbolLeft->next)
	{
		symbolLeft->next->previous = NULL;
		symbolLeft->next = NULL;
	}
	managePriorityQueueDecrement(tmpPairRecordAdjacent, priorityQueue);
	if (tmpPairRecordAdjacent->count == 0)
		activePairs->erase(tmpPairRecordAdjacent->pair);
}

void AlgorithmP::replacePair(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolNext,
	unique_ptr<int>& Symbols,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs)
{
	stringstream ss;
	string tmpPair;
	char newSymbol = (char)(*Symbols);
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();

	if (symbolLeft && symbolLeft->next)
	{
		symbolLeft->next->previous = NULL;
		symbolLeft->next = NULL;
	}

	(*dictionary)[newSymbol] = tmpPair;
	symbolLeft->symbol = newSymbol;
	symbolRight->symbol = (char)0;

	if (symbolNext && symbolNext->symbol != '\0')
	{
		symbolRight->next = symbolNext;
	}
	else
		symbolRight->next = NULL;
	
	symbolRight->previous = symbolLeft;

	(*activePairs)[tmpPair]->count--;

	if ((*activePairs)[tmpPair]->count == 0)
	{
		symbolLeft->next = NULL;
		(*activePairs).erase(tmpPair);
	}
		
}

void AlgorithmP::increaseCount(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs)
{
	stringstream ss;
	string tmpPair;
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();
	tmpPairRecord = (*activePairs)[tmpPair];
	tmpPairRecord->count++;	
}

void AlgorithmP::setupPairRecord(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord)
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
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	shared_ptr<PairRecord>& tmpPairRecord)
{
	(*sequenceArray)[tmpPairRecord->arrayIndexFirst]->next = NULL;
	(*sequenceArray)[tmpPairRecord->arrayIndexFirst]->previous = NULL;
}

void AlgorithmP::updatePairRecord(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<PairRecord>& tmpPairRecord)
{
	tmpPairRecord->arrayIndexLast = symbolLeft->index;
}

void AlgorithmP::updatePairSequence(
	shared_ptr<SymbolRecord>& symbolLeft,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	shared_ptr<PairRecord>& tmpPairRecord)
{
	(*sequenceArray)[tmpPairRecord->arrayIndexLast]->next =
		(*sequenceArray)[symbolLeft->index];
	(*sequenceArray)[symbolLeft->index]->previous =
		(*sequenceArray)[tmpPairRecord->arrayIndexLast];
}

void AlgorithmP::replaceInstanceOfPair(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols,
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext)
{
	
	auto tmpPairRecord = make_shared<PairRecord>();
	auto tmpPairRecordAdjacent = make_shared<PairRecord>();
	char newSymbol;

	stringstream ss;
	string tmpPair;	

	/*Test test;

	test.Sequence("Sequence", sequenceArray);
	test.ActivePairsDetails("Active pairs", activePairs);
	test.PriorityQueue("Priority queue", priorityQueue);
	test.Dictionary("Dictionary", dictionary);
	test.Context("Context", symbolLeft, symbolRight, symbolPrevious, symbolNext);
	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;*/

	//Step 2, decrement counts of xa and by
	if (symbolPrevious) //xa
	{

		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecordAdjacent = (*activePairs)[tmpPair];
		if (tmpPairRecordAdjacent)
			decrementCount(symbolPrevious, symbolLeft, activePairs, priorityQueue, tmpPairRecordAdjacent);
	}
	
	if (symbolNext) //by
	{

		ss << symbolRight->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecordAdjacent = (*activePairs)[tmpPair];

		if (tmpPairRecordAdjacent)
			decrementCount(symbolRight, symbolNext, activePairs, priorityQueue, tmpPairRecordAdjacent);
	}

	//Step 3, replace ab, leaving xAy

	replacePair(symbolLeft, symbolRight, symbolNext, Symbols, dictionary, activePairs);

	//Step 4, increase counts of xA and Ay
	if (symbolPrevious) //xA
	{
		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();

		tmpPairRecord = (*activePairs)[tmpPair];
		if (!tmpPairRecord)
		{
			(*activePairs)[tmpPair] = make_shared<PairRecord>();
			tmpPairRecord = (*activePairs)[tmpPair];
		}

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
		{
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		}
		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
	if (symbolNext) //Ay
	{
		ss << symbolLeft->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();

		tmpPairRecord = (*activePairs)[tmpPair];
		if (!tmpPairRecord)
		{
			(*activePairs)[tmpPair] = make_shared<PairRecord>();
			tmpPairRecord = (*activePairs)[tmpPair];
		}

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
		{
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		}

		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
}

void AlgorithmP::establishContext(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	int sequenceIndex)
{
	SymbolRecord tmpSymbol;

	symbolLeft = (*sequenceArray)[sequenceIndex];
	symbolRight = (*sequenceArray)[sequenceIndex + 1];
	
	if ((symbolRight)->symbol == (char)0)
	{
		tmpSymbol = *symbolRight;
		//Update threading counter - start
		if (symbolRight->next->index + 1 < sequenceArray->size())
		{
			symbolRight->next = (*sequenceArray)[symbolRight->next->index + 1];
			(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		}			
		else
			symbolRight->next = NULL;
		//(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		if (symbolRight->next && (symbolRight->next)->symbol == (char)0)
		{
			symbolRight->next = symbolRight->next->next;
			(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		}
		//Update threading counter - end
		symbolRight = tmpSymbol.next;
	}
		
	if (sequenceIndex != 0)
	{
		symbolPrevious = (*sequenceArray)[sequenceIndex - 1];
		if ((symbolPrevious)->symbol == (char)0)
			symbolPrevious = symbolPrevious->previous;
	}
	else
		symbolPrevious = NULL;

	if (symbolRight->index != sequenceArray->size()-1)
	{
		symbolNext = (*sequenceArray)[symbolRight->index + 1];
		if (symbolNext->symbol == (char)0)
			symbolNext = symbolNext->next;
	}
	else
		symbolNext = NULL;

	if (symbolLeft->symbol == '\0' || symbolRight->symbol == '\0')
	{
		cout << "something is wrong!!" << endl;
		cout << "previous: " << symbolPrevious->symbol << endl;
		cout << "left: " << symbolLeft->symbol << endl;
		cout << "right: " << symbolRight->symbol << endl;
		cout << "next: " << symbolNext->symbol << endl;
		exit;
	}
}

void AlgorithmP::replaceAllPairs(
	int sequenceIndex,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols)
{
	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
	auto symbolRight = make_shared<SymbolRecord>(); //b
	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
	auto symbolNext = make_shared<SymbolRecord>(); //y

	bool firstPair;
	bool lastPair;
	bool firstInstance = true;
	bool running = true;
	SymbolRecord symbolOld = *(*sequenceArray)[sequenceIndex];
	//Test test;

	do
	{
		//Step 1, Establish context of xaby

		establishContext(symbolLeft, symbolRight, symbolPrevious, symbolNext, sequenceArray, sequenceIndex);
		//test.Context("Context", symbolLeft, symbolRight, symbolPrevious, symbolNext);

		replaceInstanceOfPair(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			symbolLeft,
			symbolRight,
			symbolPrevious,
			symbolNext);

		if (!symbolOld.next)
			break;

		sequenceIndex = (*symbolOld.next).index;
		symbolOld = *(*sequenceArray)[sequenceIndex];


	} while (running);
}

void AlgorithmP::manageHighPriorityList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols)
{
	auto tmpPairRecord = make_shared<PairRecord>();
	auto tmpPairRecordSelected = make_shared<PairRecord>();
	int sequenceIndex = 0;

	while ((*priorityQueue)[priorityQueue->size() - 1])
	{
		tmpPairRecordSelected = (*priorityQueue)[priorityQueue->size() - 1];
		tmpPairRecord = (*priorityQueue)[priorityQueue->size() - 1];
		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		} 

		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols);

		(*Symbols)++;
	}
}

void AlgorithmP::manageOneEntryOnList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols,
	int i)
{
	auto tmpPairRecord = make_shared<PairRecord>();
	int sequenceIndex;

	tmpPairRecord = (*priorityQueue)[i];

	sequenceIndex = tmpPairRecord->arrayIndexFirst;

	//Remove current pair from priority queue
	if (tmpPairRecord->nextPair)
	{
		(*priorityQueue)[i] = tmpPairRecord->nextPair;
		(*priorityQueue)[i]->previousPair = NULL;
		tmpPairRecord->previousPair = NULL;
		tmpPairRecord->nextPair = NULL;
	}		
	else
	{
		(*priorityQueue)[i] = NULL;
	}
		

	replaceAllPairs(
		sequenceIndex,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	(*Symbols)++;
}

void AlgorithmP::manageOneList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols,
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
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols)
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
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, string>>& dictionary,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<int>& Symbols)
{
	/*manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);*/

	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);
}