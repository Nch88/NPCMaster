#pragma once

using namespace std;

class Initializer
{
public:
	Initializer();
	~Initializer();

	void Initializer::resetCompleted(
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		int blockSize);
	void resetForNextBlock(
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		int blockSize);
	void addToSequenceArray(
		vector<SymbolRecord*> & sequenceArray,
		char & symbol,
		long & index,
		int & symbolCount,
		unordered_set<unsigned int>& terminals);
	int SequenceArray(
		Conditions c,
		ifstream & file,
		int & blockSize,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<unsigned int>& terminals);
	void setupPairRecord(
		unsigned int leftSymbol,
		unsigned int rightSymbol,
		int offset,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray);
	void PriorityQueue(int priorityQueueSize,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<PairRecord*> & priorityQueue,
		Conditions & c);
};