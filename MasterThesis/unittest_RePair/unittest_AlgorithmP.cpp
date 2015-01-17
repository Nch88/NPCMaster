#include "gtest\gtest.h"
#include "RePair\stdafx.h"
#include <memory>

using namespace std;

//
//TEST(removeFromListInPriorityQueue, onlyInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//	
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	ASSERT_EQ(tmpPair, (*priorityQueue)[4]->pair);
//	ASSERT_FALSE((*priorityQueue)[4]->nextPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(4, tmpPairRecordAdjacent, priorityQueue);
//
//	ASSERT_FALSE((*priorityQueue)[4]);
//}
//
//TEST(removeFromListInPriorityQueue, firstInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "dy";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	ASSERT_EQ(tmpPair, (*priorityQueue)[1]->pair);
//	ASSERT_EQ("id", (*priorityQueue)[1]->nextPair->pair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(1, tmpPairRecordAdjacent, priorityQueue);
//
//	ASSERT_EQ("id", (*priorityQueue)[1]->pair);
//}
//
//TEST(removeFromListInPriorityQueue, lastInTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "dd";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->previousPair->nextPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count -1, tmpPairRecordAdjacent, priorityQueue);
//
//	ASSERT_FALSE(tmpPairRecordAdjacent->previousPair);
//}
//
//TEST(removeFromListInPriorityQueue, middleOfTheList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "id";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//	shared_ptr<PairRecord> tmpPairRecordAdjacentPrevious = tmpPairRecordAdjacent->previousPair;
//	shared_ptr<PairRecord> tmpPairRecordAdjacentNext = tmpPairRecordAdjacent->nextPair;
//
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->previousPair->nextPair);
//	ASSERT_EQ(tmpPairRecordAdjacent, tmpPairRecordAdjacent->nextPair->previousPair);
//
//	tmpPairRecordAdjacent->count--;
//
//	algP.removeFromListInPriorityQueue(tmpPairRecordAdjacent->count - 1, tmpPairRecordAdjacent, priorityQueue);
//
//	ASSERT_EQ(tmpPairRecordAdjacentPrevious->nextPair, tmpPairRecordAdjacentNext);
//	ASSERT_EQ(tmpPairRecordAdjacentNext->previousPair, tmpPairRecordAdjacentPrevious);
//}
//
//TEST(insertIntoListInPriorityQueue, insertIntoEmptyList)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	ASSERT_FALSE((*priorityQueue)[5]);
//
//	algP.insertIntoListInPriorityQueue(5, tmpPairRecordAdjacent, priorityQueue);
//
//	ASSERT_EQ(tmpPair, (*priorityQueue)[5]->pair);
//	ASSERT_FALSE((*priorityQueue)[5]->nextPair);	
//}
//
//TEST(establishContext, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	int sequenceIndex = 7;
//
//	ASSERT_EQ('.', (*sequenceArray)[sequenceIndex]->symbol);
//
//		algP.establishContext(
//		symbolLeft, 
//		symbolRight, 
//		symbolPrevious, 
//		symbolNext,  
//		sequenceArray, 
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
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "si";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	int sequenceIndex = 0;
//
//	ASSERT_EQ('s', (*sequenceArray)[sequenceIndex]->symbol);
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('s', symbolLeft->symbol);
//	ASSERT_EQ('i', symbolRight->symbol);
//	ASSERT_FALSE(symbolPrevious);
//	ASSERT_EQ('n', symbolNext->symbol);
//}
//
//TEST(decrementCount, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	int sequenceIndex = 7;
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ(6, tmpPairRecordAdjacent->count);
//	ASSERT_EQ(tmpPairRecordAdjacent, (*priorityQueue)[4]);
//
//	algP.decrementCount(
//		symbolLeft,
//		symbolRight,
//		activePairs,
//		priorityQueue,
//		tmpPairRecordAdjacent);
//
//	ASSERT_EQ(5, tmpPairRecordAdjacent->count);
//	ASSERT_FALSE((*priorityQueue)[4]);
//	ASSERT_EQ(tmpPairRecordAdjacent, (*priorityQueue)[3]);
//}
//
//TEST(replacePair, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	int sequenceIndex = 7;
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('.', symbolLeft->symbol);
//	ASSERT_EQ('d', symbolRight->symbol);
//	ASSERT_ANY_THROW((*dictionary).at('A'));
//
//	algP.replacePair(
//		symbolLeft,
//		symbolRight,
//		symbolNext,
//		Symbols,
//		dictionary,
//		activePairs);
//
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_EQ(symbolNext, symbolRight->next);
//	ASSERT_EQ(symbolLeft, symbolRight->previous);
//	ASSERT_EQ(tmpPair, (*dictionary)['A']);
//}
//
//TEST(replacePair, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "do";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	int sequenceIndex = 37;
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ('d', symbolLeft->symbol);
//	ASSERT_EQ('o', symbolRight->symbol);
//	ASSERT_ANY_THROW((*dictionary).at('A'));
//
//	algP.replacePair(
//		symbolLeft,
//		symbolRight,
//		symbolNext,
//		Symbols,
//		dictionary,
//		activePairs);
//
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_FALSE(symbolRight->next);
//	ASSERT_EQ(symbolLeft, symbolRight->previous);
//	ASSERT_EQ(tmpPair, (*dictionary)['A']);
//}
//
//TEST(replaceInstanceOfPair, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	bool firstPair = false;
//	bool lastPair = false;
//	int sequenceIndex = 7;
//	stringstream ss;
//	string s;
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	
//	ASSERT_EQ(1, (*activePairs)["g."]->count);	
//	ASSERT_EQ(2, (*activePairs)["do"]->count);
//	ASSERT_EQ(6, (*activePairs)[".d"]->count);
//	ASSERT_EQ('.', symbolLeft->symbol);
//	ASSERT_EQ('d', symbolRight->symbol);
//	ASSERT_ANY_THROW((*activePairs).at("gA"));
//	ASSERT_ANY_THROW((*activePairs).at("Ao"));
//
//	algP.replaceInstanceOfPair(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols,
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext);
//
//	ASSERT_EQ(5, (*activePairs)[".d"]->count);
//	ASSERT_ANY_THROW((*activePairs).at("g."));
//	ASSERT_EQ(1, (*activePairs)["do"]->count);
//	ASSERT_EQ('A', symbolLeft->symbol);
//	ASSERT_EQ('\0', symbolRight->symbol);
//	ASSERT_EQ(1, (*activePairs)["gA"]->count);
//	ASSERT_EQ(1, (*activePairs)["Ao"]->count);
//	ASSERT_EQ('\0', (*sequenceArray)[symbolRight->index]->symbol);
//	ASSERT_EQ('o', (*sequenceArray)[symbolRight->index]->next->symbol);
//	ASSERT_EQ('A', (*sequenceArray)[symbolRight->index]->previous->symbol);
//}
//
//TEST(replaceInstanceOfPair, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "do";
//
//	shared_ptr<PairRecord> tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//	auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//	auto symbolRight = make_shared<SymbolRecord>(); //b
//	auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//	auto symbolNext = make_shared<SymbolRecord>(); //y
//	bool firstPair = false;
//	bool lastPair = true;
//	int sequenceIndex = 37;
//	stringstream ss;
//	string s;
//
//	algP.establishContext(
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext,
//		sequenceArray,
//		sequenceIndex);
//
//	ASSERT_EQ(2, (*activePairs)["do"]->count);
//
//	algP.replaceInstanceOfPair(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols,
//		symbolLeft,
//		symbolRight,
//		symbolPrevious,
//		symbolNext);
//
//	ASSERT_EQ(1, (*activePairs)["do"]->count);
//}
//
//TEST(replaceAllPairs, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//
//
//	ASSERT_EQ(6, (*activePairs)[".d"]->count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_ANY_THROW((*activePairs).at(".d"));
//	
//}
//
//TEST(replaceAllPairs, startOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//
//	string tmpPair = "si";
//	int sequenceIndex = 0;
//
//
//	ASSERT_EQ(1, (*activePairs)["si"]->count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//	ASSERT_EQ(1, countNewSymbols);
//	ASSERT_ANY_THROW(activePairs->at("si"));
//
//}
//
//TEST(replaceAllPairs, endOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "do";
//	int sequenceIndex = 8;
//
//	ASSERT_EQ(39, sequenceArray->size());
//	ASSERT_EQ(2, (*activePairs)["do"]->count);
//
//	algP.replaceAllPairs(
//		sequenceIndex,
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols);
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW((*activePairs).at("do"));
//	ASSERT_EQ(2, countNewSymbols);
//
//}
//
//TEST(manageOneEntryOnList, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//	int i = 4;
//
//	algP.manageOneEntryOnList(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols,
//		i);
//
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW((*activePairs).at(".d"));
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_FALSE((*priorityQueue)[i]);
//
//}
//
//TEST(manageOneList, middleOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = ".d";
//	int sequenceIndex = 7;
//	int i = 4;
//
//	algP.manageOneList(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols,
//		i);
//
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW((*activePairs).at(".d"));
//	ASSERT_EQ(6, countNewSymbols);
//	ASSERT_FALSE((*priorityQueue)[i]);
//
//}
//
//TEST(manageOneList, startOfSequence)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//
//	string tmpPair = "si";
//	int sequenceIndex = 0;
//	int i = 0;
//
//	algP.manageOneList(
//		sequenceArray,
//		dictionary,
//		activePairs,
//		priorityQueue,
//		Symbols,
//		i);
//
//	int countNewSymbols = 0;
//
//	for (int i = 0; i < sequenceArray->size(); i++)
//	{
//		if ((*sequenceArray)[i]->symbol == 'A')
//			countNewSymbols++;
//	}
//
//
//	ASSERT_ANY_THROW((*activePairs).at("dd"));
//	ASSERT_EQ(3, countNewSymbols);
//	ASSERT_FALSE((*priorityQueue)[i]);
//
//}
//
//TEST(manageRun, everythingExplicit)
//{
//	Initializer init;
//	AlgorithmP algP;
//
//	auto dictionary = make_unique<unordered_map<char, string>>();
//	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
//	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
//	auto Symbols = make_unique<int>(65);
//
//	init.SequenceArray("diddy.txt", sequenceArray, activePairs);
//
//	int priorityQueueSize;
//
//	priorityQueueSize = sqrt(sequenceArray->size());
//
//	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
//
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
//	MyTest test;
//	int count = 0;
//
//	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
//	string diddy2 = "singingAo.wahAiddyAiddyAumAiddyAo";
//	string diddy3 = "singingAo.wahAiByAiByAumAiByAo";
//	string diddy4 = "singingAo.wahCByCByAumCByAo";
//
//	ASSERT_EQ(diddy1, test.SequenceToString(sequenceArray));
//
//	for (int i = priorityQueue->size() - 2; i >= 0; i--)
//	{
//		while ((*priorityQueue)[i])
//		{
//			auto tmpPairRecord = make_shared<PairRecord>();
//			int sequenceIndex;
//
//			tmpPairRecord = (*priorityQueue)[i];
//
//			if ((*Symbols) == 66)
//			{
//				int x = 0;
//			}
//			if ((*Symbols) == 67)
//			{
//				ASSERT_EQ("Ai", tmpPairRecord->pair);
//			}
//
//			sequenceIndex = tmpPairRecord->arrayIndexFirst;
//
//			//Remove current pair from priority queue
//			if (tmpPairRecord->nextPair)
//			{
//				(*priorityQueue)[i] = tmpPairRecord->nextPair;
//				(*priorityQueue)[i]->previousPair = NULL;
//				tmpPairRecord->previousPair = NULL;
//				tmpPairRecord->nextPair = NULL;
//			}
//			else
//			{
//				(*priorityQueue)[i] = NULL;
//			}
//
//			auto symbolLeft = make_shared<SymbolRecord>(); //Left symbol of the pair to be replaced, a
//			auto symbolRight = make_shared<SymbolRecord>(); //b
//			auto symbolPrevious = make_shared<SymbolRecord>(); //Symbol to the left of pair to be replaced, x
//			auto symbolNext = make_shared<SymbolRecord>(); //y
//
//			bool firstPair;
//			bool lastPair;
//			bool firstInstance = true;
//			bool running = true;
//			SymbolRecord symbolOld = *(*sequenceArray)[sequenceIndex];
//			//Test test;
//
//			do
//			{
//				//Step 1, Establish context of xaby
//
//				algP.establishContext(symbolLeft, symbolRight, symbolPrevious, symbolNext, sequenceArray, sequenceIndex);
//
//				if ((*Symbols) == 65 && count == 0)
//				{
//					ASSERT_EQ('g', symbolPrevious->symbol);
//					ASSERT_EQ('.', symbolLeft->symbol);
//					ASSERT_EQ('d', symbolRight->symbol);
//					ASSERT_EQ('o', symbolNext->symbol);
//				}
//
//				auto tmpPairRecord = make_shared<PairRecord>();
//				auto tmpPairRecordAdjacent = make_shared<PairRecord>();
//				char newSymbol;
//
//				stringstream ss;
//				string tmpPair;
//
//				
//
//				//Step 2, decrement counts of xa and by
//				if (symbolPrevious) //xa
//				{
//					ASSERT_NE('\0', symbolPrevious->symbol);
//					ASSERT_NE('\0', symbolLeft->symbol);
//					ss << symbolPrevious->symbol << symbolLeft->symbol;
//					ss >> tmpPair;
//					ss.clear();
//					tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//					if ((*Symbols) == 65 && count == 0)
//					{
//						ASSERT_EQ(1, tmpPairRecordAdjacent->count);
//					}
//					if (tmpPairRecordAdjacent)
//						algP.decrementCount(symbolPrevious, symbolLeft, activePairs, priorityQueue, tmpPairRecordAdjacent);
//
//					if ((*Symbols) == 66 && count == 2)
//					{
//						ASSERT_EQ("id", tmpPair);
//					}
//					if ((*Symbols) == 67 && count == 0)
//					{
//						ASSERT_ANY_THROW((*activePairs).at("hA"));
//					}
//				}
//
//				if (symbolNext) //by
//				{
//					ASSERT_NE('\0', symbolPrevious->symbol);
//					ASSERT_NE('\0', symbolLeft->symbol);
//					ss << symbolRight->symbol << symbolNext->symbol;
//					ss >> tmpPair;
//					ss.clear();
//					tmpPairRecordAdjacent = (*activePairs)[tmpPair];
//
//					if (tmpPairRecordAdjacent)
//						algP.decrementCount(symbolRight, symbolNext, activePairs, priorityQueue, tmpPairRecordAdjacent);
//
//					if ((*Symbols) == 66 && count == 2)
//					{
//						ASSERT_EQ("dy", tmpPair);
//					}
//					if ((*Symbols) == 67 && count == 0)
//					{
//						ASSERT_EQ(2, (*activePairs)["iB"]->count);
//					}
//				}
//
//				//Step 3, replace ab, leaving xAy
//				if ((*Symbols) == 67 && count == 2)
//				{
//					int x = 0;
//				}
//
//				if (symbolRight->symbol == '\0')
//				{
//					int x = 0;
//				}
//				algP.replacePair(symbolLeft, symbolRight, symbolNext, Symbols, dictionary, activePairs);
//
//				if ((*Symbols) == 66 && count == 2)
//				{
//					ASSERT_ANY_THROW((*activePairs).at("dd"));
//				}
//				if ((*Symbols) == 67 && count == 0)
//				{
//					ASSERT_EQ(2, (*activePairs)["Ai"]->count);
//				}
//
//				//Step 4, increase counts of xA and Ay
//				if (symbolPrevious) //xA
//				{
//					ASSERT_NE('\0', symbolPrevious->symbol);
//					ASSERT_NE('\0', symbolLeft->symbol);
//					ss << symbolPrevious->symbol << symbolLeft->symbol;
//					ss >> tmpPair;
//					ss.clear();
//
//					tmpPairRecord = (*activePairs)[tmpPair];
//					if (!tmpPairRecord)
//					{
//						(*activePairs)[tmpPair] = make_shared<PairRecord>();
//						tmpPairRecord = (*activePairs)[tmpPair];
//					}
//
//					algP.increaseCount(symbolPrevious, symbolLeft, tmpPairRecord, activePairs);
//
//					if (tmpPairRecord->count == 1) //New pair
//					{
//						algP.setupPairRecord(symbolPrevious, symbolLeft, tmpPairRecord);
//						algP.setupPairSequence(sequenceArray, tmpPairRecord);
//					}
//					else //Update link between  pair sequence
//					{
//						algP.updatePairSequence(symbolPrevious, sequenceArray, tmpPairRecord);
//						algP.updatePairRecord(symbolPrevious, tmpPairRecord);
//					}
//
//					if (tmpPairRecord->count == 2) //Insert into priority queue					
//					{
//						algP.insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
//					}
//					//Move up in priority queue
//					else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
//					{
//						algP.removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
//						algP.insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
//					}
//					if ((*Symbols) == 67 && count == 0)
//					{
//						ASSERT_EQ(1, (*activePairs)["hC"]->count);
//					}
//				}
//				if (symbolNext) //Ay
//				{			
//					ASSERT_NE('\0', symbolPrevious->symbol);
//					ASSERT_NE('\0', symbolLeft->symbol);
//					ss << symbolLeft->symbol << symbolNext->symbol;
//					ss >> tmpPair;
//					ss.clear();
//
//					tmpPairRecord = (*activePairs)[tmpPair];
//					if (!tmpPairRecord)
//					{
//						(*activePairs)[tmpPair] = make_shared<PairRecord>();
//						tmpPairRecord = (*activePairs)[tmpPair];
//					}
//
//					algP.increaseCount(symbolLeft, symbolNext, tmpPairRecord, activePairs);
//
//					if (tmpPairRecord->count == 1) //New pair
//					{
//						algP.setupPairRecord(symbolLeft, symbolNext, tmpPairRecord);
//						algP.setupPairSequence(sequenceArray, tmpPairRecord);
//					}
//					else //Update link between  pair sequence
//					{
//						algP.updatePairSequence(symbolLeft, sequenceArray, tmpPairRecord);
//						algP.updatePairRecord(symbolLeft, tmpPairRecord);
//					}
//
//					if (tmpPairRecord->count == 2) //Insert into priority queue	
//					{
//						algP.insertIntoListInPriorityQueue(0, tmpPairRecord, priorityQueue);
//					}
//
//					//Move up in priority queue
//					else if (tmpPairRecord->count > 2 && tmpPairRecord->count <= priorityQueue->size())
//					{
//						algP.removeFromListInPriorityQueue(tmpPairRecord->count - 3, tmpPairRecord, priorityQueue);
//						algP.insertIntoListInPriorityQueue(tmpPairRecord->count - 2, tmpPairRecord, priorityQueue);
//					}	
//					if ((*Symbols) == 67 && count == 0)
//					{
//						ASSERT_EQ(1, (*activePairs)["CB"]->count);
//					}
//				}
//
//				if ((*Symbols) == 67 && count == 2)
//				{
//					ASSERT_ANY_THROW((*activePairs).at("Ai"));
//				}
//				count++;
//				if (!symbolOld.next)
//					break;
//
//				sequenceIndex = (*symbolOld.next).index;
//				symbolOld = *(*sequenceArray)[sequenceIndex];
//
//
//			} while (running);
//
//			(*Symbols)++;
//
//			test.Dictionary("Dictionary", dictionary);
//			test.Sequence("Sequence", sequenceArray);
//			test.PriorityQueue("Priority queue", priorityQueue);
//			cout << "<------------- next round" << endl;
//
//			if (*Symbols == 66 + 1)
//			{
//				ASSERT_EQ("dd", (*dictionary)['B']);
//				ASSERT_EQ(diddy3, test.SequenceToString(sequenceArray));	
//				count = 0;
//			}
//			if (*Symbols == 67 + 1)
//			{
//				ASSERT_EQ("Ai", (*dictionary)['C']);
//				ASSERT_EQ(diddy4, test.SequenceToString(sequenceArray));
//				count = 0;
//			}
//		}
//		if (i == 4)
//		{
//			ASSERT_EQ(".d", (*dictionary)['A']);
//			ASSERT_EQ(diddy2, test.SequenceToString(sequenceArray));	
//			count = 0;
//		}
//	}
//}

