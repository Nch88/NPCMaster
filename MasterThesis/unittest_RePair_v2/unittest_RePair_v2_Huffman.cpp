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

TEST(testingHuffman, codeToString)
{
	Huffman h;

	int code = 42;
	int length = 6;

	string scode = h.codeToString(code, length);

	ASSERT_EQ("101010", scode);
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

	int *firstCode = new int[maxLength];
	h.generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, huffmanCodes);

	ASSERT_EQ("0000", huffmanCodes[115]->code);
	ASSERT_EQ("0001", huffmanCodes[104]->code);
	ASSERT_EQ("100", huffmanCodes[72]->code);
	ASSERT_EQ("0010", huffmanCodes[97]->code);
	ASSERT_EQ("0011", huffmanCodes[65]->code);
	ASSERT_EQ("0100", huffmanCodes[119]->code);
	ASSERT_EQ("101", huffmanCodes[111]->code);
	ASSERT_EQ("110", huffmanCodes[70]->code);
	ASSERT_EQ("0101", huffmanCodes[46]->code);
	ASSERT_EQ("0110", huffmanCodes[69]->code);
	ASSERT_EQ("0111", huffmanCodes[117]->code);
	ASSERT_EQ("111", huffmanCodes[109]->code);
}

TEST(testingHuffman, fillBitset)
{
	Huffman h;

	int raw = 42;
	bitset<32> *bits = new bitset<32>();

	h.fillBitset(raw, bits);

	for (int i = 0; i < 32; i++)
	{
		if (i == 1 || i == 3 || i == 5) //Bits 2, 4, and 6
			ASSERT_EQ(1, (*bits)[i]);
		else
			ASSERT_EQ(0, (*bits)[i]);
	}
}

TEST(huffman, decoder)
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
	Outputter out;

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

	h.encode(sequenceArray, huffmanCodes);

	out.huffmanEncoding(
		input1,
		sequenceArray,
		huffmanCodes,
		true);

	
	string expected1 = "00000100100001110101010100001000";
	string expected2 = "00111001100111111110101000000000";
	string expected3 = "10000000000000000000000000001001";

	unordered_map<int, unordered_map<string, string>> huffmanToSymbols;
	//Huffman dictionary
	huffmanToSymbols[4]["0000"] = "s";
	huffmanToSymbols[4]["0001"] = "h";
	huffmanToSymbols[3]["100"]  = "H";
	huffmanToSymbols[4]["0010"] = "a";
	huffmanToSymbols[4]["0011"] = "A";
	huffmanToSymbols[4]["0100"] = "w";
	huffmanToSymbols[3]["101"]  = "o";
	huffmanToSymbols[3]["110"]  = "F";
	huffmanToSymbols[4]["0101"] = ".";
	huffmanToSymbols[4]["0110"] = "E";
	huffmanToSymbols[4]["0111"] = "u";
	huffmanToSymbols[3]["111"]  = "m";

	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> symbolIndices;
	symbolIndices[4][0] = 0;
	symbolIndices[4][1] = 1;
	symbolIndices[4][2] = 3;
	symbolIndices[4][3] = 4;
	symbolIndices[4][4] = 5;
	symbolIndices[4][5] = 8;
	symbolIndices[4][6] = 9;
	symbolIndices[4][7] = 10;
	symbolIndices[3][4] = 2;
	symbolIndices[3][5] = 6;
	symbolIndices[3][6] = 7;
	symbolIndices[3][7] = 11;

	string testTranslator[12] = { "0000", "0001", "100", "0010", "0011", "0100", "101", "110", "0101", "0110", "0111", "111" };

	int firstCode[4] = { 2, 2, 4, 0 };
	
	vector<unsigned int> *symbolIndexSequence = new vector<unsigned int>();

	ifstream ifs;
	ifs.open("Compressed_diddy.txt", ios::binary);
	string result = "";
	string totalResult = "";
	char byte;
	bitset<8> *bits;
	int count = 0;

	if (ifs.is_open())
	{
		h.decode(firstCode, ifs, &symbolIndices, *symbolIndexSequence);

		for (int i = 0; i < symbolIndexSequence->size(); i++)
		{
			if (i == 2 || i == 6 || i == 7 || i == 11)
			{
				totalResult += huffmanToSymbols[3][testTranslator[(*symbolIndexSequence)[i]]];
			}
			else
				totalResult += huffmanToSymbols[4][testTranslator[(*symbolIndexSequence)[i]]];
		}
		ASSERT_EQ(string2, totalResult);
	}
	else
		ASSERT_TRUE(false);
}