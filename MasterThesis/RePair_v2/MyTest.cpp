#include "stdafx.h"
#include "MyTest.h"


MyTest::MyTest()
{
}


MyTest::~MyTest()
{
}

int MyTest::SanityCheck(
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue, unordered_map<unsigned int,
	unordered_map<unsigned int, PairTracker >> &activePairs)
{
	return SanityCheckThreadingPointers(sequenceArray) + SanityCheckPairRecords(priorityQueue, activePairs);
}

int MyTest::SanityCheckThreadingPointers(vector<SymbolRecord*> & sequenceArray)
{
	bool sane = true;
	for (int i = 0; i < sequenceArray.size(); i++)//each (SymbolRecord* p in sequenceArray)
	{
		SymbolRecord* p = sequenceArray[i];
		if (p->next)
			sane = sane && (p->next->index > p->index) && (p->symbol == 0 || p->symbol == p->next->symbol);
		if (p->previous)
			sane = sane && (p->previous->index < p->index) && (p->symbol == 0 || p->symbol == p->previous->symbol);
		if (p->symbol == 0 && ((i>0 && sequenceArray[i-1]->symbol != 0)||((i<sequenceArray.size()-1) && sequenceArray[i+1]->symbol != 0)))
		//If this is an empty symbol next to a non-empty symbol
		{
			if (p->next)
			{
				sane = sane && (p->next->symbol != 0);
				for (int j = i + 1; j < p->next->index; j++)
					sane = sane && (sequenceArray[j]->symbol == 0);
			}
			if (p->previous)
			{
				sane = sane && (p->previous->symbol != 0);
				for (int j = p->previous->index + 1; j < i; j++)
					sane = sane && (sequenceArray[j]->symbol == 0);
			}
		}
	}
	if (!sane)
		return 100;
	return 0;
}

int MyTest::SanityCheckPairRecords(vector<PairRecord*>& priorityQueue, unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs)
{
	bool sane = true;
	int result = 0;
	//Check priority queue
	for (int i = 0; i < priorityQueue.size(); i++)
	{
		if (priorityQueue[i])
		{
			PairRecord* current = priorityQueue[i];
			while (current->nextPair)
			{
				sane = sane && current->count == i + 2 && (current->arrayIndexFirst < current->arrayIndexLast);
				current = current->nextPair;
			}
		}
	}
	if (!sane)
		result = 10;
	sane = true;
	//Check active pairs
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>::iterator iterone;
	unordered_map<unsigned int, PairTracker>::iterator itertwo;
	for (iterone = activePairs.begin(); iterone != activePairs.end(); iterone++)
	{
		for (itertwo = iterone->second.begin(); itertwo != iterone->second.end(); itertwo++)
		{
			if (itertwo->second.pairRecord)
				sane = (itertwo->second.pairRecord->count > 1);
		}
	}
	if (!sane)
		result += 1;
	return result;
}

void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, long numbers[], int count)
{
	for (int i = 0; i < count; i++)
	{
		SymbolRecord * p = new SymbolRecord(numbers[i], i);
		sequenceArray.push_back(p);
	}
}

void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, string input, int size)
{
	long * numbers = new long[size];
	for (int i = 0; i < size; i++)
	{
		numbers[i] = (long)input[i];
	}
	buildSequenceArray(sequence, numbers, size);
}

string MyTest::SequenceToCompleteString(vector<SymbolRecord*> & sequenceArray)
{
	string s;

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		s += (char)sequenceArray[i]->symbol;
	}
	return s;
}

string MyTest::SequenceToString(vector<SymbolRecord*> & sequenceArray)
{
	//Test
	string s;

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i]->symbol != (char)0)
			s += (char)sequenceArray[i]->symbol;
	}
	return s;
	//End Test
}

void MyTest::ActivePairs(string msg, unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs)
{
	cout << msg << ": ";
	for each (auto leftSymbol in activePairs)
	{
		for each (auto pair in leftSymbol.second)
		{
			cout << leftSymbol.first << pair.first << " ";
		}
	}
	cout << endl << endl;
}

bool MyTest::inPriorityQueue(
	PairRecord * pairRecord,
	vector<PairRecord*> & priorityQueue)
{
	PairRecord * tmpPairRecord;

	for (int i = 0; i < priorityQueue.size(); i++)
	{
		tmpPairRecord = priorityQueue[i];

		while (tmpPairRecord)
		{
			if (pairRecord == tmpPairRecord)
				return true;
			tmpPairRecord = tmpPairRecord->nextPair;
		}
	}
	return false;
}

bool MyTest::inPriorityQueueAtPosition(
	PairRecord * pairRecord,
	vector<PairRecord*> & priorityQueue,
	long index)
{
	PairRecord * tmpPairRecord;

	
	tmpPairRecord = priorityQueue[index];

	while (tmpPairRecord)
	{
		if (pairRecord == tmpPairRecord)
			return true;
		tmpPairRecord = tmpPairRecord->nextPair;
	}
	
	return false;
}