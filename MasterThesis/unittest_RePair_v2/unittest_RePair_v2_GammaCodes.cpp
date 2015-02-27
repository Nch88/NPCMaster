#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(encoding, getBinaryCode_1to15)
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

TEST(encoding, getBinaryCode_0)
{
	GammaCode gc;
	ASSERT_EQ("0", gc.getBinaryCode(0));
}

TEST(encoding, getGammaCode)
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

TEST(encoding, encode_simplePairs)
{
	GammaCode gc;

	//This should be (0,1)(1,2)...(4,5)
	vector<CompactPair*> pairs;
	for (int i = 0; i < 5; ++i)
	{
		CompactPair *c = new CompactPair(i, i + 1);
		pairs.push_back(c);
	}
	unordered_set<unsigned int> terminals = { 1, 2, 3, 4, 5, 6 };
	string terminalsGamma = "",leftElementsGamma = "", rightElementsBinary = "";
	gc.encode(pairs, terminals, terminalsGamma, leftElementsGamma, rightElementsBinary);
	
	ASSERT_EQ("10010111000110011101011011", terminalsGamma);
	ASSERT_EQ("100100100100100", leftElementsGamma);
	ASSERT_EQ("001010011100101", rightElementsBinary);
	
	//Cleanup
	for (int i = 0; i < 5; ++i)
	{
		delete pairs[i];
	}
}

TEST(encoding, makeFinalString)
{
	GammaCode gc;

	//This should be (0,1)(1,2)...(4,5)
	vector<CompactPair*> pairs;
	for (int i = 0; i < 5; ++i)
	{
		CompactPair *c = new CompactPair(i, i + 1);
		pairs.push_back(c);
	}
	unordered_set<unsigned int> terminals = { 1, 2, 3, 4, 5, 6 };
	string terminalsGamma = "", finalString = "";
	gc.makeFinalString(pairs, terminals, terminalsGamma, finalString);

	ASSERT_EQ("10010111000110011101011011", terminalsGamma);
	ASSERT_EQ("00000000000000000000000000000101100100100100100001010011100101", finalString);
	
	//Cleanup
	for (int i = 0; i < 5; ++i)
	{
		delete pairs[i];
	}
}

TEST(decode, binaryToInt)
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

TEST(decode, decodeGammaString_simple)
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

TEST(decode, decodeGammaString_remainder)
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

TEST(decode, decodeGammaString_empty)
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