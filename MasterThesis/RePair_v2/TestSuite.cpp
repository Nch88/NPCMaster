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
	if (offset == 0.0)
		unit = "ns";

	ofstream ofs;
	string file = "TestData.csv";
	ofs.open(file, ios::trunc);

	ofs << "Data for encoding file " << s_filename << ":" << endl << endl;

	ofs << "Timing (in " << unit << "):" << endl;

	ofs << "Initialization" << ", " << t_initialization.count() / offset << endl;
	ofs << "Re-Pair, " << t_repair.count() / offset << endl;
	ofs << "Huffman encoding, " << t_huffmanEncoding.count() / offset << endl;
	ofs << "Encode sequence, " << t_encodeSequence.count() / offset << endl;
	ofs << "Write Huffman dictionary, " << t_writeHuffmanDictionary.count() / offset << endl;
	ofs << "Setup dictionary, " << t_setupDictionary.count() / offset << endl;
	ofs << "Write dictionary, " << t_writeDictionary.count() / offset << endl;
	ofs << endl;

	ofs << "Compression (in bytes):" << endl;

	ofs << "Sequence, " << c_sequence << endl;
	ofs << "Huffman dictionary, " << c_huffmanDictionary << endl;
	ofs << "Dictionary, " << c_dictionary << endl;
	ofs << "Total dictionary, " << c_dictionary + c_huffmanDictionary << endl;
	ofs << endl;

	ofs << "memory (in words):" << endl;

	ofs << "Initialization - sequence array, " << m_init_sequenceArray_max << endl;
	ofs << "Initialization - total, " << m_init_sequenceArray_max << endl;
	ofs << endl;

	ofs.close();

	cout << "Created file with test data." << endl;
}

void TestSuite::addMemory(std::string part, long value)
{
	if (part == "initSeq")
	{
		m_init_sequenceArray_current += value;
		if (m_init_sequenceArray_current > m_init_sequenceArray_max)
			m_init_sequenceArray_max = m_init_sequenceArray_current;
	}
}