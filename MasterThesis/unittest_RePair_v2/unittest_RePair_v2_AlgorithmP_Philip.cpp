//#include "gtest\gtest.h"
//#include "RePair_v2\stdafx.h"
//
//using namespace std;
//
//MyTest mtest;
//
//TEST(compaction, diddy)
//{
//	using namespace google;
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unsigned long symbols;
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//
//	string input1 = "diddy.txt";
//
//	bool skip = false;
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//
//	string filename = input1;
//	ifstream file(filename);
//
//	unordered_set<unsigned long> terminals;
//
//	init.SequenceArray(
//		c,
//		file,
//		blockSize,
//		activePairs,
//		sequenceArray);
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//	priorityQueue.resize(priorityQueueSize);
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//	priorityQueue[4] = nullptr;
//
//	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
//
//	algP.replaceAllPairs(7, sequenceArray, activePairs, priorityQueue, symbols, c);
//
//	string expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', '_', 'o', '.', 'w', 'a', 'h', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'u', 'm', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'o' };
//
//	string result = mtest.SequenceToCompleteString(sequenceArray);
//
//	for (int i = 0; i < expected.size(); ++i)
//	{
//		if (expected[i] == 'A')
//			ASSERT_EQ(symbols, sequenceArray[i]->symbol);
//		else if (expected[i] == '_')
//			ASSERT_EQ(0, sequenceArray[i]->symbol);
//		else
//			ASSERT_EQ(expected[i], sequenceArray[i]->symbol);
//	}
//	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
//
//	//Setup complete, we can now test compaction
//	algP.compact(sequenceArray, activePairs, priorityQueue);
//
//	expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', 'o', '.', 'w', 'a', 'h', 'A', 'i', 'd', 'd', 'y', 'A', 'i', 'd', 'd', 'y', 'A', 'u', 'm', 'A', 'i', 'd', 'd', 'y', 'A', 'o'};
//	result = mtest.SequenceToCompleteString(sequenceArray);
//
//	for (int i = 0; i < expected.size(); ++i)
//	{
//		if (expected[i] == 'A')
//			ASSERT_EQ(symbols, sequenceArray[i]->symbol);
//		else
//			ASSERT_EQ(expected[i],sequenceArray[i]->symbol);
//	}
//
//	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
//}
//
////TEST(compaction, compactingAfterEachNewSymbol_diddy)
////{
////	using namespace google;
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	AlgorithmP algP;
////
////	string input1 = "diddy.txt";
////
////	bool skip = false;
////
////	int priorityQueueSize;
////	int blockSize;
////	blockSize = 1048576;
////
////	string filename = input1;
////	ifstream file(filename);
////
////	unordered_set<unsigned long> terminals;
////
////	init.SequenceArray(
////		c,
////		file,
////		blockSize,
////		activePairs,
////		sequenceArray);
////
////	priorityQueueSize = sqrt(sequenceArray.size());
////	priorityQueue.resize(priorityQueueSize);
////	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
////
////	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
////	string diddy2 = "singingAo.wahAiddyAiddyAumAiddyAo";
////	string diddy3 = "singingAo.wahAiddBiddBumAiddBo";
////
////	int count = 0;
////
////	//Compaction counters
////	CompactionData cData(1);
////
////	for (long i = priorityQueue.size() - 2; i >= 0; i--)
////	{
////		while (priorityQueue[i])
////		{
////			algP.manageOneEntryOnList(
////				i,
////				sequenceArray,
////				activePairs,
////				priorityQueue,
////				symbols,
////				cData,
////				c);
////
////			ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
////			algP.compact(sequenceArray, activePairs, priorityQueue);
////			ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
////		}
////
////		ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
////	}
////	string s = mtest.SequenceToString(sequenceArray);
////	int x = 0;
////
////	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
////}
//
////TEST(compaction, compactingAfterEachNewSymbol_ecoli)
////{
////	string filename;
////	int blockSize;
////	blockSize = 1048576;
////
////	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	dense_hash_map<long, Pair> dictionary;
////	long symbols(256);
////	
////	
////
////	Initializer init;
////	Conditions c;
////	c.timing = false;
////	AlgorithmP algP;
////	MyTest t;
////	int priorityQueueSize;
////
////	filename = "E.coli";
////
////	ifstream file(filename);
////
////	if (file.is_open())
////	{
////		while (file.is_open())
////		{			
////			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
////
////			priorityQueueSize = sqrt(sequenceArray.size());
////			priorityQueue.resize(priorityQueueSize);
////			init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
////			
////			
////			algP.run(sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);
////
////			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
////			algP.compact(sequenceArray, activePairs, priorityQueue);
////			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
////
////
////			init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
////		}
////	}
////	else
////	{
////		cout << "Problem opening file: " << filename << endl;
////	}	
////}
//
//TEST(compaction, findNextEmpty)
//{
//	vector<SymbolRecord*> sequenceArray;
//	AlgorithmP algP;
//
//	unsigned long a[] = { 97, 0, 98, 0, 0, 99, 100, 0, 101, 102, 103, 0 };
//	mtest.buildSequenceArray(sequenceArray, a, 12);
//	SymbolRecord *sr = sequenceArray[0];
//
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(1, sr->index);
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(3, sr->index);
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(4, sr->index);
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(7, sr->index);
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(11, sr->index);
//	sr = algP.findNextEmpty(sequenceArray, sr);
//	ASSERT_EQ(nullptr, sr);
//}
//
//TEST(compaction, calculateCompactionTime)
//{
//	AlgorithmP algo;
//	long size = 100;
//	int result;
//	int count = 1;
//	CompactionData cData(size);
//	ASSERT_EQ(25, cData.compactTotal);
//	cData.updateCompactTotal();
//	ASSERT_EQ(44, cData.compactTotal);
//	cData.updateCompactTotal();
//	ASSERT_EQ(59, cData.compactTotal);
//	cData.updateCompactTotal();
//	ASSERT_EQ(70, cData.compactTotal);
//}
//
////TEST(compaction, completeRunWithCompaction_world)
////{
////	string filename;
////	int blockSize;
////	blockSize = 1048576;
////
////	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	dense_hash_map<long, Pair> dictionary;
////	long symbols(256);
////
////	Initializer init;
////	Conditions c;
////	c.compact = true;
////	c.timing = false;
////	CompactionData cData(sequenceArray.size());
////	AlgorithmP algP;
////	MyTest t;
////	int priorityQueueSize;
////
////	filename = "world192.txt";
////
////	ifstream file(filename);
////
////	if (file.is_open())
////	{
////		while (file.is_open())
////		{
////			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
////
////			priorityQueueSize = sqrt(sequenceArray.size());
////			priorityQueue.resize(priorityQueueSize);
////			init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
////
////			if (t.SanityCheck(sequenceArray, priorityQueue, activePairs))
////				cout << t.SanityCheckPairRecordsDetailed(sequenceArray, priorityQueue);
////
////			algP.run(sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);
////
////			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
////
////			init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
////		}
////	}
////	else
////	{
////		cout << "Problem opening file: " << filename << endl;
////	}
////}
//
//
