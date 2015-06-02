// RePair_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace google;

void getArg(char *& arg, string &result)
{
	result = "";

	while (*arg != '\0')
	{
		result += *arg;
		++arg;
	}
}

int setMode(string &mode)
{
	if (mode == "e" || mode == "encoding")
		return 1;
	if (mode == "d" || mode == "decoding")
		return 2;
	return 0;
}

int asciiToInt(const int &v)
{
	switch (v)
	{
	case 48:
			return 0;
	case 49:
		return 1;
	case 50:
		return 2;
	case 51:
		return 3;
	case 52:
		return 4;
	case 53:
		return 5;
	case 54:
		return 6;
	case 55:
		return 7;
	case 56:
		return 8;
	case 57:
		return 9;

	default:
		return -1;
		break;
	}
}

int stringToInt(string &arg, int &result)
{
	int size = arg.size();
	result = 0;
	if (size > 2000000000)
		return 2;

	for (int i = 0; i < size; i++)
	{
		if ((int)arg[i] >= 48 && (int)arg[i] <= 57)						//Check that the arg is a number
		{
			result += (asciiToInt((int)arg[i]) * (pow(10, size - i - 1)));			//Add the value according to base 10 interpretation
		}
		else
			return 1;
	}
	return 0;
}

void getAvgResult(TestSuite & avgResult, vector<TestSuite> & testResults)
{
	for (int i = 0; i < testResults.size(); i++)
	{
		if (i == 0)
		{
			avgResult.blocksizemb = testResults[i].blocksizemb;
			avgResult.c_dictionary = testResults[i].c_dictionary;
			avgResult.c_huffmanDictionary = testResults[i].c_huffmanDictionary;
			avgResult.c_origSize = testResults[i].c_origSize;
			avgResult.c_sequence = testResults[i].c_sequence;

			avgResult.m_huffDic_firstCodes_max_acrossBlocks = testResults[i].m_huffDic_firstCodes_max_acrossBlocks;
			avgResult.m_huffDic_huffmanToSymbol_max_acrossBlocks = testResults[i].m_huffDic_huffmanToSymbol_max_acrossBlocks;
			avgResult.m_huffDic_nrOfCodes_max_acrossBlocks = testResults[i].m_huffDic_nrOfCodes_max_acrossBlocks;
			avgResult.m_huffDic_pairVectors_max_acrossBlocks = testResults[i].m_huffDic_pairVectors_max_acrossBlocks;
			avgResult.m_huffDic_phraseTable_max_acrossBlocks = testResults[i].m_huffDic_phraseTable_max_acrossBlocks;
			avgResult.m_huffDic_symbolToGen_max_acrossBlocks = testResults[i].m_huffDic_symbolToGen_max_acrossBlocks;
			avgResult.m_huffDic_terminalVector_max_acrossBlocks = testResults[i].m_huffDic_terminalVector_max_acrossBlocks;
			avgResult.m_huffDic_total_acrossBlocks = testResults[i].m_huffDic_total_acrossBlocks;
			avgResult.m_huffEnc_codeLengths_max_acrossBlocks = testResults[i].m_huffEnc_codeLengths_max_acrossBlocks;
			avgResult.m_huffEnc_firstCodes_max_acrossBlocks = testResults[i].m_huffEnc_firstCodes_max_acrossBlocks;
			avgResult.m_huffEnc_frequencies_max_acrossBlocks = testResults[i].m_huffEnc_frequencies_max_acrossBlocks;
			avgResult.m_huffEnc_huffmanCodes_max_acrossBlocks = testResults[i].m_huffEnc_huffmanCodes_max_acrossBlocks;
			avgResult.m_huffEnc_huffmanToSymbol_max_acrossBlocks = testResults[i].m_huffEnc_huffmanToSymbol_max_acrossBlocks;
			avgResult.m_huffEnc_nextCodes_max_acrossBlocks = testResults[i].m_huffEnc_nextCodes_max_acrossBlocks;
			avgResult.m_huffEnc_nrOfCodes_max_acrossBlocks = testResults[i].m_huffEnc_nrOfCodes_max_acrossBlocks;
			avgResult.m_huffEnc_phraseTable_max_acrossBlocks = testResults[i].m_huffEnc_phraseTable_max_acrossBlocks;
			avgResult.m_huffEnc_sequenceArray_max_acrossBlocks = testResults[i].m_huffEnc_sequenceArray_max_acrossBlocks;
			avgResult.m_huffEnc_total_acrossBlocks = testResults[i].m_huffEnc_total_acrossBlocks;
			avgResult.m_init_pairRecord_max_acrossBlocks = testResults[i].m_init_pairRecord_max_acrossBlocks;
			avgResult.m_init_pairTracker_max_acrossBlocks = testResults[i].m_init_pairTracker_max_acrossBlocks;
			avgResult.m_init_priorityQueue_max_acrossBlocks = testResults[i].m_init_priorityQueue_max_acrossBlocks;
			avgResult.m_init_sequenceArray_max_acrossBlocks = testResults[i].m_init_sequenceArray_max_acrossBlocks;
			avgResult.m_init_total_acrossBlocks = testResults[i].m_init_total_acrossBlocks;
			avgResult.m_norDic_firstCodes_max_acrossBlocks = testResults[i].m_norDic_firstCodes_max_acrossBlocks;
			avgResult.m_norDic_huffmanToSymbol_max_acrossBlocks = testResults[i].m_norDic_huffmanToSymbol_max_acrossBlocks;
			avgResult.m_norDic_nrOfCodes_max_acrossBlocks = testResults[i].m_norDic_nrOfCodes_max_acrossBlocks;
			avgResult.m_norDic_offsets_max_acrossBlocks = testResults[i].m_norDic_offsets_max_acrossBlocks;
			avgResult.m_norDic_pairVectors_max_acrossBlocks = testResults[i].m_norDic_pairVectors_max_acrossBlocks;
			avgResult.m_norDic_phraseTable_max_acrossBlocks = testResults[i].m_norDic_phraseTable_max_acrossBlocks;
			avgResult.m_norDic_roots_max_acrossBlocks = testResults[i].m_norDic_roots_max_acrossBlocks;
			avgResult.m_norDic_sequenceArray_max_acrossBlocks = testResults[i].m_norDic_sequenceArray_max_acrossBlocks;
			avgResult.m_norDic_supportStructures_total_acrossBlocks = testResults[i].m_norDic_supportStructures_total_acrossBlocks;
			avgResult.m_norDic_symbolToGen_max_acrossBlocks = testResults[i].m_norDic_symbolToGen_max_acrossBlocks;
			avgResult.m_norDic_terminals_max_acrossBlocks = testResults[i].m_norDic_terminals_max_acrossBlocks;
			avgResult.m_norDic_terminalVector_max_acrossBlocks = testResults[i].m_norDic_terminalVector_max_acrossBlocks;
			avgResult.m_norDic_total_acrossBlocks = testResults[i].m_norDic_total_acrossBlocks;
			avgResult.m_repair_pairRecord_max_acrossBlocks = testResults[i].m_repair_pairRecord_max_acrossBlocks;
			avgResult.m_repair_phraseTable_max_acrossBlocks = testResults[i].m_repair_phraseTable_max_acrossBlocks;
			avgResult.m_repair_priorityQueue_max_acrossBlocks = testResults[i].m_repair_priorityQueue_max_acrossBlocks;
			avgResult.m_repair_sequenceArray_max_acrossBlocks = testResults[i].m_repair_sequenceArray_max_acrossBlocks;
			avgResult.m_repair_total_acrossBlocks = testResults[i].m_repair_total_acrossBlocks;
			avgResult.m_total_acrossBlocks = testResults[i].m_total_acrossBlocks;

			avgResult.m_huffDic_firstCodes_max = testResults[i].m_huffDic_firstCodes_max;
			avgResult.m_huffDic_huffmanToSymbol_max = testResults[i].m_huffDic_huffmanToSymbol_max;
			avgResult.m_huffDic_nrOfCodes_max = testResults[i].m_huffDic_nrOfCodes_max;
			avgResult.m_huffDic_pairVectors_max = testResults[i].m_huffDic_pairVectors_max;
			avgResult.m_huffDic_phraseTable_max = testResults[i].m_huffDic_phraseTable_max;
			avgResult.m_huffDic_symbolToGen_max = testResults[i].m_huffDic_symbolToGen_max;
			avgResult.m_huffDic_terminalVector_max = testResults[i].m_huffDic_terminalVector_max;
			avgResult.m_huffDic_total = testResults[i].m_huffDic_total;
			avgResult.m_huffEnc_codeLengths_max = testResults[i].m_huffEnc_codeLengths_max;
			avgResult.m_huffEnc_firstCodes_max = testResults[i].m_huffEnc_firstCodes_max;
			avgResult.m_huffEnc_frequencies_max = testResults[i].m_huffEnc_frequencies_max;
			avgResult.m_huffEnc_huffmanCodes_max = testResults[i].m_huffEnc_huffmanCodes_max;
			avgResult.m_huffEnc_huffmanToSymbol_max = testResults[i].m_huffEnc_huffmanToSymbol_max;
			avgResult.m_huffEnc_nextCodes_max = testResults[i].m_huffEnc_nextCodes_max;
			avgResult.m_huffEnc_nrOfCodes_max = testResults[i].m_huffEnc_nrOfCodes_max;
			avgResult.m_huffEnc_phraseTable_max = testResults[i].m_huffEnc_phraseTable_max;
			avgResult.m_huffEnc_sequenceArray_current = testResults[i].m_huffEnc_sequenceArray_current;
			avgResult.m_huffEnc_sequenceArray_max = testResults[i].m_huffEnc_sequenceArray_max;
			avgResult.m_huffEnc_total = testResults[i].m_huffEnc_total;
			avgResult.m_init_pairRecord_current = testResults[i].m_init_pairRecord_current;
			avgResult.m_init_pairRecord_max = testResults[i].m_init_pairRecord_max;
			avgResult.m_init_pairTracker_current = testResults[i].m_init_pairTracker_current;
			avgResult.m_init_pairTracker_max = testResults[i].m_init_pairTracker_max;
			avgResult.m_init_priorityQueue_max = testResults[i].m_init_priorityQueue_max;
			avgResult.m_init_sequenceArray_current = testResults[i].m_init_sequenceArray_current;
			avgResult.m_init_sequenceArray_max = testResults[i].m_init_sequenceArray_max;
			avgResult.m_init_total = testResults[i].m_init_total;
			avgResult.m_norDic_firstCodes_max = testResults[i].m_norDic_firstCodes_max;
			avgResult.m_norDic_huffmanToSymbol_max = testResults[i].m_norDic_huffmanToSymbol_max;
			avgResult.m_norDic_nrOfCodes_max = testResults[i].m_norDic_nrOfCodes_max;
			avgResult.m_norDic_offsets_max = testResults[i].m_norDic_offsets_max;
			avgResult.m_norDic_pairVectors_max = testResults[i].m_norDic_pairVectors_max;
			avgResult.m_norDic_phraseTable_max = testResults[i].m_norDic_phraseTable_max;
			avgResult.m_norDic_roots_max = testResults[i].m_norDic_roots_max;
			avgResult.m_norDic_sequenceArray_current = testResults[i].m_norDic_sequenceArray_current;
			avgResult.m_norDic_sequenceArray_max = testResults[i].m_norDic_sequenceArray_max;
			avgResult.m_norDic_supportStructures_total = testResults[i].m_norDic_supportStructures_total;
			avgResult.m_norDic_symbolToGen_max = testResults[i].m_norDic_symbolToGen_max;
			avgResult.m_norDic_terminals_max = testResults[i].m_norDic_terminals_max;
			avgResult.m_norDic_terminalVector_max = testResults[i].m_norDic_terminalVector_max;
			avgResult.m_norDic_total = testResults[i].m_norDic_total;
			avgResult.m_repair_pairRecord_current = testResults[i].m_repair_pairRecord_current;
			avgResult.m_repair_pairRecord_max = testResults[i].m_repair_pairRecord_max;
			avgResult.m_repair_phraseTable_max = testResults[i].m_repair_phraseTable_max;
			avgResult.m_repair_priorityQueue_max = testResults[i].m_repair_priorityQueue_max;
			avgResult.m_repair_sequenceArray_current = testResults[i].m_repair_sequenceArray_current;
			avgResult.m_repair_sequenceArray_max = testResults[i].m_repair_sequenceArray_max;
			avgResult.m_repair_total = testResults[i].m_repair_total;
			avgResult.m_total = testResults[i].m_total;
			avgResult.s_avgNrOfPhrases_acrossBlocks = testResults[i].s_avgNrOfPhrases_acrossBlocks;
			avgResult.s_filename = testResults[i].s_filename;
			avgResult.s_huffmanCodeLength_max_acrossBlocks = testResults[i].s_huffmanCodeLength_max_acrossBlocks;
			avgResult.s_largestGeneration_acrossBlocks = testResults[i].s_largestGeneration_acrossBlocks;
			avgResult.s_largestGenerationMax_acrossBlocks = testResults[i].s_largestGenerationMax_acrossBlocks;
			avgResult.s_largestGenerationCount_acrossBlocks = testResults[i].s_largestGenerationCount_acrossBlocks;
			avgResult.s_largestGenerationCountMax_acrossBlocks = testResults[i].s_largestGenerationCountMax_acrossBlocks;
			avgResult.s_maxPairs_acrossBlocks = testResults[i].s_maxPairs_acrossBlocks;
			avgResult.s_nrOfBlocks = testResults[i].s_nrOfBlocks;
			avgResult.s_nrOfGenerations_acrossBlocks = testResults[i].s_nrOfGenerations_acrossBlocks;
			avgResult.s_nrOfGenerationsMax_acrossBlocks = testResults[i].s_nrOfGenerationsMax_acrossBlocks;
			avgResult.s_nrOfPhrases_acrossBlocks = testResults[i].s_nrOfPhrases_acrossBlocks;
			avgResult.s_nrOfTerminals_acrossBlocks = testResults[i].s_nrOfTerminals_acrossBlocks;
			avgResult.s_nrOfTerminalsMax_acrossBlocks = testResults[i].s_nrOfTerminalsMax_acrossBlocks;

			avgResult.s_avgNrOfPhrases = testResults[i].s_avgNrOfPhrases;
			avgResult.s_filename = testResults[i].s_filename;
			avgResult.s_huffmanCodeLength_max = testResults[i].s_huffmanCodeLength_max;
			avgResult.s_largestGeneration = testResults[i].s_largestGeneration;
			avgResult.s_largestGenerationMax = testResults[i].s_largestGenerationMax;
			avgResult.s_largestGenerationCount = testResults[i].s_largestGenerationCount;
			avgResult.s_largestGenerationCountMax = testResults[i].s_largestGenerationCountMax;
			avgResult.s_maxPairs = testResults[i].s_maxPairs;
			avgResult.s_nrOfGenerations = testResults[i].s_nrOfGenerations;
			avgResult.s_nrOfGenerationsMax = testResults[i].s_nrOfGenerationsMax;
			avgResult.s_nrOfPhrases = testResults[i].s_nrOfPhrases;
			avgResult.s_nrOfTerminals = testResults[i].s_nrOfTerminals;
			avgResult.s_nrOfTerminalsMax = testResults[i].s_nrOfTerminalsMax;

		}

		avgResult.t_decompression_count += testResults[i].t_decompression.count() / testResults.size();
		avgResult.t_encodeSequence_count += testResults[i].t_encodeSequence.count() / testResults.size();
		avgResult.t_huffmanEncoding_count += testResults[i].t_huffmanEncoding.count() / testResults.size();
		avgResult.t_initialization_count += testResults[i].t_initialization.count() / testResults.size();
		avgResult.t_readDictionary_count += testResults[i].t_readDictionary.count() / testResults.size();
		avgResult.t_repair_count += testResults[i].t_repair.count() / testResults.size();
		avgResult.t_setupDictionary_count += testResults[i].t_setupDictionary.count() / testResults.size();
		avgResult.t_writeDictionary_count += testResults[i].t_writeDictionary.count() / testResults.size();
		avgResult.t_writeHuffmanDictionary_count += testResults[i].t_writeHuffmanDictionary.count() / testResults.size();
	}

}

