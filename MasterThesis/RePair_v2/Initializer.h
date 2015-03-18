#pragma once

using namespace std;
using namespace google;

class Initializer
{
public:
	Initializer();
	~Initializer();

	void Initializer::resetCompleted(
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		int blockSize);
	void Initializer::resetForNextBlock(
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		unordered_set<long> & terminals,
		dense_hash_map<long, Pair> &dictionary);
	void addToSequenceArray(
		vector<SymbolRecord*> & sequenceArray,
		unsigned char & symbol,
		long & index,
		int & symbolCount,
		unordered_set<long>& terminals);
	int SequenceArray(
		Conditions c,
		ifstream & file,
		int & blockSize,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<long>& terminals);
	void setupPairRecord(
		long leftSymbol,
		long rightSymbol,
		int offset,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray);
	void PriorityQueue(int priorityQueueSize,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*> & priorityQueue,
		Conditions & c);
};