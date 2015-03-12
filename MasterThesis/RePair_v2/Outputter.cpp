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

string Outputter::addFilenameEnding(string inputFile, string addName)
{
	inputFile += addName;
	return inputFile;
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

void Outputter::writeChunkFromString(ofstream &myfile, string chunk, bitset<32> *&bitsToWrite)
{											
	for (int i = 0; i < 32; i++)
	{
		if (chunk[i] == '1')
			bitsToWrite->set(31 - i, true);
		else
			bitsToWrite->set(31 - i, false);
	}

	writeChunk(myfile, bitsToWrite);
}

void Outputter::huffmanEncoding(
	string outFile,
	ofstream &myfile,
	vector<SymbolRecord *>& sequenceArray,
	dense_hash_map<long, HuffmanNode> &huffmanCodes,
	bool firstBlock)
{
	bitset<32> *bitsToWrite = new bitset<32>();
	short chunkSize = sizeof(bitset<32>) * CHAR_BIT; //Bitset outputs a certain minimum nr of bytes
	string chunk = "";
	string specialBit = "0";
	string code = "";
	long seqIndex = 0;
	long codeIndex = 0;
	short paddingBits = 0;

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
					code = huffmanCodes[sequenceArray[seqIndex++]->symbol].code;
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
			writeChunkFromString(myfile, chunk, bitsToWrite);
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
	writeChunkFromString(myfile, chunk, bitsToWrite);
	chunk = "";

	//Write padding chunk
	delete bitsToWrite;
	bitsToWrite = new bitset<32>(paddingBits);
	bitsToWrite->set(bitsToWrite->size() - 1, true);
	writeChunk(myfile, bitsToWrite);
	delete bitsToWrite;

	if (firstBlock)
		cout << "created compressed file: " << outFile << endl;
}

void Outputter::huffmanDictionary(
	string outFile,
	ofstream &myfile,
	long maxLength,
	long *firstCode,
	long *numl,
	dense_hash_map<long, Pair> &dictionary,
	dense_hash_map <long, dense_hash_map<long, long>> &indices,
	dense_hash_map<long, long> &terminalIndices,
	dense_hash_map<long, dense_hash_map<long, long>> &huffmanToSymbol)
{
	bitset<32> *bitsToWrite = new bitset<32>();
	GammaCode gc;

	string gammaCodes = "";
	string toWrite = "";
	string stringToWrite;

	gammaCodes += gc.getGammaCode(maxLength);									//Write this many "items"

	for (long i = 0; i < maxLength; i++)
	{
		toWrite = gc.getGammaCode(numl[i]);
		gammaCodes += toWrite;													//Convert number of codes of this length to gamma code
																				//and append to the string of codes we want to write.
		toWrite = gc.getGammaCode(firstCode[i]);
		gammaCodes += toWrite;													//Convert the value of the first code as well

		for (int j = 0; j < numl[i]; j++)
		{
			long symbol = (huffmanToSymbol[i + 1])[firstCode[i] + j];
			long index;
			if (symbol >= initialSymbolValue)
			{
				long symbolLeft = dictionary[symbol].leftSymbol;
				long symbolRight = dictionary[symbol].rightSymbol;
				index = (indices[symbolLeft])[symbolRight];
			}
			else
				index = (terminalIndices)[symbol];
			
			toWrite = gc.getGammaCode(index);
			gammaCodes += toWrite;												//Write the index corresponding to a specific huffman code (as gamma code)
		}

		while (gammaCodes.size() >= 32)											//Write as much as possible to file
		{
			stringToWrite = gammaCodes.substr(0, 32);
			gammaCodes = gammaCodes.substr(32, gammaCodes.size());

			writeChunkFromString(myfile, stringToWrite, bitsToWrite);			//Write 4 bytes of the sequence of gamma codes
		}
	}			
	while (gammaCodes.size() < 32)
	{
		gammaCodes += '0';
	}
	writeChunkFromString(myfile, gammaCodes, bitsToWrite);						//Write the last gamma codes and possibly padding

	delete bitsToWrite;
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
	ofstream &myfile,
	string& output,
	bool firstBlock)
{
	bitset<32> *bitsToWrite = new bitset<32>();
	
	
	string stringToWrite, rest;
	rest.assign(output);

	//Write as much as possible to file
	while (rest.size() >= 32)
	{ 
		//Write 4 bytes of the sequence of gamma codes
		stringToWrite = rest.substr(0, 32);
		rest = rest.substr(32, string::npos);
		writeChunkFromString(myfile, stringToWrite, bitsToWrite);
	}

	//Write the last bit, if any is left
	if (rest != "")
	{
		while (rest.size() < 32)
		{
			rest += '0';
		}
		writeChunkFromString(myfile, rest, bitsToWrite);
	}

	if (firstBlock)
		cout << "created dictionary file: " << outFile << endl;

	delete bitsToWrite;
}

void Outputter::all(
	string filename,
	bool firstBlock,
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<long, Pair>& dictionary,
	dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
	vector<PairRecord*>& priorityQueue,
	unordered_set<long>& terminals,
	Conditions& c)
{
	//Create names for output files
	string compressedFilename = this->addFilenameEnding(filename, ".NPC");
	string compressedDictionaryName = this->addFilenameEnding(filename, ".dict.NPC");

	ofstream ofs_compressed;
	if (firstBlock)
		ofs_compressed.open(compressedFilename, ios::binary | ios::trunc);
	else
		ofs_compressed.open(compressedFilename, ios::binary | ios::app);

	ofstream ofs_dictionary;
	if (firstBlock)
		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::trunc);
	else
		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::app);

	//Do Huffman encoding
	Huffman h;
	dense_hash_map<long, HuffmanNode> huffmanCodes;
	huffmanCodes.set_empty_key(-1);
	huffmanCodes.set_deleted_key(-2);
	long *firstCode = nullptr;
	long *numl = nullptr;
	long maxLength = 0;
	dense_hash_map<long, dense_hash_map<long, long>> huffmanToSymbol;
	huffmanToSymbol.set_empty_key(-1);
	huffmanToSymbol.set_deleted_key(-2);

	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);

	//Write Huffman encoded sequence to file
	this->huffmanEncoding(
		compressedFilename,
		ofs_compressed,
		sequenceArray,
		huffmanCodes,
		firstBlock);

	//Encode generations for dictionary
	Dictionary finalDict;
	vector<vector<CompactPair>> pairs;
	vector<vector<CompactPair>> generationVectors;
	dense_hash_map<long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	dense_hash_map<long, long> terminalIndices;
	terminalIndices.set_empty_key(-1);
	terminalIndices.set_deleted_key(-2);

	finalDict.generateCompactDictionary(
		dictionary,
		terminals,
		pairs,
		indices,
		terminalIndices,
		generationVectors);	

	//Write dictionary to file
	GammaCode gc;
	string output = "";

	gc.makeFinalString(
		pairs,
		terminals,
		output,
		generationVectors);

	this->dictionary(
		compressedDictionaryName,		
		ofs_dictionary,
		output,
		firstBlock);

	//Write Huffman dictionary to file
	this->huffmanDictionary(
		compressedDictionaryName,
		ofs_dictionary,
		maxLength,
		firstCode,
		numl,
		dictionary,
		indices,
		terminalIndices,
		huffmanToSymbol);

	ofs_compressed.close();
	ofs_dictionary.close();

	//Clean up
	delete[] firstCode;
	delete[] numl;
}