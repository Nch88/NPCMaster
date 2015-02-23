#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(testingHuffman, getFrequencies)
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
	Huffman h;

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

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		c);
	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));

	unordered_map<unsigned int, HuffmanNode *> huffmanCodes;
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	int cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);

	int freqOne = 0;
	int freqTwo = 0;

	for (int i = 0; i < heapSize; i++)
	{
		if (codeLengths[codeLengths[i]] == 1)
			++freqOne;
		else if (codeLengths[codeLengths[i]] == 2)
			++freqTwo;
	}

	ASSERT_EQ(9, freqOne);
	ASSERT_EQ(3, freqTwo);

	h.phaseTwo(heapSize, codeLengths);

	ASSERT_EQ(1, codeLengths[0]);
	ASSERT_EQ(15, codeLengths[1]);

	h.phaseThree(cardinality, codeLengths);

	ASSERT_EQ(3, codeLengths[cardinality * 2 - 1]);
}
