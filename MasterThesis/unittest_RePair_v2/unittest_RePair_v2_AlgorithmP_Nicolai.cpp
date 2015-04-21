#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(manageOneList, oneEntry)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

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

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	long index = 4;

	CompactionData cData(1);

	algP.manageOneList(
		index,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		cData,
		c);

	ASSERT_EQ(nullptr, priorityQueue[index]);
	MyTest mt;
	ASSERT_EQ(0, mt.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(manageOneList, multipleEntries)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

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

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	long index = 1;

	CompactionData cData(1);

	algP.manageOneList(
		index,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		cData,
		c);

	ASSERT_EQ(nullptr, priorityQueue[index]);
	MyTest mt;
	ASSERT_EQ(0, mt.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

//TEST(replaceAllPairsThorough, diddy)
//{
//	using namespace google;
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	dense_hash_map<long, Pair> dictionary;
//	dictionary.set_empty_key(-1);
//	dictionary.set_deleted_key(-2);
//	long Symbols(65);//A
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//	MyTest t;
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
//	unordered_set<long> terminals;
//
//	init.SequenceArray(
//		c,
//		file,
//		blockSize,
//		activePairs,
//		sequenceArray,
//		terminals);
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//	priorityQueue.resize(priorityQueueSize);
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
//	string diddy2 = "singingAo.wahAiddyAiddyAumAiddyAo";
//	string diddy3 = "singingAo.wahBddyBddyAumBddyAo";
//
//	int sequenceIndex = 7;
//	int count = 0;
//
//	long indexSymbolLeft = -1;
//	long indexSymbolRight = -1;
//	long indexSymbolPrevious = -1;
//	long indexSymbolPreviousPrevious = -1;
//	long indexSymbolNext = -1;
//
//	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
//	if (activePairs[100].empty())
//	{
//		activePairs[100].set_empty_key(-1);
//		activePairs[100].set_deleted_key(-2);
//	}
//		
//	PairRecord * tmpPairRecord0 = activePairs[100][111].pairRecord;
//
//	ASSERT_TRUE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));
//
//	//Remove .d pair record from priority queue
//	priorityQueue[4] = nullptr;
//
//	do
//	{
//		sequenceIndex = nextSymbol->index;
//		nextSymbol = nextSymbol->next;
//
//		algP.establishContext(
//			indexSymbolLeft,
//			indexSymbolRight,
//			indexSymbolPrevious,
//			indexSymbolNext,
//			sequenceIndex,
//			sequenceArray);	
//
//		//Replace instance of pair
//
//		if (count == 2)
//		{
//			//y. at 19
//			tmpPairRecord0 = activePairs[121][46].pairRecord;
//		}
//
//		//Decrement count of xa
//		algP.decrementCountLeft(
//			indexSymbolPreviousPrevious,
//			indexSymbolPrevious,
//			indexSymbolLeft,
//			indexSymbolRight,
//			activePairs,
//			sequenceArray,
//			priorityQueue,
//			Symbols,
//			c);
//
//		if (count == 0)
//		{
//			//g. is not an active pair, nothing happens
//			//do at 8
//			tmpPairRecord0 = activePairs[100][111].pairRecord;
//		}
//		if (count == 1)
//		{
//			//h. is not an active pair, nothing happens
//			//di at 15
//			tmpPairRecord0 = activePairs[100][105].pairRecord;
//		}
//		if (count == 2)
//		{
//			//y. at 19
//			ASSERT_EQ(2, activePairs[121][46].pairRecord->count);
//			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
//			ASSERT_EQ(nullptr, sequenceArray[19]->next);
//			ASSERT_EQ(nullptr, sequenceArray[25]->previous);
//			//di at 21
//			tmpPairRecord0 = activePairs[100][105].pairRecord;
//		}
//
//		//Decrement count of by
//		algP.decrementCountRight(
//			indexSymbolRight,
//			indexSymbolNext,
//			activePairs,
//			sequenceArray,
//			priorityQueue,
//			c);
//
//		if (count == 0)
//		{//do at 8
//			ASSERT_EQ(nullptr, activePairs[100][111].pairRecord);
//			ASSERT_FALSE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));
//			ASSERT_EQ(nullptr, sequenceArray[8]->next);
//			ASSERT_EQ(nullptr, sequenceArray[37]->previous);
//		}
//		if (count == 1)
//		{//di at 15
//			ASSERT_EQ(2, activePairs[100][105].pairRecord->count);
//			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
//			ASSERT_EQ(nullptr, sequenceArray[15]->next);
//			ASSERT_EQ(nullptr, sequenceArray[21]->previous);
//		}
//		if (count == 2)
//		{//di at 21
//			ASSERT_EQ(nullptr, activePairs[100][105].pairRecord);
//			ASSERT_FALSE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));
//			ASSERT_EQ(nullptr, sequenceArray[21]->next);
//			ASSERT_EQ(nullptr, sequenceArray[31]->previous);
//		}
//
//		//Replace xaby with xA_y
//		algP.replacePair(
//			indexSymbolLeft,
//			indexSymbolRight,
//			indexSymbolNext,
//			activePairs,
//			sequenceArray,
//			dictionary,
//			Symbols,
//			c);
//
//		if (count == 0)
//		{//.d to A at 7
//			ASSERT_EQ(65, sequenceArray[7]->symbol);
//			ASSERT_EQ(0, sequenceArray[8]->symbol);
//			ASSERT_EQ(nullptr, sequenceArray[7]->next);
//
//			ASSERT_EQ(sequenceArray[9], sequenceArray[8]->next);
//			ASSERT_EQ(sequenceArray[7], sequenceArray[8]->previous);
//		}
//		if (count == 1)
//		{//.d to A at 14
//			int i = 14;
//			ASSERT_EQ(65, sequenceArray[i]->symbol);
//			ASSERT_EQ(0, sequenceArray[i+1]->symbol);
//			ASSERT_EQ(nullptr, sequenceArray[i]->next);
//			ASSERT_EQ(nullptr, sequenceArray[i]->previous);
//
//			ASSERT_EQ(sequenceArray[i+2], sequenceArray[i+1]->next);
//			ASSERT_EQ(sequenceArray[i], sequenceArray[i+1]->previous);
//		}
//		if (count == 2)
//		{//.d to A at 20
//			int i = 20;
//			ASSERT_EQ(65, sequenceArray[i]->symbol);
//			ASSERT_EQ(0, sequenceArray[i + 1]->symbol);
//			ASSERT_EQ(nullptr, sequenceArray[i]->next);
//			ASSERT_EQ(nullptr, sequenceArray[i]->previous);
//
//			ASSERT_EQ(sequenceArray[i + 2], sequenceArray[i + 1]->next);
//			ASSERT_EQ(sequenceArray[i], sequenceArray[i + 1]->previous);
//						
//		}
//
//		//Increment count of xA
//		algP.incrementCountLeft(
//			indexSymbolPrevious,
//			indexSymbolLeft,
//			activePairs,
//			sequenceArray,
//			priorityQueue,
//			Symbols,
//			skip,
//			c);
//
//		if (count == 0)
//		{//gA at 6
//			ASSERT_EQ(true, activePairs[103][65].seenOnce);
//			ASSERT_EQ(nullptr, activePairs[103][65].pairRecord);
//		}
//		if (count == 1)
//		{//hA at 13
//			ASSERT_EQ(true, activePairs[104][65].seenOnce);
//			ASSERT_EQ(nullptr, activePairs[104][65].pairRecord);
//		}
//		if (count == 2)
//		{//yA at 19
//			int left = 121;
//			int right = 65;
//			ASSERT_EQ(true, activePairs[left][right].seenOnce);
//			ASSERT_EQ(nullptr, activePairs[left][right].pairRecord);
//		}
//
//		//Increment count of Ay
//		algP.incrementCountRight(
//			indexSymbolLeft,
//			indexSymbolNext,
//			activePairs,
//			sequenceArray,
//			priorityQueue,
//			Symbols,
//			c);
//
//		if (count == 0)
//		{//Ao at 7
//			ASSERT_EQ(true, activePairs[65][111].seenOnce);
//			ASSERT_EQ(nullptr, activePairs[65][111].pairRecord);
//		}
//		if (count == 1)
//		{//Ai at 14
//			ASSERT_EQ(true, activePairs[65][105].seenOnce);
//			ASSERT_EQ(nullptr, activePairs[65][105].pairRecord);
//		}
//		if (count == 2)
//		{//Ai at 20
//			int left = 65;
//			int right = 105;
//			ASSERT_EQ(false, activePairs[left][right].seenOnce);
//			//ASSERT_EQ(-1, activePairs[left][right].indexFirst);
//			ASSERT_EQ(2, activePairs[left][right].pairRecord->count);
//			//Set to Ai
//			tmpPairRecord0 = activePairs[65][105].pairRecord;
//			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
//		}
//		
//		//Replace instance of pair - end
//
//		//Check that nothing random is added to the priority queue
//		for (int i = 2; i < priorityQueue.size(); i++)
//		{
//			ASSERT_EQ(nullptr, priorityQueue[i]);
//		}
//
//		count++;
//	} while (nextSymbol);
//
//	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
//}

TEST(testingLowerPriority, diddy)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

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

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string diddy2 = "singingAo.wahAiddyAiddyAumAiddyAo";
	string diddy3 = "singingAo.wahAiddBiddBumAiddBo";

	ASSERT_EQ(diddy1, t.SequenceToString(sequenceArray));

	int count = 0;

	CompactionData cData(1);

	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		while (priorityQueue[i])
		{
			if (i == 1 && count++ == 0)
				ASSERT_EQ(diddy2, t.SequenceToString(sequenceArray));
			algP.manageOneEntryOnList(
				i,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				symbols,
				cData,
				c);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

			if (i == 1 && count++ == 1)
				ASSERT_EQ(diddy3, t.SequenceToString(sequenceArray));			
		}
		if (i == 4)
			ASSERT_EQ(diddy2, t.SequenceToString(sequenceArray));

		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
	}
	string s = t.SequenceToString(sequenceArray);
	int x = 0;

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingLowerPriority, duplicates)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicates.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaabbbb";
	string string2 = "aaaaAA";
	string string3 = "AABB";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	int count = 0;

	CompactionData cData(1);

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
				cData,
				c);

			if (i == 1 && count++ == 0)
				ASSERT_EQ(string2, t.SequenceToString(sequenceArray));

			if (i == 1 && count++ == 1)
				ASSERT_EQ(string3, t.SequenceToString(sequenceArray));

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}		
	}
	string result = t.SequenceToString(sequenceArray);
	ASSERT_EQ(string3, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicates2)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicates2.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaaabbbb";
	string string2 = "AAaBB";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicates3)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicates3.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aabbbbaa";
	string string2 = "ABBA";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	string result = t.SequenceToString(sequenceArray);
	ASSERT_EQ(string2, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicatesLong)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicatesLong.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbb";
	string string2 = "DDAEE";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicatesLong3)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicatesLong3.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbcccccccccccccccccccccccccccccccccc";
	string string2 = "HHAaIIGGB";
	
	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	string result = t.SequenceToString(sequenceArray);
	ASSERT_EQ(string2, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicatesLong4)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicatesLong4.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);


	//19a3c16a4b19c2b6c -> 9Aa3c8A4b19c2b6c -> 9AaBc8A4b9Bc2b3B -> 4CAaBc4C4b9Bc2b3B ->4CAaBc4C4b4DBc2bDB -> 
	//2EAaBc2E4b4DBc2bDB -> 2EAaBc2E2F4DBcFDB -> 2EAaBc2EFG3DBcGB -> HAaBcHFG3DBcGB -> HAaIHFG3DIGB
	string string1 = "aaaaaaaaaaaaaaaaaaacccaaaaaaaaaaaaaaaabbbbcccccccccccccccccccaaaacccbbcccccc";
	string string2 = "IAaFIGHDDDFCFHB";
	

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	string result = t.SequenceToString(sequenceArray);
	ASSERT_EQ(string2, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicatesLong4_explicit)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long Symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	int testcount = 0;

	string input1 = "duplicatesLong4.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);


	//19a3c16a4b19c4a3c2b6c -> 9Aa3c8A4b19c2b6c -> 9AaBc8A4b9Bc2b3B -> 4CAaBc4C4b9Bc2b3B ->4CAaBc4C4b4DBc2bDB -> 
	//2EAaBc2E4b4DBc2bDB -> 2EAaBc2E2F4DBcFDB -> 2EAaBc2EFG3DBcGB -> HAaBcHFG3DBcGB -> HAaIHFG3DIGB
	string string1 = "aaaaaaaaaaaaaaaaaaacccaaaaaaaaaaaaaaaabbbbcccccccccccccccccccaaaacccbbcccccc";
	string string2 = "AAAAAAAAAacccAAAAAAAAbbbbcccccccccccccccccccAAcccbbcccccc";
	string string3 = "AAAAAAAAAaBcAAAAAAAAbbbbBBBBBBBBBcAABcbbBBB";
	string string4 = "CCCCAaBcCCCCbbbbBBBBBBBBBcCBcbbBBB";
	string string5 = "CCCCAaBcCCCCbbbbDDDDBcCBcbbDB";
	string string6 = "EEAaBcEEbbbbDDDDBcCBcbbDB"; //2EE 3Bc 3bb 2DB 2DD
	string string7 = "EEAaFEEbbbbDDDDFCFbbDB"; //2EE 3bb 2DD
	string string8 = "EEAaFEEGGDDDDFCFGDB"; // 2EE 2DD 2GD
	string string9 = "EEAaFEEGHDDDFCFHB"; //2EE 
	string string10 = "IAaFIGHDDDFCFHB";


	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	//Run - start
	CompactionData cData(sequenceArray.size());

	//manageHighPriorityList - start
	PairRecord * tmpPairRecord = nullptr;
	PairRecord * tmpPairRecordSelected = nullptr;
	long sequenceIndex = 0;
	long last = priorityQueue.size() - 1;

	while (priorityQueue[last])
	{
		tmpPairRecordSelected = priorityQueue[last];
		tmpPairRecord = priorityQueue[last];

		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		}
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (tmpPairRecordSelected->previousPair && tmpPairRecordSelected->nextPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		else if (tmpPairRecordSelected->previousPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = nullptr;
		}
		else if (tmpPairRecordSelected->nextPair)
		{
			priorityQueue[last] = tmpPairRecordSelected->nextPair;
			priorityQueue[last]->previousPair = nullptr;
		}
		else
			priorityQueue[last] = nullptr;
		tmpPairRecordSelected->previousPair = nullptr;
		tmpPairRecordSelected->nextPair = nullptr;

		//Find the count of the pair to be replaced and update counter for compaction
		if (c.compact)
		{
			long i = sequenceIndex;
			long s1 = sequenceArray[i]->symbol;
			long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;
			cData.replaceCount += activePairs[s1][s2].pairRecord->count;
		}

		//replaceAllPairs - start
		long indexSymbolLeft = -1;
		long indexSymbolRight = -1;
		long indexSymbolPrevious = -1;
		long indexSymbolNext = -1;

		SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];


		algP.firstPass(
			sequenceIndex,
			sequenceArray,
			activePairs,
			priorityQueue,
			Symbols,
			c);

		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

		bool skip = false;

		int testcount2 = 0;

		do
		{
			indexSymbolLeft = -1;
			indexSymbolRight = -1;
			indexSymbolPrevious = -1;
			indexSymbolNext = -1;

			sequenceIndex = nextSymbol->index;
			//Store the pointer to the next symbol now, as the current symbol is changed as we go
			nextSymbol = nextSymbol->next;

			algP.establishContext(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceIndex,
				sequenceArray);

			algP.replaceInstanceOfPair(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				Symbols,
				skip,
				c);

			

		} while (nextSymbol);
		//replaceAllPairs - end

		cout << "Sanity check: " << t.SanityCheckPairRecordsDetailed(sequenceArray, priorityQueue) << endl;
		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

		//Compaction
		if (c.compact)
		{
			if (cData.replaceCount > cData.compactTotal)
			{
				algP.compact(sequenceArray, activePairs, priorityQueue);
				cData.updateCompactTotal();
			}
		}

		//Pick new symbol
		algP.newSymbol(Symbols);

		//Assertion tests
		if (testcount == 0)
		{
			string result = t.SequenceToString(sequenceArray);
			ASSERT_EQ(string2, result);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}

		if (testcount == 1)
		{
			string result = t.SequenceToString(sequenceArray);
			ASSERT_EQ(string3, result);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}

		if (testcount == 2)
		{
			string result = t.SequenceToString(sequenceArray);
			ASSERT_EQ(string4, result);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}

		testcount++;
	}
	//manageHighPriorityList - end

	//manageLowerPriorityLists - start
	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		//manageOneList - start
		while (priorityQueue[i])
		{
			//manageOneEntryOnList - start 
			PairRecord * tmpPairRecord = nullptr;
			long sequenceIndex = -1;

			tmpPairRecord = priorityQueue[i];
			sequenceIndex = tmpPairRecord->arrayIndexFirst;

			//Remove current pair from priority queue
			if (tmpPairRecord->nextPair)
			{
				priorityQueue[i] = tmpPairRecord->nextPair;
				priorityQueue[i]->previousPair = nullptr;
			}
			else
				priorityQueue[i] = nullptr;
			tmpPairRecord->previousPair = nullptr;
			tmpPairRecord->nextPair = nullptr;

			//Find the count of the pair to be replaced and update counter for compaction
			if (c.compact)
			{
				long idx = sequenceIndex;
				long s1 = sequenceArray[idx]->symbol;
				long s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
				cData.replaceCount += activePairs[s1][s2].pairRecord->count;
			}
			//replaceAllPairs - start
			long indexSymbolLeft = -1;
			long indexSymbolRight = -1;
			long indexSymbolPrevious = -1;
			long indexSymbolNext = -1;

			SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];

			if (testcount == 5)
				int x = 0;

			algP.firstPass(
				sequenceIndex,
				sequenceArray,
				activePairs,
				priorityQueue,
				Symbols,
				c);

			bool skip = false;

			do
			{
				indexSymbolLeft = -1;
				indexSymbolRight = -1;
				indexSymbolPrevious = -1;
				indexSymbolNext = -1;

				sequenceIndex = nextSymbol->index;
				//Store the pointer to the next symbol now, as the current symbol is changed as we go
				nextSymbol = nextSymbol->next;

				algP.establishContext(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceIndex,
					sequenceArray);

				algP.replaceInstanceOfPair(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceArray,
					dictionary,
					activePairs,
					priorityQueue,
					Symbols,
					skip,
					c);

			} while (nextSymbol);
			//replaceAllPairs - end

			//Compaction
			if (c.compact)
			{
				if (cData.replaceCount > cData.compactTotal)
				{
					algP.compact(sequenceArray, activePairs, priorityQueue);
					cData.updateCompactTotal();
				}
			}

			//Pick new symbol
			algP.newSymbol(Symbols);
			//manageOneEntryOnList - end

			//Assertion tests
			//19a3c16a4b19c2b6c -> 9Aa3c8A4b19c2b6c -> 9AaBc8A4b9Bc2b3B -> 4CAaBc4C4b9Bc2b3B ->4CAaBc4C4b4DBc2bDB -> 
			//2EAaBc2E4b4DBc2bDB -> 2EAaBc2E2F4DBcFDB -> 2EAaBc2EFG3DBcGB -> HAaBcHFG3DBcGB -> HAaIHFG3DIGB

			

			if (testcount == 3)
			{
				string result = t.SequenceToString(sequenceArray);
				ASSERT_EQ(string5, result);

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 4)
			{
				string result = t.SequenceToString(sequenceArray);
				ASSERT_EQ(string6, result);

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 5)
			{
				string result = t.SequenceToString(sequenceArray);
				ASSERT_EQ(string7, result);

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 6)
			{
				string result = t.SequenceToString(sequenceArray);
				ASSERT_EQ(string8, result);

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 7)
			{
				string result = t.SequenceToString(sequenceArray);
				ASSERT_EQ(string9, result);

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			testcount++;
		}
		//manageOneList - end
	}
	//manageLowerPriorityLists - end
	//Run - end
	string result = t.SequenceToString(sequenceArray);
	ASSERT_EQ(string10, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, duplicatesLong5)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long Symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "duplicatesLong5.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	int testcount = 0;

	string string1 = "aaaacccaaaaabbbbccccaaaacccbbccc";
	string string2 = "FDaEEBBFEC";


	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));


	//Check result of initialization
	//Pair aa
	ASSERT_FALSE(sequenceArray[0]->previous);
	ASSERT_EQ(sequenceArray[2], sequenceArray[0]->next);

	ASSERT_EQ(sequenceArray[0], sequenceArray[2]->previous);
	ASSERT_EQ(sequenceArray[7], sequenceArray[2]->next);

	ASSERT_EQ(sequenceArray[2], sequenceArray[7]->previous);
	ASSERT_EQ(sequenceArray[9], sequenceArray[7]->next);

	ASSERT_EQ(sequenceArray[7], sequenceArray[9]->previous);
	ASSERT_EQ(sequenceArray[20], sequenceArray[9]->next);

	ASSERT_EQ(sequenceArray[9], sequenceArray[20]->previous);
	ASSERT_EQ(sequenceArray[22], sequenceArray[20]->next);

	ASSERT_EQ(sequenceArray[20], sequenceArray[22]->previous);
	ASSERT_FALSE(sequenceArray[22]->next);

	//Pair cc
	ASSERT_FALSE(sequenceArray[4]->previous);
	ASSERT_EQ(sequenceArray[16], sequenceArray[4]->next);

	ASSERT_EQ(sequenceArray[4], sequenceArray[16]->previous);
	ASSERT_EQ(sequenceArray[18], sequenceArray[16]->next);

	ASSERT_EQ(sequenceArray[16], sequenceArray[18]->previous);
	ASSERT_EQ(sequenceArray[24], sequenceArray[18]->next);

	ASSERT_EQ(sequenceArray[18], sequenceArray[24]->previous);
	ASSERT_EQ(sequenceArray[29], sequenceArray[24]->next);

	ASSERT_EQ(sequenceArray[24], sequenceArray[29]->previous);
	ASSERT_FALSE(sequenceArray[29]->next);

	//Pair bb
	ASSERT_FALSE(sequenceArray[12]->previous);
	ASSERT_EQ(sequenceArray[14], sequenceArray[12]->next);

	ASSERT_EQ(sequenceArray[12], sequenceArray[14]->previous);
	ASSERT_EQ(sequenceArray[27], sequenceArray[14]->next);

	ASSERT_EQ(sequenceArray[14], sequenceArray[27]->previous);
	ASSERT_FALSE(sequenceArray[27]->next);

	//Pair ac
	ASSERT_FALSE(sequenceArray[3]->previous);
	ASSERT_EQ(sequenceArray[23], sequenceArray[3]->next);

	ASSERT_EQ(sequenceArray[3], sequenceArray[23]->previous);
	ASSERT_FALSE(sequenceArray[23]->next);

	//Pair ca
	ASSERT_FALSE(sequenceArray[6]->previous);
	ASSERT_EQ(sequenceArray[19], sequenceArray[6]->next);

	ASSERT_EQ(sequenceArray[6], sequenceArray[19]->previous);
	ASSERT_FALSE(sequenceArray[19]->next);

	//Pair bc
	ASSERT_FALSE(sequenceArray[15]->previous);
	ASSERT_EQ(sequenceArray[28], sequenceArray[15]->next);

	ASSERT_EQ(sequenceArray[15], sequenceArray[28]->previous);
	ASSERT_FALSE(sequenceArray[28]->next);


	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

	//Run - start
	CompactionData cData(sequenceArray.size());

	//manageHighPriorityList - start
	PairRecord * tmpPairRecord = nullptr;
	PairRecord * tmpPairRecordSelected = nullptr;
	long sequenceIndex = 0;
	long last = priorityQueue.size() - 1;

	while (priorityQueue[last])
	{
		tmpPairRecordSelected = priorityQueue[last];
		tmpPairRecord = priorityQueue[last];

		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		}
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (tmpPairRecordSelected->previousPair && tmpPairRecordSelected->nextPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		else if (tmpPairRecordSelected->previousPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = nullptr;
		}
		else if (tmpPairRecordSelected->nextPair)
		{
			priorityQueue[last] = tmpPairRecordSelected->nextPair;
			priorityQueue[last]->previousPair = nullptr;
		}
		else
			priorityQueue[last] = nullptr;
		tmpPairRecordSelected->previousPair = nullptr;
		tmpPairRecordSelected->nextPair = nullptr;

		//Find the count of the pair to be replaced and update counter for compaction
		if (c.compact)
		{
			long i = sequenceIndex;
			long s1 = sequenceArray[i]->symbol;
			long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;
			cData.replaceCount += activePairs[s1][s2].pairRecord->count;
		}

		//replaceAllPairs - start
		long indexSymbolLeft = -1;
		long indexSymbolRight = -1;
		long indexSymbolPrevious = -1;
		long indexSymbolNext = -1;

		SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];

		//First pass - start
		long indexSymbolPreviousPrevious = -1;
		long indexSymbolNextNext = -1;

		long sequenceIndex2 = sequenceIndex;
		SymbolRecord * nextSymbol2 = sequenceArray[sequenceIndex2];
		bool skip2 = false;

		do
		{
			indexSymbolLeft = -1;
			indexSymbolRight = -1;
			indexSymbolPrevious = -1;
			indexSymbolPreviousPrevious = -1;
			indexSymbolNext = -1;
			indexSymbolNextNext = -1;

			sequenceIndex2 = nextSymbol2->index;
			//Store the pointer to the next symbol now, as the current symbol is changed as we go
			nextSymbol2 = nextSymbol2->next;

			algP.establishExtendedContext(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolPreviousPrevious,
				indexSymbolNext,
				indexSymbolNextNext,
				sequenceIndex2,
				sequenceArray);

			if (indexSymbolLeft == 7)
			{
				int x = 0;
			}

			bool activeLeft = false;
			if (indexSymbolPrevious >= 0)
				activeLeft = sequenceArray[indexSymbolPrevious]->next ||
				sequenceArray[indexSymbolPrevious]->previous;

			//Decrement count of xa
			algP.decrementCountLeft(
				indexSymbolPrevious,
				indexSymbolLeft,
				indexSymbolRight,
				activePairs,
				sequenceArray,
				priorityQueue,
				Symbols,
				c);

			//We need to reset this as we no longer do it while replacing the pair. This is because we need to set this previous pointer in the first pass.
			sequenceArray[indexSymbolLeft]->previous = nullptr;

			//Left pair
			algP.checkCountLeft(
				indexSymbolPreviousPrevious,
				indexSymbolPrevious,
				indexSymbolLeft,
				indexSymbolRight,
				activePairs,
				sequenceArray,
				Symbols,
				activeLeft,
				skip2,
				c);

			//Right pair
			algP.checkCountRight(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolNext,
				indexSymbolNextNext,
				activePairs,
				sequenceArray,
				Symbols,
				c);

			

		} while (nextSymbol2);
		//First pass - end

		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

		bool skip = false;

		int testcount2 = 0;

		ASSERT_FALSE(activePairs[65][97].pairRecord);

		do
		{
			indexSymbolLeft = -1;
			indexSymbolRight = -1;
			indexSymbolPrevious = -1;
			indexSymbolNext = -1;

			sequenceIndex = nextSymbol->index;
			//Store the pointer to the next symbol now, as the current symbol is changed as we go
			nextSymbol = nextSymbol->next;

			algP.establishContext(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceIndex,
				sequenceArray);

			if (indexSymbolLeft == 7)
			{
				int x = 0;
			}


			algP.replaceInstanceOfPair(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				Symbols,
				skip,
				c);


		} while (nextSymbol);
		//replaceAllPairs - end

		cout << "Sanity check: " << t.SanityCheckPairRecordsDetailed(sequenceArray, priorityQueue) << endl;
		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

		//Compaction
		if (c.compact)
		{
			if (cData.replaceCount > cData.compactTotal)
			{
				algP.compact(sequenceArray, activePairs, priorityQueue);
				cData.updateCompactTotal();
			}
		}

		//Pick new symbol
		algP.newSymbol(Symbols);

		//Assertion tests
		if (testcount == 0)
		{
			//Check result of compacting aa
			//Pair AA
			ASSERT_FALSE(sequenceArray[0]->previous);
			ASSERT_EQ(sequenceArray[7], sequenceArray[0]->next);			

			ASSERT_EQ(sequenceArray[0], sequenceArray[7]->previous);
			ASSERT_EQ(sequenceArray[20], sequenceArray[7]->next);			
						
			ASSERT_EQ(sequenceArray[7], sequenceArray[20]->previous);
			ASSERT_FALSE(sequenceArray[20]->next);

			//Lonely Aa
			ASSERT_FALSE(sequenceArray[9]->previous);
			ASSERT_FALSE(sequenceArray[9]->next);

			//Pair cA
			ASSERT_FALSE(sequenceArray[6]->previous);
			ASSERT_EQ(sequenceArray[19], sequenceArray[6]->next);

			ASSERT_EQ(sequenceArray[6], sequenceArray[19]->previous);
			ASSERT_FALSE(sequenceArray[19]->next);

			//Pair Ac
			ASSERT_FALSE(sequenceArray[2]->previous);
			ASSERT_EQ(sequenceArray[22], sequenceArray[2]->next);

			ASSERT_EQ(sequenceArray[2], sequenceArray[22]->previous);
			ASSERT_FALSE(sequenceArray[22]->next);

			//Pair cc
			ASSERT_FALSE(sequenceArray[4]->previous);
			ASSERT_EQ(sequenceArray[16], sequenceArray[4]->next);

			ASSERT_EQ(sequenceArray[4], sequenceArray[16]->previous);
			ASSERT_EQ(sequenceArray[18], sequenceArray[16]->next);

			ASSERT_EQ(sequenceArray[16], sequenceArray[18]->previous);
			ASSERT_EQ(sequenceArray[24], sequenceArray[18]->next);

			ASSERT_EQ(sequenceArray[18], sequenceArray[24]->previous);
			ASSERT_EQ(sequenceArray[29], sequenceArray[24]->next);

			ASSERT_EQ(sequenceArray[24], sequenceArray[29]->previous);
			ASSERT_FALSE(sequenceArray[29]->next);

			//Pair bb
			ASSERT_FALSE(sequenceArray[12]->previous);
			ASSERT_EQ(sequenceArray[14], sequenceArray[12]->next);

			ASSERT_EQ(sequenceArray[12], sequenceArray[14]->previous);
			ASSERT_EQ(sequenceArray[27], sequenceArray[14]->next);

			ASSERT_EQ(sequenceArray[14], sequenceArray[27]->previous);
			ASSERT_FALSE(sequenceArray[27]->next);

			//Pair bc
			ASSERT_FALSE(sequenceArray[15]->previous);
			ASSERT_EQ(sequenceArray[28], sequenceArray[15]->next);

			ASSERT_EQ(sequenceArray[15], sequenceArray[28]->previous);
			ASSERT_FALSE(sequenceArray[28]->next);
			

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}


		testcount++;
	}
	//manageHighPriorityList - end

	//manageLowerPriorityLists - start
	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		//manageOneList - start
		while (priorityQueue[i])
		{
			//manageOneEntryOnList - start 
			PairRecord * tmpPairRecord = nullptr;
			long sequenceIndex = -1;

			tmpPairRecord = priorityQueue[i];
			sequenceIndex = tmpPairRecord->arrayIndexFirst;

			//Remove current pair from priority queue
			if (tmpPairRecord->nextPair)
			{
				priorityQueue[i] = tmpPairRecord->nextPair;
				priorityQueue[i]->previousPair = nullptr;
			}
			else
				priorityQueue[i] = nullptr;
			tmpPairRecord->previousPair = nullptr;
			tmpPairRecord->nextPair = nullptr;

			//Find the count of the pair to be replaced and update counter for compaction
			if (c.compact)
			{
				long idx = sequenceIndex;
				long s1 = sequenceArray[idx]->symbol;
				long s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
				cData.replaceCount += activePairs[s1][s2].pairRecord->count;
			}
			//replaceAllPairs - start
			long indexSymbolLeft = -1;
			long indexSymbolRight = -1;
			long indexSymbolPrevious = -1;
			long indexSymbolNext = -1;

			SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];


			//First pass - start
			long indexSymbolPreviousPrevious = -1;
			long indexSymbolNextNext = -1;

			long sequenceIndex2 = sequenceIndex;
			SymbolRecord * nextSymbol2 = sequenceArray[sequenceIndex2];
			bool skip2 = false;

			do
			{
				indexSymbolLeft = -1;
				indexSymbolRight = -1;
				indexSymbolPrevious = -1;
				indexSymbolPreviousPrevious = -1;
				indexSymbolNext = -1;
				indexSymbolNextNext = -1;

				sequenceIndex2 = nextSymbol2->index;
				//Store the pointer to the next symbol now, as the current symbol is changed as we go
				nextSymbol2 = nextSymbol2->next;

				algP.establishExtendedContext(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolPreviousPrevious,
					indexSymbolNext,
					indexSymbolNextNext,
					sequenceIndex2,
					sequenceArray);

				if (indexSymbolLeft == 4)
				{
					int x = 0;
				}
				if (indexSymbolLeft == 24)
				{
					int x = 0;
				}

				bool activeLeft = false;
				if (indexSymbolPrevious >= 0)
					activeLeft = sequenceArray[indexSymbolPrevious]->next ||
					sequenceArray[indexSymbolPrevious]->previous;

				//Decrement count of xa
				algP.decrementCountLeft(
					indexSymbolPrevious,
					indexSymbolLeft,
					indexSymbolRight,
					activePairs,
					sequenceArray,
					priorityQueue,
					Symbols,
					c);

				//We need to reset this as we no longer do it while replacing the pair. This is because we need to set this previous pointer in the first pass.
				sequenceArray[indexSymbolLeft]->previous = nullptr;

				//Left pair
				algP.checkCountLeft(
					indexSymbolPreviousPrevious,
					indexSymbolPrevious,
					indexSymbolLeft,
					indexSymbolRight,
					activePairs,
					sequenceArray,
					Symbols,
					activeLeft,
					skip2,
					c);

				//Right pair
				algP.checkCountRight(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolNext,
					indexSymbolNextNext,
					activePairs,
					sequenceArray,
					Symbols,
					c);



			} while (nextSymbol2);
			//First pass - end

			bool skip = false;

			do
			{
				indexSymbolLeft = -1;
				indexSymbolRight = -1;
				indexSymbolPrevious = -1;
				indexSymbolNext = -1;

				sequenceIndex = nextSymbol->index;
				//Store the pointer to the next symbol now, as the current symbol is changed as we go
				nextSymbol = nextSymbol->next;

				algP.establishContext(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceIndex,
					sequenceArray);

				

				algP.replaceInstanceOfPair(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceArray,
					dictionary,
					activePairs,
					priorityQueue,
					Symbols,
					skip,
					c);

			} while (nextSymbol);
			//replaceAllPairs - end

			//Compaction
			if (c.compact)
			{
				if (cData.replaceCount > cData.compactTotal)
				{
					algP.compact(sequenceArray, activePairs, priorityQueue);
					cData.updateCompactTotal();
				}
			}

			//Pick new symbol
			algP.newSymbol(Symbols);
			//manageOneEntryOnList - end

			//Assertion tests
			if (testcount == 1)
			{
				//Check result of compacting cc
				//pair Bc
				ASSERT_FALSE(sequenceArray[4]->previous);
				ASSERT_EQ(sequenceArray[24], sequenceArray[4]->next);				

				ASSERT_EQ(sequenceArray[4], sequenceArray[24]->previous);
				ASSERT_EQ(sequenceArray[29], sequenceArray[24]->next);

				ASSERT_EQ(sequenceArray[24], sequenceArray[29]->previous);
				ASSERT_FALSE(sequenceArray[29]->next);

				//lonely BB
				ASSERT_FALSE(sequenceArray[16]->previous);
				ASSERT_FALSE(sequenceArray[16]->next);

				ASSERT_FALSE(sequenceArray[18]->previous);
				ASSERT_FALSE(sequenceArray[18]->next);

				//Pair AB

				ASSERT_FALSE(sequenceArray[2]->previous);
				ASSERT_EQ(sequenceArray[22], sequenceArray[2]->next);

				ASSERT_EQ(sequenceArray[2], sequenceArray[22]->previous);
				ASSERT_FALSE(sequenceArray[22]->next);

				//Pair AA
				ASSERT_FALSE(sequenceArray[0]->previous);
				ASSERT_EQ(sequenceArray[7], sequenceArray[0]->next);

				ASSERT_EQ(sequenceArray[0], sequenceArray[7]->previous);
				ASSERT_EQ(sequenceArray[20], sequenceArray[7]->next);

				ASSERT_EQ(sequenceArray[7], sequenceArray[20]->previous);
				ASSERT_FALSE(sequenceArray[20]->next);

				//Lonely Aa
				ASSERT_FALSE(sequenceArray[9]->previous);
				ASSERT_FALSE(sequenceArray[9]->next);


				//Pair bb
				ASSERT_FALSE(sequenceArray[12]->previous);
				ASSERT_EQ(sequenceArray[14], sequenceArray[12]->next);

				ASSERT_EQ(sequenceArray[12], sequenceArray[14]->previous);
				ASSERT_EQ(sequenceArray[27], sequenceArray[14]->next);

				ASSERT_EQ(sequenceArray[14], sequenceArray[27]->previous);
				ASSERT_FALSE(sequenceArray[27]->next);

				//Pair bB
				ASSERT_FALSE(sequenceArray[15]->previous);
				ASSERT_EQ(sequenceArray[28], sequenceArray[15]->next);

				ASSERT_EQ(sequenceArray[15], sequenceArray[28]->previous);
				ASSERT_FALSE(sequenceArray[28]->next);





				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 2)
			{
				//Check result of compacting Bc
				
				//lonely BB
				ASSERT_FALSE(sequenceArray[16]->previous);
				ASSERT_FALSE(sequenceArray[16]->next);

				ASSERT_FALSE(sequenceArray[18]->previous);
				ASSERT_FALSE(sequenceArray[18]->next);

				//Pair AA
				ASSERT_FALSE(sequenceArray[0]->previous);
				ASSERT_EQ(sequenceArray[7], sequenceArray[0]->next);

				ASSERT_EQ(sequenceArray[0], sequenceArray[7]->previous);
				ASSERT_EQ(sequenceArray[20], sequenceArray[7]->next);

				ASSERT_EQ(sequenceArray[7], sequenceArray[20]->previous);
				ASSERT_FALSE(sequenceArray[20]->next);

				//Lonely Aa
				ASSERT_FALSE(sequenceArray[9]->previous);
				ASSERT_FALSE(sequenceArray[9]->next);


				//Pair bb
				ASSERT_FALSE(sequenceArray[12]->previous);
				ASSERT_EQ(sequenceArray[14], sequenceArray[12]->next);

				ASSERT_EQ(sequenceArray[12], sequenceArray[14]->previous);
				ASSERT_EQ(sequenceArray[27], sequenceArray[14]->next);

				ASSERT_EQ(sequenceArray[14], sequenceArray[27]->previous);
				ASSERT_FALSE(sequenceArray[27]->next);

				//Pair AC
				ASSERT_FALSE(sequenceArray[2]->previous);
				ASSERT_EQ(sequenceArray[22], sequenceArray[2]->next);
				
				ASSERT_EQ(sequenceArray[2], sequenceArray[22]->previous);
				ASSERT_FALSE(sequenceArray[22]->next);






				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 3)
			{
				//Check result of compacting AA

				//lonely BB
				ASSERT_FALSE(sequenceArray[16]->previous);
				ASSERT_FALSE(sequenceArray[16]->next);

				ASSERT_FALSE(sequenceArray[18]->previous);
				ASSERT_FALSE(sequenceArray[18]->next);

				//Lonely Aa
				ASSERT_FALSE(sequenceArray[9]->previous);
				ASSERT_FALSE(sequenceArray[9]->next);


				//Pair bb
				ASSERT_FALSE(sequenceArray[12]->previous);
				ASSERT_EQ(sequenceArray[14], sequenceArray[12]->next);

				ASSERT_EQ(sequenceArray[12], sequenceArray[14]->previous);
				ASSERT_EQ(sequenceArray[27], sequenceArray[14]->next);

				ASSERT_EQ(sequenceArray[14], sequenceArray[27]->previous);
				ASSERT_FALSE(sequenceArray[27]->next);

				//Pair DC
				ASSERT_FALSE(sequenceArray[0]->previous);
				ASSERT_EQ(sequenceArray[20], sequenceArray[0]->next);

				ASSERT_EQ(sequenceArray[0], sequenceArray[20]->previous);
				ASSERT_FALSE(sequenceArray[20]->next);






				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 4)
			{
				//Check result of compacting bb

				//lonely BB
				ASSERT_FALSE(sequenceArray[16]->previous);
				ASSERT_FALSE(sequenceArray[16]->next);

				ASSERT_FALSE(sequenceArray[18]->previous);
				ASSERT_FALSE(sequenceArray[18]->next);

				//Lonely Aa
				ASSERT_FALSE(sequenceArray[9]->previous);
				ASSERT_FALSE(sequenceArray[9]->next);


				//Pair DC
				ASSERT_FALSE(sequenceArray[0]->previous);
				ASSERT_EQ(sequenceArray[20], sequenceArray[0]->next);

				ASSERT_EQ(sequenceArray[0], sequenceArray[20]->previous);
				ASSERT_FALSE(sequenceArray[20]->next);





				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}

			if (testcount == 5)
			{
				//Check result of compacting DC

				//lonely BB
				ASSERT_FALSE(sequenceArray[16]->previous);
				ASSERT_FALSE(sequenceArray[16]->next);

				ASSERT_FALSE(sequenceArray[18]->previous);
				ASSERT_FALSE(sequenceArray[18]->next);

				//Lonely Aa
				ASSERT_FALSE(sequenceArray[9]->previous);
				ASSERT_FALSE(sequenceArray[9]->next);




				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}


			testcount++;
		}
		//manageOneList - end
	}
	//manageLowerPriorityLists - end
	//Run - end


	string result = t.SequenceToString(sequenceArray);
	//ASSERT_EQ(string2, result);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

