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
		ofstream &myfile,
		vector<SymbolRecord *>& sequenceArray,
		dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes,
		bool firstBlock);
	void Outputter::huffmanDictionary(
		string outFile,
		ofstream &myfile,
		unsigned long  maxLength,
		unsigned long  *firstCode,
		unsigned long  *numl,
		dense_hash_map <unsigned long , dense_hash_map<unsigned long , unsigned long >> &indices,
		dense_hash_map<unsigned long , unsigned long > &terminalIndices,
		dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &huffmanToSymbol);
	void compressedFile(
		string inputFile,
		vector<SymbolRecord>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string outfile,
		ofstream &myfile,
		string& output,
		bool firstBlock);
	void Outputter::all(
		string filename,
		bool firstBlock,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unordered_set<unsigned long >& terminals,
		Conditions& c);
};

