#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

MyTest mytest;

TEST(establishContext, adjacentSymbolsPreviousAndNext)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 1;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(1, indexSymbolLeft);
	ASSERT_EQ(2, indexSymbolRight);
	ASSERT_EQ(3, indexSymbolNext);
}

TEST(establishContext, adjacentSymbolsNoPrevious)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 0;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(-1, indexSymbolPrevious);
	ASSERT_EQ(0, indexSymbolLeft);
	ASSERT_EQ(1, indexSymbolRight);
	ASSERT_EQ(2, indexSymbolNext);
}

TEST(establishContext, adjacentSymbolsNoNext)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 2;
	index = 1;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 3;
	index = 2;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 4;
	index = 3;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(1, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(3, indexSymbolRight);
	ASSERT_EQ(-1, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbols)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 2;
	index = 2;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 3;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 3;
	index = 4;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 5;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 4;
	index = 6;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = right;
	empty2->previous = left;
	empty3->next = next;
	empty3->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(4, indexSymbolRight);
	ASSERT_EQ(6, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbolsLargeGap)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 2;
	index = 2;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 3;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 0;
	index = 4;
	SymbolRecord * emptyExtra1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra1);

	symbol = 0;
	index = 5;
	SymbolRecord * emptyExtra2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra2);

	symbol = 0;
	index = 6;
	SymbolRecord * emptyExtra3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra3);

	symbol = 0;
	index = 7;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 3;
	index = 8;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 9;
	SymbolRecord * empty4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty4);

	symbol = 4;
	index = 10;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = right;
	empty2->previous = left;
	empty3->next = right;
	empty3->previous = left;
	empty4->next = next;
	empty4->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(2, indexSymbolLeft);
	ASSERT_EQ(8, indexSymbolRight);
	ASSERT_EQ(10, indexSymbolNext);
}

TEST(establishContext, notAdjacentSymbolsLargeGaps)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 6;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * previous = new SymbolRecord(symbol, index);
	sequenceArray.push_back(previous);

	symbol = 0;
	index = 1;
	SymbolRecord * empty1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty1);

	symbol = 0;
	index = 2;
	SymbolRecord * emptyExtra1 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra1);

	symbol = 0;
	index = 3;
	SymbolRecord * emptyExtra2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra2);

	symbol = 0;
	index = 4;
	SymbolRecord * emptyExtra3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra3);

	symbol = 0;
	index = 5;
	SymbolRecord * empty2 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty2);

	symbol = 2;
	index = 6;
	SymbolRecord * left = new SymbolRecord(symbol, index);
	sequenceArray.push_back(left);

	symbol = 0;
	index = 7;
	SymbolRecord * empty3 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty3);

	symbol = 0;
	index = 8;
	SymbolRecord * emptyExtra4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra4);

	symbol = 0;
	index = 9;
	SymbolRecord * emptyExtra5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra5);

	symbol = 0;
	index = 10;
	SymbolRecord * emptyExtra6 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra6);

	symbol = 0;
	index = 11;
	SymbolRecord * empty4 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty4);

	symbol = 3;
	index = 12;
	SymbolRecord * right = new SymbolRecord(symbol, index);
	sequenceArray.push_back(right);

	symbol = 0;
	index = 13;
	SymbolRecord * empty5 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty5);

	symbol = 0;
	index = 14;
	SymbolRecord * emptyExtra7 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra7);

	symbol = 0;
	index = 15;
	SymbolRecord * emptyExtra8 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra8);

	symbol = 0;
	index = 16;
	SymbolRecord * emptyExtra9 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(emptyExtra9);

	symbol = 0;
	index = 17;
	SymbolRecord * empty6 = new SymbolRecord(symbol, index);
	sequenceArray.push_back(empty6);

	symbol = 4;
	index = 18;
	SymbolRecord * next = new SymbolRecord(symbol, index);
	sequenceArray.push_back(next);

	//Thread empty symbols
	empty1->next = left;
	empty1->previous = previous;
	empty2->next = left;
	empty2->previous = previous;

	empty3->next = right;
	empty3->previous = left;
	empty4->next = right;
	empty4->previous = left;

	empty5->next = next;
	empty5->previous = right;
	empty6->next = next;
	empty6->previous = right;

	algP.establishContext(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceIndex,
		sequenceArray);

	ASSERT_EQ(0, indexSymbolPrevious);
	ASSERT_EQ(6, indexSymbolLeft);
	ASSERT_EQ(12, indexSymbolRight);
	ASSERT_EQ(18, indexSymbolNext);
}

