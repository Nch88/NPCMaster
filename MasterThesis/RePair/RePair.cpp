// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	auto dictionary = make_unique<unordered_map<char, Pair>>();
	auto activePairs = make_unique<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<unsigned int>(127);
	auto symbolMap = make_unique<unordered_map<char, bool>>();

	
	Initializer init;
	AlgorithmP algP;
	MyTest test;
	Outputter out;

	string input1 = "diddy.txt";
	string input2 = "test.txt";
	string input3 = "world192.txt";
	string input4 = "bible.txt";
	string input5 = "E.coli";

	string input = input3;
	
	init.SequenceArray(input, sequenceArray, activePairs, symbolMap);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
	
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	//See fig. 4, algorithm P
	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		symbolMap);
	
	out.compressedFile(input, sequenceArray);
	out.dictionary(input, dictionary);

	return 0;
}

