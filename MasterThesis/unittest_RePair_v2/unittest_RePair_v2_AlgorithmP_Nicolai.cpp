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

TEST(replaceAllPairsThorough, diddy)
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

	int sequenceIndex = 7;
	int count = 0;

	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
	if (activePairs[100].empty())
	{
		activePairs[100].set_empty_key(-1);
		activePairs[100].set_deleted_key(-2);
	}
		
	PairRecord * tmpPairRecord0 = activePairs[100][111].pairRecord;

	ASSERT_TRUE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));

	//Remove .d pair record from priority queue
	priorityQueue[4] = nullptr;

	do
	{
		sequenceIndex = nextSymbol->index;
		nextSymbol = nextSymbol->next;

		algP.establishContext(
			indexSymbolLeft,
			indexSymbolRight,
			indexSymbolPrevious,
			indexSymbolNext,
			sequenceIndex,
			sequenceArray);	

		//Replace instance of pair

		if (count == 2)
		{
			//y. at 19
			tmpPairRecord0 = activePairs[121][46].pairRecord;
		}

		//Decrement count of xa
		algP.decrementCountLeft(
			indexSymbolPreviousPrevious,
			indexSymbolPrevious,
			indexSymbolLeft,
			indexSymbolRight,
			activePairs,
			sequenceArray,
			priorityQueue,
			Symbols,
			c);

		if (count == 0)
		{
			//g. is not an active pair, nothing happens
			//do at 8
			tmpPairRecord0 = activePairs[100][111].pairRecord;
		}
		if (count == 1)
		{
			//h. is not an active pair, nothing happens
			//di at 15
			tmpPairRecord0 = activePairs[100][105].pairRecord;
		}
		if (count == 2)
		{
			//y. at 19
			ASSERT_EQ(2, activePairs[121][46].pairRecord->count);
			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
			ASSERT_EQ(nullptr, sequenceArray[19]->next);
			ASSERT_EQ(nullptr, sequenceArray[25]->previous);
			//di at 21
			tmpPairRecord0 = activePairs[100][105].pairRecord;
		}

		//Decrement count of by
		algP.decrementCountRight(
			indexSymbolRight,
			indexSymbolNext,
			activePairs,
			sequenceArray,
			priorityQueue,
			c);

		if (count == 0)
		{//do at 8
			ASSERT_EQ(nullptr, activePairs[100][111].pairRecord);
			ASSERT_FALSE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));
			ASSERT_EQ(nullptr, sequenceArray[8]->next);
			ASSERT_EQ(nullptr, sequenceArray[37]->previous);
		}
		if (count == 1)
		{//di at 15
			ASSERT_EQ(2, activePairs[100][105].pairRecord->count);
			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
			ASSERT_EQ(nullptr, sequenceArray[15]->next);
			ASSERT_EQ(nullptr, sequenceArray[21]->previous);
		}
		if (count == 2)
		{//di at 21
			ASSERT_EQ(nullptr, activePairs[100][105].pairRecord);
			ASSERT_FALSE(t.inPriorityQueue(tmpPairRecord0, priorityQueue));
			ASSERT_EQ(nullptr, sequenceArray[21]->next);
			ASSERT_EQ(nullptr, sequenceArray[31]->previous);
		}

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

		if (count == 0)
		{//.d to A at 7
			ASSERT_EQ(65, sequenceArray[7]->symbol);
			ASSERT_EQ(0, sequenceArray[8]->symbol);
			ASSERT_EQ(nullptr, sequenceArray[7]->next);

			ASSERT_EQ(sequenceArray[9], sequenceArray[8]->next);
			ASSERT_EQ(sequenceArray[7], sequenceArray[8]->previous);
		}
		if (count == 1)
		{//.d to A at 14
			int i = 14;
			ASSERT_EQ(65, sequenceArray[i]->symbol);
			ASSERT_EQ(0, sequenceArray[i+1]->symbol);
			ASSERT_EQ(nullptr, sequenceArray[i]->next);
			ASSERT_EQ(nullptr, sequenceArray[i]->previous);

			ASSERT_EQ(sequenceArray[i+2], sequenceArray[i+1]->next);
			ASSERT_EQ(sequenceArray[i], sequenceArray[i+1]->previous);
		}
		if (count == 2)
		{//.d to A at 20
			int i = 20;
			ASSERT_EQ(65, sequenceArray[i]->symbol);
			ASSERT_EQ(0, sequenceArray[i + 1]->symbol);
			ASSERT_EQ(nullptr, sequenceArray[i]->next);
			ASSERT_EQ(nullptr, sequenceArray[i]->previous);

			ASSERT_EQ(sequenceArray[i + 2], sequenceArray[i + 1]->next);
			ASSERT_EQ(sequenceArray[i], sequenceArray[i + 1]->previous);
						
		}

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

		if (count == 0)
		{//gA at 6
			ASSERT_EQ(true, activePairs[103][65].seenOnce);
			ASSERT_EQ(nullptr, activePairs[103][65].pairRecord);
		}
		if (count == 1)
		{//hA at 13
			ASSERT_EQ(true, activePairs[104][65].seenOnce);
			ASSERT_EQ(nullptr, activePairs[104][65].pairRecord);
		}
		if (count == 2)
		{//yA at 19
			int left = 121;
			int right = 65;
			ASSERT_EQ(true, activePairs[left][right].seenOnce);
			ASSERT_EQ(nullptr, activePairs[left][right].pairRecord);
		}

		//Increment count of Ay
		algP.incrementCountRight(
			indexSymbolLeft,
			indexSymbolNext,
			activePairs,
			sequenceArray,
			priorityQueue,
			Symbols,
			c);

		if (count == 0)
		{//Ao at 7
			ASSERT_EQ(true, activePairs[65][111].seenOnce);
			ASSERT_EQ(nullptr, activePairs[65][111].pairRecord);
		}
		if (count == 1)
		{//Ai at 14
			ASSERT_EQ(true, activePairs[65][105].seenOnce);
			ASSERT_EQ(nullptr, activePairs[65][105].pairRecord);
		}
		if (count == 2)
		{//Ai at 20
			int left = 65;
			int right = 105;
			ASSERT_EQ(false, activePairs[left][right].seenOnce);
			//ASSERT_EQ(-1, activePairs[left][right].indexFirst);
			ASSERT_EQ(2, activePairs[left][right].pairRecord->count);
			//Set to Ai
			tmpPairRecord0 = activePairs[65][105].pairRecord;
			ASSERT_TRUE(t.inPriorityQueueAtPosition(tmpPairRecord0, priorityQueue, 0));
		}
		
		//Replace instance of pair - end

		//Check that nothing random is added to the priority queue
		for (int i = 2; i < priorityQueue.size(); i++)
		{
			ASSERT_EQ(nullptr, priorityQueue[i]);
		}

		count++;
	} while (nextSymbol);

	ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

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