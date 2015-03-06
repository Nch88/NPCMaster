#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(gammaCodes, getBinaryCode_1to15)
{
	GammaCode gc;
	vector<string> expected = {"1","10","11","100","101","110","111","1000","1001","1010","1011","1100","1101","1110","1111"};
	vector<string> output;
	for (int i = 1; i <= expected.size(); ++i)
	{
		output.push_back(gc.getBinaryCode(i));
	}	
	for (int i = 0; i < expected.size(); ++i)
	{
		ASSERT_EQ(expected[i], output[i]);
	}
}

TEST(gammaCodes, getBinaryCode_0)
{
	GammaCode gc;
	ASSERT_EQ("0", gc.getBinaryCode(0));
}

TEST(gammaCodes, getGammaCode)
{
	GammaCode gc;
	vector<string> expected = { "0", "100", "101", "11000", "11001", "11010", "11011", "1110000", "1110001", "1110010", "1110011", "1110100", "1110101", "1110110", "1110111"};
	vector<string> output;
	for (int i = 0; i < expected.size(); ++i)
	{
		output.push_back(gc.getGammaCode(i));
	}
	for (int i = 0; i < expected.size(); ++i)
	{
		ASSERT_EQ(expected[i], output[i]);
	}
}

//TEST(gammaCodes, encode_diddy)
//{
//	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unordered_map<unsigned int, Pair> dictionary;
//	unsigned int symbols(initialSymbolValue);
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//	MyTest t;
//	Huffman h;
//	GammaCode gc;
//	Dictionary dict;
//
//	string input1 = "diddy.txt";
//
//	bool skip = false;
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned int> terminals;
//	string filename = input1;
//	ifstream file(filename);
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
//	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
//	string string2 = "sHHAo.wahFEumFo";
//
//	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
//
//	algP.run(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		terminals,
//		symbols,
//		c);
//
//	vector<vector<CompactPair*>*> generationVectors;
//	vector<vector<CompactPair*>*> pairs;
//	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> indices;
//	unordered_map<unsigned int, unsigned int> *terminalIndices = new unordered_map<unsigned int, unsigned int>();
//	dict.generateCompactDictionary(dictionary, terminals, pairs, indices, terminalIndices, generationVectors);
//
//	string terminalsGamma = "";
//	vector<string> leftElementsGamma;
//	vector<string> rightElementsBinary;
//
//	gc.encode(pairs, terminals, terminalsGamma, leftElementsGamma, rightElementsBinary, generationVectors);
//
//	ASSERT_TRUE(true);
//}

TEST(gammaCodes, encode_makeFinalString)
{
	//GammaCode gc;

	////This should be (0,1)(1,2)...(4,5)
	//vector<CompactPair*> pairs;
	//for (int i = 0; i < 5; ++i)
	//{
	//	CompactPair *c = new CompactPair(i, i + 1);
	//	pairs.push_back(c);
	//}
	//unordered_set<unsigned int> terminals = { 1, 2, 3, 4, 5, 6 };
	//string finalString = "";
	//gc.makeFinalString(pairs, terminals, finalString);

	//ASSERT_EQ("1101110010111000110011101011011110100100100100100001010011100101", finalString);
	//
	////Cleanup
	//for (int i = 0; i < 5; ++i)
	//{
	//	delete pairs[i];
	//}
}

TEST(gammaCodes, binaryToInt)
{
	GammaCode gc;
	ASSERT_EQ(0, gc.binaryToInt(""));
	ASSERT_EQ(0, gc.binaryToInt("0"));
	ASSERT_EQ(1, gc.binaryToInt("1"));
	ASSERT_EQ(1, gc.binaryToInt("01"));
	ASSERT_EQ(1, gc.binaryToInt("001"));
	ASSERT_EQ(2, gc.binaryToInt("10"));
	ASSERT_EQ(3, gc.binaryToInt("11"));
}

