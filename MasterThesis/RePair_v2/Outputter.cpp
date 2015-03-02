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

void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite)
{
	int n = bitsToWrite->size() / 8;
	for (int i = n - 1; i>=0; --i) {
		uint8_t byte = 0;
		for (int j = 7; j>=0; --j)
			byte = (byte << 1) | (*bitsToWrite)[i * 8 + j];
		myfile.write((char*)&byte, 1);
	}
}

void Outputter::writeChunkFromString(ofstream &myfile, string chunk)
{
	bitset<32> *bitsToWrite;
	bitsToWrite = new bitset<32>(chunk);											//!!!!!!!!!!!!!!  Dont allocate/deallocate every time! !!!!!!!!!!!!!!!

	writeChunk(myfile, bitsToWrite);

	delete bitsToWrite;
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
			writeChunkFromString(myfile, chunk);
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
	writeChunkFromString(myfile, chunk);
	chunk = "";

	//Write padding chunk
	bitsToWrite = new bitset<32>(paddingBits);
	bitsToWrite->set(bitsToWrite->size() - 1, true);
	writeChunk(myfile, bitsToWrite);

	myfile.close();

	if (firstBlock)
		cout << "created compressed file: " << outFile << endl;
}

void Outputter::huffmanDictionary(
	string outFile,
	unsigned int maxLength,
	unsigned int *firstCode,
	unsigned int *numl,
	unordered_map<unsigned int, Pair> &dictionary,
	unordered_map <unsigned int, unordered_map<unsigned int, unsigned int>*> &indices,
	unordered_map<unsigned int, unsigned int> *terminalIndices,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol)
{
	ofstream myfile;
	myfile.open(outFile, ios::binary | ios::trunc);

	GammaCode gc;

	string gammaCodes = "";
	string stringToWrite;

	gammaCodes += gc.getGammaCode(maxLength);									//Write this many "items"

	for (unsigned int i = 0; i < maxLength; i++)
	{
		gammaCodes += gc.getGammaCode(numl[i]);									//Convert number of codes of this length to gamma code
																				//and append to the string of codes we want to write.
		gammaCodes += gc.getGammaCode(firstCode[i]);							//Convert the value of the first code as well

		for (int j = 0; j < numl[i]; j++)
		{
			unsigned int symbol = (*huffmanToSymbol[i + 1])[firstCode[i] + j];
			unsigned int index;
			if (symbol >= initialSymbolValue)
			{
				unsigned int symbolLeft = dictionary[symbol].leftSymbol;
				unsigned int symbolRight = dictionary[symbol].rightSymbol;
				index = (*indices[symbolLeft])[symbolRight];
			}
			else
				index = (*terminalIndices)[symbol];
			
			gammaCodes += gc.getGammaCode(index);								//Write the index corresponding to a specific huffman code (as gamma code)
		}

		while (gammaCodes.size() >= 32)											//Write as much as possible to file
		{
			stringToWrite = gammaCodes.substr(0, 32);
			gammaCodes = gammaCodes.substr(32, gammaCodes.size());

			writeChunkFromString(myfile, stringToWrite);						//Write 4 bytes of the sequence of gamma codes
		}
	}			
	while (gammaCodes.size() < 32)
	{
		gammaCodes += '0';
	}
	writeChunkFromString(myfile, gammaCodes);									//Write the last gamma codes and possibly padding
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
	string outFile,
	string& output,
	bool firstBlock)
{
	ofstream myfile;
	if (firstBlock)
		myfile.open(outFile, ios::binary | ios::trunc);
	else
		myfile.open(outFile, ios::binary | ios::app);
	
	string stringToWrite, rest = output;

	//Write as much as possible to file
	while (rest.size() >= 32)
	{ 
		//Write 4 bytes of the sequence of gamma codes
		stringToWrite = rest.substr(0, 32);
		rest = rest.substr(32, string::npos);
		writeChunkFromString(myfile, stringToWrite);						
	}

	//Write the last bit, if any is left
	if (rest != "")
	{
		while (rest.size() < 32)
		{
			rest += '0';
		}
		writeChunkFromString(myfile, rest);
	}

	myfile.close();
}