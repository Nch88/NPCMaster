#include "stdafx.h"
#include "TestSuite.h"


TestSuite::TestSuite()
{
}


TestSuite::~TestSuite()
{
}

long double TestSuite::totalTime(double offset)
{
	return t_initialization_count / offset +
		t_repair_count / offset +
		t_huffmanEncoding_count / offset +
		t_encodeSequence_count / offset +
		t_writeHuffmanDictionary_count / offset +
		t_setupDictionary_count / offset +
		t_writeDictionary_count / offset;
}

void TestSuite::calculateAverages()
{
	double nrOfBlocksCorrected = (s_nrOfBlocks - 1.0) +
		(s_lastBlockSize / s_fullBlockSize);

	//calculate avgs of all values kept across blocks
	//Memory
	m_total_acrossBlocks /= nrOfBlocksCorrected;

	//m_initialization;
	m_init_sequenceArray_max_acrossBlocks /= nrOfBlocksCorrected;
	m_init_pairRecord_max_acrossBlocks /= nrOfBlocksCorrected;
	m_init_pairTracker_max_acrossBlocks /= nrOfBlocksCorrected;
	m_init_priorityQueue_max_acrossBlocks /= nrOfBlocksCorrected;

	m_init_total_acrossBlocks /= nrOfBlocksCorrected;


	// m_repair;
	m_repair_sequenceArray_max_acrossBlocks /= nrOfBlocksCorrected;
	m_repair_pairRecord_max_acrossBlocks /= nrOfBlocksCorrected;
	m_repair_priorityQueue_max_acrossBlocks /= nrOfBlocksCorrected;
	m_repair_phraseTable_max_acrossBlocks /= nrOfBlocksCorrected;

	m_repair_total_acrossBlocks /= nrOfBlocksCorrected;

	m_repair_dictionary_max_acrossBlocks /= nrOfBlocksCorrected;
	m_repair_terminals_max_acrossBlocks /= nrOfBlocksCorrected;


	// m_huffmanEncoding;
	m_huffEnc_sequenceArray_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_phraseTable_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_frequencies_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_codeLengths_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_firstCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_nrOfCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_nextCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_huffmanCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_huffmanToSymbol_max_acrossBlocks /= nrOfBlocksCorrected;

	m_huffEnc_total_acrossBlocks /= nrOfBlocksCorrected;

	m_huffEnc_dictionary_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffEnc_terminals_max_acrossBlocks /= nrOfBlocksCorrected;

	// m_normalDictionary;
	m_norDic_sequenceArray_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_phraseTable_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_firstCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_nrOfCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_huffmanToSymbol_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_roots_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_symbolToGen_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_pairVectors_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_terminalVector_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_offsets_max_acrossBlocks /= nrOfBlocksCorrected;

	m_norDic_total_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_supportStructures_total_acrossBlocks /= nrOfBlocksCorrected;

	m_norDic_dictionary_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_terminals_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_indices_max_acrossBlocks /= nrOfBlocksCorrected;
	m_norDic_terminalIndices_max_acrossBlocks /= nrOfBlocksCorrected;

	// m_huffmanDictionary;
	m_huffDic_phraseTable_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_firstCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_nrOfCodes_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_huffmanToSymbol_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_symbolToGen_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_pairVectors_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_terminalVector_max_acrossBlocks /= nrOfBlocksCorrected;

	m_huffDic_total_acrossBlocks /= nrOfBlocksCorrected;

	m_huffDic_dictionary_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_terminals_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_indices_max_acrossBlocks /= nrOfBlocksCorrected;
	m_huffDic_terminalIndices_max_acrossBlocks /= nrOfBlocksCorrected;

	//Statistics
	s_maxPairs_acrossBlocks /= nrOfBlocksCorrected;
	s_nrOfTerminals_acrossBlocks /= nrOfBlocksCorrected;
	s_nrOfTerminalsMax_acrossBlocks /= nrOfBlocksCorrected;
	s_nrOfGenerations_acrossBlocks /= nrOfBlocksCorrected;
	s_nrOfPhrases_acrossBlocks /= nrOfBlocksCorrected;
	s_avgNrOfPhrases_acrossBlocks /= nrOfBlocksCorrected;
	s_largestGeneration_acrossBlocks /= nrOfBlocksCorrected;
	s_largestGenerationCount_acrossBlocks /= nrOfBlocksCorrected;
}