TEST(removeSymbolThreadingPointers, bothPreviousAndNextPointers)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 6;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 2;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(removeSymbolThreadingPointers, onlyPreviousPointer)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 6;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 4;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(scdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, scdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->next);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(removeSymbolThreadingPointers, onlyNextPointer)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 6;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	indexSymbolLeft = 0;
	algP.removeSymbolThreadingPointers(indexSymbolLeft, sequenceArray);

	ASSERT_EQ(nullptr, fstPairLeft->next);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(scdPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, trdPairLeft->next);
	ASSERT_EQ(trdPairLeft, scdPairLeft->next);
}

TEST(updatePairRecord, countMoreThanTwoMiddlePair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;
	
	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;

	
	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = 
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		scdPairLeft->index,
		scdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countMoreThanTwoFirstPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		fstPairLeft->index,
		fstPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countMoreThanTwoLastPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[trdPairLeft->symbol][trdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		trdPairLeft->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
}

TEST(updatePairRecord, countTwoFirstPair)
{
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);
	
	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 2;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);

	algP.updatePairRecord(
		fstPairLeft->index,
		fstPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(nullptr, tracker);
	ASSERT_EQ(nullptr, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord);
}

TEST(removeFromPriorityQueueList, middleOfList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair2->count = 3;

	tracker->pairRecord = pair2;

	algP.removeFromPriorityQueueList(index, tracker, priorityQueue);

	ASSERT_EQ(pair3, pair1->nextPair);
	ASSERT_EQ(pair1, pair3->previousPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(nullptr, pair2->nextPair);
}

TEST(removeFromPriorityQueueList, firstInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair1;

	algP.removeFromPriorityQueueList(index, tracker, priorityQueue);

	ASSERT_EQ(nullptr, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(pair2, pair3->previousPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(pair3, pair2->nextPair);
	ASSERT_EQ(pair2, priorityQueue[index]);
}

TEST(removeFromPriorityQueueList, lastInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();
	PairRecord * pair3 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = pair2;
	pair1->previousPair = nullptr;
	pair2->nextPair = pair3;
	pair2->previousPair = pair1;
	pair3->previousPair = pair2;
	pair3->nextPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair3;

	algP.removeFromPriorityQueueList(index, tracker, priorityQueue);

	ASSERT_EQ(pair2, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(nullptr, pair3->previousPair);
	ASSERT_EQ(pair1, pair2->previousPair);
	ASSERT_EQ(nullptr, pair2->nextPair);
	ASSERT_EQ(pair1, priorityQueue[index]);
}

TEST(addToPriorityQueueList, emptyList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = nullptr;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair1;

	algP.addToPriorityQueueList(index, tracker, priorityQueue);

	ASSERT_EQ(nullptr, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(pair1, priorityQueue[index]);
}

TEST(addToPriorityQueueList, somethingInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair2->count = 3;

	tracker->pairRecord = pair2;

	algP.addToPriorityQueueList(index, tracker, priorityQueue);

	ASSERT_EQ(nullptr, pair1->nextPair);
	ASSERT_EQ(pair2, pair1->previousPair);
	ASSERT_EQ(pair1, pair2->nextPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(pair2, priorityQueue[index]);
}

TEST(addToPriorityQueueList, largeFrequency)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair2->count = 7;

	tracker->pairRecord = pair2;

	algP.addToPriorityQueueList(5, tracker, priorityQueue);

	ASSERT_EQ(nullptr, pair1->nextPair);
	ASSERT_EQ(nullptr, pair1->previousPair);
	ASSERT_EQ(nullptr, pair2->nextPair);
	ASSERT_EQ(nullptr, pair2->previousPair);
	ASSERT_EQ(pair2, priorityQueue[2]);
	ASSERT_EQ(pair1, priorityQueue[1]);
}

TEST(incrementCountLeft, firstTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long previous = 0, left = 1;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100};
	mytest.buildSequenceArray(sequenceArray, a, 4);

	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that new pair was counted
	ASSERT_TRUE(activePairs[99][65].seenOnce);

	//Check that no pair record was added
	ASSERT_EQ(NULL, activePairs[99][65].pairRecord);

	//Check that index of first occurrence is set
	ASSERT_TRUE(activePairs[99][65].indexFirst = 1);
}

TEST(incrementCountRight, firstTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long left = 1, next = 3;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 4);

	algo.incrementCountRight(left, next, activePairs, sequenceArray, priorityQueue, symbols, c);

	//Check that new pair was counted
	ASSERT_TRUE(activePairs[65][100].seenOnce);

	//Check that no pair record was added
	ASSERT_EQ(NULL, activePairs[65][100].pairRecord);

	//Check that index of first occurrence is set
	ASSERT_TRUE(activePairs[65][100].indexFirst = 1);
}

TEST(incrementCountLeft, secondTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long previous = 3, left = 4;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 99, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 7);

	activePairs[99][65].seenOnce = true;
	activePairs[99][65].indexFirst = 0;

	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[99][65].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[99][65].pairRecord);

	//Check that index of first occurrence is not reset
	ASSERT_TRUE(activePairs[99][65].indexFirst = 1);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[0]->next == sequenceArray[3]);
	ASSERT_TRUE(sequenceArray[3]->previous == sequenceArray[0]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0]->count == 2);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 0);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexLast == 3);
}

