#include "stdafx.h"
#include "MyTest.h"

using namespace std;

MyTest::MyTest()
{
}


MyTest::~MyTest()
{
}

void MyTest::Sequence(string msg, unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": ";
	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != (char)0)
			ss << (*sequenceArray)[i]->symbol;
	}
	ss >> s;
	cout << s << endl << endl;
	//End Test
}

string MyTest::SequenceToString(unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
{
	//Test
	stringstream ss;
	string s;

	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != (char)0)
			s += (*sequenceArray)[i]->symbol;
	}
	return s;
	//End Test
}

void MyTest::SequenceWithIndex(string msg, unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": " << endl;
	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != (char)0)
			cout << (*sequenceArray)[i]->symbol << " at: " << (*sequenceArray)[i]->index << endl;
	}
	cout << endl << endl;
	//End Test
}

void MyTest::Dictionary(string msg, unique_ptr<unordered_map<char, Pair>>& dictionary)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": " << endl;
	for each (auto pair in (*dictionary))
	{
		cout << pair.first << " -> " << pair.second.leftSymbol << pair.second.rightSymbol << ", ";
	}
	cout << s << endl << endl;
	//End Test
}

void MyTest::ActivePairs(string msg, unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs)
{
	cout << msg << ": ";
	for each (auto leftSymbol in (*activePairs))
	{
		for each (auto pair in leftSymbol.second)
		{
			cout << leftSymbol.first << pair.first << " ";
		}
	}
	cout << endl << endl;
}

void MyTest::ActivePairsDetails(string msg, unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs)
{
	cout << msg << ": ";
	for each (auto leftSymbol in (*activePairs))
	{
		for each (auto pair in leftSymbol.second)
		{
			cout << "\'" << leftSymbol.first << pair.first << " " << pair.second->pairRecord->count << "\' ";
		}
	}
	cout << endl << endl;
}

void MyTest::PriorityQueue(string msg, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
{
	cout << msg << ": " << endl;
	auto tmpP = make_shared<PairRecord>();
	for (int i = 0; i < priorityQueue->size(); i++)
	{
		tmpP = (*priorityQueue)[i];
		cout << "Count " << i+2 << ": ";
		while (tmpP)
		{
			cout << tmpP->pair.leftSymbol << tmpP->pair.rightSymbol << " ";
			tmpP = tmpP->nextPair;
		}
		cout << endl << endl;
	}
}

void MyTest::Context(
	string msg, 
	shared_ptr<SymbolRecord>& symbolLeft, 
	shared_ptr<SymbolRecord>& symbolRight,
	shared_ptr<SymbolRecord>& symbolPrevious,
	shared_ptr<SymbolRecord>& symbolNext)
{
	cout << msg << ": ";

	cout << symbolPrevious->symbol;
	cout << symbolLeft->symbol;
	cout << symbolRight->symbol;
	cout << symbolNext->symbol;
	cout << endl << endl;
}