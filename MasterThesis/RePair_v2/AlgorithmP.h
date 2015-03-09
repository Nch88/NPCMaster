#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	long AlgorithmP::findGeneration(
		unordered_map<long, Pair>& dictionary, 
		long left, 
		long right);
	SymbolRecord* AlgorithmP::findNextEmpty(
		vector<SymbolRecord*> & sequenceArray,
		SymbolRecord* current);
	void AlgorithmP::compact(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue);
	void removeSymbolThreadingPointers(
		long & indexSymbolLeft,
		vector<SymbolRecord*> & sequenceArray);
	void AlgorithmP::deletePairRecord(
		long & symbolLeft,
		long & symbolRight,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs);
	void updatePairRecord(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
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
	void AlgorithmP::moveUpInPriorityQueue(
		PairTracker *& tracker,
		vector<PairRecord*>& priorityQueue);
	void decrementCount(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		PairTracker *& tracker,
		Conditions& c);
	void decrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);
	void decrementCountRight(
		long & indexSymbolRight,
		long & indexSymbolNext,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);
	void incrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		bool &skip,
		Conditions& c);
	void incrementCountRight(
		long & indexSymbolLeft,
		long & indexSymbolNext,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue, 
		long & Symbols,
		Conditions& c);
	void threadEmptySymbols(
		SymbolRecord *& leftSymbolRecord,
		SymbolRecord *& rightSymbolRecord,
		SymbolRecord *& nextSymbolRecord,
		vector<SymbolRecord*> & sequenceArray);
	void replacePair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolNext,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		long & Symbols,
		Conditions& c);
	void replaceInstanceOfPair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		bool& skip,
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
	void replaceAllPairs(
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		Conditions& c);
	void AlgorithmP::newSymbol(long & Symbols);
	void AlgorithmP::manageOneEntryOnList(
		long i,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);
	void AlgorithmP::manageOneList(
		long i,
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);
	void AlgorithmP::manageLowerPriorityLists(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);
	void AlgorithmP::manageHighPriorityList(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);
	void AlgorithmP::run(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<long, Pair>& dictionary,
		unordered_map<long, unordered_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unordered_set<long>& terminals,
		long & Symbols,
		Conditions& c);
};