TEST(incrementCountRight, secondTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long left = 4, next = 6;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 7);

	activePairs[65][100].seenOnce = true;
	activePairs[65][100].indexFirst = 1;

	algo.incrementCountRight(left, next, activePairs, sequenceArray, priorityQueue, symbols, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[65][100].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[65][100].pairRecord);

	//Check that index of first occurrence is not reset
	ASSERT_TRUE(activePairs[65][100].indexFirst = 1);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[1]->next == sequenceArray[4]);
	ASSERT_TRUE(sequenceArray[4]->previous == sequenceArray[1]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0]->count == 2);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 1);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexLast == 4);
}

TEST(incrementCountLeft, thirdTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long previous = 6, left = 7;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 99, 65, 0, 99, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 10);
	  
	activePairs[99][65].seenOnce = false;
	activePairs[99][65].indexFirst = 0;
	activePairs[99][65].pairRecord = new PairRecord(0, 3);
	activePairs[99][65].pairRecord->count = 2;

	PairTracker* tracker = &activePairs[99][65];
	algo.addToPriorityQueueList(0, tracker, priorityQueue);

	sequenceArray[0]->next = sequenceArray[3];
	sequenceArray[3]->previous = sequenceArray[0];

	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[99][65].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[99][65].pairRecord);

	//Check that index of first occurrence is not reset
	ASSERT_TRUE(activePairs[99][65].indexFirst = 1);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[3]->next == sequenceArray[6]);
	ASSERT_TRUE(sequenceArray[6]->previous == sequenceArray[3]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0] == nullptr);

	ASSERT_TRUE(priorityQueue[1]->count == 3);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexFirst == 0);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexLast == 6);
}

TEST(incrementCountRight, thirdTimeSeen)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	long left = 7, next = 9;
	bool skip = false;

	long a[] = { 99, 65, 0, 100, 65, 0, 100, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 10);

	activePairs[65][100].seenOnce = false;
	activePairs[65][100].indexFirst = 0;
	activePairs[65][100].pairRecord = new PairRecord(1, 4);
	activePairs[65][100].pairRecord->count = 2;

	PairTracker* tracker = &activePairs[65][100];
	algo.addToPriorityQueueList(0, tracker, priorityQueue);

	sequenceArray[1]->next = sequenceArray[4];
	sequenceArray[4]->previous = sequenceArray[1];

	algo.incrementCountRight(left, next, activePairs, sequenceArray, priorityQueue, symbols, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[65][100].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[65][100].pairRecord);

	//Check that index of first occurrence is not reset
	ASSERT_TRUE(activePairs[65][100].indexFirst = 1);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[4]->next == sequenceArray[7]);
	ASSERT_TRUE(sequenceArray[7]->previous == sequenceArray[4]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0] == nullptr);

	ASSERT_TRUE(priorityQueue[1]->count == 3);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexFirst == 1);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexLast == 7);
}

