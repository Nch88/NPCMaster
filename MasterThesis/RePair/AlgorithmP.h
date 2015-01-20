#include "stdafx.h"

using namespace std;

#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	
	void updatePairRecord(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<PairRecord>& tmpPairRecord);
	void updatePairSequence(
		shared_ptr<SymbolRecord>& symbolLeft,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		shared_ptr<PairRecord>& tmpPairRecord);
	void setupPairSequence(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		shared_ptr<PairRecord>& tmpPairRecord);
	void setupPairRecord(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<PairRecord>& tmpPairRecord);
	void increaseCount(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<PairRecord>& tmpPairRecord,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs);
	void threadEmptySymbols(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
	void replacePair(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<unsigned int>& Symbols,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
	void insertIntoListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void removeFromListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void managePriorityQueueDecrement(shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void manageSequenceDecrement(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<PairRecord>& tmpPairRecordAdjacent);
	void decrementCount(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		shared_ptr<PairRecord>& tmpPairRecordAdjacent);
	void checkActivePair(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext);
	void checkActivePairs(
		int sequenceIndex,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols);
	void establishContext(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		int sequenceIndex);
	void replaceInstanceOfPair(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext);
	void replaceAllPairs(
		int sequenceIndex,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols);
	void newSymbol(
		unique_ptr<unsigned int>& Symbols,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void manageOneEntryOnList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		int i,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void manageOneList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		int i,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void manageHighPriorityList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void AlgorithmP::manageLowerPriorityLists(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
	void run(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, Pair>>& dictionary,
		unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<unsigned int>& Symbols,
		unique_ptr<unordered_map<char, bool>>& symbolMap);
};