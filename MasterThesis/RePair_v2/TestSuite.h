#pragma once
class TestSuite
{
public:
	bool firstBlock = true;
	int blocksizemb = 1;

	double pairRecordWords = 5;
	double pairTrackerWords = 2.25 * 4.0;
	double pairRecordSubtractWords = -pairRecordWords;
	double symbolRecordWords = 4 + 2;
	double huffmanNodeWords = 2 * 1;
	double terminalsWords = 2 * 1;
	double rootsWords = 2 * 1;
	double symbolToGenWords = 2 * 1;
	double pairVectorsWords = 2 * 1;
	double offsetWords = 2 * 1;

	//Timing
	boost::chrono::nanoseconds t_initialization;
	boost::chrono::nanoseconds t_repair;
	boost::chrono::nanoseconds t_huffmanEncoding;
	boost::chrono::nanoseconds t_encodeSequence;
	boost::chrono::nanoseconds t_writeHuffmanDictionary;
	boost::chrono::nanoseconds t_setupDictionary;
	boost::chrono::nanoseconds t_writeDictionary;

	boost::chrono::nanoseconds t_readDictionary;
	boost::chrono::nanoseconds t_decompression;

	long double t_initialization_count = 0;
	long double t_repair_count = 0;
	long double t_huffmanEncoding_count = 0;
	long double t_encodeSequence_count = 0;
	long double t_writeHuffmanDictionary_count = 0;
	long double t_setupDictionary_count = 0;
	long double t_writeDictionary_count = 0;

	long double t_readDictionary_count = 0;
	long double t_decompression_count = 0;

	//Memory

	long double m_total_acrossBlocks = 0;

	long double m_total = 0;

	//m_initialization;
	long double m_init_sequenceArray_max_acrossBlocks = 0;
	long double m_init_pairRecord_max_acrossBlocks = 0;
	long double m_init_pairTracker_max_acrossBlocks = 0;
	long double m_init_priorityQueue_max_acrossBlocks = 0;

	long double m_init_total_acrossBlocks = 0;

	long double m_init_sequenceArray_current = 0;
	long double m_init_sequenceArray_max = 0;
	long double m_init_pairRecord_current = 0;
	long double m_init_pairRecord_max = 0;
	long double m_init_pairTracker_current = 0;
	long double m_init_pairTracker_max = 0;
	long double m_init_priorityQueue_max = 0;

	long double m_init_total = 0;



	// m_repair;
	long double m_repair_sequenceArray_max_acrossBlocks = 0;
	long double m_repair_pairRecord_max_acrossBlocks = 0;
	long double m_repair_priorityQueue_max_acrossBlocks = 0;
	long double m_repair_phraseTable_max_acrossBlocks = 0;

	long double m_repair_total_acrossBlocks = 0;

	long double m_repair_sequenceArray_current = 0;
	long double m_repair_sequenceArray_max = 0;
	long double m_repair_pairRecord_current = 0;
	long double m_repair_pairRecord_max = 0;
	long double m_repair_priorityQueue_max = 0;
	long double m_repair_phraseTable_max = 0;

	long double m_repair_total = 0;



	// m_huffmanEncoding;
	long double m_huffEnc_sequenceArray_max_acrossBlocks = 0;
	long double m_huffEnc_phraseTable_max_acrossBlocks = 0;
	long double m_huffEnc_frequencies_max_acrossBlocks = 0;
	long double m_huffEnc_codeLengths_max_acrossBlocks = 0;
	long double m_huffEnc_firstCodes_max_acrossBlocks = 0;
	long double m_huffEnc_nrOfCodes_max_acrossBlocks = 0;
	long double m_huffEnc_nextCodes_max_acrossBlocks = 0;
	long double m_huffEnc_huffmanCodes_max_acrossBlocks = 0;
	long double m_huffEnc_huffmanToSymbol_max_acrossBlocks = 0;

	long double m_huffEnc_total_acrossBlocks = 0;

	long double m_huffEnc_sequenceArray_current = 0;
	long double m_huffEnc_sequenceArray_max = 0;
	long double m_huffEnc_phraseTable_max = 0;
	long double m_huffEnc_frequencies_max = 0;
	long double m_huffEnc_codeLengths_max = 0;
	long double m_huffEnc_firstCodes_max = 0;
	long double m_huffEnc_nrOfCodes_max = 0;
	long double m_huffEnc_nextCodes_max = 0;
	long double m_huffEnc_huffmanCodes_max = 0;
	long double m_huffEnc_huffmanToSymbol_max = 0;

	long double m_huffEnc_total = 0;


