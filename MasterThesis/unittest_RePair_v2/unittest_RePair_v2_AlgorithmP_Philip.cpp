#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

MyTest mtest;

TEST(compaction, diddy)
{
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
	priorityQueue[4] = nullptr;

	algP.replaceAllPairs(7, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	string expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', '_', 'o', '.', 'w', 'a', 'h', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'u', 'm', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'o' };

	string result = mtest.SequenceToCompleteString(sequenceArray);

	ASSERT_EQ(expected, result);
	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));

	//Setup complete, we can now test compaction
	algP.compact(sequenceArray, activePairs, priorityQueue);

	expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', 'o', '.', 'w', 'a', 'h', 'A', 'i', 'd', 'd', 'y', 'A', 'i', 'd', 'd', 'y', 'A', 'u', 'm', 'A', 'i', 'd', 'd', 'y', 'A', 'o'};
	result = mtest.SequenceToCompleteString(sequenceArray);

	ASSERT_EQ(expected, result);
	ASSERT_EQ(0, mtest.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(compactingAfterEachNewSymbol, diddy)
{
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string diddy2 = "singingAo.wahAiddyAiddyAumAiddyAo";
	string diddy3 = "singingAo.wahAiddBiddBumAiddBo";

	int count = 0;

	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		while (priorityQueue[i])
		{
			algP.manageOneEntryOnList(
				i,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				symbols,
				c);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			algP.compact(sequenceArray, activePairs, priorityQueue);
			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}

		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
	}
	string s = t.SequenceToString(sequenceArray);
	int x = 0;

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

//TEST(compactingAfterEachNewSymbol, ecoli)
//{
//	string filename;
//	int blockSize;
//	blockSize = 1048576;
//
//	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unordered_map<unsigned int, Pair> dictionary;
//	unsigned int symbols(256);
//	
//	
//
//	Initializer init;
//	Conditions c;
//	c.timing = false;
//	AlgorithmP algP;
//	MyTest t;
//	int priorityQueueSize;
//
//	filename = "E.coli";
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		while (file.is_open())
//		{			
//			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//			priorityQueueSize = sqrt(sequenceArray.size());
//			priorityQueue.resize(priorityQueueSize);
//			init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//			
//			
//			init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//	}	
//}