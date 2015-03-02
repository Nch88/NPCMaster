#pragma once
class Outputter
{
public:
	Outputter();
	~Outputter();

	string createName(string inputFile, string addName);
	void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite);
	void Outputter::writeChunkFromString(ofstream &myfile, string chunk);	
	void Outputter::huffmanEncoding(
		string inputFile,
		vector<SymbolRecord *>& sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		bool firstBlock);
	void Outputter::canonicalHuffmanEncoding(
		string inputFile,
		vector<SymbolRecord *>& sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		bool firstBlock);
	void Outputter::huffmanDictionary(
		string outFile,
		unsigned int maxLength,
		unsigned int *firstCode,
		unsigned int *numl,
		unordered_map<unsigned int, unsigned int> codeToIndex);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string outFile,
		string& output,
		bool firstBlock);
};

