#include "stdafx.h"
#include "AlgorithmP.h"

using namespace std;

AlgorithmP::AlgorithmP()
{
}


AlgorithmP::~AlgorithmP()
{
}


void AlgorithmP::removeFromListInPriorityQueue(
	int index, 
	shared_ptr<PairRecord>& tmpPairRecordAdjacent, 
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
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

void AlgorithmP::insertIntoListInPriorityQueue(
	int index, 
	shared_ptr<PairRecord>& tmpPairRecord, 
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
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
	}
}

void AlgorithmP::managePriorityQueueDecrement(
	shared_ptr<PairRecord>& tmpPairRecordAdjacent, 
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
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

void AlgorithmP::manageSequenceDecrement(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<PairRecord>& tmpPairRecordAdjacent)
{
	if (symbolLeft->index == tmpPairRecordAdjacent->arrayIndexFirst && symbolLeft->index != tmpPairRecordAdjacent->arrayIndexLast)
	{
		tmpPairRecordAdjacent->arrayIndexFirst = symbolLeft->next->index;
		symbolLeft->next->previous = NULL;
	}
	else if (symbolLeft->index != tmpPairRecordAdjacent->arrayIndexFirst && symbolLeft->index == tmpPairRecordAdjacent->arrayIndexLast)
	{
		tmpPairRecordAdjacent->arrayIndexLast = symbolLeft->previous->index;
		symbolLeft->previous->next = NULL;
	}
	else if (tmpPairRecordAdjacent->count == 1)
	{
		tmpPairRecordAdjacent->arrayIndexFirst = -1;
		tmpPairRecordAdjacent->arrayIndexLast = -1;
	}
	else if (symbolLeft->previous && symbolLeft->next)
	{
		symbolLeft->previous->next = symbolLeft->next;
		symbolLeft->next->previous = symbolLeft->previous;
	}

	symbolLeft->next = NULL;
	symbolLeft->previous = NULL;
}

void AlgorithmP::decrementCount(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	shared_ptr<PairRecord>& tmpPairRecordAdjacent)
{
	if (tmpPairRecordAdjacent->arrayIndexFirst != -1 && 
		tmpPairRecordAdjacent->arrayIndexLast != -1)
		manageSequenceDecrement(symbolLeft, tmpPairRecordAdjacent);

	if (tmpPairRecordAdjacent->count != 0)
	{
		tmpPairRecordAdjacent->count--;
		managePriorityQueueDecrement(tmpPairRecordAdjacent, priorityQueue);

		if (tmpPairRecordAdjacent->count == 0)
		{
			//(*activePairs)[tmpPairRecordAdjacent->pair.leftSymbol][tmpPairRecordAdjacent->pair.rightSymbol]->pairRecord = NULL;
		}
	}	
}

void AlgorithmP::threadEmptySymbols(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolNext,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
{
	int index;
	if (symbolNext && symbolNext->symbol != '\0')
	{
		symbolRight->next = symbolNext;
		(*sequenceArray)[symbolLeft->index + 1]->next = symbolNext;
		(*sequenceArray)[symbolNext->index - 1]->previous = symbolLeft;
	}
	else
	{
		symbolRight->next = NULL;
		(*sequenceArray)[symbolLeft->index + 1]->next = NULL;
	}	

	symbolRight->previous = symbolLeft;
	(*sequenceArray)[symbolLeft->index + 1]->previous = symbolLeft;	
}

void AlgorithmP::replacePair(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolNext,
	unique_ptr<unsigned int>& Symbols,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
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

	threadEmptySymbols(
		symbolLeft,
		symbolRight,
		symbolNext,
		sequenceArray);

	(*activePairs)[tmpPair.leftSymbol][tmpPair.rightSymbol]->pairRecord->count--;

	if ((*activePairs)[tmpPair.leftSymbol][tmpPair.rightSymbol]->pairRecord->count == 0)
	{
		symbolLeft->next = NULL;
		//(*activePairs)[tmpPair.leftSymbol][tmpPair.rightSymbol]->pairRecord = NULL;
	}
}

void AlgorithmP::increaseCount(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs)
{
	tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolRight->symbol]->pairRecord;
	tmpPairRecord->count++;	
}

void AlgorithmP::setupPairRecord(
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<PairRecord>& tmpPairRecord)
{
	tmpPairRecord->previousPair = NULL;
	tmpPairRecord->nextPair = NULL;
	tmpPairRecord->arrayIndexFirst = symbolLeft->index;
	tmpPairRecord->arrayIndexLast = symbolLeft->index;
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

void AlgorithmP::checkActivePair(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext)
{

	shared_ptr<PairRecord> tmpPairRecord;
	shared_ptr<PairTracker> tmpPairTracker;
	char newSymbol = (char)(*Symbols);

	if (symbolPrevious) //xA
	{
		tmpPairTracker = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];
		if (tmpPairTracker && tmpPairTracker->pairRecord) //if xa is not an active pair xA cannot be either, skip
		{
			tmpPairTracker = (*activePairs)[symbolPrevious->symbol][newSymbol];
			if (!tmpPairTracker)
			{
				(*activePairs)[symbolPrevious->symbol][newSymbol] = make_shared<PairTracker>();
				tmpPairTracker = (*activePairs)[symbolPrevious->symbol][newSymbol];
				tmpPairTracker->seenOnce = true;
			}
			else if (tmpPairTracker && tmpPairTracker->seenOnce) //xA will appear more than once, make it an active pair
			{
				(*activePairs)[symbolPrevious->symbol][newSymbol] = make_shared<PairTracker>();
				(*activePairs)[symbolPrevious->symbol][newSymbol]->pairRecord = make_shared<PairRecord>();
				(*activePairs)[symbolPrevious->symbol][newSymbol]->pairRecord->pair.leftSymbol = symbolPrevious->symbol;
				(*activePairs)[symbolPrevious->symbol][newSymbol]->pairRecord->pair.rightSymbol = newSymbol;

				tmpPairTracker->seenOnce = false;
			}
		}

		tmpPairTracker = (*activePairs)[newSymbol][symbolLeft->symbol];
		if (tmpPairTracker && tmpPairTracker->pairRecord) //if xa is not an active pair xA cannot be either, skip
		{
			tmpPairTracker = (*activePairs)[newSymbol][newSymbol];
			if (!tmpPairTracker)
			{
				(*activePairs)[newSymbol][newSymbol] = make_shared<PairTracker>();
				tmpPairTracker = (*activePairs)[newSymbol][newSymbol];
				tmpPairTracker->seenOnce = true;
			}
			else if (tmpPairTracker && tmpPairTracker->seenOnce) //xA will appear more than once, make it an active pair
			{
				(*activePairs)[newSymbol][newSymbol] = make_shared<PairTracker>();
				(*activePairs)[newSymbol][newSymbol]->pairRecord = make_shared<PairRecord>();
				(*activePairs)[newSymbol][newSymbol]->pairRecord->pair.leftSymbol = symbolPrevious->symbol;
				(*activePairs)[newSymbol][newSymbol]->pairRecord->pair.rightSymbol = newSymbol;

				tmpPairTracker->seenOnce = false;
			}
		}
	}
	if (symbolNext) //Ay
	{
		tmpPairTracker = (*activePairs)[symbolRight->symbol][symbolNext->symbol];
		if (tmpPairTracker && tmpPairTracker->pairRecord) //if xa is not an active pair xA cannot be either, skip
		{
			tmpPairTracker = (*activePairs)[newSymbol][symbolNext->symbol];
			if (!tmpPairTracker)
			{
				(*activePairs)[newSymbol][symbolNext->symbol] = make_shared<PairTracker>();
				tmpPairTracker = (*activePairs)[newSymbol][symbolNext->symbol];
				tmpPairTracker->seenOnce = true;
			}
			else if (tmpPairTracker && tmpPairTracker->seenOnce) //xA will appear more than once, make it an active pair
			{				
				(*activePairs)[newSymbol][symbolNext->symbol]->pairRecord = make_shared<PairRecord>();
				(*activePairs)[newSymbol][symbolNext->symbol]->pairRecord->pair.leftSymbol = newSymbol;
				(*activePairs)[newSymbol][symbolNext->symbol]->pairRecord->pair.rightSymbol = symbolNext->symbol;

				tmpPairTracker->seenOnce = false;
			}
		}
	}
}

void AlgorithmP::replaceInstanceOfPair(
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols,
	shared_ptr<SymbolRecord>& symbolLeft,
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext)
{
	
	shared_ptr<PairRecord> tmpPairRecord;
	shared_ptr<PairRecord> tmpPairRecordAdjacent;
	shared_ptr<PairTracker> tmpPairTracker;
	char newSymbol;

	//Step 2, decrement counts of xa and by
	if (symbolPrevious) //xa
	{
		tmpPairTracker = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];
		if (tmpPairTracker)
		{
			tmpPairRecordAdjacent = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol]->pairRecord;

			if (tmpPairRecordAdjacent)
				decrementCount(symbolPrevious, symbolLeft, activePairs, priorityQueue, tmpPairRecordAdjacent);
		}
		
	}
	
	if (symbolNext) //by
	{
		tmpPairTracker = (*activePairs)[symbolRight->symbol][symbolNext->symbol];
		if (tmpPairTracker)
		{
			tmpPairRecordAdjacent = (*activePairs)[symbolRight->symbol][symbolNext->symbol]->pairRecord;

			if (tmpPairRecordAdjacent &&																		//If Pair record exists
				!(symbolRight->symbol == symbolNext->symbol &&													//But it is not the case that the symbols are identical
				symbolRight->symbol == symbolLeft->symbol &&
				!(symbolRight->next && symbolRight->previous)))													//while not being part of a sequence of pairs 
				decrementCount(symbolRight, symbolNext, activePairs, priorityQueue, tmpPairRecordAdjacent);		//= the two symbols are not counted as a pair and should not be decreased
		}
	}

	//Step 3, replace ab, leaving xAy

	replacePair(symbolLeft, symbolRight, symbolNext, Symbols, dictionary, activePairs, sequenceArray);

	//Step 4, increase counts of xA and Ay
	if (symbolPrevious) //xA
	{
		tmpPairTracker = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol];		

		if (tmpPairTracker && tmpPairTracker->pairRecord)
		{
			//if (symbolPrevious->symbol == -117) //TEST
			//{
			//	bool b1 = symbolPrevious->symbol == symbolLeft->symbol && tmpPairRecord->count != 0;
			//	bool b2 = symbolPrevious->index > 0;
			//	bool b3 = symbolPrevious->index < sequenceArray->size();
			//	shared_ptr<SymbolRecord> s1 = (*sequenceArray)[symbolPrevious->index - 1];
			//	bool b4 = symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->symbol;
			//	bool b5 = (*sequenceArray)[symbolPrevious->index - 1]->symbol == '\0';
			//	shared_ptr<SymbolRecord> s6 = (*sequenceArray)[symbolPrevious->index - 5]->previous;
			//	shared_ptr<SymbolRecord> s5 = (*sequenceArray)[symbolPrevious->index - 4]->previous;
			//	shared_ptr<SymbolRecord> s4 = (*sequenceArray)[symbolPrevious->index - 3]->previous;
			//	shared_ptr<SymbolRecord> s3 = (*sequenceArray)[symbolPrevious->index - 2]->previous;
			//	shared_ptr<SymbolRecord> s2 = (*sequenceArray)[symbolPrevious->index - 1]->previous;
			//	bool b6 = symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->previous->symbol;
			//	bool b7 = !tmpPairRecord->skippedPair;
			//}
			tmpPairRecord = (*activePairs)[symbolPrevious->symbol][symbolLeft->symbol]->pairRecord;

			if (tmpPairRecord)
			{
				if (symbolPrevious->symbol == symbolLeft->symbol && tmpPairRecord->count != 0 &&				//If we have identical symbols which have been seen before
					symbolPrevious->index > 0 &&
					symbolPrevious->index < sequenceArray->size() &&
					(*sequenceArray)[symbolPrevious->index - 1] &&
					(symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->symbol ||			//and the previous symbol was also the same (meaning at least three in a row)
					((*sequenceArray)[symbolPrevious->index - 1]->symbol == '\0' &&
					(*sequenceArray)[symbolPrevious->index - 1]->previous &&
					symbolPrevious->symbol == (*sequenceArray)[symbolPrevious->index - 1]->previous->symbol)) &&
					!(*activePairs)[symbolPrevious->symbol][symbolLeft->symbol]->seenOnce)																//and we registered the last pair
				{
					(*activePairs)[symbolPrevious->symbol][symbolLeft->symbol]->seenOnce = true;															//Then skip this pair
				}
				else																							//else register pair as normal
				{
					(*activePairs)[symbolPrevious->symbol][symbolLeft->symbol]->seenOnce = false;

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
		}
	}
	if (symbolNext) //Ay
	{
		tmpPairTracker = (*activePairs)[symbolLeft->symbol][symbolNext->symbol];		

		if (tmpPairTracker && tmpPairTracker->pairRecord)
		{
			tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolNext->symbol]->pairRecord;

			if (tmpPairRecord)
			{
				tmpPairRecord = (*activePairs)[symbolLeft->symbol][symbolNext->symbol]->pairRecord;

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
	char empty = '\0';

	symbolLeft = (*sequenceArray)[sequenceIndex];
	symbolRight = (*sequenceArray)[sequenceIndex + 1];
	
	if ((symbolRight)->symbol == empty)
	{
		//tmpSymbol = *symbolRight;
		////Update threading counter - start
		//if (symbolRight->next->index + 1 < sequenceArray->size())
		//{
		//	symbolRight->next = (*sequenceArray)[symbolRight->next->index + 1];
		//	(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		//}			
		//else
		//	symbolRight->next = NULL;
		////(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		//if (symbolRight->next && (symbolRight->next)->symbol == empty)
		//{
		//	symbolRight->next = symbolRight->next->next;
		//	(*sequenceArray)[symbolRight->next->index - 1]->previous = symbolLeft;
		//}
		////Update threading counter - end
		symbolRight = symbolRight->next;
	}
		
	if (sequenceIndex > 0)
	{
		symbolPrevious = (*sequenceArray)[sequenceIndex - 1];
		if ((symbolPrevious)->symbol == empty)
			symbolPrevious = symbolPrevious->previous;
	}
	else
		symbolPrevious = NULL;

	if (symbolRight->index < sequenceArray->size()-1)
	{
		symbolNext = (*sequenceArray)[symbolRight->index + 1];
		if (symbolNext->symbol == empty)
			symbolNext = symbolNext->next;
	}
	else
		symbolNext = NULL;

	if (symbolLeft->symbol == empty || symbolRight->symbol == empty)
	{
		cout << "something is wrong!!" << endl;
		cout << "previous: " << symbolPrevious->symbol << endl;
		cout << "left: " << symbolLeft->symbol << endl;
		cout << "right: " << symbolRight->symbol << endl;
		cout << "next: " << symbolNext->symbol << endl;
		exit;
	}
}

void AlgorithmP::checkActivePairs(
	int sequenceIndex,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	unique_ptr<unsigned int>& Symbols)
{
	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
	auto symbolRight = make_shared<SymbolRecord>(); //b
	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
	auto symbolNext = make_shared<SymbolRecord>(); //y

	bool firstInstance = true;
	bool running = true;
	SymbolRecord symbolOld = *(*sequenceArray)[sequenceIndex];
	MyTest test;

	do
	{
		//Step 1, Establish context of xaby
		establishContext(symbolLeft, symbolRight, symbolPrevious, symbolNext, sequenceArray, sequenceIndex);

		checkActivePair(
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

void AlgorithmP::replaceAllPairs(
	int sequenceIndex,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, Pair>>& dictionary,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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

	checkActivePairs(
		sequenceIndex,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	do
	{
		//Step 1, Establish context of xaby
		establishContext(symbolLeft, symbolRight, symbolPrevious, symbolNext, sequenceArray, sequenceIndex);
		
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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