void firstPassOnePair(
	AlgorithmP & algP,
	bool & skip,
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolPreviousPrevious,
	long & indexSymbolNext,
	long & indexSymbolNextNext,
	int & sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> & activePairs,
	vector<PairRecord*> & priorityQueue,
	long & Symbols,
	Conditions & c)
{
	algP.establishExtendedContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		sequenceIndex,
		sequenceArray);

	bool activeLeft = false;
	if (indexSymbolPrevious >= 0)
		activeLeft = sequenceArray[indexSymbolPrevious]->next ||
		sequenceArray[indexSymbolPrevious]->previous;
	

	//Decrement count of xa
	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		Symbols,
		c);

	//We need to reset this as we no longer do it while replacing the pair. This is because we need to set this previous pointer in the first pass.
	sequenceArray[indexSymbolLeft]->previous = nullptr;

	//Left pair
	algP.checkCountLeft(
		indexSymbolPreviousPrevious,
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		Symbols,
		activeLeft,
		skip,
		c);

	//Right pair
	algP.checkCountRight(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolNext,
		indexSymbolNextNext,
		activePairs,
		sequenceArray,
		Symbols,
		c);
}

void secondPassOnePair(
	AlgorithmP & algP,
	bool & skip,
	long & indexSymbolLeft,
	long & indexSymbolRight,
	long & indexSymbolPrevious,
	long & indexSymbolPreviousPrevious,
	long & indexSymbolNext,
	int & sequenceIndex,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> & activePairs,
	vector<PairRecord*> & priorityQueue,
	dense_hash_map<long, Pair> & dictionary,
	long & Symbols,
	Conditions & c)
{
	


	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	//We must not increment a temporary pair
	//aaaa -> Aaa, Aa is about to disappear so we must not count it
	bool skipright = false;
	if (sequenceArray[indexSymbolLeft]->next &&
		sequenceArray[indexSymbolLeft]->next == sequenceArray[indexSymbolNext])
		skipright = true;

	//Decrement count of xa
	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		Symbols,
		c);

	//Decrement count of by
	algP.decrementCountRight(
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);


	//Replace xaby with xA_y
	algP.replacePair(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		dictionary,
		Symbols,
		c);

	//Increment count of xA
	algP.incrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		activePairs,
		sequenceArray,
		priorityQueue,
		Symbols,
		skip,
		c);

	//Increment count of Ay
	algP.incrementCountRight(
		indexSymbolLeft,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		priorityQueue,
		Symbols,
		c,
		skipright);
}