TEST(incrementCountLeft, skipTest)
{
	AlgorithmP algo;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(5);
	unordered_map<long, Pair> dictionary;
	long symbols = 65;
	Conditions c;

	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 65, 0, 65, 0, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 10);

	long previous = 0, left = 1;
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	ASSERT_FALSE(skip);
	previous = 1; left = 3;
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	ASSERT_TRUE(skip);
	previous = 3; left = 5;
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	ASSERT_FALSE(skip);
	previous = 5; left = 7;
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	ASSERT_TRUE(skip);
	previous = 7; left = 9;
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that seenOnce was set for cA
	ASSERT_TRUE(activePairs[99][65].seenOnce);

	//Check that a pair record was added for AA
	ASSERT_FALSE(activePairs[65][65].seenOnce);
	ASSERT_TRUE(NULL != activePairs[65][65].pairRecord);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[1]->next == sequenceArray[5]);
	ASSERT_TRUE(sequenceArray[3]->next == NULL);
	ASSERT_TRUE(sequenceArray[5]->previous == sequenceArray[1]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0]->count == 2);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 1);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexLast == 5);
}

TEST(moveDownInPriorityQueue, middleOfList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 1;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair1->count = 3;

	tracker->pairRecord = pair1;

	algP.moveDownInPriorityQueue(tracker, priorityQueue);

	ASSERT_EQ(pair1, priorityQueue[index - 1]);
	ASSERT_EQ(nullptr, priorityQueue[index]);
}

TEST(moveDownInPriorityQueue, firstInList)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 0;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair1->count = 2;

	tracker->pairRecord = pair1;

	algP.moveDownInPriorityQueue(tracker, priorityQueue);

	ASSERT_EQ(nullptr, priorityQueue[index]);
}

TEST(moveDownInPriorityQueue, lastInListLargeFrequency)
{
	AlgorithmP algP;
	vector<PairRecord*> priorityQueue(3);
	int index = 2;

	PairTracker * tracker = new PairTracker();

	PairRecord * pair1 = new PairRecord();
	PairRecord * pair2 = new PairRecord();

	priorityQueue[index] = pair1;
	pair1->nextPair = nullptr;
	pair1->previousPair = nullptr;
	pair2->nextPair = nullptr;
	pair2->previousPair = nullptr;

	pair1->count = 6;

	tracker->pairRecord = pair1;

	algP.moveDownInPriorityQueue(tracker, priorityQueue);

	ASSERT_EQ(pair1, priorityQueue[index]);
	ASSERT_EQ(nullptr, priorityQueue[index - 1]);
	ASSERT_EQ(nullptr, priorityQueue[index - 2]);
}

TEST(decrementCount, threePairsRemoveMiddle)
{
	AlgorithmP algP;
	Conditions c;
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolLeft = scdPairLeft->index;
	indexSymbolRight = scdPairRight->index;

	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[1]);
	ASSERT_EQ(nullptr, priorityQueue[0]);

	algP.decrementCount(
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		tracker,
		c);


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountLeft, hasPrevious)
{
	AlgorithmP algP;
	Conditions c;
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolPrevious = scdPairLeft->index;
	indexSymbolLeft = scdPairRight->index;
	indexSymbolRight = trdPairLeft->index;


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[1]);
	ASSERT_EQ(nullptr, priorityQueue[0]);

	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountLeft, hasPreviousNotActivePair)
{
	AlgorithmP algP;
	Conditions c;
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = trdPairLeft;
	scdPairLeft->previous = nullptr;
	scdPairLeft->next = nullptr;
	trdPairLeft->previous = fstPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 2;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolPrevious = scdPairLeft->index;
	indexSymbolLeft = scdPairRight->index;
	indexSymbolRight = trdPairLeft->index;


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);

	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountRight, hasNext)
{
	AlgorithmP algP;
	Conditions c;
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;


	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2, sequenceIndex + 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolRight = scdPairLeft->index;
	indexSymbolNext = scdPairRight->index;

	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[1]);
	ASSERT_EQ(nullptr, priorityQueue[0]);

	algP.decrementCountLeft(
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(4, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexLast);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}


