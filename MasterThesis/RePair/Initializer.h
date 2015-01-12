#include "stdafx.h"

using namespace std;

#pragma once
class Initializer
{
public:
	Initializer();
	~Initializer();

	void SequenceArray(string filename,
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<std::string, PairRecord> * activePairs);

	void PriorityQueue(int priorityQueueSize,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue);
};