void TestSuite::resetForNextBlock()
{
	//Transfer data for this block and reset for the next
	//Memory

	m_total_acrossBlocks += m_total;
	m_total = 0;

	//m_initialization;
	m_init_sequenceArray_max_acrossBlocks += m_init_sequenceArray_max;
	m_init_pairRecord_max_acrossBlocks += m_init_pairRecord_max;
	m_init_pairTracker_max_acrossBlocks += m_init_pairTracker_max;
	m_init_priorityQueue_max_acrossBlocks += m_init_priorityQueue_max;

	m_init_total_acrossBlocks += m_init_total;

	m_init_sequenceArray_current = 0;
	m_init_sequenceArray_max = 0;
	m_init_pairRecord_current = 0;
	m_init_pairRecord_max = 0;
	m_init_pairTracker_current = 0;
	m_init_pairTracker_max = 0;
	m_init_priorityQueue_max = 0;

	m_init_total = 0;



	// m_repair;
	m_repair_sequenceArray_max_acrossBlocks += m_repair_sequenceArray_max;
	m_repair_pairRecord_max_acrossBlocks += m_repair_pairRecord_max;
	m_repair_priorityQueue_max_acrossBlocks += m_repair_priorityQueue_max;
	m_repair_phraseTable_max_acrossBlocks += m_repair_phraseTable_max;
	m_repair_dictionary_max_acrossBlocks += m_repair_dictionary_max;
	m_repair_terminals_max_acrossBlocks += m_repair_terminals_max;

	m_repair_total_acrossBlocks += m_repair_total;

	m_repair_sequenceArray_current = 0;
	m_repair_sequenceArray_max = 0;
	m_repair_pairRecord_current = 0;
	m_repair_pairRecord_max = 0;
	m_repair_priorityQueue_max = 0;
	m_repair_phraseTable_max = 0;
	m_repair_dictionary_max = 0;
	m_repair_terminals_max = 0;

	m_repair_total = 0;


	// m_huffmanEncoding;
	m_huffEnc_sequenceArray_max_acrossBlocks += m_huffEnc_sequenceArray_max;
	m_huffEnc_phraseTable_max_acrossBlocks += m_huffEnc_phraseTable_max;
	m_huffEnc_frequencies_max_acrossBlocks += m_huffEnc_frequencies_max;
	m_huffEnc_codeLengths_max_acrossBlocks += m_huffEnc_codeLengths_max;
	m_huffEnc_firstCodes_max_acrossBlocks += m_huffEnc_firstCodes_max;
	m_huffEnc_nrOfCodes_max_acrossBlocks += m_huffEnc_nrOfCodes_max;
	m_huffEnc_nextCodes_max_acrossBlocks += m_huffEnc_nextCodes_max;
	m_huffEnc_huffmanCodes_max_acrossBlocks += m_huffEnc_huffmanCodes_max;
	m_huffEnc_huffmanToSymbol_max_acrossBlocks += m_huffEnc_huffmanToSymbol_max;
	m_huffEnc_dictionary_max_acrossBlocks += m_repair_dictionary_max;
	m_huffEnc_terminals_max_acrossBlocks += m_repair_terminals_max;

	m_huffEnc_total_acrossBlocks += m_huffEnc_total;

	m_huffEnc_sequenceArray_current = 0;
	m_huffEnc_sequenceArray_max = 0;
	m_huffEnc_phraseTable_max = 0;
	m_huffEnc_frequencies_max = 0;
	m_huffEnc_codeLengths_max = 0;
	m_huffEnc_firstCodes_max = 0;
	m_huffEnc_nrOfCodes_max = 0;
	m_huffEnc_nextCodes_max = 0;
	m_huffEnc_huffmanCodes_max = 0;
	m_huffEnc_huffmanToSymbol_max = 0;
	m_huffEnc_dictionary_max = 0;
	m_huffEnc_terminals_max = 0;

	m_huffEnc_total = 0;


	// m_normalDictionary;
	m_norDic_sequenceArray_max_acrossBlocks += m_norDic_sequenceArray_max;
	m_norDic_phraseTable_max_acrossBlocks += m_norDic_phraseTable_max;
	m_norDic_firstCodes_max_acrossBlocks += m_norDic_firstCodes_max;
	m_norDic_nrOfCodes_max_acrossBlocks += m_norDic_nrOfCodes_max;
	m_norDic_huffmanToSymbol_max_acrossBlocks += m_norDic_huffmanToSymbol_max;
	m_norDic_roots_max_acrossBlocks += m_norDic_roots_max;
	m_norDic_symbolToGen_max_acrossBlocks += m_norDic_symbolToGen_max;
	m_norDic_pairVectors_max_acrossBlocks += m_norDic_pairVectors_max;
	m_norDic_terminalVector_max_acrossBlocks += m_norDic_terminalVector_max;
	m_norDic_offsets_max_acrossBlocks += m_norDic_offsets_max;
	m_norDic_dictionary_max_acrossBlocks += m_repair_dictionary_max;
	m_norDic_terminals_max_acrossBlocks += m_repair_terminals_max;
	m_norDic_indices_max_acrossBlocks += m_norDic_indices_max;
	m_norDic_terminalIndices_max_acrossBlocks += m_norDic_terminalIndices_max;

	m_norDic_total_acrossBlocks += m_norDic_total;
	m_norDic_supportStructures_total_acrossBlocks += m_norDic_supportStructures_total;

	m_norDic_sequenceArray_current = 0;
	m_norDic_sequenceArray_max = 0;
	m_norDic_phraseTable_max = 0;
	m_norDic_firstCodes_max = 0;
	m_norDic_nrOfCodes_max = 0;
	m_norDic_huffmanToSymbol_max = 0;
	m_norDic_roots_max = 0;
	m_norDic_symbolToGen_max = 0;
	m_norDic_pairVectors_max = 0;
	m_norDic_terminalVector_max = 0;
	m_norDic_offsets_max = 0;
	m_norDic_dictionary_max = 0;
	m_norDic_terminals_max = 0;
	m_norDic_indices_max = 0;
	m_norDic_terminalIndices_max = 0;

	m_norDic_total = 0;
	m_norDic_supportStructures_total = 0;


	// m_huffmanDictionary;
	m_huffDic_phraseTable_max_acrossBlocks += m_huffDic_phraseTable_max;
	m_huffDic_firstCodes_max_acrossBlocks += m_huffDic_firstCodes_max;
	m_huffDic_nrOfCodes_max_acrossBlocks += m_huffDic_nrOfCodes_max;
	m_huffDic_huffmanToSymbol_max_acrossBlocks += m_huffDic_huffmanToSymbol_max;
	m_huffDic_symbolToGen_max_acrossBlocks += m_huffDic_symbolToGen_max;
	m_huffDic_pairVectors_max_acrossBlocks += m_huffDic_pairVectors_max;
	m_huffDic_terminalVector_max_acrossBlocks += m_huffDic_terminalVector_max;
	m_huffDic_indices_max_acrossBlocks += m_huffDic_indices_max;
	m_huffDic_terminalIndices_max_acrossBlocks += m_huffDic_terminalIndices_max;

	m_huffDic_total_acrossBlocks += m_huffDic_total;

	m_huffDic_phraseTable_max = 0;
	m_huffDic_firstCodes_max = 0;
	m_huffDic_nrOfCodes_max = 0;
	m_huffDic_huffmanToSymbol_max = 0;
	m_huffDic_symbolToGen_max = 0;
	m_huffDic_pairVectors_max = 0;
	m_huffDic_terminalVector_max = 0;
	m_huffDic_indices_max = 0;
	m_huffDic_terminalIndices_max = 0;

	m_huffDic_total = 0;

	//Statistics
	s_currentBlockSize = 0;

	s_maxPairs_acrossBlocks += s_maxPairs;
	s_nrOfTerminals_acrossBlocks += s_nrOfTerminals;
	s_nrOfGenerations_acrossBlocks += s_nrOfGenerations;
	s_nrOfPhrases_acrossBlocks += s_nrOfPhrases;
	s_avgNrOfPhrases_acrossBlocks += s_largestGeneration;
	s_largestGeneration_acrossBlocks += s_largestGeneration;
	s_largestGenerationCount_acrossBlocks += s_largestGenerationCount;

	s_maxPairs = 0;
	s_nrOfTerminals = 0;
	s_nrOfGenerations = 0;
	s_nrOfPhrases = 0;
	s_avgNrOfPhrases = 0;
	s_largestGeneration = 0;
	s_largestGenerationCount = 0;
}

