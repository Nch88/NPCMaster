#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(testingHuffman, getFrequenciesAndCodeLengths)
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
	Huffman h;

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

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);
	int j = 0;
	for (j = cardinality; j < cardinality * 2; j++)
	{
		if (j == cardinality + 0 || j == cardinality + 3 || j == cardinality + 4)
			ASSERT_EQ(2, codeLengths[j]);
		else
			ASSERT_EQ(1, codeLengths[j]);
		ASSERT_EQ(j, codeLengths[j - cardinality]);
	}

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);
	vector<int> testCodelengths;

	for (int i = 0; i < cardinality * 2; i++)
	{
		testCodelengths.push_back(codeLengths[i]);
	}

	for (int i = 0; i < heapSize; i++)
	{
		if (i == 0)
			ASSERT_EQ(13, codeLengths[i]);
		if (i == 1)
			ASSERT_EQ(19, codeLengths[i]);
		if (i == 2)
			ASSERT_EQ(14, codeLengths[i]);
		if (i == 3)
			ASSERT_EQ(20, codeLengths[i]);
		if (i == 4)
			ASSERT_EQ(21, codeLengths[i]);
		if (i == 5)
			ASSERT_EQ(17, codeLengths[i]);
		if (i == 6)
			ASSERT_EQ(18, codeLengths[i]);
		if (i == 7)
			ASSERT_EQ(15, codeLengths[i]);
		if (i == 8)
			ASSERT_EQ(12, codeLengths[i]);
		if (i == 9)
			ASSERT_EQ(16, codeLengths[i]);
		if (i == 10)
			ASSERT_EQ(22, codeLengths[i]);
		if (i == 11)
			ASSERT_EQ(23, codeLengths[i]);

		if (i == 7 || i == 8 || i == 9)
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
	Huffman h;

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

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);

	h.collapseHuffmanTree(heapSize, codeLengths);

	vector<int> testCodelengths;

	for (int i = 0; i < cardinality * 2; i++)
	{
		testCodelengths.push_back(codeLengths[i]);
	}

	ASSERT_EQ(1, codeLengths[0]);
	ASSERT_EQ(15, codeLengths[1]);

}

TEST(testingHuffman, phaseThree)
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
	Huffman h;

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

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
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
	long maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	vector<int> testCodelengths;

	for (int i = 0; i < cardinality * 2; i++)
	{
		testCodelengths.push_back(codeLengths[i]);
	}

	for (int i = cardinality; i < cardinality * 2; i++)
	{
		if (i == 12 ||
			i == 15 || 
			i == 16 || 
			i == 18)
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
	Huffman h;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
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

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
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
	long maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	long *firstCode = new long[maxLength];
	long *numl = new long[maxLength];
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, numl, huffmanCodes, huffmanToSymbol);

	vector<long> testhuffmanCodessymbols;
	vector<string> testhuffmanCodes;

	for (auto &entry : huffmanCodes)
	{
		testhuffmanCodes.push_back(entry.second.code);
		testhuffmanCodessymbols.push_back(entry.first);
	}
		

	ASSERT_EQ("0011", huffmanCodes[115].code);
	ASSERT_EQ("0000", huffmanCodes[104].code);
	ASSERT_EQ("100", huffmanCodes[72].code);
	ASSERT_EQ("111", huffmanCodes[97].code);
	ASSERT_EQ("0010", huffmanCodes[65].code);
	ASSERT_EQ("0110", huffmanCodes[119].code);
	ASSERT_EQ("110", huffmanCodes[111].code);
	ASSERT_EQ("101", huffmanCodes[70].code);
	ASSERT_EQ("0101", huffmanCodes[46].code);
	ASSERT_EQ("0100", huffmanCodes[69].code);
	ASSERT_EQ("0001", huffmanCodes[117].code);
	ASSERT_EQ("0111", huffmanCodes[109].code);
}

