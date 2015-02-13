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

	unordered_map<unsigned int, HuffmanNode> frequencies;
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	h.getFrequencies(sequenceArray, frequencies);

	ASSERT_EQ(1, frequencies[(unsigned int)'s'].frequency);
	ASSERT_EQ(2, frequencies[(unsigned int)'H'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'A'].frequency);
	ASSERT_EQ(2, frequencies[(unsigned int)'o'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'.'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'w'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'a'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'h'].frequency);
	ASSERT_EQ(2, frequencies[(unsigned int)'F'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'E'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'u'].frequency);
	ASSERT_EQ(1, frequencies[(unsigned int)'m'].frequency);
}

TEST(testingHuffman, setupPriorityQueue)
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

	unordered_map<unsigned int, HuffmanNode> frequencies;
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	h.getFrequencies(sequenceArray, frequencies);

	h.setupPriorityQueue(frequencies, pq);

	ASSERT_EQ(1, pq.top().frequency);
}

TEST(testingHuffmanCompareNodes, compare)
{
	bool reverse = true;
	CompareNodes compare(reverse);

	HuffmanNode * n1 = new HuffmanNode(1, 1);
	HuffmanNode * n2 = new HuffmanNode(2, 2);

	ASSERT_TRUE(compare.operator()(*n1, *n2));
	reverse = false;
	CompareNodes compare2(reverse);
	ASSERT_TRUE(compare2.operator()(*n2, *n1));
}

TEST(testingHuffman, collapseTree)
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

	unordered_map<unsigned int, HuffmanNode> frequencies;
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	h.getFrequencies(sequenceArray, frequencies);

	h.setupPriorityQueue(frequencies, pq);

	h.collapseTree(pq);
	ASSERT_EQ(2, pq.size());

	//Test this!!
}

TEST(testingHuffman, unravel)
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

	unordered_map<unsigned int, HuffmanNode> frequencies;
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	h.getFrequencies(sequenceArray, frequencies);

	h.setupPriorityQueue(frequencies, pq);

	h.collapseTree(pq);

	HuffmanNode * leftChild = &pq.top();
	pq.pop();
	HuffmanNode * rightChild = &pq.top();
	pq.pop();
	
	//h.unravel(leftChild, rightChild); Does not work
}