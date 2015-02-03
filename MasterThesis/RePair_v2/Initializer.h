#include "stdafx.h"
#pragma once

using namespace std;

class Initializer
{
public:
	Initializer();
	~Initializer();

	int SequenceArray(
		Conditions c,
		ifstream & file,
		int & blockSize,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord> & sequenceArray);
	void setupPairRecord(
		unsigned int leftSymbol,
		unsigned int rightSymbol,
		int offset,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
		vector<SymbolRecord> & sequenceArray);
};