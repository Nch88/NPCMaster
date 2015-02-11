#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

MyTest mtest;

//TEST(setup, diddy)
//{
//	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unordered_map<unsigned int, Pair> dictionary;
//	unsigned int symbols(65);//A
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//
//	bool skip = false;
//
//	int priorityQueueSize;
//
//	//Setup sequence array
//	long a[] = { 'a', 'b', 'a', 'b', 'a', 'b' };
//	mtest.buildSequenceArray(sequenceArray, a, 4);
//
//	//Setup threading pointers
//	sequenceArray[0]->next = sequenceArray[2];
//	sequenceArray[2]->previous = sequenceArray[0];
//	sequenceArray[2]->next = sequenceArray[4];
//	sequenceArray[4]->previous = sequenceArray[2];
//	sequenceArray[1]->next = sequenceArray[3];
//	sequenceArray[3]->previous = sequenceArray[1];
//
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//	priorityQueue.resize(priorityQueueSize);
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//	algP.replaceAllPairs(7, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);
//
//	string expected = { 'a', 'b', 'a', 'b', 'a', 'b' };
//
//	string result = mtest.SequenceToCompleteString(sequenceArray);
//
//	ASSERT_EQ(expected, result);
//
//}
