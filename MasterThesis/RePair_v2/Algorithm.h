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
		MyTimer t,
		int blockSize,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord*> & sequenceArray);
};

