#include "stdafx.h"
#include "Outputter.h"

using namespace std;

Outputter::Outputter()
{
}


Outputter::~Outputter()
{
}

string Outputter::createName(string inputFile, string addName)
{
	string outFile = "";
	int i = 0;
	int empty = 0;

	outFile += addName;
	outFile += "_";

	while (inputFile[i] != '.')
		outFile += inputFile[i++];	

	while (inputFile[i] != empty)
		outFile += inputFile[i++];

	return outFile;
}

void Outputter::writeChunk(ofstream &myfile, string chunk)
{
	bitset<32> *bitsToWrite;
	bitsToWrite = new bitset<32>(chunk);

	for (size_t i = 0, n = (bitsToWrite->size() + 1) % 8; i<n; ++i) {
		uint8_t byte = 0;
		for (size_t j = 0; j<8; ++j)
			byte = (byte << 1) | (*bitsToWrite)[i * 8 + j];
		myfile << byte;
	}
}

void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite)
{
	for (size_t i = 0, n = (bitsToWrite->size() + 1) % 8; i<n; ++i) {
		uint8_t byte = 0;
		for (size_t j = 0; j<8; ++j)
			byte = (byte << 1) | (*bitsToWrite)[i * 8 + j];
		myfile << byte;
	}
}

void Outputter::huffmanEncoding(
	string inputFile,
	vector<SymbolRecord *>& sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "Compressed");	
	bitset<32> *bitsToWrite;
	short chunkSize = sizeof(bitset<32>) * CHAR_BIT; //Bitset outputs a certain minimum nr of bytes
	string chunk = "";
	string specialBit = "0";
	string code = "";
	unsigned int seqIndex = 0;
	unsigned int codeIndex = 0;
	short paddingBits = 0;

	if (firstBlock)
		myfile.open(outFile, ios::binary | ios::trunc);
	else
		myfile.open(outFile, ios::binary | ios::app);

	//Write chunks of Huffman codes until an entire block is processed
	while (seqIndex < sequenceArray.size())
	{
		//Start new chunk
		chunk += specialBit;
		while (chunk.size() < chunkSize && seqIndex < sequenceArray.size())
		{
			if (codeIndex == code.size() || code.size() == 0) //Current code is processed but chunk is not full
			{
				while (seqIndex < sequenceArray.size() && sequenceArray[seqIndex]->symbol == 0)
					seqIndex++;
				
				if (seqIndex < sequenceArray.size())
				{
					code = huffmanCodes[sequenceArray[seqIndex++]->symbol]->code;
					codeIndex = 0;
				}				
			}

			while (
				chunk.size() < chunkSize && 
				codeIndex < code.size())
				//Process Huffman code for current symbol
			{
				chunk += code[codeIndex++];
			}	
		}

		//Write chunk and reset for next chunk
		//If last symbol the do not write yet as we need to pad the chunk
		if (seqIndex < sequenceArray.size())
		{
			writeChunk(myfile, chunk);
			chunk = "";
		}
	}
	//Add the last part of the code for the last symbol to current chunk if necessary
	while (codeIndex != code.size() && code.size() != 0)
	{
		chunk += code[codeIndex++];
	}

	//Add padding bits on the last actual chunk if there was not enough code to fill it out
	paddingBits = chunkSize - chunk.size();
	while (chunk.size() < chunkSize)
	{
		chunk += "0";
	}

	//Write the last actual chunk
	writeChunk(myfile, chunk);
	chunk = "";

	//Write padding chunk
	bitsToWrite = new bitset<32>(paddingBits);
	bitsToWrite->set(bitsToWrite->size() - 1, true);
	writeChunk(myfile, bitsToWrite);

	myfile.close();

	if (firstBlock)
		cout << "created compressed file: " << outFile << endl;
}

void Outputter::compressedFile(
	string inputFile,
	vector<SymbolRecord>& sequenceArray,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "CompressedNoHuffman");

	if (firstBlock)
		myfile.open(outFile, ios::trunc);
	else
		myfile.open(outFile, ios::app);

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i].symbol != 0)
			myfile << sequenceArray[i].symbol;
	}
	myfile << UINT_MAX;
	myfile.close();

	if (firstBlock)
		cout << "created compressed file (no Huffman): " << outFile << endl;
}

void Outputter::dictionary(
	string inputFile,
	unordered_map<unsigned int, Pair>& dictionary,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "CompressedDictionary");

	if (firstBlock)
		myfile.open(outFile, ios::trunc);
	else
		myfile.open(outFile, ios::app);

	for each (auto pair in dictionary)
	{
		myfile << pair.first << " " << pair.second.leftSymbol << "" << pair.second.rightSymbol << endl;
	}
	myfile << UINT_MAX << endl;
	myfile.close();

	if (firstBlock)
		cout << "created dictionary file: " << outFile << endl;
}