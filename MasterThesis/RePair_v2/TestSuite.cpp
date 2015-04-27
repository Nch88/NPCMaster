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

	ofs << "Timing:" << endl;

	ofs << "Initialization, " << t_initialization << endl;
	ofs << "Re-Pair, " << t_repair << endl;
	ofs << "Huffman encoding, " << t_huffmanEncoding << endl;
	ofs << "Encode sequence, " << t_encodeSequence << endl;
	ofs << "Write Huffman dictionary, " << t_writeHuffmanDictionary << endl;
	ofs << "Setup dictionary, " << t_setupDictionary << endl;
	ofs << "Write dictionary, " << t_writeDictionary << endl;

	ofs.close();
}