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

TEST(gammaCodes, encode_diddy_explicit)
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
	long symbols(initialSymbolValue);

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	GammaCode gc;
	Dictionary dict;


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

	vector<vector<CompactPair>> pairs;
	dense_hash_map<long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);
	vector<long> terminalVector;
	dict.generateCompactDictionary(dictionary, terminals, terminalVector, pairs, indices, terminalIndices, c);

	string terminalsGamma = "";
	vector<string> leftElementsGammas;
	vector<string> rightElementsBinaries;

	//Test variables
	string terminalsGammaResult = ""; 
	vector<string> terminalsGammaResults;


	//!!!!!!!!!!!!!!!! This is encode explicit !!!!!!!!!!!!!!!!!!!
	int generations = pairs.size();
	int genP1 = 0;
	long firstElement = 0;
	string fstElmtGamma = "";

	//Sort terminals
	//terminalVector.resize(terminals.size());
	//terminalVector.assign(terminals.begin(), terminals.end());
	string tmpGammaCode = "";
	//Gamma code for terminals
	for (int iP1 = 0; iP1 < terminalVector.size(); ++iP1)
	{
		tmpGammaCode.assign(gc.getGammaCode(terminalVector[iP1]));
		terminalsGamma += tmpGammaCode;
		terminalsGammaResults.push_back(tmpGammaCode);
	}

	for (int i = 0; i < terminalsGammaResults.size(); i++)
	{
		if (i == 0)		
			ASSERT_EQ(46, gc.gammaToInt(terminalsGammaResults[i]));		
		if (i == 1)
			ASSERT_EQ(97, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 2)
			ASSERT_EQ(100, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 3)
			ASSERT_EQ(103, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 4)
			ASSERT_EQ(104, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 5)
			ASSERT_EQ(105, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 6)
			ASSERT_EQ(109, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 7)
			ASSERT_EQ(110, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 8)
			ASSERT_EQ(111, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 9)
			ASSERT_EQ(115, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 10)
			ASSERT_EQ(117, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 11)
			ASSERT_EQ(119, gc.gammaToInt(terminalsGammaResults[i]));
		if (i == 12)
			ASSERT_EQ(121, gc.gammaToInt(terminalsGammaResults[i]));
		terminalsGammaResult += terminalsGammaResults[i];
		
	}
	

	ASSERT_EQ(terminalsGammaResult, terminalsGamma);
	long bitLengthRightValue = terminalVector.size();
	long bitLengthRight = floor(log2(bitLengthRightValue)) + 1;

	string gam1 = "";
	string gam2 = "";
	string gamRes = "";

	//For each generation
	for (genP1 = 0; genP1 < generations; ++genP1)
	{

		//Gamma code for left elements
		firstElement = (pairs[genP1])[0].leftSymbol;
		fstElmtGamma = gc.getGammaCode(firstElement);
		leftElementsGammas.push_back(fstElmtGamma);
		for (int i = 0; i < (pairs[genP1]).size() - 1; ++i)
		{
			tmpGammaCode.assign(gc.getGammaCode((pairs[genP1])[i + 1].leftSymbol - (pairs[genP1])[i].leftSymbol));
			leftElementsGammas[genP1] += tmpGammaCode;
		}

		if (genP1 == 0) //Test
		{
			gam1 = gc.getGammaCode(0);
			gam2 = gc.getGammaCode(5);
			gamRes = gam1 + gam2;

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);			
		}
		if (genP1 == 1) //Test
		{
			gam1 = gc.getGammaCode(12);
			gam2 = gc.getGammaCode(2);
			gamRes = gam1 + gam2;

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);
		}
		if (genP1 == 2) //Test
		{
			gamRes = gc.getGammaCode(2);

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);
		}
		if (genP1 == 3) //Test
		{
			gamRes = gc.getGammaCode(2);

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);
		}
		if (genP1 == 4) //Test
		{
			gamRes = gc.getGammaCode(5);

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);
		}
		if (genP1 == 5) //Test
		{
			gamRes = gc.getGammaCode(13);

			ASSERT_EQ(gamRes, leftElementsGammas[genP1]);
		}

		//Binary code for right elements
		
		string s = "";
		for (int i = 0; i < (pairs[genP1]).size(); ++i)
		{
			s.assign(gc.getBinaryCode((pairs[genP1])[i].rightSymbol));

			ASSERT_TRUE(s.length() <= bitLengthRight);

			rightElementsBinaries.push_back("");
			for (int k = 0; k < (bitLengthRight - s.length()); ++k)
			{
				rightElementsBinaries[genP1] += '0';
			}
			rightElementsBinaries[genP1] += s;
		}

		if (genP1 == 0) //Test
		{
			ASSERT_EQ(4, bitLengthRight);
			ASSERT_EQ("00100111", rightElementsBinaries[genP1]);
		}
		if (genP1 == 1) //Test
		{
			ASSERT_EQ(4, bitLengthRight);
			ASSERT_EQ("11010011", rightElementsBinaries[genP1]);
		}
		if (genP1 == 2) //Test
		{
			ASSERT_EQ(5, bitLengthRight);
			ASSERT_EQ("01111", rightElementsBinaries[genP1]);
		}
		if (genP1 == 3) //Test
		{
			ASSERT_EQ(5, bitLengthRight);
			ASSERT_EQ("10001", rightElementsBinaries[genP1]);
		}
		if (genP1 == 4) //Test
		{
			ASSERT_EQ(5, bitLengthRight);
			ASSERT_EQ("10010", rightElementsBinaries[genP1]);
		}
		if (genP1 == 5) //Test
		{
			ASSERT_EQ(5, bitLengthRight);
			ASSERT_EQ("10011", rightElementsBinaries[genP1]);
		}

		bitLengthRightValue += pairs[genP1].size();
		bitLengthRight = floor(log2(bitLengthRightValue)) + 1;
	}
	
}