void TestSuite::resetForNextTest()
{
	//Timing
	t_initialization -= t_initialization;
	t_repair -= t_repair;
	t_huffmanEncoding -= t_huffmanEncoding;
	t_encodeSequence -= t_encodeSequence;
	t_writeHuffmanDictionary -= t_writeHuffmanDictionary;
	t_setupDictionary -= t_setupDictionary;
	t_writeDictionary -= t_writeDictionary;

	t_readDictionary -= t_readDictionary;
	t_decompression -= t_decompression;

	//Memory
	m_total_acrossBlocks = 0;

	m_total = 0;

	//m_init
	m_init_sequenceArray_max_acrossBlocks = 0;
	m_init_pairRecord_max_acrossBlocks = 0;
	m_init_priorityQueue_max_acrossBlocks = 0;

	m_init_total_acrossBlocks = 0;

	m_init_sequenceArray_current = 0;
	m_init_sequenceArray_max = 0;
	m_init_pairRecord_current = 0;
	m_init_pairRecord_max = 0;
	m_init_priorityQueue_max = 0;

	m_init_total = 0;

	// m_repair;
	m_repair_sequenceArray_max_acrossBlocks = 0;
	m_repair_pairRecord_max_acrossBlocks = 0;
	m_repair_priorityQueue_max_acrossBlocks = 0;
	m_repair_phraseTable_max_acrossBlocks = 0;
	m_repair_dictionary_max_acrossBlocks = 0;
	m_repair_terminals_max_acrossBlocks = 0;

	m_repair_total_acrossBlocks = 0;

	m_repair_sequenceArray_current = 0;
	m_repair_sequenceArray_max = 0;
	m_repair_pairRecord_current = 0;
	m_repair_pairRecord_max = 0;
	m_repair_priorityQueue_max = 0;
	m_repair_phraseTable_max = 0;
	m_repair_dictionary_max = 0;
	m_repair_terminals_max = 0;

	m_repair_total = 0;


	// m_huffmanEncoding;
	m_huffEnc_sequenceArray_max_acrossBlocks = 0;
	m_huffEnc_phraseTable_max_acrossBlocks = 0;
	m_huffEnc_frequencies_max_acrossBlocks = 0;
	m_huffEnc_codeLengths_max_acrossBlocks = 0;
	m_huffEnc_firstCodes_max_acrossBlocks = 0;
	m_huffEnc_nrOfCodes_max_acrossBlocks = 0;
	m_huffEnc_nextCodes_max_acrossBlocks = 0;
	m_huffEnc_huffmanCodes_max_acrossBlocks = 0;
	m_huffEnc_huffmanToSymbol_max_acrossBlocks = 0;
	m_huffEnc_dictionary_max_acrossBlocks = 0;
	m_huffEnc_terminals_max_acrossBlocks = 0;

	m_huffEnc_total_acrossBlocks = 0;

	m_huffEnc_sequenceArray_current = 0;
	m_huffEnc_sequenceArray_max = 0;
	m_huffEnc_phraseTable_max = 0;
	m_huffEnc_frequencies_max = 0;
	m_huffEnc_codeLengths_max = 0;
	m_huffEnc_firstCodes_max = 0;
	m_huffEnc_nrOfCodes_max = 0;
	m_huffEnc_nextCodes_max = 0;
	m_huffEnc_huffmanCodes_max = 0;
	m_huffEnc_huffmanToSymbol_max = 0;
	m_huffEnc_dictionary_max = 0;
	m_huffEnc_terminals_max = 0;

	m_huffEnc_total = 0;

	// m_normalDictionary;
	m_norDic_sequenceArray_max_acrossBlocks = 0;
	m_norDic_phraseTable_max_acrossBlocks = 0;
	m_norDic_firstCodes_max_acrossBlocks = 0;
	m_norDic_nrOfCodes_max_acrossBlocks = 0;
	m_norDic_huffmanToSymbol_max_acrossBlocks = 0;
	m_norDic_roots_max_acrossBlocks = 0;
	m_norDic_symbolToGen_max_acrossBlocks = 0;
	m_norDic_pairVectors_max_acrossBlocks = 0;
	m_norDic_terminalVector_max_acrossBlocks = 0;
	m_norDic_offsets_max_acrossBlocks = 0;
	m_norDic_dictionary_max_acrossBlocks = 0;
	m_norDic_terminals_max_acrossBlocks = 0;
	m_norDic_indices_max_acrossBlocks = 0;
	m_norDic_terminalIndices_max_acrossBlocks = 0;

	m_norDic_total_acrossBlocks = 0;
	m_norDic_supportStructures_total_acrossBlocks = 0;

	m_norDic_sequenceArray_current = 0;
	m_norDic_sequenceArray_max = 0;
	m_norDic_phraseTable_max = 0;
	m_norDic_firstCodes_max = 0;
	m_norDic_nrOfCodes_max = 0;
	m_norDic_huffmanToSymbol_max = 0;
	m_norDic_roots_max = 0;
	m_norDic_symbolToGen_max = 0;
	m_norDic_pairVectors_max = 0;
	m_norDic_terminalVector_max = 0;
	m_norDic_offsets_max = 0;
	m_norDic_dictionary_max = 0;
	m_norDic_terminals_max = 0;
	m_norDic_indices_max = 0;
	m_norDic_terminalIndices_max = 0;

	m_norDic_total = 0;
	m_norDic_supportStructures_total = 0;

	// m_huffmanDictionary;
	m_huffDic_phraseTable_max_acrossBlocks = 0;
	m_huffDic_firstCodes_max_acrossBlocks = 0;
	m_huffDic_nrOfCodes_max_acrossBlocks = 0;
	m_huffDic_huffmanToSymbol_max_acrossBlocks = 0;
	m_huffDic_symbolToGen_max_acrossBlocks = 0;
	m_huffDic_pairVectors_max_acrossBlocks = 0;
	m_huffDic_terminalVector_max_acrossBlocks = 0;
	m_huffDic_indices_max_acrossBlocks = 0;
	m_huffDic_terminalIndices_max_acrossBlocks = 0;

	m_huffDic_total_acrossBlocks = 0;

	m_huffDic_phraseTable_max = 0;
	m_huffDic_firstCodes_max = 0;
	m_huffDic_nrOfCodes_max = 0;
	m_huffDic_huffmanToSymbol_max = 0;
	m_huffDic_symbolToGen_max = 0;
	m_huffDic_pairVectors_max = 0;
	m_huffDic_terminalVector_max = 0;
	m_huffDic_indices_max = 0;
	m_huffDic_terminalIndices_max = 0;

	m_huffDic_total = 0;

	//Compression (in bytes)
	c_origSize = 0;
	c_sequence = 0;
	c_huffmanDictionary = 0;
	c_dictionary = 0;

	//Statistics
	s_maxPairs_acrossBlocks = 0;
	s_nrOfTerminals_acrossBlocks = 0;
	s_nrOfTerminalsMax_acrossBlocks = 0;
	s_nrOfGenerations_acrossBlocks = 0;
	s_nrOfGenerationsMax_acrossBlocks = 0;
	s_nrOfPhrases_acrossBlocks = 0;
	s_avgNrOfPhrases_acrossBlocks = 0;
	s_largestGeneration_acrossBlocks = 0;
	s_largestGenerationMax_acrossBlocks = 0;
	s_largestGenerationCount_acrossBlocks = 0;
	s_largestGenerationCountMax_acrossBlocks = 0;
	s_huffmanCodeLength_max_acrossBlocks = 0;

	s_maxPairs = 0;
	s_nrOfTerminals = 0;
	s_nrOfTerminalsMax = 0;
	s_nrOfGenerations = 0;
	s_nrOfGenerationsMax = 0;
	s_nrOfPhrases = 0;
	s_avgNrOfPhrases = 0;
	s_largestGeneration = 0;
	s_largestGenerationMax = 0;
	s_largestGenerationCount = 0;
	s_largestGenerationCountMax = 0;
	s_nrOfBlocks = 0;
	s_huffmanCodeLength_max = 0;

	s_currentBlockSize = 0;
	s_lastBlockSize = 0;
	s_fullBlockSize = 0;
}