TEST(manageRun, everything)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "diddy.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string diddy1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string diddy2 = "sHHG.wahEEAumEG";

	ASSERT_EQ(diddy1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(diddy2, test.SequenceToString(sequenceArray));
}

TEST(testDuplicates, evenNrOfSymbols)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicates.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aaaabbbb";
	string string2 = "AABB";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}

TEST(testDuplicates, evenNrOfSymbolsSplit)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicates3.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aabbbbaa";
	string string2 = "ABBA";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}

TEST(testDuplicates, unevenNrOFSymbols)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicates2.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aaaaabbbb";
	string string2 = "AAaBB";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}

TEST(testHighPriorityLists, withDuplicates1)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicatesLong.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbb";
	string string2 = "EEADD";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}

TEST(testHighPriorityLists, withDuplicates2)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicatesLong2.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbb";
	string string2 = "EEAaDD";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}

TEST(testHighPriorityLists, withDuplicates3)
{
	Initializer init;
	AlgorithmP algP;

	auto dictionary = make_unique<unordered_map<char, string>>();
	auto activePairs = make_unique<unordered_map<string, shared_ptr<PairRecord>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<int>(65);

	string input = "duplicatesLong3.txt";

	init.SequenceArray(input, sequenceArray, activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue);
	MyTest test;
	int count = 0;

	string string1 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbcccccccccccccccccccccccccccccccccc";
	string string2 = "HHAaGGIIB";

	ASSERT_EQ(string1, test.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols);

	ASSERT_EQ(string2, test.SequenceToString(sequenceArray));
}