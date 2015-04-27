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
	ofstream ofs;
	string file = "TestData";
	ofs.open(file, ios::trunc);

	ofs << "Data for encoding file " << s_filename << ":" << endl << endl;

	ofs << "Timing (in ns):" << endl;

	ofs << "Initialization, " << t_initialization.count() << endl;
	ofs << "Re-Pair, " << t_repair.count() << endl;
	ofs << "Huffman encoding, " << t_huffmanEncoding.count() << endl;
	ofs << "Encode sequence, " << t_encodeSequence.count() << endl;
	ofs << "Write Huffman dictionary, " << t_writeHuffmanDictionary.count() << endl;
	ofs << "Setup dictionary, " << t_setupDictionary.count() << endl;
	ofs << "Write dictionary, " << t_writeDictionary.count() << endl;

	ofs.close();

	cout << "Created file with test data." << endl;
}