void TestSuite::WriteToFileEncoding(int runs)
{
	double offset = 1000000.000;
	double mb = 1000000.0;
	string unit = "unknown unit";

	if (offset == 1000000000.0)
		unit = "s";
	if (offset == 1000000.0)
		unit = "ms";
	if (offset == 1000.0)
		unit = "us";
	if (offset == 1.0)
		unit = "ns";

	string folder = "TestData/";

	ofstream ofs;
	string file = folder;
	file += "TestData - ";
	file += s_filename;
	file += "_blocksize";
	file += to_string(blocksizemb);
	file += "_avg";
	file += to_string(runs);
	file += ".csv";

	ofs.open(file, ios::trunc);

	ofs << "sep=;" << endl;

	ofs << "Data for encoding file " << s_filename << ":" << endl << endl;

	ofs << "Timing (in " << unit << "):" << endl;

	ofs << "Initialization" << "; " << t_initialization_count / offset << endl;
	ofs << "Re-Pair; " << t_repair_count / offset << endl;
	ofs << "Huffman encoding; " << t_huffmanEncoding_count / offset << endl;
	ofs << "Encode sequence; " << t_encodeSequence_count / offset << endl;
	ofs << "Write Huffman dictionary; " << t_writeHuffmanDictionary_count / offset << endl;
	ofs << "Setup dictionary; " << t_setupDictionary_count / offset << endl;
	ofs << "Write dictionary; " << t_writeDictionary_count / offset << endl;
	ofs << "Total time; " << totalTime(offset) << endl;

	ofs << endl;

	ofs << "Compression (in bytes):" << endl;

	ofs << "Sequence; " << c_sequence << endl;
	ofs << "Huffman dictionary; " << c_huffmanDictionary << endl;
	ofs << "Dictionary; " << c_dictionary << endl;
	ofs << "Total dictionary; " << c_dictionary + c_huffmanDictionary << endl;
	ofs << "Original file size; " << c_origSize << endl;
	ofs << "Original file size (mb); " << c_origSize / mb << endl;
	ofs << "Compressed file size; " << c_dictionary + c_huffmanDictionary + c_sequence << endl;
	ofs << "Compressed file size (mb); " << (c_dictionary + c_huffmanDictionary + c_sequence) / mb << endl;
	ofs << "Compression ratio; " << ((double)c_origSize / ((double)c_dictionary + (double)c_huffmanDictionary + (double)c_sequence)) << endl;
	ofs << endl;

	ofs << "memory (in words):" << endl;

	ofs << "Initialization - sequence array; " << m_init_sequenceArray_max_acrossBlocks << endl;
	ofs << "Initialization - active pairs; " << m_init_pairRecord_max_acrossBlocks + m_init_pairTracker_max_acrossBlocks << endl;
	ofs << "Initialization - priority queue; " << m_init_priorityQueue_max_acrossBlocks << endl;
	ofs << "Initialization - total; " << m_init_total_acrossBlocks << endl;
	ofs << "Initialization - total (mb); " << (m_init_total_acrossBlocks / mb) * 4 << endl;

	ofs << "Re-Pair - sequence array; " << m_repair_sequenceArray_max_acrossBlocks << endl;
	ofs << "Re-Pair - active pairs; " << m_repair_pairRecord_max_acrossBlocks << endl;
	ofs << "Re-Pair - priority queue; " << m_repair_priorityQueue_max_acrossBlocks << endl;
	ofs << "Re-Pair - dictinary; " << m_repair_dictionary_max_acrossBlocks << endl;
	ofs << "Re-Pair - terminals; " << m_repair_terminals_max_acrossBlocks << endl;
	ofs << "Re-Pair - total; " << m_repair_total_acrossBlocks << endl;
	ofs << "Re-Pair - total (mb); " << (m_repair_total_acrossBlocks / mb) * 4 << endl;

	ofs << "Huffman encoding - sequence array; " << m_huffEnc_sequenceArray_max_acrossBlocks << endl;
	ofs << "Huffman encoding - dictionary; " << m_huffEnc_dictionary_max_acrossBlocks << endl;
	ofs << "Huffman encoding - terminals; " << m_huffEnc_terminals_max_acrossBlocks << endl;
	ofs << "Huffman encoding - symbol frequencies; " << m_huffEnc_frequencies_max_acrossBlocks << endl;
	ofs << "Huffman encoding - code lengths array; " << m_huffEnc_codeLengths_max_acrossBlocks << endl;
	ofs << "Huffman encoding - first codes array; " << m_huffEnc_firstCodes_max_acrossBlocks << endl;
	ofs << "Huffman encoding - nr of codes array; " << m_huffEnc_nrOfCodes_max_acrossBlocks << endl;
	ofs << "Huffman encoding - next codes array; " << m_huffEnc_nextCodes_max_acrossBlocks << endl;
	ofs << "Huffman encoding - combined Huffman codes as strings; " << m_huffEnc_huffmanCodes_max_acrossBlocks << endl;
	ofs << "Huffman encoding - Huffman to symbol; " << m_huffEnc_huffmanToSymbol_max_acrossBlocks << endl;
	ofs << "Huffman encoding - total; " << m_huffEnc_total_acrossBlocks << endl;
	ofs << "Huffman encoding - total (mb); " << (m_huffEnc_total_acrossBlocks / mb) * 4 << endl;

	ofs << "Normal dictionary - sequence array; " << m_norDic_sequenceArray_max_acrossBlocks << endl;
	ofs << "Normal dictionary - dictionary; " << m_norDic_dictionary_max_acrossBlocks< endl;
	ofs << "Normal dictionary - first codes array; " << m_norDic_firstCodes_max_acrossBlocks << endl;
	ofs << "Normal dictionary - nr of codes array; " << m_norDic_nrOfCodes_max_acrossBlocks << endl;
	ofs << "Normal dictionary - Huffman to symbol; " << m_norDic_huffmanToSymbol_max_acrossBlocks << endl;
	ofs << "Normal dictionary - terminals set; " << m_norDic_terminals_max_acrossBlocks << endl;
	ofs << "Normal dictionary - roots; " << m_norDic_roots_max_acrossBlocks << endl;
	ofs << "Normal dictionary - symbol to generation; " << m_norDic_symbolToGen_max_acrossBlocks << endl;
	ofs << "Normal dictionary - pair vectors; " << m_norDic_pairVectors_max_acrossBlocks << endl;
	ofs << "Normal dictionary - terminals; " << m_norDic_terminals_max_acrossBlocks << endl;
	ofs << "Normal dictionary - offset array; " << m_norDic_offsets_max_acrossBlocks << endl;
	ofs << "Normal dictionary - indices; " << m_norDic_indices_max_acrossBlocks << endl;
	ofs << "Normal dictionary - terminal indices; " << m_norDic_terminalIndices_max_acrossBlocks << endl;

	ofs << "Normal dictionary - total; " << max(m_norDic_supportStructures_total_acrossBlocks, m_norDic_total_acrossBlocks) << endl;
	ofs << "Normal dictionary - total (mb); " << (max(m_norDic_supportStructures_total_acrossBlocks, m_norDic_total_acrossBlocks) / mb) * 4 << endl;

	ofs << "Huffman dictionary - dictionary; " << m_huffDic_dictionary_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - first codes array; " << m_huffDic_firstCodes_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - nr of codes array; " << m_huffDic_nrOfCodes_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - Huffman to symbol; " << m_huffDic_huffmanToSymbol_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - symbol to generation; " << m_huffDic_symbolToGen_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - pair vectors; " << m_huffDic_pairVectors_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - terminal vector; " << m_huffDic_terminalVector_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - indices; " << m_huffDic_indices_max_acrossBlocks << endl;
	ofs << "Huffman dictionary - terminal indices; " << m_huffDic_terminalIndices_max_acrossBlocks << endl;

	ofs << "Huffman dictionary - total; " << m_huffDic_total_acrossBlocks << endl;
	ofs << "Huffman dictionary - total (mb); " << (m_huffDic_total_acrossBlocks / mb) * 4 << endl;
	ofs << endl;
	ofs << endl;

	ofs << "Maximum amount of memory used; " << m_total_acrossBlocks << endl;
	ofs << "Maximum amount of memory used (mb); " << (m_total_acrossBlocks / mb) * 4 << endl;
	ofs << endl;


	ofs << "Statistics:" << endl;

	ofs << "Nr of blocks; " << s_nrOfBlocks << endl;

	ofs << "Average across blocks:" << endl;

	ofs << "Nr of terminals; " << s_nrOfTerminals_acrossBlocks << endl;
	ofs << "Nr of pairs created; " << s_maxPairs_acrossBlocks << endl;
	ofs << "Nr of generations; " << s_nrOfGenerations_acrossBlocks << endl;
	ofs << "Nr of phrases; " << s_nrOfPhrases_acrossBlocks << endl;
	ofs << "Avg nr of phrases per generation; " << s_avgNrOfPhrases_acrossBlocks << endl;
	ofs << "Largest generation; " << s_largestGeneration_acrossBlocks << endl;
	ofs << "Largest generation count; " << s_largestGenerationCount_acrossBlocks << endl;

	ofs << "Max seen in one block:" << endl;

	ofs << "Nr of terminals; " << s_nrOfTerminalsMax << endl;
	ofs << "Huffman code max length; " << s_huffmanCodeLength_max << endl;
	ofs << "Nr of generations; " << s_nrOfGenerationsMax << endl;
	ofs << "Largest generation; " << s_largestGenerationMax << endl;
	ofs << "Largest generation count; " << s_largestGenerationCountMax << endl;
	ofs << endl;

	ofs.close();


	cout << "Created file with test data." << endl;
}

