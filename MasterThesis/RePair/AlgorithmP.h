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
		long indexFirst,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<PairRecord>& tmpPairRecord);
	void increaseCount(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<PairRecord>& tmpPairRecord,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs);
	void threadEmptySymbols(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray);
	void replacePair(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<long>& Symbols,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		Conditions& c);
	void insertIntoListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void removeFromListInPriorityQueue(int index, shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void managePriorityQueueDecrement(shared_ptr<PairRecord>& tmpPairRecordAdjacent, unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue);
	void manageSequenceDecrement(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<PairRecord>& tmpPairRecordAdjacent);
	void decrementCount(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		shared_ptr<PairRecord>& tmpPairRecordAdjacent);
	void checkActivePair(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext,
		Conditions& c);
	void checkActivePairs(
		int sequenceIndex,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		Conditions& c);
	void establishContext(
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		int sequenceIndex,
		Conditions& c);
	void replaceInstanceOfPair(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		shared_ptr<SymbolRecord>& symbolLeft,
		shared_ptr<SymbolRecord>& symbolRight,
		shared_ptr<SymbolRecord>& symbolPrevious,
		shared_ptr<SymbolRecord>& symbolNext,
		Conditions& c);
	void replaceAllPairs(
		int sequenceIndex,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		Conditions& c);
	void newSymbol(
		unique_ptr<long>& Symbols);
	void manageOneEntryOnList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		int i,
		Conditions& c);
	void manageOneList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		int i,
		Conditions& c);
	void manageHighPriorityList(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		Conditions& c);
	void AlgorithmP::manageLowerPriorityLists(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		Conditions& c);
	void run(
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<dense_hash_map<long, Pair>>& dictionary,
		unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
		unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<long>& Symbols,
		Conditions& c);
};