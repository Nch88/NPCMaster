#pragma once

using namespace google;
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	long AlgorithmP::findGeneration(
		dense_hash_map<long, Pair>& dictionary, 
		long left, 
		long right);

	SymbolRecord* AlgorithmP::findNextEmpty(
		vector<SymbolRecord*> & sequenceArray,
		SymbolRecord* current);

	void AlgorithmP::compact(
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*>& priorityQueue);

	void removeSymbolThreadingPointers(
		long & indexSymbolLeft,
		vector<SymbolRecord*> & sequenceArray);

	void AlgorithmP::deletePairRecord(
		long & symbolLeft,
		long & symbolRight,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs);

	void updatePairRecord(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
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

	///Updates the records of a pair that just had an instance removed
	void decrementCount(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		PairTracker *& tracker,
		Conditions& c);

	//Decrements count and updates structures of the pair whose right symbol
	//is the current symbol
	void decrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);

	//Decrements count and updates structures of the pair whose left symbol
	//is to the right of the current symbol
	void decrementCountRight(
		long & indexSymbolRight,
		long & indexSymbolNext,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray, 
		vector<PairRecord*>& priorityQueue,
		Conditions& c);

	void incrementCountLeft(
		long & indexSymbolPrevious,
		long & indexSymbolLeft,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		bool &skip,
		Conditions& c);

	void incrementCountRight(
		long & indexSymbolLeft,
		long & indexSymbolNext,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue, 
		long & Symbols,
		Conditions& c);

	//Makes sure that empty symbols have pointers to the previous and next actual symbols
	//in the sequence array
	void threadEmptySymbols(
		SymbolRecord *& leftSymbolRecord,
		SymbolRecord *& rightSymbolRecord,
		SymbolRecord *& nextSymbolRecord,
		vector<SymbolRecord*> & sequenceArray);

	//Replaces the symbols of the current pair in the sequence array with a new and an empty symbol
	//while adding a record of the replacement to the dictionary
	void replacePair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolNext,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		long & Symbols,
		Conditions& c);

	//Replaces one instance of an active pair in the current context:
	//xaby --> xA_y
	void replaceInstanceOfPair(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		bool& skip,
		Conditions& c);

	//Identifies the context of the current left symbol in the sequence
	//*a** --> xaby
	void establishContext(
		long & indexSymbolLeft,
		long & indexSymbolRight,
		long & indexSymbolPrevious,
		long & indexSymbolNext,
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray);

	//Makes a pass of the instances of one active pair an replaces them in the sequence array
	void replaceAllPairs(
		long sequenceIndex,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		Conditions& c);

	//Finds the next symbol and notifies us if we run out of symbols
	void AlgorithmP::newSymbol(long & Symbols);

	//Replaces all instances of a pair from one list entry in the priority queue
	void AlgorithmP::manageOneEntryOnList(
		long i,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);

	//Replaces all pairs on one list entry in the priority queue
	void AlgorithmP::manageOneList(
		long i,
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);

	//Runs though the priority list from second last to first entry, replacing all pairs
	void AlgorithmP::manageLowerPriorityLists(
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);

	//Replaces all pairs in decreasing order of frequency from the last list in the priority queue
	void AlgorithmP::manageHighPriorityList(
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		long & Symbols,
		CompactionData &cData,
		Conditions& c);

	//Runs the Re-Pair algorithm on the current block
	void AlgorithmP::run(
		vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, Pair>& dictionary,
		dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs,
		vector<PairRecord*>& priorityQueue,
		unordered_set<long>& terminals,
		long & Symbols,
		Conditions& c);
};