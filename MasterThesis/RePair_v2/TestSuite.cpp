#include "stdafx.h"
#include "TestSuite.h"


TestSuite::TestSuite()
{
}


TestSuite::~TestSuite()
{
}


void TestSuite::WriteToFileEncoding()
{
	double offset = 1000000.000;
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
	ofs << endl;

	ofs << "Compression (in bytes):" << endl;

	ofs << "Sequence; " << c_sequence << endl;
	ofs << "Huffman dictionary; " << c_huffmanDictionary << endl;
	ofs << "Dictionary; " << c_dictionary << endl;
	ofs << "Total dictionary; " << c_dictionary + c_huffmanDictionary << endl;
	ofs << endl;

	ofs << "memory (in words):" << endl;

	ofs << "Initialization - sequence array; " << m_init_sequenceArray_max << endl;
	ofs << "Initialization - active pairs; " << m_init_pairRecord_max << endl;
	ofs << "Initialization - priority queue; " << m_init_priorityQueue_max << endl;
	ofs << "Initialization - total; " << m_init_total << endl;

	ofs << "Re-Pair - sequence array; " << m_repair_sequenceArray_max << endl;
	ofs << "Re-Pair - active pairs; " << m_repair_pairRecord_max << endl;
	ofs << "Re-Pair - priority queue; " << m_repair_priorityQueue_max << endl;
	ofs << "Re-Pair - phrase table; " << m_repair_phraseTable_max << endl;
	ofs << "Re-Pair - total; " << m_repair_total << endl;

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
	ofs << endl;



	ofs << "Statistics:" << endl;

	ofs << "Huffman code max length; " << s_huffmanCodeLength_max << endl;
	ofs << endl;

	ofs.close();

	cout << "Created file with test data." << endl;
}

void TestSuite::addMemory(std::string part, long value)
{
	//Initialization
	if (part == "initSeq")
	{
		m_init_sequenceArray_current += value;
		if (m_init_sequenceArray_current > m_init_sequenceArray_max)
		{
			m_init_total -= m_init_sequenceArray_max;
			m_init_sequenceArray_max = m_init_sequenceArray_current;
			m_init_total += m_init_sequenceArray_max;
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
		}
			
	}
	else if (part == "initPrio")
	{
		m_init_priorityQueue_max += value;
		m_init_total += m_init_priorityQueue_max;
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
		}

	}
	else if (part == "repairPrio")
	{
		m_repair_priorityQueue_max += value;
		m_repair_total += value;
	}
	else if (part == "repairPhrase")
	{
		m_repair_phraseTable_max += value;
		m_repair_total += value;
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
		}

	}
	else if (part == "huffEncPhrase")
	{
		m_huffEnc_phraseTable_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncFreq")
	{
		m_huffEnc_frequencies_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncCodeLength")
	{
		m_huffEnc_codeLengths_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncFirstCodes")
	{
		m_huffEnc_firstCodes_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncNrOfCodes")
	{
		m_huffEnc_nrOfCodes_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncNextCodes")
	{
		m_huffEnc_nextCodes_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncHuffmanCodes")
	{
		m_huffEnc_huffmanCodes_max += value;
		m_huffEnc_total += value;
	}
	else if (part == "huffEncHuffmanToSymbol")
	{
		m_huffEnc_huffmanToSymbol_max += value;
		m_huffEnc_total += value;
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
		}

	}
	else if (part == "norDicPhrase")
	{
		m_norDic_phraseTable_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicFirstCodes")
	{
		m_norDic_firstCodes_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicNrOfCodes")
	{
		m_norDic_nrOfCodes_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicHuffmanToSymbol")
	{
		m_norDic_huffmanToSymbol_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicTerminals")
	{
		m_norDic_terminals_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicRoots")
	{
		m_norDic_roots_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicSymbolToGen")
	{
		m_norDic_symbolToGen_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicPairVectors")
	{
		m_norDic_pairVectors_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicTerminalVector")
	{
		m_norDic_terminalVector_max += value;
		m_norDic_total += value;
	}
	else if (part == "norDicOffsets")
	{
		m_norDic_offsets_max += value;
		m_norDic_total += value;
	}


	else
	{
		cout << "Testing, add memory - program part not supported" << endl;
	}
}