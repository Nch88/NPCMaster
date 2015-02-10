#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

MyTest mytest;

TEST(setup, diddy)
{
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	char a[] = { 's', 'i', 'n', 'g', 'i', 'n', 'g', '.', 'd', 'o', '.', 'w', 'a', 'h', '.', 'd', 'i', 'd', 'd', 'y', '.', 'd', 'i', 'd', 'd', 'y', '.', 'd', 'u', 'm', '.', 'd', 'i', 'd', 'd', 'y', '.', 'd', 'o' };
	mytest.charArrayToSequence(sequenceArray, a, 200);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	algP.replaceAllPairs(7, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	string expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', '\0', 'o', '.', 'w', 'a', 'h', 'A', '\0', 'i', 'd', 'd', 'y', 'A', '\0', 'i', 'd', 'd', 'y', 'A', '\0', 'u', 'm', 'A', '\0', 'i', 'd', 'd', 'y', 'A', '\0', 'o' };

	MyTest mytest;
	string result = mytest.SequenceToCompleteString(sequenceArray);

	ASSERT_EQ(expected, result);
}