TEST(testingRun, skiptestnew)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "skiptestnew.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaaaaaaaaaaaaaaaaaa";
	string string2 = "CCB";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);

	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));
}

TEST(testingRun, skiptestnew_explicit)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "skiptestnew.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "aaaaaaaaaaaaaaaaaaaa";

	//Asserts to check initialization
	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	ASSERT_FALSE(activePairs[97][97].seenOnce);
	ASSERT_TRUE(activePairs[97][97].pairRecord);
	ASSERT_EQ(10, activePairs[97][97].pairRecord->count);
	ASSERT_EQ(0, activePairs[97][97].pairRecord->arrayIndexFirst);
	ASSERT_TRUE(priorityQueue[priorityQueueSize - 1]);

	ASSERT_FALSE(sequenceArray[0]->previous);
	ASSERT_EQ(2, sequenceArray[0]->next->index);
	for (int i = 2; i < sequenceArray.size() - 2; i = i + 2)
	{
		ASSERT_EQ(i - 2, sequenceArray[i]->previous->index);
		ASSERT_EQ(i + 2, sequenceArray[i]->next->index);
	}
	ASSERT_EQ(16, sequenceArray[18]->previous->index);
	ASSERT_TRUE(sequenceArray[0]->next);

	//Skip test
	priorityQueue[priorityQueueSize - 1] = nullptr;

	//first pass
	int index = 0;
	bool skip = false;

	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;
	long indexSymbolNextNext = -1;

	//First pair
	index = 0;
	SymbolRecord * nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	if (activePairs[symbols].empty())
	{
		activePairs[symbols].set_empty_key(-1);
		activePairs[symbols].set_deleted_key(-2);
	}

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Second pair
	index = 2;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_TRUE(activePairs[symbols][symbols].seenOnce);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_TRUE(skip);

	//Third pair
	index = 4;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_TRUE(activePairs[symbols][symbols].seenOnce);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Fourth pair
	index = 6;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(2, activePairs[symbols][symbols].pairRecord->count);
	ASSERT_EQ(sequenceArray[indexSymbolPreviousPrevious]->index, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_TRUE(skip);

	//Fifth pair
	index = 8;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(2, activePairs[symbols][symbols].pairRecord->count);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Sixth pair
	index = 10;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(3, activePairs[symbols][symbols].pairRecord->count);
	ASSERT_EQ(sequenceArray[indexSymbolPreviousPrevious]->index, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);
	ASSERT_TRUE(sequenceArray[indexSymbolPreviousPrevious]->previous);

	ASSERT_TRUE(skip);

	//Seventh pair
	index = 12;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(3, activePairs[symbols][symbols].pairRecord->count);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Eigth pair
	index = 14;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(4, activePairs[symbols][symbols].pairRecord->count);
	ASSERT_EQ(sequenceArray[indexSymbolPreviousPrevious]->index, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);
	ASSERT_TRUE(sequenceArray[indexSymbolPreviousPrevious]->previous);

	ASSERT_TRUE(skip);

	//Ninth pair
	index = 16;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(4, activePairs[symbols][symbols].pairRecord->count);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_TRUE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Tenth pair
	index = 18;
	nextSymbol = sequenceArray[index];

	firstPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		indexSymbolNextNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_FALSE(activePairs[symbols][97].seenOnce);
	ASSERT_FALSE(activePairs[symbols][97].pairRecord);
	ASSERT_FALSE(activePairs[symbols][symbols].seenOnce);
	ASSERT_TRUE(activePairs[symbols][symbols].pairRecord);
	ASSERT_EQ(5, activePairs[symbols][symbols].pairRecord->count);
	ASSERT_EQ(sequenceArray[indexSymbolPreviousPrevious]->index, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);

	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_FALSE(sequenceArray[index]->next);
	ASSERT_TRUE(sequenceArray[indexSymbolPreviousPrevious]->previous);

	ASSERT_TRUE(skip);


	//Checks after first pass done
	//Sequence array
	index = 0;
	ASSERT_FALSE(sequenceArray[index]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index]->next);

	for (int i = 1; i < sequenceArray.size() - 2; i = i + 2)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	for (int i = 2; i < sequenceArray.size() - 4; i = i + 2)
	{
		if (i == 8)
			ASSERT_EQ(sequenceArray[i - 4], sequenceArray[i]->previous);
		else if (i == 12)
			ASSERT_EQ(sequenceArray[i - 4], sequenceArray[i]->previous);
		else if (i == 16)
			ASSERT_EQ(sequenceArray[i - 4], sequenceArray[i]->previous);
		else
			ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_EQ(sequenceArray[i + 2], sequenceArray[i]->next);
	}

	

	//second pass
	index = 0;
	skip = false;

	indexSymbolLeft = -1;
	indexSymbolRight = -1;
	indexSymbolPrevious = -1;
	indexSymbolPreviousPrevious = -1;
	indexSymbolNext = -1;

	//First pair
	index = 0;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);
	
	ASSERT_FALSE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Second pair
	index = 2;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_FALSE(sequenceArray[index]->next);

	ASSERT_EQ(0, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);
	ASSERT_EQ(5, activePairs[symbols][symbols].pairRecord->count);

	ASSERT_EQ(activePairs[symbols][symbols].pairRecord, priorityQueue[priorityQueue.size() - 1]);

	ASSERT_TRUE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 17; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}


	//Third pair
	index = 4;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_FALSE(sequenceArray[index]->next);

	ASSERT_FALSE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 17; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Fourth pair
	index = 6;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_EQ(sequenceArray[index - 6], sequenceArray[index - 2]->previous);
	ASSERT_EQ(sequenceArray[index - 2], sequenceArray[index - 6]->next);

	ASSERT_TRUE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 13; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Fifth pair
	index = 8;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_FALSE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 13; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Sixth pair
	index = 10;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_EQ(sequenceArray[index - 6], sequenceArray[index - 2]->previous);
	ASSERT_EQ(sequenceArray[index - 2], sequenceArray[index - 6]->next);

	ASSERT_TRUE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 9; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Seventh pair
	index = 12;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_FALSE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 9; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Eigth pair
	index = 14;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_EQ(sequenceArray[index - 6], sequenceArray[index - 2]->previous);
	ASSERT_EQ(sequenceArray[index - 2], sequenceArray[index - 6]->next);

	ASSERT_TRUE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 5; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Ninth pair
	index = 16;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_EQ(sequenceArray[index + 2], sequenceArray[index + 1]->next);

	ASSERT_FALSE(skip);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 5; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Tenth pair
	index = 18;
	nextSymbol = sequenceArray[index];

	secondPassOnePair(
		algP,
		skip,
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolPreviousPrevious,
		indexSymbolNext,
		index,
		sequenceArray,
		activePairs,
		priorityQueue,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, sequenceArray[index]->symbol);
	ASSERT_EQ(0, sequenceArray[index + 1]->symbol);

	ASSERT_EQ(sequenceArray[index], sequenceArray[index + 1]->previous);
	ASSERT_FALSE(sequenceArray[index + 1]->next);

	ASSERT_EQ(sequenceArray[index - 6], sequenceArray[index - 2]->previous);
	ASSERT_EQ(sequenceArray[index - 2], sequenceArray[index - 6]->next);

	ASSERT_TRUE(skip);

	
	//Checks after second pass done
	//Sequence array
	index = 0;

	//Check that empty symbols are threaded correctly
	for (int i = 1; i < sequenceArray.size() - 1; i = i + 2)
	{
		ASSERT_EQ(sequenceArray[i - 1], sequenceArray[i]->previous);
		ASSERT_EQ(sequenceArray[i + 1], sequenceArray[i]->next);
	}
	ASSERT_EQ(sequenceArray[18], sequenceArray[19]->previous);
	ASSERT_FALSE(sequenceArray[19]->next);

	//Check that right symbols in pairs do not have pointers
	for (int i = 2; i < sequenceArray.size() - 1; i = i + 4)
	{
		ASSERT_FALSE(sequenceArray[i]->previous);
		ASSERT_FALSE(sequenceArray[i]->next);
	}

	//Check that pointers between pairs are correct
	ASSERT_FALSE(sequenceArray[0]->previous);
	ASSERT_EQ(sequenceArray[4], sequenceArray[0]->next);
	for (int i = 4; i < sequenceArray.size() - 4; i = i + 4)
	{
		ASSERT_EQ(sequenceArray[i - 4], sequenceArray[i]->previous);
		ASSERT_EQ(sequenceArray[i + 4], sequenceArray[i]->next);
	}
	ASSERT_EQ(sequenceArray[12], sequenceArray[16]->previous);
	ASSERT_FALSE(sequenceArray[16]->next);

	//Check that symbols have correctly updated
	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (i % 2 == 0)
		{
			ASSERT_EQ(symbols, sequenceArray[i]->symbol);
		}
		else
			ASSERT_EQ(0, sequenceArray[i]->symbol);
	}

	//Check that the priority queue has been correctly populated
	for (int i = 0; i < priorityQueue.size(); i++)
	{
		if (i == priorityQueue.size() - 1)
			ASSERT_TRUE(priorityQueue[i]);
		else
			ASSERT_FALSE(priorityQueue[i]);
	}

	//Check that the active pairs record is correct
	ASSERT_EQ(5, activePairs[symbols][symbols].pairRecord->count);
	ASSERT_EQ(0, activePairs[symbols][symbols].pairRecord->arrayIndexFirst);


	//Round 2 - 





	string result = t.SequenceToString(sequenceArray);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));


}

