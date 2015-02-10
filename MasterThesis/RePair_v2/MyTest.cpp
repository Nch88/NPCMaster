#include "stdafx.h"
#include "MyTest.h"


MyTest::MyTest()
{
}


MyTest::~MyTest()
{
}

void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, char input[], int size)
{
	for (int i = 0; i < size; i++)
	{
		long number = (long)input[i];
		SymbolRecord * p = new SymbolRecord(number, i);
		sequence.push_back(p);
	}
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