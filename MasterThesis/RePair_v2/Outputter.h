#pragma once
class Outputter
{
public:
	Outputter();
	~Outputter();

	string createName(string inputFile, string addName);
	void Outputter::writeChunk(ofstream &myfile, string chunk);
	void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite);
	void Outputter::huffmanEncoding(
		string inputFile,
		vector<SymbolRecord *>& sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		bool firstBlock);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string inputFile,
		unordered_map<unsigned int, Pair>& dictionary,
		bool firstBlock);
};

