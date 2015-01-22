// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	auto dictionary = make_unique<unordered_map<unsigned int, Pair>>();
	auto activePairs = make_unique<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<unsigned int>(256);

	bool verbose = true;
	bool extraVerbose = false;
	bool timer = true;

	MyTimer t;
			
	Initializer init;
	AlgorithmP algP;
	MyTest test;
	Outputter out;
	Conditions c(verbose, extraVerbose, timer);

	string input1 = "diddy.txt";
	string input2 = "duplicates.txt";
	string input3 = "world192.txt";
	string input4 = "bible.txt";
	string input5 = "E.coli";
	string input6 = "duplicatesLong.txt";
	string input7 = "duplicatesLong2.txt";
	string input8 = "duplicatesLong3.txt";
	string input9 = "duplicatesLong4.txt";

	string input = input5;	

	init.SequenceArray(input, sequenceArray, activePairs,c );
	
	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);	

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
	//See fig. 4, algorithm P
	if (c.verbose)
	{
		cout << "Running Re-Pair compression algorithm" << endl;
	}
	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);
	
	out.compressedFile(input, sequenceArray);
	out.dictionary(input, dictionary);

	return 0;
}

