#pragma once
class Outputter
{
public:
	Outputter();
	~Outputter();

	string createName(string inputFile, string addName);
	string Outputter::addFilenameEnding(string inputFile, string addName);
	void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite);
	void Outputter::writeChunkFromString(ofstream &myfile, string chunk, bitset<32> *&bitsToWrite);
	void Outputter::writeDictionaryChunk(ofstream &myfile, string &inchunk, bitset<32> *&bitsToWrite);
	void Outputter::huffmanEncoding(
		string outFile,
		ofstream &myfile,
		vector<SymbolRecord *>& sequenceArray,
		dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes,
		bool firstBlock,
		Conditions &c);
	void Outputter::writeBuffer(
		ofstream &myfile,
		string &gammaCodes,
		string &stringToWrite,
		bitset<32> *bitsToWrite,
		Conditions &c);
	void Outputter::huffmanDictionary(
		string outFile,
		ofstream &myfile,
		unsigned long  maxLength,
		unsigned long  *firstCode,
		unsigned long  *numl,
		std::vector<std::vector<unsigned long *>>& pairVectors,
		dense_hash_map<unsigned long, unsigned long >& symbolToGen,
		vector<unsigned long >& terminals,
		dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &huffmanToSymbol,
		Conditions &c);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string outfile,
		ofstream &myfile,
		string& output,
		bool firstBlock);
	void Outputter::dictionary2(
		std::string outFile,
		std::ofstream &myfile,
		std::vector<std::vector<unsigned long *>>& pairVectors,
		vector<unsigned long >& terminalVector,
		bool firstBlock,
		Conditions &c);
	void Outputter::all(
		string filename,
		bool firstBlock,
		vector<SymbolRecord*> & sequenceArray,
		Conditions& c);
};

