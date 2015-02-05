#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	void establishContext(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray);
	void replaceAllPairs(
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		Conditions& c);


};

