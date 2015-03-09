#pragma once
class Algorithm
{
public:
	Algorithm();
	~Algorithm();

	int Algorithm::run(
		string filename,
		ifstream & file,
		Conditions c,
		Initializer init,
		AlgorithmP algP,
		MyTimer t,
		int blockSize,
		unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		unordered_map<long, Pair> & dictionary,
		long & symbols);
};