TEST(threadEmptySymbols, singleEmptySymbol)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 0;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	algP.threadEmptySymbols(
		scdPairLeft,
		scdPairRight,
		trdPairLeft,
		sequenceArray);

	ASSERT_EQ(scdPairLeft, scdPairRight->previous);
	ASSERT_EQ(trdPairLeft, scdPairRight->next);
}

TEST(threadEmptySymbols, sequenceOfEmptySymbols)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 0;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 0;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 0;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 0;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	algP.threadEmptySymbols(
		fstPairLeft,
		scdPairLeft,
		trdPairRight,
		sequenceArray);

	ASSERT_EQ(fstPairLeft, fstPairRight->previous);
	ASSERT_EQ(trdPairRight, fstPairRight->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(trdPairRight, trdPairLeft->next);
}

TEST(replacePair, middleOfSequence)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	long symbols(256);
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	Pair pair(scdPairLeft->symbol,
		scdPairRight->symbol, 
		0);

	PairRecord * pairRecord = activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord->count = 2;

	algP.replacePair(
		scdPairLeft->index,
		scdPairRight->index,
		trdPairLeft->index,
		activePairs,
		sequenceArray,
		dictionary,
		symbols,
		c);



	ASSERT_EQ(symbols, scdPairLeft->symbol);
	ASSERT_EQ(0, scdPairRight->symbol);
	ASSERT_EQ(scdPairLeft, scdPairRight->previous);
	ASSERT_EQ(trdPairLeft, scdPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
}

