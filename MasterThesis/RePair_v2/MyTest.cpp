#include "stdafx.h"
#include "MyTest.h"


MyTest::MyTest()
{
}


MyTest::~MyTest()
{
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