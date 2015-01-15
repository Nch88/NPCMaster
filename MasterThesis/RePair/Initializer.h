#include "stdafx.h"

using namespace std;

#pragma once
class Initializer
{
public:
	Initializer();
	~Initializer();

	void SequenceArray(string filename,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs);
	void PriorityQueue(int priorityQueueSize,
		unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
};

