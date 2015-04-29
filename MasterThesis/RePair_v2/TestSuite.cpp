#include "stdafx.h"
#include "TestSuite.h"


TestSuite::TestSuite()
{
}


TestSuite::~TestSuite()
{
}

double TestSuite::totalTime(double offset)
{
	return t_initialization.count() / offset +
		t_repair.count() / offset +
		t_huffmanEncoding.count() / offset +
		t_encodeSequence.count() / offset +
		t_writeHuffmanDictionary.count() / offset +
		t_setupDictionary.count() / offset +
		t_writeDictionary.count() / offset;
}

void TestSuite::resetForNextBlock()
{
	m_init_sequenceArray_current = 0;
	m_init_sequenceArray_max = 0;
	m_init_pairRecord_current = 0;
	m_init_pairRecord_max = 0;
	m_init_priorityQueue_max = 0;

	
	// m_repair;
	m_repair_sequenceArray_current = 0;
	m_repair_sequenceArray_max = 0;
	m_repair_pairRecord_current = 0;
	m_repair_pairRecord_max = 0;
	m_repair_priorityQueue_max = 0;
	m_repair_phraseTable_max = 0;


	// m_huffmanEncoding;
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

	
	// m_normalDictionary;
	m_norDic_sequenceArray_current = 0;
	m_norDic_sequenceArray_max = 0;
	m_norDic_phraseTable_max = 0;
	m_norDic_firstCodes_max = 0;
	m_norDic_nrOfCodes_max = 0;
	m_norDic_huffmanToSymbol_max = 0;
	m_norDic_terminals_max = 0;
	m_norDic_roots_max = 0;
	m_norDic_symbolToGen_max = 0;
	m_norDic_pairVectors_max = 0;
	m_norDic_terminalVector_max = 0;
	m_norDic_offsets_max = 0;

	
	// m_huffmanDictionary;
	m_huffDic_phraseTable_max = 0;
	m_huffDic_firstCodes_max = 0;
	m_huffDic_nrOfCodes_max = 0;
	m_huffDic_huffmanToSymbol_max = 0;
	m_huffDic_symbolToGen_max = 0;
	m_huffDic_pairVectors_max = 0;
	m_huffDic_terminalVector_max = 0;
}