	// m_normalDictionary;
	long double m_norDic_sequenceArray_max_acrossBlocks = 0;
	long double m_norDic_phraseTable_max_acrossBlocks = 0;
	long double m_norDic_firstCodes_max_acrossBlocks = 0;
	long double m_norDic_nrOfCodes_max_acrossBlocks = 0;
	long double m_norDic_huffmanToSymbol_max_acrossBlocks = 0;
	long double m_norDic_terminals_max_acrossBlocks = 0;
	long double m_norDic_roots_max_acrossBlocks = 0;
	long double m_norDic_symbolToGen_max_acrossBlocks = 0;
	long double m_norDic_pairVectors_max_acrossBlocks = 0;
	long double m_norDic_terminalVector_max_acrossBlocks = 0;
	long double m_norDic_offsets_max_acrossBlocks = 0;

	long double m_norDic_total_acrossBlocks = 0;
	long double m_norDic_supportStructures_total_acrossBlocks = 0;

	long double m_norDic_sequenceArray_current = 0;
	long double m_norDic_sequenceArray_max = 0;
	long double m_norDic_phraseTable_max = 0;
	long double m_norDic_firstCodes_max = 0;
	long double m_norDic_nrOfCodes_max = 0;
	long double m_norDic_huffmanToSymbol_max = 0;
	long double m_norDic_terminals_max = 0;
	long double m_norDic_roots_max = 0;
	long double m_norDic_symbolToGen_max = 0;
	long double m_norDic_pairVectors_max = 0;
	long double m_norDic_terminalVector_max = 0;
	long double m_norDic_offsets_max = 0;

	long double m_norDic_total = 0;
	long double m_norDic_supportStructures_total = 0;



	// m_huffmanDictionary;
	long double m_huffDic_phraseTable_max_acrossBlocks = 0;
	long double m_huffDic_firstCodes_max_acrossBlocks = 0;
	long double m_huffDic_nrOfCodes_max_acrossBlocks = 0;
	long double m_huffDic_huffmanToSymbol_max_acrossBlocks = 0;
	long double m_huffDic_symbolToGen_max_acrossBlocks = 0;
	long double m_huffDic_pairVectors_max_acrossBlocks = 0;
	long double m_huffDic_terminalVector_max_acrossBlocks = 0;

	long double m_huffDic_total_acrossBlocks = 0;

	long double m_huffDic_phraseTable_max = 0;
	long double m_huffDic_firstCodes_max = 0;
	long double m_huffDic_nrOfCodes_max = 0;
	long double m_huffDic_huffmanToSymbol_max = 0;
	long double m_huffDic_symbolToGen_max = 0;
	long double m_huffDic_pairVectors_max = 0;
	long double m_huffDic_terminalVector_max = 0;

	long double m_huffDic_total = 0;



	//Compression (in bytes)
	long double c_origSize = 0;
	long double c_sequence = 0;
	long double c_huffmanDictionary = 0;
	long double c_dictionary = 0;

	//Statistics
	long double s_maxPairs_acrossBlocks = 0;
	long double s_nrOfTerminals_acrossBlocks = 0;
	long double s_nrOfTerminalsMax_acrossBlocks = 0;
	long double s_nrOfGenerations_acrossBlocks = 0;
	long double s_nrOfGenerationsMax_acrossBlocks = 0;
	long double s_nrOfPhrases_acrossBlocks = 0;
	long double s_avgNrOfPhrases_acrossBlocks = 0;
	long double s_largestGeneration_acrossBlocks = 0;
	long double s_largestGenerationCount_acrossBlocks = 0;
	long double s_largestGenerationMax_acrossBlocks = 0;
	long double s_largestGenerationCountMax_acrossBlocks = 0;
	long double s_huffmanCodeLength_max_acrossBlocks = 0;

	long double s_maxPairs = 0;
	long double s_nrOfTerminals = 0;
	long double s_nrOfTerminalsMax = 0;
	long double s_nrOfGenerations = 0;
	long double s_nrOfGenerationsMax = 0;
	long double s_nrOfPhrases = 0;
	long double s_avgNrOfPhrases = 0;
	long double s_largestGeneration = 0;
	long double s_largestGenerationCount = 0;
	long double s_largestGenerationMax = 0;
	long double s_largestGenerationCountMax = 0;
	long double s_huffmanCodeLength_max = 0;

	double s_nrOfBlocks = 0;
	std::string s_filename = "";

	long double s_currentBlockSize = 0;
	long double s_fullBlockSize = 0;
	long double s_lastBlockSize = 0;

	MyTimer testTimer;

	TestSuite();
	~TestSuite();

	void resetForNextBlock();
	void resetForNextTest();
	long double totalTime(double offset);
	void calculateAverages();
	void WriteToFileEncoding(int runs);
	void updateMaxMemory(long localTotal);
	void addMemory(std::string part, long value);
};