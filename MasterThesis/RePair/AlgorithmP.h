#include "stdafx.h"

using namespace std;

#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	void removeFromListInPriorityQueue(
		int index, 
		PairRecord * tmpPairRecordAdjacent, 
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue);
	void replaceAllPairs(
		int sequenceIndex,
		unique_ptr<vector<unique_ptr<SymbolRecord>>> * sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols);
	void decrementCount(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		unordered_map<string,
		PairRecord> * activePairs,
		PairRecord * tmpPairRecordAdjacent,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue);
	void replaceInstanceOfPair(
		unique_ptr<vector<unique_ptr<SymbolRecord>>> * sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols,
		bool firstPair,
		bool lastPair,
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		SymbolRecord* symbolPrevious,
		SymbolRecord* symbolNext);
	void managePriorityQueueDecrement(PairRecord * tmpPairRecordAdjacent, unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue);
	void insertIntoListInPriorityQueue(int index, PairRecord * tmpPairRecord, unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue);
	void replacePair(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		SymbolRecord* symbolNext,
		unique_ptr<int>& Symbols,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs);
	void AlgorithmP::increaseCount(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		PairRecord * tmpPairRecord,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<SymbolRecord>>> * sequenceArray,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue);
	void setupPairRecord(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		PairRecord * tmpPairRecord);
	void setupPairSequence(
		unique_ptr<vector<unique_ptr<SymbolRecord>>> * sequenceArray,
		PairRecord * tmpPairRecord);
	void updatePairSequence(
		SymbolRecord* symbolLeft,
		unique_ptr<vector<unique_ptr<SymbolRecord>>> * sequenceArray,
		PairRecord * tmpPairRecord);
	void updatePairRecord(
		SymbolRecord* symbolLeft,
		PairRecord * tmpPairRecord);
	void establishContext(
		SymbolRecord** symbolLeft,
		SymbolRecord** symbolRight,
		SymbolRecord** symbolPrevious,
		SymbolRecord** symbolNext,
		bool firstPair,
		bool lastPair,
		unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray,
		int sequenceIndex);
	void manageHighPriorityList(
		unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols);
	void AlgorithmP::manageOneEntryOnList(
		unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols,
		int i);
	void manageOneList(
		unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols,
		int i);
	void AlgorithmP::manageLowerPriorityLists(
		unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols);
	void run(
		unique_ptr<vector<shared_ptr<SymbolRecord>>> & sequenceArray,
		unique_ptr<unordered_map<char, string>>& dictionary,
		unique_ptr<unordered_map<string, PairRecord>>& activePairs,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		unique_ptr<int>& Symbols);
};