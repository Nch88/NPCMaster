#include "stdafx.h"

using namespace std;

#pragma once
class Initializer
{
public:
	Initializer();
	~Initializer();

	void checkSymbol(char symbol, unique_ptr<unordered_map<char, bool>>& symbolMap);
	void SequenceArray(string filename,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void PriorityQueue(int priorityQueueSize,
		unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void setupPairRecord(
		char leftSymbol,
		char rightSymbol,
		int offset,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs);	
};

