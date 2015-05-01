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
	void Outputter::huffmanEncoding(
		string outFile,
		ofstream &myfile,
		vector<SymbolRecord *>& sequenceArray,
		dense_hash_map<long, HuffmanNode> &huffmanCodes,
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
		dense_hash_map<long, Pair> &dictionary,
		dense_hash_map <long, dense_hash_map<long, long>> &indices,
		dense_hash_map<long, long> &terminalIndices,
		dense_hash_map<long, dense_hash_map<long, long>> &huffmanToSymbol,
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
	void Outputter::all(
		string filename,
		bool firstBlock,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		unordered_set<long>& terminals,
		Conditions& c);
};