TEST(replacePair, endOfSequence)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	long symbols(256);
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	Pair pair(trdPairLeft->symbol,
		trdPairRight->symbol,
		0);

	long noNext = -1;

	PairRecord * pairRecord = activePairs[trdPairLeft->symbol][trdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord->count = 2;

	algP.replacePair(
		trdPairLeft->index,
		trdPairRight->index,
		noNext,
		activePairs,
		sequenceArray,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, trdPairLeft->symbol);
	ASSERT_EQ(0, trdPairRight->symbol);
	ASSERT_EQ(trdPairLeft, trdPairRight->previous);
	ASSERT_EQ(nullptr, scdPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
}

TEST(replacePair, severalEmptySymbols)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	long symbols(256);
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 0;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 0;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 0;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	Pair pair(fstPairLeft->symbol,
		trdPairLeft->symbol,
		0);

	PairRecord * pairRecord = activePairs[fstPairLeft->symbol][trdPairLeft->symbol].pairRecord = new PairRecord();
	pairRecord->count = 2;

	algP.replacePair(
		fstPairLeft->index,
		trdPairLeft->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, fstPairLeft->symbol);
	ASSERT_EQ(0, trdPairLeft->symbol);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(trdPairRight, trdPairLeft->next);
	ASSERT_EQ(fstPairLeft, fstPairRight->previous);
	ASSERT_EQ(trdPairRight, fstPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
}

TEST(replacePair, emptySymbolsAroundRightSymbol)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	long symbols(256);
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 0;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 0;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 0;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	Pair pair(fstPairLeft->symbol,
		scdPairRight->symbol,
		0);

	PairRecord * pairRecord = activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord->count = 2;

	algP.replacePair(
		fstPairLeft->index,
		scdPairRight->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, fstPairLeft->symbol);
	ASSERT_EQ(0, scdPairRight->symbol);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(trdPairRight, trdPairLeft->next);
	ASSERT_EQ(fstPairLeft, fstPairRight->previous);
	ASSERT_EQ(trdPairRight, fstPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
}

TEST(replacePair, deletingPairRecord)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	long symbols(256);
	long symbol;
	long index;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 0;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 0;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 0;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	Pair pair(fstPairLeft->symbol,
		scdPairRight->symbol,
		0);

	PairRecord * pairRecord = activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord->count = 1;

	algP.replacePair(
		fstPairLeft->index,
		scdPairRight->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		dictionary,
		symbols,
		c);

	ASSERT_EQ(symbols, fstPairLeft->symbol);
	ASSERT_EQ(0, scdPairRight->symbol);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(trdPairRight, trdPairLeft->next);
	ASSERT_EQ(fstPairLeft, fstPairRight->previous);
	ASSERT_EQ(trdPairRight, fstPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
	ASSERT_EQ(nullptr, activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord);
}

TEST(replaceInstanceOfPairOnlyDecrementAndReplace, leftAndRightLowCount)
{
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	unordered_map<long, Pair> dictionary;
	vector<PairRecord*> priorityQueue;
	long symbols(256);
	long symbol;
	long index;

	bool skip = false;

	//Setup symbol records in sequence array
	symbol = 1;
	index = 0;
	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairLeft);

	symbol = 2;
	index = 1;
	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(fstPairRight);

	symbol = 1;
	index = 2;
	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairLeft);

	symbol = 2;
	index = 3;
	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(scdPairRight);

	symbol = 1;
	index = 4;
	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairLeft);

	symbol = 2;
	index = 5;
	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
	sequenceArray.push_back(trdPairRight);

	fstPairLeft->previous = nullptr;
	fstPairLeft->next = scdPairLeft;
	scdPairLeft->previous = fstPairLeft;
	scdPairLeft->next = trdPairLeft;
	trdPairLeft->previous = scdPairLeft;
	trdPairLeft->next = nullptr;

	fstPairRight->previous = nullptr;
	fstPairRight->next = scdPairRight;
	scdPairRight->previous = fstPairRight;
	scdPairRight->next = nullptr;

	Pair pair(scdPairLeft->symbol,
		scdPairRight->symbol,
		0);

	priorityQueue.resize(sqrt(sequenceArray.size()));

	//Setup pair record for pair 12
	PairRecord * pairRecord1 = activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord1->count = 3;
	pairRecord1->arrayIndexFirst = 0;
	pairRecord1->arrayIndexLast = 4;

	//Setup pair record for pair 21
	PairRecord * pairRecord2 = activePairs[scdPairRight->symbol][trdPairLeft->symbol].pairRecord = new PairRecord();
	pairRecord2->count = 2;
	pairRecord2->arrayIndexFirst = 1;
	pairRecord2->arrayIndexLast = 3;
	priorityQueue[0] = pairRecord2;

	algP.replaceInstanceOfPair(
		scdPairLeft->index,
		scdPairRight->index,
		fstPairRight->index,
		trdPairLeft->index,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		skip,
		c);

	ASSERT_EQ(symbols, scdPairLeft->symbol);
	ASSERT_EQ(0, scdPairRight->symbol);
	ASSERT_EQ(scdPairLeft, scdPairRight->previous);
	ASSERT_EQ(trdPairLeft, scdPairRight->next);
	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
	ASSERT_EQ(nullptr, activePairs[2][1].pairRecord);
	ASSERT_EQ(2, activePairs[1][2].pairRecord->count);
	ASSERT_EQ(nullptr, priorityQueue[0]);
}

