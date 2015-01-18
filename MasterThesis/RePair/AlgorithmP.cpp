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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
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
	{
		(*activePairs)[tmpPairRecordAdjacent->pair.leftSymbol].erase(tmpPairRecordAdjacent->pair.rightSymbol);
		if ((*activePairs)[tmpPairRecordAdjacent->pair.leftSymbol].empty())
			(*activePairs).erase(tmpPairRecordAdjacent->pair.leftSymbol);
	}
		
}

void AlgorithmP::replacePair(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolNext,
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs)
{
	Pair tmpPair;
	char newSymbol = (char)(*Symbols);
	tmpPair.leftSymbol = symbolLeft->symbol;
	tmpPair.rightSymbol = symbolRight->symbol;

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
	(*activePairs)[tmpPair.leftSymbol][tmpPair.rightSymbol]->count--;

	if ((*activePairs)[tmpPair.leftSymbol][tmpPair.rightSymbol]->count == 0)
	{
		symbolLeft->next = NULL;
		(*activePairs)[tmpPair.leftSymbol].erase(tmpPair.rightSymbol);
		if ((*activePairs)[tmpPair.leftSymbol].empty())
			(*activePairs).erase(tmpPair.leftSymbol);
	}
		
}

void AlgorithmP::increaseCount(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs)
{
	tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolRight->symbol];
	tmpPairRecord->count++;	
}

void AlgorithmP::setupPairRecord(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord)
{
	Pair tmpPair;
	tmpPair.leftSymbol = symbolLeft->symbol;
	tmpPair.rightSymbol = symbolRight->symbol;

	tmpPairRecord->previousPair = NULL;
	tmpPairRecord->nextPair = NULL;
	tmpPairRecord->arrayIndexFirst = symbolLeft->index;
	tmpPairRecord->arrayIndexLast = symbolLeft->index;
	tmpPairRecord->pair.leftSymbol = tmpPair.leftSymbol;
	tmpPairRecord->pair.rightSymbol = tmpPair.rightSymbol;
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
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext)
{
	
	auto tmpPairRecord = make_shared<PairRecord>();
	auto tmpPairRecordAdjacent = make_shared<PairRecord>();
	char newSymbol;

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
		tmpPairRecordAdjacent = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];

		if (tmpPairRecordAdjacent)
			decrementCount(symbolPrevious, symbolLeft, activePairs, priorityQueue, tmpPairRecordAdjacent);
	}
	
	if (symbolNext) //by
	{
		tmpPairRecordAdjacent = (*activePairs)[symbolRight->symbol][symbolNext->symbol];

		if (tmpPairRecordAdjacent &&																		//If Pair record exists
			!(symbolRight->symbol == symbolNext->symbol &&													//But it is not the case that the symbols are identical
			symbolRight->symbol == symbolLeft->symbol &&
			!(symbolRight->next && symbolRight->previous)))													//while not being part of a sequence of pairs
			decrementCount(symbolRight, symbolNext, activePairs, priorityQueue, tmpPairRecordAdjacent);
	}

	//Step 3, replace ab, leaving xAy

	replacePair(symbolLeft, symbolRight, symbolNext, Symbols, dictionary, activePairs);

	//Step 4, increase counts of xA and Ay
	if (symbolPrevious) //xA
	{
		tmpPairRecord = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];
		if (!tmpPairRecord)
		{
			(*activePairs)[symbolPrevious->symbol][symbolLeft->symbol] = make_shared<PairRecord>();
			tmpPairRecord = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];
		}

		if (symbolPrevious->symbol == symbolLeft->symbol && tmpPairRecord->count != 0 &&								//If we have identical symbols which have been seen before
			(symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->symbol ||			//and the previous symbol was also the same (meaning at least three in a row)
			((*sequenceArray)[symbolPrevious->index - 1]->symbol == '\0' &&								
			symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->previous->symbol)) &&
			!tmpPairRecord->skippedPair)																//and we registered the last pair
		{
			tmpPairRecord->skippedPair = true;															//Then skip this pair
		}
		else																							//else register pair as normal
		{
			tmpPairRecord->skippedPair = false;

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
			else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size() + 1)
			{
				removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
				insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
			}
		}

		
	}
	if (symbolNext) //Ay
	{
		tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolNext->symbol];

		if (!tmpPairRecord)
		{
			(*activePairs)[symbolLeft->symbol][symbolNext->symbol] = make_shared<PairRecord>();
			tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolNext->symbol];
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
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size() + 1)
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
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols)
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
	MyTest test;

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

		if (!symbolOld.next || ((*symbolOld.next).symbol == '\0' && !symbolOld.next->next))
			break;

		if ((*symbolOld.next).symbol == '\0')
		{
			sequenceIndex = (*symbolOld.next->next).index;
			symbolOld = *(*sequenceArray)[sequenceIndex];
		}
		else
		{
			sequenceIndex = (*symbolOld.next).index;
			symbolOld = *(*sequenceArray)[sequenceIndex];
		}
	} while (running);
}

void AlgorithmP::newSymbol(
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{	
	bool badSymbol = true;

	if ((*Symbols) == 254)
	{
		cout << "Ran out of symbols, aborting compression" << endl;
		exit;
	}

	while (badSymbol)
	{		
		(*Symbols)++;
		if ((*symbolMap)[(*Symbols)])// || (*Symbols) == 129)
			badSymbol = true;
		else
			badSymbol = false;
	}
}

void AlgorithmP::manageHighPriorityList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	auto tmpPairRecord = make_shared<PairRecord>();
	auto tmpPairRecordSelected = make_shared<PairRecord>();
	int sequenceIndex = 0;
	int last = priorityQueue->size() - 1;
	MyTest test;

	while ((*priorityQueue)[last])
	{
		tmpPairRecordSelected = (*priorityQueue)[last];
		tmpPairRecord = (*priorityQueue)[last];
		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		} 
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (!tmpPairRecordSelected->previousPair && !tmpPairRecordSelected->nextPair)				//Only in the list
		{
			(*priorityQueue)[last] = NULL;			
		}
		else if (!tmpPairRecordSelected->previousPair)												//First in the list
		{
			(*priorityQueue)[last] = tmpPairRecordSelected->nextPair;
			(*priorityQueue)[last]->previousPair = NULL;
		}
		else if (!tmpPairRecordSelected->nextPair)													//Last in the list
		{
			tmpPairRecordSelected->previousPair->nextPair = NULL;
		}
		else																						//Middle of the list
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		tmpPairRecordSelected->previousPair = NULL;
		tmpPairRecordSelected->nextPair = NULL;		

		newSymbol(Symbols, symbolMap);

		replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols);

		
	}
}

void AlgorithmP::manageOneEntryOnList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	int i,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
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
		
	newSymbol(Symbols, symbolMap);

	replaceAllPairs(
		sequenceIndex,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);	
}

void AlgorithmP::manageOneList(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	int i,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	while ((*priorityQueue)[i])
	{
		manageOneEntryOnList(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			i,
			symbolMap);
	}
}

void AlgorithmP::manageLowerPriorityLists(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	
	for (int i = priorityQueue->size() - 2; i >= 0; i--)
	{		
		manageOneList(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			Symbols,
			i,
			symbolMap);
	}
}

void AlgorithmP::run(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairRecord>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	manageHighPriorityList(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		symbolMap);

	manageLowerPriorityLists(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		symbolMap);
}