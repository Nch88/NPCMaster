#include "stdafx.h"

using namespace std;

#pragma once
class AlgorithmP
{
public:
	AlgorithmP();
	~AlgorithmP();

	void removeFromListInPriorityQueue(PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue);
	void replaceAllPairs(
		int sequenceIndex,
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols);
	void replaceInstanceOfPair(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols,
		bool firstPair,
		bool lastPair,
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		SymbolRecord* symbolPrevious,
		SymbolRecord* symbolNext);
	void managePriorityQueueDecrement(PairRecord * tmpPairRecordAdjacent, vector<PairRecord*> * priorityQueue);
	void insertIntoListInPriorityQueue(int index, PairRecord * tmpPairRecord, vector<PairRecord*> * priorityQueue);
	void decrementCount(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		unordered_map<string,
		PairRecord> * activePairs,
		PairRecord * tmpPairRecordAdjacent,
		vector<PairRecord*> * priorityQueue);
	void replacePair(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		SymbolRecord* symbolNext,
		int * Symbols,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs);
	void increaseCount(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		PairRecord * tmpPairRecord,
		unordered_map<string, PairRecord> * activePairs);
	void setupPairRecord(
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		PairRecord * tmpPairRecord);
	void setupPairSequence(
		vector<SymbolRecord*> * sequenceArray,
		PairRecord * tmpPairRecord);
	void updatePairSequence(
		SymbolRecord* symbolLeft,
		vector<SymbolRecord*> * sequenceArray,
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
		vector<SymbolRecord*> * sequenceArray,
		int sequenceIndex);
	void manageHighPriorityList(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols);
	void AlgorithmP::manageOneEntryOnList(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols,
		int i);
	void manageOneList(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols,
		int i);
	void AlgorithmP::manageLowerPriorityLists(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols);
	void run(
		vector<SymbolRecord*> * sequenceArray,
		unordered_map<char, string> * dictionary,
		unordered_map<string, PairRecord> * activePairs,
		vector<PairRecord*> * priorityQueue,
		int * Symbols);
};