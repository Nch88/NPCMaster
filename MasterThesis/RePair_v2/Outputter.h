#pragma once
class Outputter
{
public:
	Outputter();
	~Outputter();

	string createName(string inputFile, string addName);
	string Outputter::addFilenameEnding(string inputFile, string addName);
	void Outputter::writeChunk(ofstream &myfile, bitset<32> *&bitsToWrite);
	void Outputter::writeChunkFromString(ofstream &myfile, string chunk);
	void Outputter::writeDictionaryChunk(ofstream &myfile, string &inchunk, bitset<32> *&bitsToWrite);
	void Outputter::huffmanEncoding(
		string outFile,
		ofstream &myfile,
		vector<SymbolRecord *>& sequenceArray,
		dense_hash_map<unsigned long, HuffmanNode> &huffmanCodes,
		bool firstBlock,
		Conditions & c);
	void Outputter::writeBuffer(
		ofstream &myfile,
		string &gammaCodes,
		string &stringToWrite,
		Conditions &c);
	void Outputter::huffmanDictionary(
		string outFile,
		ofstream &myfile,
		long maxLength,
		long *firstCode,
		long *numl,
		vector<unsigned long> terminalVector,
		dense_hash_map<unsigned long, Pair> &dictionary,
		dense_hash_map<unsigned long, unsigned long> &indices,
		dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> &huffmanToSymbol,
		Conditions &c);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string outfile,
		ofstream &myfile,
		string& output,
		bool firstBlock,
		Conditions &c);
	void Outputter::dictionary2(
		string outFile,
		ofstream &myfile,
		vector<vector<unsigned long>>& pairVectors,
		dense_hash_map<unsigned long, Pair>& dictionary,
		vector<unsigned long>& terminalVector,
		bool firstBlock,
		Conditions &c);
	void Outputter::all(
		string filename,
		bool firstBlock,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<unsigned long, Pair>& dictionary,
		unordered_set<unsigned long>& terminals,
		Conditions& c);
};