void TestSuite::updateMaxMemory(long localTotal)
{
	if (localTotal > m_total)
	{
		m_total = localTotal;
	}
}

void TestSuite::addMemory(std::string part, long value)
{
	if (!firstBlock)
	{
		return;
	}
	//Initialization
	if (part == "initSeq")
	{
		m_init_sequenceArray_current += value;
		if (m_init_sequenceArray_current > m_init_sequenceArray_max)
		{
			m_init_total -= m_init_sequenceArray_max;
			m_init_sequenceArray_max = m_init_sequenceArray_current;
			m_init_total += m_init_sequenceArray_max;
			updateMaxMemory(m_init_total);
		}
	}
	else if (part == "initTracker")
	{
		m_init_pairTracker_current += value;
		if (m_init_pairTracker_current > m_init_pairTracker_max)
		{
			m_init_total -= m_init_pairTracker_max;
			m_init_pairTracker_max = m_init_pairTracker_current;
			m_init_total += m_init_pairTracker_max;
			updateMaxMemory(m_init_total);
		}

	}
	else if (part == "initPair")
	{
		m_init_pairRecord_current += value;
		if (m_init_pairRecord_current > m_init_pairRecord_max)
		{
			m_init_total -= m_init_pairRecord_max;
			m_init_pairRecord_max = m_init_pairRecord_current;
			m_init_total += m_init_pairRecord_max;
			updateMaxMemory(m_init_total);
		}

	}
	else if (part == "initPrio")
	{
		m_init_priorityQueue_max += value;
		m_init_total += m_init_priorityQueue_max;
		updateMaxMemory(m_init_total);
	}

	//Re-Pair
	else if (part == "repairSeq")
	{
		m_repair_sequenceArray_current += value;
		if (m_repair_sequenceArray_current > m_repair_sequenceArray_max)
		{
			m_repair_total -= m_repair_sequenceArray_max;
			m_repair_sequenceArray_max = m_repair_sequenceArray_current;
			m_repair_total += m_repair_sequenceArray_max;
			updateMaxMemory(m_repair_total);
		}

	}
	else if (part == "repairPair")
	{
		m_repair_pairRecord_current += value;
		if (m_repair_pairRecord_current > m_repair_pairRecord_max)
		{
			m_repair_total -= m_repair_pairRecord_max;
			m_repair_pairRecord_max = m_repair_pairRecord_current;
			m_repair_total += m_repair_pairRecord_max;
			updateMaxMemory(m_repair_total);
		}

	}
	else if (part == "repairPrio")
	{
		m_repair_priorityQueue_max += value;
		m_repair_total += value;
		updateMaxMemory(m_repair_total);
	}
	else if (part == "repairDict")
	{
		m_repair_dictionary_max += value;
		m_repair_total += value;
		updateMaxMemory(m_repair_total);
	}


	//Huffman encoding
	else if (part == "huffEncSeq")
	{
		m_huffEnc_sequenceArray_current += value;
		if (m_huffEnc_sequenceArray_current > m_huffEnc_sequenceArray_max)
		{
			m_huffEnc_total -= m_huffEnc_sequenceArray_max;
			m_huffEnc_sequenceArray_max = m_huffEnc_sequenceArray_current;
			m_huffEnc_total += m_huffEnc_sequenceArray_max;
			updateMaxMemory(m_huffEnc_total);
		}

	}
	else if (part == "huffEncDictionary")
	{
		m_huffEnc_dictionary_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncTerminals")
	{
		m_huffEnc_terminals_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncFreq")
	{
		m_huffEnc_frequencies_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncCodeLength")
	{
		m_huffEnc_codeLengths_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncFirstCodes")
	{
		m_huffEnc_firstCodes_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncNrOfCodes")
	{
		m_huffEnc_nrOfCodes_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncNextCodes")
	{
		m_huffEnc_nextCodes_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncHuffmanCodes")
	{
		m_huffEnc_huffmanCodes_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}
	else if (part == "huffEncHuffmanToSymbol")
	{
		m_huffEnc_huffmanToSymbol_max += value;
		m_huffEnc_total += value;
		updateMaxMemory(m_huffEnc_total);
	}

	//Normal dictionary
	else if (part == "norDicSeq")
	{
		m_norDic_sequenceArray_current += value;
		if (m_norDic_sequenceArray_current > m_norDic_sequenceArray_max)
		{
			m_norDic_total -= m_norDic_sequenceArray_max;
			m_norDic_sequenceArray_max = m_norDic_sequenceArray_current;
			m_norDic_total += m_norDic_sequenceArray_max;
			updateMaxMemory(m_norDic_total);
		}

	}
	else if (part == "norDicDictionary")
	{
		m_norDic_dictionary_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicTerminals")
	{
		m_norDic_terminals_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicFirstCodes")
	{
		m_norDic_firstCodes_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicNrOfCodes")
	{
		m_norDic_nrOfCodes_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicHuffmanToSymbol")
	{
		m_norDic_huffmanToSymbol_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicTerminals")
	{
		m_norDic_terminals_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicRoots")
	{
		m_norDic_roots_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicIndices")
	{
		m_norDic_indices_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicTerminalIndices")
	{
		m_norDic_terminalIndices_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicSymbolToGen")
	{
		m_norDic_symbolToGen_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicPairVectors")
	{
		m_norDic_pairVectors_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicTerminalVector")
	{
		m_norDic_terminalVector_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}
	else if (part == "norDicOffsets")
	{
		m_norDic_offsets_max += value;
		m_norDic_total += value;
		updateMaxMemory(m_norDic_total);
	}

	//Huffman dictionary
	else if (part == "huffDicDictionary")
	{
		m_huffDic_dictionary_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicFirstCodes")
	{
		m_huffDic_firstCodes_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicNrOfCodes")
	{
		m_huffDic_nrOfCodes_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicIndices")
	{
		m_huffDic_indices_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicTerminalIndices")
	{
		m_huffDic_terminalIndices_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicHuffmanToSymbol")
	{
		m_huffDic_huffmanToSymbol_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicSymbolToGen")
	{
		m_huffDic_symbolToGen_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicPairVectors")
	{
		m_huffDic_pairVectors_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}
	else if (part == "huffDicTerminalVector")
	{
		m_huffDic_terminalVector_max += value;
		m_huffDic_total += value;
		updateMaxMemory(m_huffDic_total);
	}


	else
	{
		cout << "Testing, add memory - program part not supported" << endl;
	}

}