TEST(crashPossiblePointerError, 264a)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "crashtestdummy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	long count = 0;
	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	string string2 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	string string3 = "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB";
	string string4 = "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC";
	string string5 = "DDDDDDDDDDDDDDDDC";
	string string6 = "GGC";
	ASSERT_EQ(16, priorityQueueSize);
	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
	
	//Manage high priority lists
	PairRecord * tmpPairRecord;
	PairRecord * tmpPairRecordSelected;
	long sequenceIndex = 0;
	long last = priorityQueue.size() - 1;

	while (priorityQueue[last])
	{
		tmpPairRecordSelected = priorityQueue[last];
		tmpPairRecord = priorityQueue[last];

		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		}
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (tmpPairRecordSelected->previousPair && tmpPairRecordSelected->nextPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		else if (tmpPairRecordSelected->previousPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = nullptr;
		}
		else if (tmpPairRecordSelected->nextPair)
		{
			priorityQueue[last] = tmpPairRecordSelected->nextPair;
			priorityQueue[last]->previousPair = nullptr;
		}
		else
			priorityQueue[last] = nullptr;
		tmpPairRecordSelected->previousPair = nullptr;
		tmpPairRecordSelected->nextPair = nullptr;

		algP.replaceAllPairs(
			sequenceIndex,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			symbols,
			c);

		if (count == 0)
		{
			ASSERT_EQ(string2, t.SequenceToString(sequenceArray));
		}
		if (count == 1)
		{
			ASSERT_EQ(string3, t.SequenceToString(sequenceArray));
		}
		if (count == 2)
		{
			ASSERT_EQ(string4, t.SequenceToString(sequenceArray));
		}
		if (count == 3)
		{
			ASSERT_EQ(string5, t.SequenceToString(sequenceArray));
		}

		ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));

		count++;
		//Pick new symbol
		algP.newSymbol(symbols);
	}

	CompactionData cData(1);

	//Manage low priority lists
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
				cData,
				c);

			ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
		}
	}
	ASSERT_EQ(string6, t.SequenceToString(sequenceArray));
}