TEST(testingHuffman, generateCodesExampleFromBook1)
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
	Huffman h;


	bool skip = false;
	string string2 = "";

	for (int i = 0; i < 10; i++)
	{
		string2 += "a";
	}
	for (int i = 0; i < 11; i++)
	{
		string2 += "b";
	}
	for (int i = 0; i < 12; i++)
	{
		string2 += "c";
	}
	for (int i = 0; i < 13; i++)
	{
		string2 += "d";
	}
	for (int i = 0; i < 22; i++)
	{
		string2 += "e";
	}
	for (int i = 0; i < 23; i++)
	{
		string2 += "f";
	}

	for (int i = 0; i < string2.size(); i++)
	{
		sequenceArray.push_back(new SymbolRecord(string2[i], i));
	}

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
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
	long maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	ASSERT_EQ(3, maxLength);

	long *firstCode = new long[maxLength];
	long *numl = new long[maxLength];
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, numl, huffmanCodes, huffmanToSymbol);

	vector<long> testhuffmanCodessymbols;
	vector<string> testhuffmanCodes;

	for (auto &entry : huffmanCodes)
	{
		testhuffmanCodes.push_back(entry.second.code);
		testhuffmanCodessymbols.push_back(entry.first);
	}

	ASSERT_EQ("010", huffmanCodes[97].code);
	ASSERT_EQ("001", huffmanCodes[98].code);
	ASSERT_EQ("000", huffmanCodes[99].code);
	ASSERT_EQ("011", huffmanCodes[100].code);
	ASSERT_EQ("11", huffmanCodes[101].code);
	ASSERT_EQ("10", huffmanCodes[102].code);
}

