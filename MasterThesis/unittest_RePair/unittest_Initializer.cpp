#include "gtest\gtest.h"
#include "RePair\stdafx.h"

using namespace std;


TEST(testInitializer, initSequenceArray)
{
	Initializer init;
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();

	init.SequenceArray("diddy.txt", sequenceArray, activePairs);

	ASSERT_EQ(39, sequenceArray->size());
	ASSERT_EQ(6, (*activePairs)[".d"]->count);
}

TEST(testInitializer, initPriorityQueue)
{
	Initializer init;
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();

	init.SequenceArray("diddy.txt", sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);

	ASSERT_EQ(6, (*priorityQueue)[4]->count);
}