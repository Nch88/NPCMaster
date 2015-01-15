// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;





int _tmain(int argc, _TCHAR* argv[])
{
	unordered_map<char, string> dictionary;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;
	int Symbols = 65;
	
	Initializer init;
	AlgorithmP algP;
	Test test;
	
	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);
	
	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);

	test.Sequence("Original sequence", &sequenceArray);

	//See fig. 4, algprithm P
	algP.run(
		&sequenceArray,
		&dictionary,
		&activePairs,
		&priorityQueue,
		&Symbols);

	test.Sequence("Altered sequence", &sequenceArray);

	test.Dictionary("Dictionary", &dictionary);

	return 0;
}