TEST(sameContext, diddy)
{
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;
	Decoder dec;

	//c.compact = true;
	c.verbose = true;
	string input1 = "diddy.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	long index = 15;
	ASSERT_TRUE(algP.sameContext(index, sequenceArray));

	index = 2;
	ASSERT_FALSE(algP.sameContext(index, sequenceArray));
}

TEST(checkLeft, recurring_pairs)
{
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long Symbols(65);

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;
	Decoder dec;

	//c.compact = true;
	c.verbose = true;
	string input1 = "recurring_pairs.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	//yxyabcdyxyefghxyxyijkyxy -> yAabcdyAefghAAijkyA -> BabcdBefghAAijkB

	string string1 = "yxyabcdyxyefghxyxyijkyxy";
	string string2 = "BabcdBefghAAijkB";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	int insane = 0;
	
	//Run - start
	CompactionData cData(sequenceArray.size());

	//manageHighPriorityList - start
	PairRecord * tmpPairRecord = nullptr;
	PairRecord * tmpPairRecordSelected = nullptr;
	long sequenceIndex = 0;
	long last = priorityQueue.size() - 1;

	while (priorityQueue[last])
	{
		tmpPairRecordSelected = priorityQueue[last];
		tmpPairRecord = priorityQueue[last];

		//Find pair with most occurences
		while (tmpPairRecord->nextPair)
		{
			tmpPairRecord = tmpPairRecord->nextPair;
			if (tmpPairRecord->count > tmpPairRecordSelected->count)
				tmpPairRecordSelected = tmpPairRecord;
		}
		sequenceIndex = tmpPairRecordSelected->arrayIndexFirst;

		//Remove current pair from priority queue
		if (tmpPairRecordSelected->previousPair && tmpPairRecordSelected->nextPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = tmpPairRecordSelected->nextPair;
			tmpPairRecordSelected->nextPair->previousPair = tmpPairRecordSelected->previousPair;
		}
		else if (tmpPairRecordSelected->previousPair)
		{
			tmpPairRecordSelected->previousPair->nextPair = nullptr;
		}
		else if (tmpPairRecordSelected->nextPair)
		{
			priorityQueue[last] = tmpPairRecordSelected->nextPair;
			priorityQueue[last]->previousPair = nullptr;
		}
		else
			priorityQueue[last] = nullptr;
		tmpPairRecordSelected->previousPair = nullptr;
		tmpPairRecordSelected->nextPair = nullptr;

		//Find the count of the pair to be replaced and update counter for compaction
		if (c.compact)
		{
			long i = sequenceIndex;
			long s1 = sequenceArray[i]->symbol;
			long s2 = sequenceArray[i + 1]->symbol != 0 ? sequenceArray[i + 1]->symbol : sequenceArray[i + 1]->next->symbol;
			cData.replaceCount += activePairs[s1][s2].pairRecord->count;
		}

		//replaceAllPairs - start
		long indexSymbolLeft = -1;
		long indexSymbolRight = -1;
		long indexSymbolPrevious = -1;
		long indexSymbolNext = -1;

		SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];


		algP.firstPass(
			sequenceIndex,
			sequenceArray,
			activePairs,
			priorityQueue,
			Symbols,
			c);

		bool skip = false;

		//DEBUG
		int count = 0;

		do
		{
			indexSymbolLeft = -1;
			indexSymbolRight = -1;
			indexSymbolPrevious = -1;
			indexSymbolNext = -1;

			sequenceIndex = nextSymbol->index;
			//Store the pointer to the next symbol now, as the current symbol is changed as we go
			nextSymbol = nextSymbol->next;

			algP.establishContext(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceIndex,
				sequenceArray);

			algP.replaceInstanceOfPair(
				indexSymbolLeft,
				indexSymbolRight,
				indexSymbolPrevious,
				indexSymbolNext,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				Symbols,
				skip,
				c);



			//DEBUG
			count++;
		} while (nextSymbol);

		//DEBUG
		MyTest t;
		int insane = t.SanityCheck(sequenceArray, priorityQueue, activePairs);
		if (insane)
		{
			string test = t.SanityCheckThreadingPointersDetailed(sequenceArray);
			int x = 0;
		}
		//replaceAllPairs - end

		t.ActivePairs("Active pairs: ", activePairs);
		insane = t.SanityCheck(sequenceArray, priorityQueue, activePairs);

		//Compaction
		if (c.compact)
		{
			if (cData.replaceCount > cData.compactTotal)
			{
				algP.compact(sequenceArray, activePairs, priorityQueue);
				cData.updateCompactTotal();
			}
		}

		//Pick new symbol
		algP.newSymbol(Symbols);
	}
	//manageHighPriorityList - end


	//manageLowerPriorityLists - start
	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		//manageOneList - start
		while (priorityQueue[i])
		{
			//manageOneEntryOnList - start
			PairRecord * tmpPairRecord = nullptr;
			long sequenceIndex = -1;

			tmpPairRecord = priorityQueue[i];
			sequenceIndex = tmpPairRecord->arrayIndexFirst;

			//Remove current pair from priority queue
			if (tmpPairRecord->nextPair)
			{
				priorityQueue[i] = tmpPairRecord->nextPair;
				priorityQueue[i]->previousPair = nullptr;
			}
			else
				priorityQueue[i] = nullptr;
			tmpPairRecord->previousPair = nullptr;
			tmpPairRecord->nextPair = nullptr;

			//Find the count of the pair to be replaced and update counter for compaction
			if (c.compact)
			{
				long idx = sequenceIndex;
				long s1 = sequenceArray[idx]->symbol;
				long s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
				cData.replaceCount += activePairs[s1][s2].pairRecord->count;
			}

			algP.replaceAllPairs(
				sequenceIndex,
				sequenceArray,
				dictionary,
				activePairs,
				priorityQueue,
				Symbols,
				c);

			t.ActivePairs("Active pairs: ", activePairs);
			insane = t.SanityCheck(sequenceArray, priorityQueue, activePairs);

			//Compaction
			if (c.compact)
			{
				if (cData.replaceCount > cData.compactTotal)
				{
					algP.compact(sequenceArray, activePairs, priorityQueue);
					cData.updateCompactTotal();
				}
			}

			//Pick new symbol
			algP.newSymbol(Symbols);
			//manageOneEntryOnList - end
		}
		//manageOneList - end
	}
	//manageLowerPriorityLists - end
	//Run - end
	
	t.ActivePairs("Active pairs: ", activePairs);

	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));
}