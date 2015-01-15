#include "stdafx.h"
#include "Test.h"


Test::Test()
{
}


Test::~Test()
{
}

void Test::Sequence(string msg, vector<SymbolRecord*> * sequenceArray)
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

void Test::SequenceWithIndex(string msg, vector<SymbolRecord*> * sequenceArray)
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

void Test::Dictionary(string msg, unordered_map<char, string> * dictionary)
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