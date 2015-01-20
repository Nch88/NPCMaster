#include "gtest\gtest.h"
#include "RePair\stdafx.h"

using namespace std;


//TEST(testInitializer, initSequenceArrayDuplicates)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("duplicates.txt", sequenceArray, activePairs);
//
//	ASSERT_EQ(8, sequenceArray->size());
//	ASSERT_EQ(2, (*activePairs)["aa"]->count);
//	ASSERT_EQ(2, (*activePairs)["bb"]->count);
//}
//
//TEST(testInitializer, initSequenceArrayDuplicates2)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("duplicates2.txt", sequenceArray, activePairs);
//
//	ASSERT_EQ(9, sequenceArray->size());
//	ASSERT_EQ(2, (*activePairs)["aa"]->count);
//	ASSERT_EQ(2, (*activePairs)["bb"]->count);
//	ASSERT_EQ(1, (*activePairs)["ab"]->count);
//}
//
//TEST(testInitializer, initSequenceArrayDuplicates3)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("duplicates3.txt", sequenceArray, activePairs);
//
//	ASSERT_EQ(8, sequenceArray->size());
//	ASSERT_EQ(2, (*activePairs)["aa"]->count);
//	ASSERT_EQ(2, (*activePairs)["bb"]->count);
//	ASSERT_EQ(1, (*activePairs)["ab"]->count);
//	ASSERT_EQ(1, (*activePairs)["ba"]->count);
//}
//
//TEST(testInitializer, initSequenceArrayDuplicatesLong)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("duplicatesLong.txt", sequenceArray, activePairs);
//
//	ASSERT_EQ(38, sequenceArray->size());
//	ASSERT_EQ(17, (*activePairs)["aa"]->count);
//	ASSERT_EQ(2, (*activePairs)["bb"]->count);
//}
//
//TEST(testInitializer, initPriorityQueueDuplicates)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("duplicatesLong.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	ASSERT_EQ(6, (*priorityQueue).size());
//
//	ASSERT_EQ(17, (*priorityQueue)[5]->count);
//}
//
TEST(testInitializer, initSequenceArray)
{
	Initializer init;
	auto activePairs = make_unique<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto symbolMap = make_unique<unordered_map<char, bool>>();

	init.SequenceArray("diddy.txt", sequenceArray, activePairs, symbolMap);

	ASSERT_EQ(39, sequenceArray->size());
	ASSERT_EQ(6, (*activePairs)['.']['d']->pairRecord->count);
}
//
//
//
//TEST(testInitializer, initPriorityQueue)
//{
//	Initializer init;
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	ASSERT_EQ(6, (*priorityQueue)[4]->count);
//}