TEST(replaceInstanceOfPairOnlyDecrementAndReplace, diddy)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(256);

	Initializer init;
	Conditions c;
	AlgorithmP algP;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	long indexSymbolLeft = 20;
	long indexSymbolRight = 21;
	long indexSymbolPrevious = 19;
	long indexSymbolNext = 22;

	PairRecord * currentPair = activePairs[sequenceArray[indexSymbolLeft]->symbol]
		[sequenceArray[indexSymbolRight]->symbol].pairRecord;
	PairRecord * leftPair = activePairs[sequenceArray[indexSymbolPrevious]->symbol]
		[sequenceArray[indexSymbolLeft]->symbol].pairRecord;
	PairRecord * rightPair = activePairs[sequenceArray[indexSymbolRight]->symbol]
		[sequenceArray[indexSymbolNext]->symbol].pairRecord;

	ASSERT_EQ(46, sequenceArray[indexSymbolLeft]->symbol);
	ASSERT_EQ(100, sequenceArray[indexSymbolRight]->symbol);
	ASSERT_EQ(121, sequenceArray[indexSymbolPrevious]->symbol);
	ASSERT_EQ(105, sequenceArray[indexSymbolNext]->symbol);

	ASSERT_TRUE(sequenceArray[indexSymbolPrevious]->next);
	ASSERT_TRUE(sequenceArray[indexSymbolLeft]->next);
	ASSERT_TRUE(sequenceArray[indexSymbolRight]->next);

	ASSERT_EQ(6, currentPair->count);
	ASSERT_EQ(3, leftPair->count);
	ASSERT_EQ(3, rightPair->count);

	ASSERT_EQ(currentPair, priorityQueue[4]);

	bool left = false;
	bool right = false;
	PairRecord * tmpPair = priorityQueue[1];

	while (tmpPair)
	{
		if (tmpPair == leftPair)
			left = true;
		if (tmpPair == rightPair)
			right = true;
		tmpPair = tmpPair->nextPair;
	}
	ASSERT_TRUE(left);
	ASSERT_TRUE(right);

	algP.replaceInstanceOfPair(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolPrevious,
		indexSymbolNext,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		symbols,
		skip,
		c);

	left = false;
	right = false;
	tmpPair = priorityQueue[0];

	while (tmpPair)
	{
		if (tmpPair == leftPair)
			left = true;
		if (tmpPair == rightPair)
			right = true;
		tmpPair = tmpPair->nextPair;
	}
	ASSERT_TRUE(left);
	ASSERT_TRUE(right);

	ASSERT_EQ(2, leftPair->count);
	ASSERT_EQ(2, rightPair->count);
	ASSERT_EQ(5, currentPair->count);

	ASSERT_EQ(nullptr, sequenceArray[indexSymbolLeft]->next);
	ASSERT_EQ(nullptr, sequenceArray[indexSymbolLeft]->previous);
	ASSERT_EQ(symbols, sequenceArray[indexSymbolLeft]->symbol);

	ASSERT_EQ(sequenceArray[indexSymbolNext], sequenceArray[indexSymbolLeft + 1]->next);
	ASSERT_EQ(sequenceArray[indexSymbolLeft], sequenceArray[indexSymbolLeft + 1]->previous);
	ASSERT_EQ(0, sequenceArray[indexSymbolLeft + 1]->symbol);

	ASSERT_EQ(sequenceArray[indexSymbolNext], sequenceArray[indexSymbolNext - 1]->next);
	ASSERT_EQ(sequenceArray[indexSymbolLeft], sequenceArray[indexSymbolNext - 1]->previous);
	ASSERT_EQ(0, sequenceArray[indexSymbolNext - 1]->symbol);


}

TEST(replaceAllInstancesOfPair, diddy)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
	priorityQueue[4] = nullptr;

	algP.replaceAllPairs(7, sequenceArray, dictionary, activePairs, priorityQueue, symbols, c);

	string expected = { 's', 'i', 'n', 'g', 'i', 'n', 'g', 'A', '_', 'o', '.', 'w', 'a', 'h', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'u', 'm', 'A', '_', 'i', 'd', 'd', 'y', 'A', '_', 'o'};

	MyTest mytest;
	string result = mytest.SequenceToCompleteString(sequenceArray);

	ASSERT_EQ(expected, result);
	ASSERT_EQ(0,mytest.SanityCheck(sequenceArray, priorityQueue, activePairs));
}

TEST(testingRun, diddy)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	string input1 = "diddy.txt";

	bool skip = false;

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;

	string filename = input1;
	ifstream file(filename);

	unordered_set<long> terminals;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);
	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));
}