TEST(gammaCodes, decodeGammaString_simple)
{
	GammaCode gc;
	vector<unsigned int> result;
	string prefix = "0100101110";
	string gamma = "0011001110101101111100001110001111001011100111110100111010111101101110111";
	unsigned int expected = 15;

	gc.decodeGammaString(prefix, gamma, result, expected);

	for (int i = 0; i < result.size(); ++i)
	{
		ASSERT_EQ(i, result[i]);
	}
	ASSERT_EQ("", prefix);
}

TEST(gammaCodes, decodeGammaString_remainder)
{
	GammaCode gc;
	vector<unsigned int> result;
	string prefix = "0100101110";
	string gamma = "001100111010110111110000111000111100101110011111010011101011110110111011111010101";
	unsigned int expected = 15;

	gc.decodeGammaString(prefix, gamma, result, expected);

	for (int i = 0; i < result.size(); ++i)
	{
		ASSERT_EQ(i, result[i]);
	}
	ASSERT_EQ("11010101", prefix);
}

TEST(gammaCodes, decodeGammaString_empty)
{
	GammaCode gc;
	vector<unsigned int> result;
	string prefix = "101010101010101";
	string gamma = "110100010111010100010101010101101001011";
	unsigned int expected = 0;

	gc.decodeGammaString(prefix, gamma, result, expected);

	ASSERT_TRUE(result.empty());
	
	ASSERT_EQ("101010101010101110100010111010100010101010101101001011", prefix);
}

TEST(gammaCodes, decode_gammaToInt)
{
	GammaCode gc;
	vector<string> gammas = { "0", "100", "101", "11000", "11001", "11010", "11011", "1110000", "1110001", "1110010", "1110011", "1110100", "1110101", "1110110", "1110111", "111100000", "111100001", "111100010", "111100011"};
	for (int i = 0; i < gammas.size(); ++i)
		ASSERT_EQ(i, gc.gammaToInt(gammas[i]));
}

TEST(gammaCodes, decode_simple)
{
	//GammaCode gc;
	//string gamma = "1001001001001";//T = {1} and P = {(1,1)}
	//vector<CompactPair*> decodedPairs;
	//unordered_set<unsigned int> decodedTerminals;
	//gc.decode(decodedPairs, decodedTerminals, gamma);
	//ASSERT_EQ(1, decodedPairs.size());
	//ASSERT_EQ(1, decodedPairs[0]->leftSymbol);
	//ASSERT_EQ(1, decodedPairs[0]->rightSymbol);
	//ASSERT_EQ(1, decodedTerminals.size());
	//ASSERT_EQ(1, decodedTerminals.count(1));
}

TEST(gammaCodes, encodeThenDecode_simplePairs)
{
	//GammaCode gc;

	////This should be (0,1)(1,2)...(4,5)
	//vector<CompactPair*> pairs;
	//for (int i = 0; i < 5; ++i)
	//{
	//	CompactPair *c = new CompactPair(i, i + 1);
	//	pairs.push_back(c);
	//}
	//unordered_set<unsigned int> terminals = { 1, 2, 3, 4, 5, 6 };
	//string encodedString;

	//gc.makeFinalString(pairs, terminals, encodedString);

	//vector<CompactPair*> decodedPairs;
	//unordered_set<unsigned int> decodedTerminals;

	//gc.decode(decodedPairs, decodedTerminals, encodedString);
	//for (int i = 0; i < pairs.size(); ++i)
	//{
	//	ASSERT_EQ(pairs[i]->leftSymbol, decodedPairs[i]->leftSymbol);
	//	ASSERT_EQ(pairs[i]->rightSymbol, decodedPairs[i]->rightSymbol);
	//}
	//ASSERT_EQ(terminals, decodedTerminals);

	////Cleanup
	//for (int i = 0; i < 5; ++i)
	//{
	//	delete pairs[i];
	//}
}

TEST(gammaCodes, writeToFile)
{
	GammaCode gc;
	Outputter out;
	string gamma = "100100100100100100100100100100100100";
	out.dictionary("gammafun.npc", gamma, true);
}