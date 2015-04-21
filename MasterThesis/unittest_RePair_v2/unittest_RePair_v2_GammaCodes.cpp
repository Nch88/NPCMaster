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

TEST(gammaCodes, binaryToInt)
{
	GammaCode gc;
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
	vector<unsigned long> result;
	string prefix = "0100101110";
	string gamma = "0011001110101101111100001110001111001011100111110100111010111101101110111";
	unsigned long expected = 15;

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
	vector<unsigned long> result;
	string prefix = "0100101110";
	string gamma = "001100111010110111110000111000111100101110011111010011101011110110111011111010101";
	unsigned long expected = 15;

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
	vector<unsigned long> result;
	string prefix = "101010101010101";
	string gamma = "110100010111010100010101010101101001011";
	unsigned long expected = 0;

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


TEST(gammaCodes, writeToFile)
{
	GammaCode gc;
	Outputter out;
	string gamma = "100100100100100100100100100100100100";

	ofstream myfile;
	myfile.open("gammafun.npc", ios::binary);
	out.dictionary("gammafun.npc", myfile, gamma, true);
}