void TestSuite::WriteToFileEncoding()
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

	ofstream ofs;
	string file = "TestData.csv";
	ofs.open(file, ios::trunc);

	ofs << "sep=;" << endl;

	ofs << "Data for encoding file " << s_filename << ":" << endl << endl;

	ofs << "Timing (in " << unit << "):" << endl;

	ofs << "Initialization" << "; " << t_initialization.count() / offset << endl;
	ofs << "Re-Pair; " << t_repair.count() / offset << endl;
	ofs << "Huffman encoding; " << t_huffmanEncoding.count() / offset << endl;
	ofs << "Encode sequence; " << t_encodeSequence.count() / offset << endl;
	ofs << "Write Huffman dictionary; " << t_writeHuffmanDictionary.count() / offset << endl;
	ofs << "Setup dictionary; " << t_setupDictionary.count() / offset << endl;
	ofs << "Write dictionary; " << t_writeDictionary.count() / offset << endl;
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
	ofs << "Compression ratio; " << ((double)c_origSize / (double)c_sequence) << endl;
	ofs << endl;

	ofs << "memory (in words):" << endl;

	ofs << "Initialization - sequence array; " << m_init_sequenceArray_max << endl;
	ofs << "Initialization - active pairs; " << m_init_pairRecord_max << endl;
	ofs << "Initialization - priority queue; " << m_init_priorityQueue_max << endl;
	ofs << "Initialization - total; " << m_init_total << endl;
	ofs << "Initialization - total (mb); " << (m_init_total / mb) * 4 << endl;

	ofs << "Re-Pair - sequence array; " << m_repair_sequenceArray_max << endl;
	ofs << "Re-Pair - active pairs; " << m_repair_pairRecord_max << endl;
	ofs << "Re-Pair - priority queue; " << m_repair_priorityQueue_max << endl;
	ofs << "Re-Pair - phrase table; " << m_repair_phraseTable_max << endl;
	ofs << "Re-Pair - total; " << m_repair_total << endl;
	ofs << "Re-Pair - total (mb); " << (m_repair_total / mb) * 4 << endl;

	ofs << "Huffman encoding - sequence array; " << m_huffEnc_sequenceArray_max << endl;
	ofs << "Huffman encoding - phrase table; " << m_huffEnc_phraseTable_max << endl;
	ofs << "Huffman encoding - symbol frequencies; " << m_huffEnc_frequencies_max << endl;
	ofs << "Huffman encoding - code lengths array; " << m_huffEnc_codeLengths_max << endl;
	ofs << "Huffman encoding - first codes array; " << m_huffEnc_firstCodes_max << endl;
	ofs << "Huffman encoding - nr of codes array; " << m_huffEnc_nrOfCodes_max << endl;
	ofs << "Huffman encoding - next codes array; " << m_huffEnc_nextCodes_max << endl;
	ofs << "Huffman encoding - combined Huffman codes as strings; " << m_huffEnc_huffmanCodes_max << endl;
	ofs << "Huffman encoding - Huffman to symbol; " << m_huffEnc_huffmanToSymbol_max << endl;
	ofs << "Huffman encoding - total; " << m_huffEnc_total << endl;
	ofs << "Huffman encoding - total (mb); " << (m_huffEnc_total / mb) * 4 << endl;

	ofs << "Normal dictionary - sequence array; " << m_norDic_sequenceArray_max << endl;
	ofs << "Normal dictionary - phrase table; " << m_norDic_phraseTable_max << endl;
	ofs << "Normal dictionary - first codes array; " << m_norDic_firstCodes_max << endl;
	ofs << "Normal dictionary - nr of codes array; " << m_norDic_nrOfCodes_max << endl;
	ofs << "Normal dictionary - Huffman to symbol; " << m_norDic_huffmanToSymbol_max << endl;
	ofs << "Normal dictionary - terminals set; " << m_norDic_terminals_max << endl;
	ofs << "Normal dictionary - roots; " << m_norDic_roots_max << endl;
	ofs << "Normal dictionary - symbol to generation; " << m_norDic_symbolToGen_max << endl;
	ofs << "Normal dictionary - pair vectors; " << m_norDic_pairVectors_max << endl;
	ofs << "Normal dictionary - terminal vector; " << m_norDic_terminalVector_max << endl;
	ofs << "Normal dictionary - offset array; " << m_norDic_offsets_max << endl;

	ofs << "Normal dictionary - total; " << max(m_norDic_supportStructures_total, m_norDic_total) << endl;
	ofs << "Normal dictionary - total (mb); " << (max(m_norDic_supportStructures_total, m_norDic_total) / mb) * 4 << endl;

	ofs << "Huffman dictionary - phrase table; " << m_huffDic_phraseTable_max << endl;
	ofs << "Huffman dictionary - first codes array; " << m_huffDic_firstCodes_max << endl;
	ofs << "Huffman dictionary - nr of codes array; " << m_huffDic_nrOfCodes_max << endl;
	ofs << "Huffman dictionary - Huffman to symbol; " << m_huffDic_huffmanToSymbol_max << endl;
	ofs << "Huffman dictionary - symbol to generation; " << m_huffDic_symbolToGen_max << endl;
	ofs << "Huffman dictionary - pair vectors; " << m_huffDic_pairVectors_max << endl;
	ofs << "Huffman dictionary - terminal vector; " << m_huffDic_terminalVector_max << endl;

	ofs << "Huffman dictionary - total; " << m_huffDic_total << endl;
	ofs << "Huffman dictionary - total (mb); " << (m_huffDic_total / mb) * 4 << endl;
	ofs << endl;
	ofs << endl;

	ofs << "Maximum amount of memory used; " << m_total << endl;
	ofs << "Maximum amount of memory used (mb); " << (m_total / mb) * 4 << endl;
	ofs << endl;


	ofs << "Statistics:" << endl;

	ofs << "Huffman code max length; " << s_huffmanCodeLength_max << endl;
	ofs << "Total nr of pairs created; " << s_maxPairs << endl;
	ofs << "Max nr of generations; " << s_nrOfGenerations << endl;
	ofs << "Total nr of phrases; " << s_nrOfPhrases << endl;
	ofs << "Avg nr of phrases per generation; " << s_avgNrOfPhrases << endl;
	ofs << "Largest generation; " << s_largestGeneration << endl;
	ofs << "Largest generation count; " << s_largestGenerationCount << endl;
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
	else if (part == "repairPhrase")
	{
		m_repair_phraseTable_max += value;
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
	else if (part == "huffEncPhrase")
	{
		m_huffEnc_phraseTable_max += value;
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
	else if (part == "norDicPhrase")
	{
		m_norDic_phraseTable_max += value;
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
	else if (part == "huffDicPhrase")
	{
		m_huffDic_phraseTable_max += value;
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