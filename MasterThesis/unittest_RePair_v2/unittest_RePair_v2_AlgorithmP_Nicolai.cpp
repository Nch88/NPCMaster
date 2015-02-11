#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(manageOneList, oneEntry)
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

	long index = 4;

	algP.manageOneList(
		index,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_EQ(nullptr, priorityQueue[index]);
}

TEST(manageOneList, multipleEntries)
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

	long index = 1;

	algP.manageOneList(
		index,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		c);

	ASSERT_EQ(nullptr, priorityQueue[index]);
}

TEST(replaceAllPairsThorough, diddy)
{
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int Symbols(65);//A

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

	int sequenceIndex = 7;
	int count = 0;

	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
	bool skip = false;

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

		//Decrement count of xa
		algP.decrementCountLeft(
			indexSymbolPrevious,
			indexSymbolLeft,
			activePairs,
			sequenceArray,
			priorityQueue,
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
			c);
		
		//Replace instance of pair - end
	} while (nextSymbol);

}

TEST(testingLowerPriority, diddy)
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

	ASSERT_EQ(diddy1, t.SequenceToString(sequenceArray));

	int count = 0;

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
				c);

			if (i == 1 && count++ == 0)
				ASSERT_EQ(diddy3, t.SequenceToString(sequenceArray));

			
		}
		if (i == 4)
			ASSERT_EQ(diddy2, t.SequenceToString(sequenceArray));
	}
	
}