#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	void replaceInstanceOfPair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		Conditions& c);
	void establishContext(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray);
	void establishContext(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolBeforePrevious,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray);
	void findAllPairs(
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unsigned int& Symbols,
		Conditions& c);
	void replaceAllPairs(
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		Conditions& c);


};

