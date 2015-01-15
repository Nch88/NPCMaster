#include "gtest\gtest.h"
#include "RePair\stdafx.h"

using namespace std;

//
//TEST(removeFromListInPriorityQueue, onlyInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	ASSERT_EQ(tmpPair, priorityQueue[4]->pair);
//	ASSERT_EQ(NULL, priorityQueue[4]->nextPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, &priorityQueue);
//
//	ASSERT_EQ(NULL, priorityQueue[4]);
//}
//
//TEST(removeFromListInPriorityQueue, firstInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "dy";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	ASSERT_EQ(tmpPair, priorityQueue[1]->pair);
//	ASSERT_EQ("id", priorityQueue[1]->nextPair->pair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, &priorityQueue);
//
//	ASSERT_EQ("id", priorityQueue[1]->pair);
//}
//
//TEST(removeFromListInPriorityQueue, lastInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "dd";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->previousPair->nextPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, &priorityQueue);
//
//	ASSERT_EQ(NULL, tmpPairRecordAdjacent->previousPair->nextPair);
//}
//
//TEST(removeFromListInPriorityQueue, middleOfTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "id";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->previousPair->nextPair);
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->nextPair->previousPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, &priorityQueue);
//
//	ASSERT_EQ(tmpPairRecordAdjacent->nextPair, tmpPairRecordAdjacent->previousPair->nextPair);
//	ASSERT_EQ(tmpPairRecordAdjacent->previousPair, tmpPairRecordAdjacent->nextPair->previousPair);
//}
//
//TEST(insertIntoListInPriorityQueue, insertIntoEmptyList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	ASSERT_EQ(NULL, priorityQueue[5]);
//
//	algP.insertIntoListInPriorityQueue(5, tmpPairRecordAdjacent, &priorityQueue);
//
//	ASSERT_EQ(tmpPair, priorityQueue[5]->pair);
//	ASSERT_EQ(NULL, priorityQueue[5]->nextPair);	
//}
//
//TEST(establishContext, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = false;
//	int sequenceIndex = 7;
//
//	ASSERT_EQ('.', sequenceArray[sequenceIndex]->symbol);
//
//		algP.establishContext(
//		&symbolLeft, 
//		&symbolRight, 
//		&symbolPrevious, 
//		&symbolNext, 
//		firstPair, 
//		lastPair, 
//		&sequenceArray, 
//		sequenceIndex);
//
//		ASSERT_EQ('.', symbolLeft->symbol);
//		ASSERT_EQ('d', symbolRight->symbol);
//		ASSERT_EQ('g', symbolPrevious->symbol);
//		ASSERT_EQ('o', symbolNext->symbol);
//}
//
//TEST(establishContext, firstPair)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = true;
//	bool lastPair = false;
//	int sequenceIndex = 0;
//
//	ASSERT_EQ('s', sequenceArray[sequenceIndex]->symbol);
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('s', symbolLeft->symbol);
//	ASSERT_EQ('i', symbolRight->symbol);
//	ASSERT_EQ(NULL, symbolPrevious);
//	ASSERT_EQ('n', symbolNext->symbol);
//}
//
//TEST(decrementCount, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = false;
//	int sequenceIndex = 7;
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ(6, tmpPairRecordAdjacent->count);
//	ASSERT_EQ(tmpPairRecordAdjacent, priorityQueue[4]);
//
//	algP.decrementCount(
//		symbolLeft,
//		symbolRight,
//		&activePairs,
//		tmpPairRecordAdjacent,
//		&priorityQueue);
//
//	ASSERT_EQ(5, tmpPairRecordAdjacent->count);
//	ASSERT_EQ(NULL, priorityQueue[4]);
//	ASSERT_EQ(tmpPairRecordAdjacent, priorityQueue[3]);
//}
//
//TEST(replacePair, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = false;
//	int sequenceIndex = 7;
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('.', symbolLeft->symbol);
//	ASSERT_EQ('d', symbolRight->symbol);
//	ASSERT_ANY_THROW(dictionary.at('A'));
//
//	algP.replacePair(
//		symbolLeft,
//		symbolRight,
//		symbolNext,
//		&Symbols,
//		&dictionary,
//		&activePairs);
//
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_EQ(symbolNext, symbolRight->next);
//	ASSERT_EQ(symbolLeft, symbolRight->previous);
//	ASSERT_EQ(tmpPair, dictionary['A']);
//}
//
//TEST(replacePair, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "do";
//
//	PairRecord * tmpPairRecordAdjacent = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = true;
//	int sequenceIndex = 37;
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('d', symbolLeft->symbol);
//	ASSERT_EQ('o', symbolRight->symbol);
//	ASSERT_ANY_THROW(dictionary.at('A'));
//
//	algP.replacePair(
//		symbolLeft,
//		symbolRight,
//		symbolNext,
//		&Symbols,
//		&dictionary,
//		&activePairs);
//
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_EQ(NULL, symbolRight->next);
//	ASSERT_EQ(symbolLeft, symbolRight->previous);
//	ASSERT_EQ(tmpPair, dictionary['A']);
//}
//
//TEST(replaceInstanceOfPair, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//
//	PairRecord * tmpPairRecord = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = false;
//	int sequenceIndex = 7;
//	stringstream ss;
//	string s;
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	
//	ASSERT_EQ(1, activePairs["g."].count);	
//	ASSERT_EQ(2, activePairs["do"].count);
//	ASSERT_EQ(6, activePairs[".d"].count);
//	ASSERT_EQ('.', symbolLeft->symbol);
//	ASSERT_EQ('d', symbolRight->symbol);
//	ASSERT_ANY_THROW(activePairs.at("gA"));
//	ASSERT_ANY_THROW(activePairs.at("Ao"));
//
//	algP.replaceInstanceOfPair(
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols,
//		firstPair,
//		lastPair,
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext);
//
//	ASSERT_EQ(5, activePairs[".d"].count);
//	ASSERT_ANY_THROW(activePairs.at("g."));	
//	ASSERT_EQ(1, activePairs["do"].count);
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_EQ(1, activePairs["gA"].count);
//	ASSERT_EQ(1, activePairs["Ao"].count);
//	ASSERT_EQ('\0', sequenceArray[symbolRight->index]->symbol);
//	ASSERT_EQ('o', sequenceArray[symbolRight->index]->next->symbol);
//	ASSERT_EQ('A', sequenceArray[symbolRight->index]->previous->symbol);
//}
//
//TEST(replaceInstanceOfPair, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "do";
//
//	PairRecord * tmpPairRecord = &activePairs[tmpPair];
//
//	SymbolRecord* symbolLeft = NULL; //Left symbol of the pair to be replaced, a
//	SymbolRecord* symbolRight = NULL; //b
//	SymbolRecord* symbolPrevious = NULL; //Symbol to the left of pair to be replaced, x
//	SymbolRecord* symbolNext = NULL; //y
//	bool firstPair = false;
//	bool lastPair = true;
//	int sequenceIndex = 37;
//	stringstream ss;
//	string s;
//
//	algP.establishContext(
//		&symbolLeft,
//		&symbolRight,
//		&symbolPrevious,
//		&symbolNext,
//		firstPair,
//		lastPair,
//		&sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ(2, activePairs["do"].count);
//
//	algP.replaceInstanceOfPair(
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols,
//		firstPair,
//		lastPair,
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext);
//
//	ASSERT_EQ(1, activePairs["do"].count);
//}
//
//TEST(replaceAllPairs, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//
//
//	ASSERT_EQ(6, activePairs[".d"].count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray.size(); i++)
//	{
//		if (sequenceArray[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_ANY_THROW(activePairs.at(".d"));
//	
//}
//
//TEST(replaceAllPairs, startOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "si";
//	int sequenceIndex = 0;
//
//
//	ASSERT_EQ(1, activePairs["si"].count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray.size(); i++)
//	{
//		if (sequenceArray[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//	ASSERT_EQ(1, countNewSymbols);
//	ASSERT_ANY_THROW(activePairs.at("si"));
//
//}
//
//TEST(replaceAllPairs, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = "do";
//	int sequenceIndex = 8;
//
//	ASSERT_EQ(39, sequenceArray.size());
//	ASSERT_EQ(2, activePairs["do"].count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray.size(); i++)
//	{
//		if (sequenceArray[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//	ASSERT_EQ(2, countNewSymbols);
//	//ASSERT_ANY_THROW(activePairs.at("do"));
//}
//
//TEST(manageOneEntryOnList, onlyEntry)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//	int i = 4;
//
//	algP.manageOneEntryOnList(
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols,
//		i);
//
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray.size(); i++)
//	{
//		if (sequenceArray[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW(activePairs.at(".d"));
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_EQ(NULL, priorityQueue[i]);
//
//}
//
//TEST(manageOneList, onlyEntry)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	unordered_map<char, string> dictionary;
//	unordered_map<string, PairRecord> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	int Symbols = 65;
//
//	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//
//	vector<PairRecord*> priorityQueue(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//	int i = 4;
//
//	algP.manageOneList(
//		&sequenceArray,
//		&dictionary,
//		&activePairs,
//		&priorityQueue,
//		&Symbols,
//		i);
//
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray.size(); i++)
//	{
//		if (sequenceArray[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW(activePairs.at(".d"));
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_EQ(NULL, priorityQueue[i]);
//
//}
//
TEST(manageOneList, multipleEntries)
{
	Initializer init;
	AlgorithmP algP;

	unordered_map<char, string> dictionary;
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;
	int Symbols = 65;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);

	int i = 1;

	algP.manageOneList(
		&sequenceArray,
		&dictionary,
		&activePairs,
		&priorityQueue,
		&Symbols,
		i);

	int countNewSymbols = 0;

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i]->symbol == 'A')
			countNewSymbols++;
	}

	ASSERT_EQ(3, countNewSymbols);
	ASSERT_EQ(NULL, priorityQueue[i]);

}