TEST(testingHuffman, generateCodesExampleFromBook2)
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
	Huffman h;


	bool skip = false;
	string string2 = "aaaaabbccddeeffffffffffffffggggggggggggggghhhhhhhhhhhhhhh";

	for (int i = 0; i < 5; i++)
	{
		string2 += "a";
	}
	for (int i = 0; i < 2; i++)
	{
		string2 += "b";
	}
	for (int i = 0; i < 2; i++)
	{
		string2 += "c";
	}
	for (int i = 0; i < 2; i++)
	{
		string2 += "d";
	}
	for (int i = 0; i < 2; i++)
	{
		string2 += "e";
	}
	for (int i = 0; i < 10; i++)
	{
		string2 += "f";
	}
	for (int i = 0; i < 10; i++)
	{
		string2 += "g";
	}
	for (int i = 0; i < 10; i++)
	{
		string2 += "h";
	}

	for (int i = 0; i < string2.size(); i++)												//Setup sequence array for test
	{
		sequenceArray.push_back(new SymbolRecord(string2[i], i));
	}

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	priority_queue<HuffmanNode, vector<HuffmanNode>, CompareNodes> pq;
	long cardinality = 0;
	h.getFrequencies(sequenceArray, huffmanCodes, cardinality);								//Get the frequency of symbols

	int *codeLengths = new int[cardinality * 2];
	h.initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);

	int heapSize = cardinality;
	h.initMinHeap(heapSize, codeLengths);

	h.collapseHuffmanTree(heapSize, codeLengths);
	long maxLength = 0;
	h.expandHuffmanTree(cardinality, codeLengths, maxLength);

	long *firstCode = new long[maxLength];
	long *numl = new long[maxLength];
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, numl, huffmanCodes, huffmanToSymbol);

	vector<long> testhuffmanCodessymbols;
	vector<string> testhuffmanCodes;

	for (auto &entry : huffmanCodes)
	{
		testhuffmanCodes.push_back(entry.second.code);
		testhuffmanCodessymbols.push_back(entry.first);
	}

	ASSERT_EQ("001", huffmanCodes[97].code);
	ASSERT_EQ("00001", huffmanCodes[98].code);
	ASSERT_EQ("00000", huffmanCodes[99].code);
	ASSERT_EQ("00011", huffmanCodes[100].code);
	ASSERT_EQ("00010", huffmanCodes[101].code);
	ASSERT_EQ("11", huffmanCodes[102].code);
	ASSERT_EQ("10", huffmanCodes[103].code);
	ASSERT_EQ("01", huffmanCodes[104].code);
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
	Huffman h;
	Outputter out;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
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

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	ASSERT_EQ(2, firstCode[0]);
	ASSERT_EQ(4, firstCode[1]);
	ASSERT_EQ(4, firstCode[2]);
	ASSERT_EQ(0, firstCode[3]);

	out.huffmanEncoding(
		out.addFilenameEnding(input1, ".NPC"),
		sequenceArray,
		huffmanCodes,
		true);

	
	string expected1 = "00000100100001110101010100001000";
	string expected2 = "00111001100111111110101000000000";
	string expected3 = "10000000000000000000000000001001";

	dense_hash_map<int, dense_hash_map<string, string>> huffmanToSymbols;
	huffmanToSymbols.set_empty_key(-1);
	huffmanToSymbols.set_deleted_key(-2);
	huffmanToSymbols[3].set_empty_key("empty");
	huffmanToSymbols[3].set_deleted_key("deleted");
	huffmanToSymbols[4].set_empty_key("empty");
	huffmanToSymbols[4].set_deleted_key("deleted");
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

	dense_hash_map<long, dense_hash_map<long, long>> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	symbolIndices[3].set_empty_key(-1);
	symbolIndices[3].set_deleted_key(-2);
	symbolIndices[4].set_empty_key(-1);
	symbolIndices[4].set_deleted_key(-2);

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

	
	vector<long> symbolIndexSequence;

	string filename2 = "Compressed_diddy.txt";
	string result = "";
	string totalResult = "";
	char byte;
	bitset<8> *bits;
	int count = 0;
	//sHHAo.wahFEumFo
	
	h.decode(firstCode, filename2, symbolIndices, symbolIndexSequence);

	for (int i = 0; i < symbolIndexSequence.size(); i++)
	{
		if (i == 1 || i == 2 || i == 4 || i == 9 || i == 12 || i == 13 || i == 14)
		{
			totalResult += huffmanToSymbols[3][testTranslator[(symbolIndexSequence)[i]]];
		}
		else
			totalResult += huffmanToSymbols[4][testTranslator[(symbolIndexSequence)[i]]];
	}
	if (totalResult == "")
		ASSERT_TRUE(false);
	else
		ASSERT_EQ(string2, totalResult);
}

