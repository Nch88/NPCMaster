#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	void removeSymbolThreadingPointers(
		long & indexSymbolLeft,
		vector<SymbolRecord*> & sequenceArray);
	void updatePairRecord(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		PairTracker *& tracker);
	void removeFromPriorityQueueList(
		long index,
		PairTracker *& tracker,
		vector<PairRecord*>& priorityQueue);
	void addToPriorityQueueList(
		long index,
		PairTracker *& tracker,
		vector<PairRecord*>& priorityQueue);
	void moveDownInPriorityQueue(
		PairTracker *& tracker,
		vector<PairRecord*>& priorityQueue);
	void decrementCount(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		PairTracker *& tracker,
		Conditions& c);
	void decrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);
	void decrementCountRight(
		long & indexSymbolRight,
		long & indexSymbolNext,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);
	void incrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		unsigned int & Symbols,
		Conditions& c);
	void incrementCountRight(
		long & indexSymbolRight,
		long & indexSymbolNext,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue, 
		unsigned int & Symbols,
		Conditions& c);
	void replaceInstanceOfPair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, Pair>& dictionary,
		unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unsigned int & Symbols,
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
		unsigned int & Symbols,
		Conditions& c);


};

