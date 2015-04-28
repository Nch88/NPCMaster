#pragma once
class TestSuite
{
public:
	long pairRecordWords = 2 + 4;
	long pairRecordSubtractWords = -4;
	long symbolRecordWords = 4;
	long huffmanNodeWords = 2 * 1;
	long terminalsWords = 2 * 1;
	long rootsWords = 2 * 1;
	long symbolToGenWords = 2 * 1;
	long pairVectorsWords = 2 * 1;
	long offsetWords = 2 * 1;

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

	//Memory
	//m_initialization;
	long m_init_sequenceArray_current = 0;
	long m_init_sequenceArray_max = 0;
	long m_init_pairRecord_current = 0;
	long m_init_pairRecord_max = 0;
	long m_init_priorityQueue_max = 0;

	long m_init_total = 0;

	// m_repair;
	long m_repair_sequenceArray_current = 0;
	long m_repair_sequenceArray_max = 0;
	long m_repair_pairRecord_current = 0;
	long m_repair_pairRecord_max = 0;
	long m_repair_priorityQueue_max = 0;
	long m_repair_phraseTable_max = 0;

	long m_repair_total = 0;

	// m_huffmanEncoding;
	long m_huffEnc_sequenceArray_current = 0;
	long m_huffEnc_sequenceArray_max = 0;
	long m_huffEnc_phraseTable_max = 0;
	long m_huffEnc_frequencies_max = 0;
	long m_huffEnc_codeLengths_max = 0;
	long m_huffEnc_firstCodes_max = 0;
	long m_huffEnc_nrOfCodes_max = 0;
	long m_huffEnc_nextCodes_max = 0;
	long m_huffEnc_huffmanCodes_max = 0;
	long m_huffEnc_huffmanToSymbol_max = 0;

	long m_huffEnc_total = 0;

	// m_normalDictionary;
	long m_norDic_sequenceArray_current = 0;
	long m_norDic_sequenceArray_max = 0;
	long m_norDic_phraseTable_max = 0;
	long m_norDic_firstCodes_max = 0;
	long m_norDic_nrOfCodes_max = 0;
	long m_norDic_huffmanToSymbol_max = 0;
	long m_norDic_terminals_max = 0;
	long m_norDic_roots_max = 0;
	long m_norDic_symbolToGen_max = 0;
	long m_norDic_pairVectors_max = 0;
	long m_norDic_terminalVector_max = 0;
	long m_norDic_offsets_max = 0;

	long m_norDic_total = 0;
	long m_norDic_supportStructures_total = 0;
	
	// m_huffmanDictionary;

	//Compression
	long c_sequence = 0;
	long c_huffmanDictionary = 0;
	long c_dictionary = 0;

	//Statistics
	long s_maxPairs = 0;
	long s_avgNrOfPhrases = 0;
	long s_longestPhrase = 0;
	long s_avgPhraseLength = 0;
	int s_nrOfBlocks = 0;
	long s_huffmanCodeLength_max = 0;
	std::string s_filename = "";

	MyTimer testTimer;

	TestSuite();
	~TestSuite();

	void WriteToFileEncoding();
	void addMemory(std::string part, long value);
};

