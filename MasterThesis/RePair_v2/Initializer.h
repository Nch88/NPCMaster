#pragma once

using namespace std;

class Initializer
{
public:
	Initializer();
	~Initializer();

	void Initializer::resetCompleted(
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		int blockSize);
	void resetForNextBlock(
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		int blockSize);
	void addToSequenceArray(
		vector<SymbolRecord*> & sequenceArray,
		char & symbol,
		long & index,
		int & symbolCount,
		unordered_set<long>& terminals);
	int SequenceArray(
		Conditions c,
		ifstream & file,
		int & blockSize,
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<long>& terminals);
	void setupPairRecord(
		long leftSymbol,
		long rightSymbol,
		int offset,
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray);
	void PriorityQueue(int priorityQueueSize,
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<PairRecord*> & priorityQueue,
		Conditions & c);
};