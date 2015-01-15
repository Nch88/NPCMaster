#include "stdafx.h"
#include "Test.h"


Test::Test()
{
}


Test::~Test()
{
}

void Test::Sequence(string msg, unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray)
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

void Test::SequenceWithIndex(string msg, unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray)
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

void Test::Dictionary(string msg, unique_ptr<unordered_map<char, string>>& dictionary)
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

void Test::PriorityQueueSpecificCount(
	string msg, 
	unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
	int i)
{
	//Test
	stringstream ss;
	string s;
	PairRecord * tmpRecord;

	cout << msg << ": " << endl;
	if ((*priorityQueue)[i])
	{
		tmpRecord = (*priorityQueue)[i];
		do
		{
			s += tmpRecord->pair + " ";
			tmpRecord = tmpRecord->nextPair;
		} while (tmpRecord);
	}
	else
	{
		s = "empty";
	}
	cout << s << endl << endl;
	//End Test
}

void Test::Context(
	string msg,
	SymbolRecord* symbolLeft,
	SymbolRecord* symbolRight,
	SymbolRecord* symbolPrevious,
	SymbolRecord* symbolNext)
{
	//Test
	stringstream ss;
	string s;

	cout << msg << ": " << endl;
	ss << symbolPrevious->symbol << symbolLeft->symbol << symbolRight->symbol << symbolNext->symbol;
	ss >> s;
	cout << s << endl << endl;
	//End Test
}