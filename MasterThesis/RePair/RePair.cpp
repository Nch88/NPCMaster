// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

void TestSequence(string msg, vector<SymbolRecord*> * sequenceArray)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": ";
	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != (char) 0)
			ss << (*sequenceArray)[i]->symbol;
	}
	ss >> s;
	cout << s << endl << endl;
	//End Test
}

void TestSequenceWithIndex(string msg, vector<SymbolRecord*> * sequenceArray)
{
	//Test

	cout << msg << ": " << endl;
	for (int i = 0; i < sequenceArray->size(); i++)
	{
		cout << (*sequenceArray)[i]->symbol << " at: " << (*sequenceArray)[i]->index << endl;
	}
	cout << endl << endl;
	//End Test
}

void TestDictionary(string msg, unordered_map<char, string> * dictionary)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": " << endl;
	for (auto it = (*dictionary).cbegin(); it != (*dictionary).cend(); ++it)
	{
		cout << it->first << " --> " << it->second << endl;
	}
	cout << s << endl << endl;
	//End Test
}

void removeFromListInPriorityQueue(PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue)
{
	int index = tmpPairRecordAdjacent->count - 1;
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

void insertIntoListInPriorityQueue(int index, PairRecord * tmpPairRecord, vector<PairRecord*> * priorityQueue)
{
	int pQIndex = index;

	if ((*priorityQueue)[pQIndex] == NULL)
		(*priorityQueue)[pQIndex] = tmpPairRecord;
	else
	{
		(*priorityQueue)[pQIndex]->previousPair = tmpPairRecord;
		tmpPairRecord->nextPair = (*priorityQueue)[pQIndex];
		(*priorityQueue)[pQIndex] = tmpPairRecord;
	}
}

void managePriorityQueueDecrement(PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue)
{

	if (tmpPairRecordAdjacent->count == 1) //Remove from priority queue
	{
		removeFromListInPriorityQueue(tmpPairRecordAdjacent, priorityQueue);
	}
	//Remove from current priority queue entry and add to one lower
	else if (tmpPairRecordAdjacent->count > 1 && tmpPairRecordAdjacent->count < priorityQueue->size() - 1)
	{
		removeFromListInPriorityQueue(tmpPairRecordAdjacent, priorityQueue);

		insertIntoListInPriorityQueue(
			tmpPairRecordAdjacent->count - 1,
			tmpPairRecordAdjacent,
			priorityQueue);
	}
}

void replaceInstanceOfPair(
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
	stringstream ss;
	string tmpPair;
	PairRecord * tmpPairRecordAdjacent;
	PairRecord * tmpPairRecord;
	char newSymbol;

	//Step 2, decrement counts of xa and by
	if (!firstPair) //xa
	{
		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();

		tmpPairRecordAdjacent = &(*activePairs)[tmpPair];
		tmpPairRecordAdjacent->count--;

		managePriorityQueueDecrement(tmpPairRecordAdjacent, priorityQueue);
		if (tmpPairRecordAdjacent->count == 0)
			activePairs->erase(tmpPairRecordAdjacent->pair);

		
	}
	if (!lastPair) //by
	{
		ss << symbolRight->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();

		tmpPairRecordAdjacent = &(*activePairs)[tmpPair];
		tmpPairRecordAdjacent->count--;

		managePriorityQueueDecrement(tmpPairRecordAdjacent, priorityQueue);
		if (tmpPairRecordAdjacent->count == 0)
			activePairs->erase(tmpPairRecordAdjacent->pair);
	}

	//Step 3, replace ab, leaving xAy
	newSymbol = (char)(*Symbols);
	ss << symbolLeft->symbol << symbolRight->symbol;
	ss >> tmpPair;
	ss.clear();

	(*dictionary)[newSymbol] = tmpPair;
	symbolLeft->symbol = newSymbol;
	symbolRight->symbol = (char)0;

	symbolRight->next = symbolNext;
	symbolRight->previous = symbolLeft;

	//Step 4, increase counts of xA and Ay
	if (!firstPair) //xA
	{
		ss << symbolPrevious->symbol << symbolLeft->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecord = &(*activePairs)[tmpPair];
		tmpPairRecord->count++;
		tmpPairRecord->pair = tmpPair;

		if (tmpPairRecord->count == 1) //New pair
		{
			tmpPairRecord->previousPair = NULL;
			tmpPairRecord->nextPair = NULL;
		}

		if (tmpPairRecord->count == 2) //Insert into priority queue					
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
	if (!lastPair) //Ay
	{
		ss << symbolRight->symbol << symbolNext->symbol;
		ss >> tmpPair;
		ss.clear();
		tmpPairRecord = &(*activePairs)[tmpPair];
		tmpPairRecord->count++;
		tmpPairRecord->pair = tmpPair;

		if (tmpPairRecord->count == 1) //New pair
		{
			tmpPairRecord->previousPair = NULL;
			tmpPairRecord->nextPair = NULL;
		}

		if (tmpPairRecord->count == 2) //Insert into priority queue					
			insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
		//Move up in priority queue
		else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
		{
			removeFromListInPriorityQueue(tmpPairRecord, priorityQueue);
			insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
		}
	}
}

void replaceAllPairs(
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

	do
	{
		if (!firstInstance)		
			sequenceIndex = (*symbolLeft->next).index;
		firstInstance = false;
		

		//Step 1, Establish context of xaby
		firstPair = sequenceIndex == 0;
		lastPair = sequenceIndex == sequenceArray->size() - 2;

		symbolLeft = (*sequenceArray)[sequenceIndex];
		symbolRight = (*sequenceArray)[sequenceIndex + 1];
		if (!firstPair)
		{
			symbolPrevious = (*sequenceArray)[sequenceIndex - 1];
			if (symbolPrevious->symbol == (char)0)
				symbolPrevious = symbolPrevious->next;
		}

		if (!lastPair)
		{
			symbolNext = (*sequenceArray)[sequenceIndex + 2];
			if (symbolNext->symbol == (char)0)
				symbolNext = symbolNext->next;
		}

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

	} while (symbolLeft->next != NULL);	
}

int _tmain(int argc, _TCHAR* argv[])
{
	unordered_map<char, string> dictionary;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;
	int Symbols = 65;
	
	Initializer init;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);
	
	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);

	TestSequence("Original sequence", &sequenceArray);

	PairRecord* tmpPairRecord;
	PairRecord* tmpPairRecordSelected;
	int sequenceIndex;
	cout << "Sequence index line 305" << endl;

	while (priorityQueue[priorityQueue.size() - 1] != NULL)
	{		
		tmpPairRecordSelected = priorityQueue[priorityQueue.size() - 1];
		//Find pair with most occurences
		do
		{
			tmpPairRecord = priorityQueue[priorityQueue.size() - 1];
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		} while (tmpPairRecord->nextPair != NULL);
		
		sequenceIndex = tmpPairRecord->arrayIndexFirst;

		replaceAllPairs(
			sequenceIndex,
			&sequenceArray,
			&dictionary,
			&activePairs,
			&priorityQueue,
			&Symbols);
		Symbols++;
	}	

	for (int i = priorityQueue.size() - 2; i >= 0; i--)
	{
		while (priorityQueue[i] != NULL)
		{
			//See fig. 4, algprithm P
				
			tmpPairRecord = priorityQueue[i];

			while (tmpPairRecord->nextPair != NULL)			
				tmpPairRecord = tmpPairRecord->nextPair;
			
				
			sequenceIndex = tmpPairRecord->arrayIndexFirst;

			replaceAllPairs(
				sequenceIndex,
				&sequenceArray,
				&dictionary,
				&activePairs,
				&priorityQueue,
				&Symbols);
			Symbols++;

			//Remove current pair from priority queue and active pairs
			if (tmpPairRecord->nextPair != NULL)
				priorityQueue[i] = tmpPairRecord->nextPair;
			else
				priorityQueue[i] = NULL;
			activePairs.erase(tmpPairRecord->pair);

			TestSequence("Altered sequence", &sequenceArray);
		}
		
	}

	TestSequence("Altered sequence", &sequenceArray);

	TestDictionary("Dictionary", &dictionary);

	return 0;
}

