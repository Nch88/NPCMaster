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
	void Outputter::huffmanEncoding(
		string outFile,
		vector<SymbolRecord *>& sequenceArray,
		dense_hash_map<long, HuffmanNode> &huffmanCodes,
		bool firstBlock);
	void Outputter::huffmanDictionary(
		string outFile,
		long maxLength,
		long *firstCode,
		long *numl,
		dense_hash_map<long, Pair> &dictionary,
		dense_hash_map <long, dense_hash_map<long, long>> &indices,
		dense_hash_map<long, long> &terminalIndices,
		dense_hash_map<long, dense_hash_map<long, long>> &huffmanToSymbol);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string outFile,
		string& output,
		bool firstBlock);
	void Outputter::all(
		string filename,
		bool firstBlock,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unordered_set<long>& terminals,
		Conditions& c);
};

