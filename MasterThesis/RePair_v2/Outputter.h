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
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		bool firstBlock);
	void Outputter::huffmanDictionary(
		string outFile,
		unsigned int maxLength,
		unsigned int *firstCode,
		unsigned int *numl,
		unordered_map<unsigned int, Pair> &dictionary,
		unordered_map <unsigned int, unordered_map<unsigned int, unsigned int>*> &indices,
		unordered_map<unsigned int, unsigned int> *terminalIndices,
		unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol);
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
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unordered_set<unsigned int>& terminals,
		Conditions& c);
};