TEST(huffman, decodeDictionaryDiddy)
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
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<vector<CompactPair>> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
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

	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);
	vector<vector<CompactPair>> generationVectors;

	finalDict.generateCompactDictionary(
		dictionary,
		terminals,
		pairs,
		indices,
		terminalIndices,
		generationVectors);

	vector<long> testIndices;

	for (auto &entry : indices)
	{
		for (auto &subentry : entry.second)
		{
			testIndices.push_back(entry.first);
			testIndices.push_back(subentry.first);
			testIndices.push_back(subentry.second);
			testIndices.push_back(-1);
		}
	}

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	vector<long> testdictionarysymbol;
	vector<Pair> testdictionary;

	for (auto &entry : dictionary)
	{
		testdictionarysymbol.push_back(entry.first);
		testdictionary.push_back(entry.second);
	}

	vector<long> testhuffmanCodessymbol;
	vector<HuffmanNode> testhuffmanCodes;

	for (auto &entry : huffmanCodes)
	{
		testhuffmanCodessymbol.push_back(entry.first);
		testhuffmanCodes.push_back(entry.second);
	}

	string outstring = "testHuffmanDictionary2";

	out.huffmanDictionary(
		outstring,
		maxLength,
		firstCode,
		numl,
		dictionary,
		indices,
		terminalIndices,
		huffmanToSymbol);

	ifstream ifs;
	ifs.open(outstring, ios::binary);

	dense_hash_map<long, dense_hash_map<long, long>> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	long *firstCodes;

	h.decodeDictionary(ifs, firstCodes, symbolIndices);

	vector<long> testsymbolIndices;

	for (auto &entry : symbolIndices)
	{
		for (auto &subentry : entry.second)
		{
			testsymbolIndices.push_back(entry.first);
			testsymbolIndices.push_back(subentry.first);
			testsymbolIndices.push_back(subentry.second);
			testsymbolIndices.push_back(-1);
		}
	}

	ASSERT_EQ(4, (symbolIndices)[3].size());
	ASSERT_EQ(8, (symbolIndices)[4].size());

	long codeLength = 3;
	long nrOfCodes = 4;
	long codeStart = firstCodes[2];
	long code = 4;
	long symbol = (huffmanToSymbol[3])[4];
	long index;

	//Test codes of length 3
	
	for (int i = codeStart; i < codeStart + nrOfCodes; i++)
	{
		code = i;
		symbol = (huffmanToSymbol[codeLength])[code];

		if (symbol >= initialSymbolValue)
			index = (indices[dictionary[symbol].leftSymbol])[dictionary[symbol].rightSymbol];
		else
			index = (terminalIndices)[symbol];

		ASSERT_EQ(index, (symbolIndices)[codeLength][code]);
	}

	//Test codes of length 4
	nrOfCodes = 8;
	codeStart = firstCodes[3];

	for (int i = codeStart; i < codeStart + nrOfCodes; i++)
	{
		code = i;
		symbol = (huffmanToSymbol[codeLength])[code];

		if (symbol >= initialSymbolValue)
			index = (indices[dictionary[symbol].leftSymbol])[dictionary[symbol].rightSymbol];
		else
			index = (terminalIndices)[symbol];

		ASSERT_EQ(index, (symbolIndices)[codeLength][code]);
	}
}

TEST(huffman, decodeDictionaryDuplicates)
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
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;

	string input1 = "duplicatesLong.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<vector<CompactPair>> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
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

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbb";
	string string2 = "DDAEE"; //Actual: "259 259 256 260 260"

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);

	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);
	vector<vector<CompactPair>> generationVectors;

	finalDict.generateCompactDictionary(
		dictionary,
		terminals,
		pairs,
		indices,
		terminalIndices,
		generationVectors);

	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	string outstring = "testDuplicatesLongCompressed";
	out.huffmanDictionary(
		outstring,
		maxLength,
		firstCode,
		numl,
		dictionary,
		indices,
		terminalIndices,
		huffmanToSymbol);

	ifstream ifs;
	ifs.open(outstring, ios::binary);

	dense_hash_map<long, dense_hash_map<long, long>> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	long *firstCodes;

	h.decodeDictionary(ifs, firstCodes, symbolIndices);

	ASSERT_EQ(1, (symbolIndices)[1].size());
	ASSERT_EQ(2, (symbolIndices)[2].size());

	long codeLength = 1;
	long code = 1;
	long symbol = (huffmanToSymbol[1])[1];
	long index;

	//Test codes of length 1

	for (int i = code; i < 2; i++)
	{
		code = i;
		symbol = (huffmanToSymbol[codeLength])[code];

		if (symbol >= initialSymbolValue)
			index = (indices[dictionary[symbol].leftSymbol])[dictionary[symbol].rightSymbol];
		else
			index = (terminalIndices)[symbol];

		ASSERT_EQ(index, (symbolIndices)[codeLength][code]);
	}

	//Test codes of length 2
	codeLength = 2;

	for (int i = 0; i < 2; i++)
	{
		code = i;
		symbol = (huffmanToSymbol[codeLength])[code];

		if (symbol >= initialSymbolValue)
			index = (indices[dictionary[symbol].leftSymbol])[dictionary[symbol].rightSymbol];
		else
			index = (terminalIndices)[symbol];

		ASSERT_EQ(index, (symbolIndices)[codeLength][code]);
	}
}