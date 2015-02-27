#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(outputter, diddyHuffmanCode)
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
	unsigned int *firstCode = nullptr;
	unsigned int *numl = nullptr;
	unsigned int maxLength = 0;
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength);

	out.huffmanEncoding(
		input1,
		sequenceArray,
		huffmanCodes,
		true);

	//Actual test
	string expected1 = "00000100100001110101010100001000";
	string expected2 = "00111001100111111110101000000000";
	string expected3 = "10000000000000000000000000001001";
	
	ifstream ifs;
	ifs.open("Compressed_diddy.txt", ios::binary);
	string result = "";
	string totalResult = "";
	char byte;
	bitset<8> *bits;
	int count = 0;

	if (ifs.is_open())
	{		
		while (ifs.get(byte))
		{
			bits = new bitset<8>(byte);

			for (int i = bits->size() - 1; i >= 0; --i)
			{
				if ((*bits)[i] == 0)
					result += "0";
				else
					result += "1";
			}
			if (result.size() == 32 && count == 0)
			{
				ASSERT_EQ(expected1, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 1)
			{
				ASSERT_EQ(expected2, result);
				++count;
				totalResult += result;
				result = "";
			}
			if (result.size() == 32 && count == 2)
			{
				ASSERT_EQ(expected3, result);
				++count;
				totalResult += result;
				result = "";
			}
			delete bits;
		}
	}
	ASSERT_EQ(expected1 + expected2 +expected3, totalResult);
}

TEST(outputter, diddyHuffmanDictionary)
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
	unsigned int *firstCode = nullptr;
	unsigned int *numl = nullptr;
	unsigned int maxLength = 0;
	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength);

	//TODO: Test output of Huffman dictionary
	//out.huffmanDictionary(
	//	"testHuffmanDictionary",
	//	cardinality,)
		
}