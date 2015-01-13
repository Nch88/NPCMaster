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



int _tmain(int argc, _TCHAR* argv[])
{
	unordered_map<char, string> dictionary;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;
	int Symbols = 65;
	
	Initializer init;
	AlgorithmP algP;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);
	
	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);

	TestSequence("Original sequence", &sequenceArray);

	//See fig. 4, algprithm P
	algP.run(
		&sequenceArray,
		&dictionary,
		&activePairs,
		&priorityQueue,
		&Symbols);

	TestSequence("Altered sequence", &sequenceArray);

	TestDictionary("Dictionary", &dictionary);

	return 0;
}

