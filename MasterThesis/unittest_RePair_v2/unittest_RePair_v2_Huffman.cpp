#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(testingHuffman, getFrequenciesAndCodeLengths)
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

	unordered_set<unsigned int> terminals;
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
	string string2 = "sHHAo.wahFEumFo";

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

	unordered_map<unsigned int, HuffmanNode *> huffmanCodes;
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	int cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);

	for (int i = cardinality; i < cardinality * 2; i++)
	{
		if (i == cardinality + 2 || i == cardinality + 6 || i == cardinality + 7)
			ASSERT_EQ(2, codeLengths[i]);
		else
			ASSERT_EQ(1, codeLengths[i]);
		ASSERT_EQ(i, codeLengths[i - cardinality]);
	}

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);

	for (int i = 0; i < heapSize; i++)
	{
		if (i == 0)
			ASSERT_EQ(12, codeLengths[i]);
		if (i == 1)
			ASSERT_EQ(13, codeLengths[i]);
		if (i == 2)
			ASSERT_EQ(17, codeLengths[i]);
		if (i == 3)
			ASSERT_EQ(15, codeLengths[i]);
		if (i == 4)
			ASSERT_EQ(16, codeLengths[i]);
		if (i == 5)
			ASSERT_EQ(23, codeLengths[i]);
		if (i == 6)
			ASSERT_EQ(18, codeLengths[i]);
		if (i == 7)
			ASSERT_EQ(19, codeLengths[i]);
		if (i == 8)
			ASSERT_EQ(20, codeLengths[i]);
		if (i == 9)
			ASSERT_EQ(21, codeLengths[i]);
		if (i == 10)
			ASSERT_EQ(22, codeLengths[i]);
		if (i == 11)
			ASSERT_EQ(14, codeLengths[i]);

		if (i == 6 || i == 7 || i == 11)
			ASSERT_EQ(2, codeLengths[codeLengths[i]]);
		else
			ASSERT_EQ(1, codeLengths[codeLengths[i]]);
	}

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
}

TEST(testingHuffman, collapseSymbols)
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
	unordered_set<unsigned int> terminals;
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
	string string2 = "sHHAo.wahFEumFo";

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

	unordered_map<unsigned int, HuffmanNode *> huffmanCodes;
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	int cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);

	h.collapseHuffmanTree(heapSize, codeLengths);

	ASSERT_EQ(1, codeLengths[0]);
	ASSERT_EQ(15, codeLengths[1]);

}

TEST(testingHuffman, phaseThree)
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
	unordered_set<unsigned int> terminals;
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
	string string2 = "sHHAo.wahFEumFo";

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

	h.collapseHuffmanTree(heapSize, codeLengths);

	ASSERT_EQ(1, codeLengths[0]);
	ASSERT_EQ(15, codeLengths[1]);
	int maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	for (int i = cardinality; i < cardinality * 2; i++)
	{
		if (i == 14 ||
			i == 18 || 
			i == 19 || 
			i == 23)
			ASSERT_EQ(3, codeLengths[i]);
		else
			ASSERT_EQ(4, codeLengths[i]);
	}
}

TEST(testingHuffman, generateCodes)
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
	unordered_set<unsigned int> terminals;
	string filename = input1;
	ifstream file(filename);

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
	string string2 = "sHHAo.wahFEumFo";

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

	h.collapseHuffmanTree(heapSize, codeLengths);
	int maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	h.generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, huffmanCodes);

	ASSERT_EQ(0, huffmanCodes[115]->code);
	ASSERT_EQ(1, huffmanCodes[104]->code);
	ASSERT_EQ(4, huffmanCodes[72]->code);
	ASSERT_EQ(2, huffmanCodes[97]->code);
	ASSERT_EQ(3, huffmanCodes[65]->code);
	ASSERT_EQ(4, huffmanCodes[119]->code);
	ASSERT_EQ(5, huffmanCodes[111]->code);
	ASSERT_EQ(6, huffmanCodes[70]->code);
	ASSERT_EQ(5, huffmanCodes[46]->code);
	ASSERT_EQ(6, huffmanCodes[69]->code);
	ASSERT_EQ(7, huffmanCodes[117]->code);
	ASSERT_EQ(7, huffmanCodes[109]->code);
}