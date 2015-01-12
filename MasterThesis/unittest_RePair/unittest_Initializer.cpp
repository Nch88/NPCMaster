#include "gtest\gtest.h"
#include "RePair\stdafx.h"

using namespace std;


TEST(testInitializer, initSequenceArray)
{
	Initializer init;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	ASSERT_EQ(39, sequenceArray.size());
	ASSERT_EQ(6, activePairs[".d"].count);
}

TEST(testInitializer, initPriorityQueue)
{
	Initializer init;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);

	ASSERT_EQ(6, priorityQueue[4]->count);
}