int interpretParameter(char *&arg, Conditions &c, int &blockSize)
{
	string argS;
	getArg(arg, argS);

	if (argS == "v" || argS == "verbose")
		c.verbose = true;
	else if (argS == "ev" || argS == "extraverbose")
	{
		c.verbose = true;
		c.extraVerbose = true;
	}
	else if (argS == "t" || argS == "timing")
		c.timing = true;
	else if (argS == "c" || argS == "compact")
		c.compact = true;
	else if (argS == "test")
	{
		c.test = true;
		c.runs = 1;
	}
	else if (argS == "test2")
	{
		c.test = true;
		c.runs = 2;
	}
	else if (argS == "test5")
	{
		c.test = true;
		c.runs = 5;
	}
	else if (argS == "test10")
	{
		c.test = true;
		c.runs = 10;
	}
	else
	{		
		int mbs = 1;
		int error = stringToInt(argS, mbs);
		if (error != 0)
		{
			if (error == 1)
			{
				cerr << "Interpret as block size failed, bad parameter." << endl;
				return 7;
			}
			if (error == 2)
			{
				cerr << "Desired multiple of 1MB for block size approaches limit of int." << endl;
				return 8;
			}
			
		}
		if (mbs <= 1000)
		{
			blockSize = blockSize * mbs;
			blockSize /= 2; //To compensate for reading two symbols at a time
			c.blocksizemb = mbs;
		}
			
		else
			cout << "Block size is too large, using default of 1MB." << endl;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	string filename;
	string mode;
	int encodingDecoding = 0;
	bool verbose = false;
	bool extraVerbose = false;
	bool timer = false;
	
	int runs = 1;
	int currentRun = 1;

	vector<TestSuite> testResults;

	if (argc <= 2)
	{
		cout << "No file input, exiting." << endl;
		return 4;
	}
	getArg(argv[1], filename);
	getArg(argv[2], mode);
	encodingDecoding = setMode(mode);

	if (encodingDecoding == 1)
		//Do encoding
	{
		dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> activePairs;
		activePairs.set_empty_key(-1);
		activePairs.set_deleted_key(-2);

		vector<SymbolRecord*> sequenceArray;
		vector<PairRecord*> priorityQueue;
		dense_hash_map<unsigned long , Pair> dictionary;
		dictionary.set_empty_key(-1);
		dictionary.set_deleted_key(-2);

		unsigned long  symbols(initialSymbolValue);

		Algorithm algorithm;
		AlgorithmP algP;
		Initializer init;
		Conditions c;
		MyTimer t;
		int r = 1;
		int blockSize = 1048576;

		//Interpret additional arguments that might be present
		for (int i = 3; i < argc; i++)
		{
			interpretParameter(argv[i], c, blockSize);
		}

		if (c.test)
		{
			c.ts = new TestSuite();
			c.ts->s_filename.assign(filename);
			c.ts->blocksizemb = c.blocksizemb;
			runs = c.runs;
		}

		//When testing we can do multiple runs
		while (currentRun <= runs)
		{

			ifstream file(filename);

			if (file.is_open())
			{
				if (c.test)
				{
					cout << endl << "Test run " << currentRun << " of " << runs << endl << endl;
				}
				r = algorithm.run(
					filename,
					file,
					c,
					init,
					algP,
					t,
					blockSize,
					activePairs,
					sequenceArray,
					priorityQueue,
					symbols);

				//Save the test results from the current run
				if (c.test)
				{
					testResults.push_back(*c.ts);
					c.ts->resetForNextTest();
				}

			}
			else
			{
				cout << "Problem opening file: " << filename << endl;
				return 5;
			}
			++currentRun;
		}
		if (c.test)
		{
			TestSuite avgResult;
			getAvgResult(avgResult, testResults);
			avgResult.WriteToFileEncoding(runs);
		}
		return r;
	}
	else if (encodingDecoding == 2)
		//Do decoding
	{
		if (argc > 3)
			cout << "Ignoring all arguments past the first two, not allowed for decoding." << endl;
		Decoder dec;
		dec.decode(filename);
	}
	else
	{
		cout << "Mode not set correct, exiting." << endl;
		return 6;
	}
}

