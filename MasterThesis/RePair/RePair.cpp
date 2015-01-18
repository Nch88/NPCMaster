// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;





int _tmain(int argc, _TCHAR* argv[])
{
	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);
	
	Initializer init;
	AlgorithmP algP;
	MyTest test;
	Outputter out;

	string input = "diddy.txt";
	string input2 = "test.txt";
	string input3 = "world192.txt";
	
	init.SequenceArray(input3, sequenceArray, activePairs);

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
		Symbols);
	
	out.compressedFile(input, sequenceArray);
	out.dictionary(input, dictionary);

	return 0;
}