TEST(gammaCodes, encode_diddy)
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
	long symbols(initialSymbolValue);

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	GammaCode gc;
	Dictionary dict;


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

	vector<vector<CompactPair>> pairs;
	dense_hash_map<long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);
	vector<long> terminalVector;
	dict.generateCompactDictionary(dictionary, terminals, terminalVector, pairs, indices, terminalIndices, c);

	string terminalsGamma = "";
	vector<string> leftElementsGammas;
	vector<string> rightElementsBinaries;

	//Test variables
	string terminalsGammaResult = "";

	for (int i = 0; i < 13; i++)
	{
		if (i == 0)
			terminalsGammaResult += gc.getGammaCode(46);
		if (i == 1)
			terminalsGammaResult += gc.getGammaCode(97);
		if (i == 2)
			terminalsGammaResult += gc.getGammaCode(100);
		if (i == 3)
			terminalsGammaResult += gc.getGammaCode(103);
		if (i == 4)
			terminalsGammaResult += gc.getGammaCode(104);
		if (i == 5)
			terminalsGammaResult += gc.getGammaCode(105);
		if (i == 6)
			terminalsGammaResult += gc.getGammaCode(109);
		if (i == 7)
			terminalsGammaResult += gc.getGammaCode(110);
		if (i == 8)
			terminalsGammaResult += gc.getGammaCode(111);
		if (i == 9)
			terminalsGammaResult += gc.getGammaCode(115);
		if (i == 10)
			terminalsGammaResult += gc.getGammaCode(117);
		if (i == 11)
			terminalsGammaResult += gc.getGammaCode(119);
		if (i == 12)
			terminalsGammaResult += gc.getGammaCode(121);
	}

	gc.encode(pairs, terminalVector, terminalsGamma, leftElementsGammas, rightElementsBinaries);

	ASSERT_EQ(terminalsGammaResult, terminalsGamma);

	for (int i = 0; i < leftElementsGammas.size(); i++)
	{
		if (i == 0) //Test
		{
			string gam1 = gc.getGammaCode(0);
			string gam2 = gc.getGammaCode(5);
			string gamRes = gam1 + gam2;

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
		if (i == 1) //Test
		{
			string gam1 = gc.getGammaCode(12);
			string gam2 = gc.getGammaCode(2);
			string gamRes = gam1 + gam2;

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
		if (i == 2) //Test
		{
			string gamRes = gc.getGammaCode(2);

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
		if (i == 3) //Test
		{
			string gamRes = gc.getGammaCode(2);

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
		if (i == 4) //Test
		{
			string gamRes = gc.getGammaCode(5);

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
		if (i == 5) //Test
		{
			string gamRes = gc.getGammaCode(13);

			ASSERT_EQ(gamRes, leftElementsGammas[i]);
		}
	}

	for (int i = 0; i < rightElementsBinaries.size(); i++)
	{
		if (i == 0) //Test
		{
			ASSERT_EQ("00100111", rightElementsBinaries[i]);
		}
		if (i == 1) //Test
		{
			ASSERT_EQ("11010011", rightElementsBinaries[i]);
		}
		if (i == 2) //Test
		{
			ASSERT_EQ("01111", rightElementsBinaries[i]);
		}
		if (i == 3) //Test
		{
			ASSERT_EQ("10001", rightElementsBinaries[i]);
		}
		if (i == 4) //Test
		{
			ASSERT_EQ("10010", rightElementsBinaries[i]);
		}
		if (i == 5) //Test
		{
			ASSERT_EQ("10011", rightElementsBinaries[i]);
		}
	}
}

TEST(gammaCodes, diddy_makeFinalString)
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
	long symbols(initialSymbolValue);

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	GammaCode gc;
	Dictionary dict;


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

	vector<vector<CompactPair>> pairs;
	dense_hash_map<long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);
	vector<long> terminalVector;
	dict.generateCompactDictionary(dictionary, terminals, terminalVector, pairs, indices, terminalIndices, c);

	//Test variables
	string terminalsGammaResult = "";

	for (int i = 0; i < 13; i++)
	{
		if (i == 0)
			terminalsGammaResult += gc.getGammaCode(46);
		if (i == 1)
			terminalsGammaResult += gc.getGammaCode(97);
		if (i == 2)
			terminalsGammaResult += gc.getGammaCode(100);
		if (i == 3)
			terminalsGammaResult += gc.getGammaCode(103);
		if (i == 4)
			terminalsGammaResult += gc.getGammaCode(104);
		if (i == 5)
			terminalsGammaResult += gc.getGammaCode(105);
		if (i == 6)
			terminalsGammaResult += gc.getGammaCode(109);
		if (i == 7)
			terminalsGammaResult += gc.getGammaCode(110);
		if (i == 8)
			terminalsGammaResult += gc.getGammaCode(111);
		if (i == 9)
			terminalsGammaResult += gc.getGammaCode(115);
		if (i == 10)
			terminalsGammaResult += gc.getGammaCode(117);
		if (i == 11)
			terminalsGammaResult += gc.getGammaCode(119);
		if (i == 12)
			terminalsGammaResult += gc.getGammaCode(121);
	}
	string finalExpectedResult = "";

	finalExpectedResult += gc.getGammaCode(13);
	finalExpectedResult += terminalsGammaResult;

	//Generation header
	finalExpectedResult += gc.getGammaCode(6);

	//Generation 1
	finalExpectedResult += gc.getGammaCode(2);
	finalExpectedResult += gc.getGammaCode(12);
	finalExpectedResult += gc.getGammaCode(0);
	finalExpectedResult += gc.getGammaCode(5);
	finalExpectedResult += "00100111";

	//Generation 2
	finalExpectedResult += gc.getGammaCode(2);
	finalExpectedResult += gc.getGammaCode(14);
	finalExpectedResult += gc.getGammaCode(12);
	finalExpectedResult += gc.getGammaCode(2);
	finalExpectedResult += "11010011";

	//Generation 3
	finalExpectedResult += gc.getGammaCode(1);
	finalExpectedResult += gc.getGammaCode(16);
	finalExpectedResult += gc.getGammaCode(2);
	finalExpectedResult += "01111";

	//Generation 4
	finalExpectedResult += gc.getGammaCode(1);
	finalExpectedResult += gc.getGammaCode(17);
	finalExpectedResult += gc.getGammaCode(2);
	finalExpectedResult += "10001";

	//Generation 5
	finalExpectedResult += gc.getGammaCode(1);
	finalExpectedResult += gc.getGammaCode(18);
	finalExpectedResult += gc.getGammaCode(5);
	finalExpectedResult += "10010";

	//Generation 6
	finalExpectedResult += gc.getGammaCode(1);
	finalExpectedResult += gc.getGammaCode(19);
	finalExpectedResult += gc.getGammaCode(13);
	finalExpectedResult += "10011";

	string *finalstring = new string();

	gc.makeFinalString(
		pairs,
		terminalVector,
		*finalstring);

	/*string pTestTHeader = finalstring->substr(0, 7);
	string pTestTHeaderExpected = "1110110";

	string pTestTerminals = finalstring->substr(7, 167);
	string pTestTerminalsExpected = terminalsGammaResult;
	ASSERT_EQ(pTestTerminalsExpected,pTestTerminals);

	string pTestPHeader = finalstring->substr(7 + 167, 5);
	string pTestPHeaderExpected = gc.getGammaCode(6);

	string pTest_gen1h = finalstring->substr(7 + 167 + 5, 10);
	string pTest_gen1h_Expected = gc.getGammaCode(2) + gc.getGammaCode(12);

	string pTest_gen1L = finalstring->substr(7 + 167 + 5 + 10, 8);
	string pTest_gen1l_Expected = gc.getGammaCode(0) + gc.getGammaCode(7);

	string pTest_gen1R = finalstring->substr(7 + 167 + 5 + 10 + 8, 8);
	string pTest_gen1R_Expected = "00100011";

	string pTest_gen2h = finalstring->substr(7 + 167 + 5 + 10 + 8 + 8, 10);
	string pTest_gen2h_Expected = gc.getGammaCode(2) + gc.getGammaCode(14);

	string pTest_gen2L = finalstring->substr(7 + 167 + 5 + 10 + 8 + 8 + 10, 12);
	string pTest_gen2l_Expected = gc.getGammaCode(5) + gc.getGammaCode(7);

	string pTest_gen2R = finalstring->substr(7 + 167 + 5 + 10 + 8 + 8 + 10 + 12, 8);
	string pTest_gen2R_Expected = "11101101";*/


	ASSERT_EQ(finalExpectedResult, *finalstring);
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
	vector<long> result;
	string prefix = "0100101110";
	string gamma = "0011001110101101111100001110001111001011100111110100111010111101101110111";
	long expected = 15;

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
	vector<long> result;
	string prefix = "0100101110";
	string gamma = "001100111010110111110000111000111100101110011111010011101011110110111011111010101";
	long expected = 15;

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
	vector<long> result;
	string prefix = "101010101010101";
	string gamma = "110100010111010100010101010101101001011";
	long expected = 0;

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
	Conditions c;
	string gamma = "100100100100100100100100100100100100";

	ofstream myfile;
	myfile.open("gammafun.npc", ios::binary);
	out.dictionary("gammafun.npc", myfile, gamma, true, c);
}