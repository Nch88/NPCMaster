#include "stdafx.h"

using namespace std;
using namespace google;

#pragma once
class Initializer
{
public:
	Initializer();
	~Initializer();

	int SequenceArray(string filename,
		bool verbose,
		bool extraVerbose,
		bool timer);
	void PriorityQueue(int priorityQueueSize,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		Conditions& c);
	void setupPairRecord(
		long leftSymbol,
		long rightSymbol,
		int offset,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs);
};

