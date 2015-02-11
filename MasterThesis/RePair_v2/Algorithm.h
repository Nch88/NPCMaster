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
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		unordered_map<unsigned int, Pair> & dictionary,
		unsigned int & symbols);
};

