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
	using namespace google;
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;
	
	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = 
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);

	algP.updatePairRecord(
		scdPairLeft->index,
		scdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
}

TEST(updatePairRecord, countMoreThanTwoFirstPair)
{
	using namespace google;
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);

	algP.updatePairRecord(
		fstPairLeft->index,
		fstPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
}

TEST(updatePairRecord, countMoreThanTwoLastPair)
{
	using namespace google;
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[trdPairLeft->symbol][trdPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);

	algP.updatePairRecord(
		trdPairLeft->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		tracker);

	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
}

TEST(updatePairRecord, countTwoFirstPair)
{
	using namespace google;
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	AlgorithmP algP;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 2;

	tracker = &activePairs[fstPairLeft->symbol][fstPairRight->symbol];

	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);

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
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long previousprevious = -1, previous = 0, left = 1, right = 2;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100, 99, 65 };
	mytest.buildSequenceArray(sequenceArray, a, 6);

	sequenceArray[0]->next = sequenceArray[4];
	sequenceArray[4]->previous = sequenceArray[0];

	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);

	//Check that new pair was counted
	if (activePairs[99].empty())
	{
		activePairs[99].set_empty_key(-1);
		activePairs[99].set_deleted_key(-2);
	}
	ASSERT_TRUE(activePairs[99][65].seenOnce);

	//Check that no pair record was added
	ASSERT_EQ(NULL, activePairs[99][65].pairRecord);
}

TEST(incrementCountRight, firstTimeSeen)
{
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary; 
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long left = 1, right = 2, next = 3, nextnext = 3;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 7);

	sequenceArray[1]->next = sequenceArray[4];
	sequenceArray[4]->previous = sequenceArray[1];

	algo.checkCountRight(left, right, next, nextnext, activePairs, sequenceArray, symbols, c);
	if (activePairs[65].empty())
	{
		activePairs[65].set_empty_key(-1);
		activePairs[65].set_deleted_key(-2);
	}
	//Check that new pair was counted
	ASSERT_TRUE(activePairs[65][100].seenOnce);

	//Check that no pair record was added
	ASSERT_EQ(NULL, activePairs[65][100].pairRecord);
}

TEST(incrementCountLeft, secondTimeSeen)
{
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long previousFirst = 0, leftFirst = 1;
	long previousprevious = 1, previous = 3, left = 4, right = 6;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 99, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 7);
	if (activePairs[99].empty())
	{
		activePairs[99].set_empty_key(-1);
		activePairs[99].set_deleted_key(-2);
	}
	activePairs[99][65].seenOnce = true;

	sequenceArray[0]->next = sequenceArray[3];
	sequenceArray[3]->previous = sequenceArray[0];

	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
	algo.incrementCountLeft(previousFirst, leftFirst, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[99][65].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[99][65].pairRecord);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[0]->next == sequenceArray[3]);
	ASSERT_TRUE(sequenceArray[3]->previous == sequenceArray[0]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0]->count == 2);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 0);
}

TEST(incrementCountRight, secondTimeSeen)
{
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long leftFirst = 1, nextFirst = 3;
	long left = 4, right = 5, next = 6, nextnext = -1;
	bool skipright = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 100, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 7);

	if (activePairs[65].empty())
	{
		activePairs[65].set_empty_key(-1);
		activePairs[65].set_deleted_key(-2);
	}
	activePairs[65][100].seenOnce = true;

	algo.checkCountRight(left, right, next, nextnext, activePairs, sequenceArray, symbols, c);
	algo.incrementCountRight(leftFirst, nextFirst, activePairs, sequenceArray, priorityQueue, symbols, c, skipright);
	algo.incrementCountRight(left, next, activePairs, sequenceArray, priorityQueue, symbols, c, skipright);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[65][100].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[65][100].pairRecord);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[1]->next == sequenceArray[4]);
	ASSERT_TRUE(sequenceArray[4]->previous == sequenceArray[1]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0]->count == 2);
	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 1);
}

TEST(incrementCountLeft, thirdTimeSeen)
{
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long previouspreviousFirst = -1, previousFirst = 0, leftFirst = 1, rightFirst = 3;
	long previouspreviousSecond = 1, previousSecond = 3, leftSecond = 4, rightSecond = 6;
	long previousprevious = 4, previous = 6, left = 7, right = 9;
	bool skip = false;

	long symbol;
	long index;

	long a[] = { 99, 65, 0, 99, 65, 0, 99, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 10);
	
	sequenceArray[0]->next = sequenceArray[3];
	sequenceArray[3]->previous = sequenceArray[0];
	sequenceArray[3]->next = sequenceArray[6];
	sequenceArray[6]->previous = sequenceArray[3];

	algo.checkCountLeft(previouspreviousFirst, previousFirst, leftFirst, rightFirst, activePairs, sequenceArray, symbols, skip, c);
	algo.checkCountLeft(previouspreviousSecond, previousSecond, leftSecond, rightSecond, activePairs, sequenceArray, symbols, skip, c);
	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);

	algo.incrementCountLeft(previousFirst, leftFirst, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	algo.incrementCountLeft(previousSecond, leftSecond, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[99][65].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[99][65].pairRecord);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[3]->next == sequenceArray[6]);
	ASSERT_TRUE(sequenceArray[6]->previous == sequenceArray[3]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0] == nullptr);

	ASSERT_TRUE(priorityQueue[1]->count == 3);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexFirst == 0);
}

TEST(incrementCountRight, thirdTimeSeen)
{
	using namespace google;
	AlgorithmP algo;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue(2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols = 65;
	Conditions c;

	long leftFirst = 1, rightFirst = 2, nextFirst = 3, nextnextFirst = 4;
	long leftSecond = 4, rightSecond = 5, nextSecond = 6, nextnextSecond = 7;
	long left = 7, right = 8, next = 9, nextnext = -1;
	bool skip = false;
	bool skipright = false;

	long a[] = { 99, 65, 0, 100, 65, 0, 100, 65, 0, 100 };
	mytest.buildSequenceArray(sequenceArray, a, 10);


	algo.checkCountRight(leftFirst, rightFirst, nextFirst, nextnextFirst, activePairs, sequenceArray, symbols, c);
	algo.checkCountRight(leftSecond, rightSecond, nextSecond, nextnextSecond, activePairs, sequenceArray, symbols, c);
	algo.checkCountRight(left, right, next, nextnext, activePairs, sequenceArray, symbols, c);

	algo.incrementCountRight(leftFirst, nextFirst, activePairs, sequenceArray, priorityQueue, symbols, c, skipright);
	algo.incrementCountRight(leftSecond, nextSecond, activePairs, sequenceArray, priorityQueue, symbols, c, skipright);
	algo.incrementCountRight(left, next, activePairs, sequenceArray, priorityQueue, symbols, c, skipright);

	//Check that seenOnce was reset
	ASSERT_FALSE(activePairs[65][100].seenOnce);

	//Check that a pair record was added
	ASSERT_TRUE(NULL != activePairs[65][100].pairRecord);

	//Check that threading pointers are correctly set
	ASSERT_TRUE(sequenceArray[4]->next == sequenceArray[7]);
	ASSERT_TRUE(sequenceArray[7]->previous == sequenceArray[4]);

	//Check entry in priority queue
	ASSERT_TRUE(priorityQueue[0] == nullptr);

	ASSERT_TRUE(priorityQueue[1]->count == 3);
	ASSERT_TRUE(priorityQueue[1]->arrayIndexFirst == 1);
}

//TEST(incrementCountLeft, skipTest)
//{
//	using namespace google;
//	AlgorithmP algo;
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue(5);
//	dense_hash_map<long, Pair> dictionary;
//	dictionary.set_empty_key(-1);
//	dictionary.set_deleted_key(-2);
//	long symbols = 65;
//	Conditions c;
//
//	bool skip = false;
//
//	long symbol;
//	long index;
//
//	long a[] = { 99, 65, 0, 65, 0, 65, 0, 65, 0, 100, 100 };
//	mytest.buildSequenceArray(sequenceArray, a, 11);
//
//	sequenceArray[1]->next = sequenceArray[5];
//	sequenceArray[5]->previous = sequenceArray[1];
//
//	long previousprevious = -1, previous = 0, left = 1, right = 3;
//	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
//	
//	previousprevious = 0, previous = 1; left = 3, right = 5;
//	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
//
//	//previousprevious = 1, previous = 3; left = 5, right = 7;
//	//algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
//	
//	previousprevious = 3, previous = 5; left = 7, right = 9;
//	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
//	
//	previousprevious = 5, previous = 7; left = 9, right = 10;
//	algo.checkCountLeft(previousprevious, previous, left, right, activePairs, sequenceArray, symbols, skip, c);
//
//	if (activePairs[99].empty())
//	{
//		activePairs[99].set_empty_key(-1);
//		activePairs[99].set_deleted_key(-2);
//	}
//
//	if (activePairs[65].empty())
//	{
//		activePairs[65].set_empty_key(-1);
//		activePairs[65].set_deleted_key(-2);
//	}
//
//	//Check that seenOnce was not set for cA
//	ASSERT_FALSE(activePairs[99][65].seenOnce);
//
//	//Check that a pair record was added for AA
//	ASSERT_FALSE(activePairs[65][65].seenOnce);
//	ASSERT_TRUE(NULL != activePairs[65][65].pairRecord);
//
//	previous = 0, left = 1;
//	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
//	ASSERT_FALSE(skip);
//	previous = 1; left = 3;
//	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
//	ASSERT_TRUE(skip);
//	previous = 3; left = 5;
//	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
//	ASSERT_FALSE(skip);
//	previous = 5; left = 7;
//	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
//	ASSERT_TRUE(skip);
//	previous = 7; left = 9;
//	algo.incrementCountLeft(previous, left, activePairs, sequenceArray, priorityQueue, symbols, skip, c);
//
//
//	//Check that threading pointers are correctly set
//	ASSERT_TRUE(sequenceArray[1]->next == sequenceArray[5]);
//	ASSERT_TRUE(sequenceArray[3]->next == NULL);
//	ASSERT_TRUE(sequenceArray[5]->previous == sequenceArray[1]);
//
//	//Check entry in priority queue
//	ASSERT_TRUE(priorityQueue[0]->count == 2);
//	ASSERT_TRUE(priorityQueue[0]->arrayIndexFirst == 1);
//}

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
	using namespace google;
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
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
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
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountLeft, hasPrevious)
{
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	long symbols(initialSymbolValue);
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 3;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolPreviousPrevious = fstPairRight->index;
	indexSymbolPrevious = scdPairLeft->index;
	indexSymbolLeft = scdPairRight->index;
	indexSymbolRight = trdPairLeft->index;


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[1]);
	ASSERT_EQ(nullptr, priorityQueue[0]);

	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		symbols,
		c);

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountLeft, hasPreviousNotActivePair)
{
	using namespace google;
	AlgorithmP algP;
	long symbols(initialSymbolValue);
	Conditions c;
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 2;

	tracker = &activePairs[scdPairLeft->symbol][scdPairRight->symbol];

	//Setup Priority queue
	priorityQueue[tracker->pairRecord->count - 2] =
		tracker->pairRecord;

	indexSymbolPreviousPrevious = fstPairRight->index;
	indexSymbolPrevious = scdPairLeft->index;
	indexSymbolLeft = scdPairRight->index;
	indexSymbolRight = trdPairLeft->index;


	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);

	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		symbols,
		c);

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}

	ASSERT_EQ(nullptr, priorityQueue[2]);
	ASSERT_EQ(nullptr, priorityQueue[1]);
	ASSERT_EQ(tracker->pairRecord, priorityQueue[0]);
	ASSERT_EQ(2, tracker->pairRecord->count);
	ASSERT_EQ(2, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->count);
	ASSERT_EQ(0, activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord->arrayIndexFirst);
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}

TEST(decrementCountRight, hasNext)
{
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	long symbols(initialSymbolValue);
	vector<PairRecord*> priorityQueue(3);
	long indexSymbolLeft = -1;
	long indexSymbolRight = -1;
	long indexSymbolPrevious = -1;
	long indexSymbolPreviousPrevious = -1;
	long indexSymbolNext = -1;

	long sequenceIndex = 2;

	PairTracker * tracker;

	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	//Setup active pair
	activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord =
		new PairRecord(sequenceIndex - 2);
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

	algP.decrementCountRight(
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
	ASSERT_EQ(trdPairLeft, fstPairLeft->next);
	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->previous);
	ASSERT_EQ(nullptr, scdPairLeft->next);
}


TEST(threadEmptySymbols, singleEmptySymbol)
{
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
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
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
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
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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

	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
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
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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

	if (activePairs[fstPairLeft->symbol].empty())
	{
		activePairs[fstPairLeft->symbol].set_empty_key(-1);
		activePairs[fstPairLeft->symbol].set_deleted_key(-2);
	}
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
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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

	if (activePairs[fstPairLeft->symbol].empty())
	{
		activePairs[fstPairLeft->symbol].set_empty_key(-1);
		activePairs[fstPairLeft->symbol].set_deleted_key(-2);
	}
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

//TEST(replacePair, deletingPairRecord)
//{
//	using namespace google;
//	AlgorithmP algP;
//	Conditions c;
//	vector<SymbolRecord*> sequenceArray;
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	dense_hash_map<long, Pair> dictionary;
//	dictionary.set_empty_key(-1);
//	dictionary.set_deleted_key(-2);
//	long symbols(256);
//	long symbol;
//	long index;
//
//	//Setup symbol records in sequence array
//	symbol = 1;
//	index = 0;
//	SymbolRecord * fstPairLeft = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(fstPairLeft);
//
//	symbol = 0;
//	index = 1;
//	SymbolRecord * fstPairRight = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(fstPairRight);
//
//	symbol = 0;
//	index = 2;
//	SymbolRecord * scdPairLeft = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(scdPairLeft);
//
//	symbol = 2;
//	index = 3;
//	SymbolRecord * scdPairRight = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(scdPairRight);
//
//	symbol = 0;
//	index = 4;
//	SymbolRecord * trdPairLeft = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(trdPairLeft);
//
//	symbol = 2;
//	index = 5;
//	SymbolRecord * trdPairRight = new SymbolRecord(symbol, index);
//	sequenceArray.push_back(trdPairRight);
//
//	Pair pair(fstPairLeft->symbol,
//		scdPairRight->symbol,
//		0);
//
//	if (activePairs[fstPairLeft->symbol].empty())
//	{
//		activePairs[fstPairLeft->symbol].set_empty_key(-1);
//		activePairs[fstPairLeft->symbol].set_deleted_key(-2);
//	}
//	activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
//	activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord->count = 1;
//
//	algP.replacePair(
//		fstPairLeft->index,
//		scdPairRight->index,
//		trdPairRight->index,
//		activePairs,
//		sequenceArray,
//		dictionary,
//		symbols,
//		c);
//
//	ASSERT_EQ(symbols, fstPairLeft->symbol);
//	ASSERT_EQ(0, scdPairRight->symbol);
//	ASSERT_EQ(fstPairLeft, trdPairLeft->previous);
//	ASSERT_EQ(trdPairRight, trdPairLeft->next);
//	ASSERT_EQ(fstPairLeft, fstPairRight->previous);
//	ASSERT_EQ(trdPairRight, fstPairRight->next);
//	ASSERT_EQ(pair.leftSymbol, dictionary[symbols].leftSymbol);
//	ASSERT_EQ(pair.rightSymbol, dictionary[symbols].rightSymbol);
//	ASSERT_EQ(nullptr, activePairs[fstPairLeft->symbol][scdPairRight->symbol].pairRecord);
//}

TEST(replaceInstanceOfPairOnlyDecrementAndReplace, leftAndRightLowCount)
{
	using namespace google;
	AlgorithmP algP;
	Conditions c;
	vector<SymbolRecord*> sequenceArray;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	vector<PairRecord*> priorityQueue;
	long symbols(initialSymbolValue);
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
	if (activePairs[scdPairLeft->symbol].empty())
	{
		activePairs[scdPairLeft->symbol].set_empty_key(-1);
		activePairs[scdPairLeft->symbol].set_deleted_key(-2);
	}
	PairRecord * pairRecord1 = activePairs[scdPairLeft->symbol][scdPairRight->symbol].pairRecord = new PairRecord();
	pairRecord1->count = 3;
	pairRecord1->arrayIndexFirst = 0;

	//Setup pair record for pair 21
	if (activePairs[scdPairRight->symbol].empty())
	{
		activePairs[scdPairRight->symbol].set_empty_key(-1);
		activePairs[scdPairRight->symbol].set_deleted_key(-2);
	}
	PairRecord * pairRecord2 = activePairs[scdPairRight->symbol][trdPairLeft->symbol].pairRecord = new PairRecord();
	pairRecord2->count = 2;
	pairRecord2->arrayIndexFirst = 1;
	priorityQueue[0] = pairRecord2;

	bool activePairLeft = sequenceArray[fstPairRight->index]->next ||
		sequenceArray[fstPairRight->index]->previous;

	algP.decrementCountLeft(
		fstPairRight->index,
		scdPairLeft->index,
		scdPairRight->index,
		activePairs,
		sequenceArray,
		priorityQueue,
		symbols,
		c);

	algP.decrementCountRight(
		scdPairRight->index,
		trdPairLeft->index,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);

	algP.checkCountLeft(
		fstPairLeft->index,
		fstPairRight->index,
		scdPairLeft->index,
		scdPairRight->index,
		activePairs,
		sequenceArray,
		symbols,
		skip,
		c);

	algP.checkCountRight(
		scdPairLeft->index,
		scdPairRight->index,
		trdPairLeft->index,
		trdPairRight->index,
		activePairs,
		sequenceArray,
		symbols,
		c);

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
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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
	long indexSymbolPreviousPrevious = 18;
	long indexSymbolNext = 22;
	long indexSymbolNextNext = 23;

	if (activePairs[sequenceArray[indexSymbolLeft]->symbol].empty())
	{
		activePairs[sequenceArray[indexSymbolLeft]->symbol].set_empty_key(-1);
		activePairs[sequenceArray[indexSymbolLeft]->symbol].set_deleted_key(-2);
	}
	if (activePairs[sequenceArray[indexSymbolPrevious]->symbol].empty())
	{
		activePairs[sequenceArray[indexSymbolPrevious]->symbol].set_empty_key(-1);
		activePairs[sequenceArray[indexSymbolPrevious]->symbol].set_deleted_key(-2);
	}
	if (activePairs[sequenceArray[indexSymbolRight]->symbol].empty())
	{
		activePairs[sequenceArray[indexSymbolRight]->symbol].set_empty_key(-1);
		activePairs[sequenceArray[indexSymbolRight]->symbol].set_deleted_key(-2);
	}
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

	bool activePairLeft = sequenceArray[indexSymbolPrevious]->next ||
		sequenceArray[indexSymbolPrevious]->previous;

	algP.decrementCountLeft(
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		priorityQueue,
		symbols,
		c);

	algP.decrementCountRight(
		indexSymbolRight,
		indexSymbolNext,
		activePairs,
		sequenceArray,
		priorityQueue,
		c);

	algP.checkCountLeft(
		indexSymbolPreviousPrevious,
		indexSymbolPrevious,
		indexSymbolLeft,
		indexSymbolRight,
		activePairs,
		sequenceArray,
		symbols,
		skip,
		c);

	algP.checkCountRight(
		indexSymbolLeft,
		indexSymbolRight,
		indexSymbolNext,
		indexSymbolNextNext,
		activePairs,
		sequenceArray,
		symbols,
		c);

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
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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

	ASSERT_EQ(6, activePairs[46][100].pairRecord->count);

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
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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
	string string2 = "sHHAo.wahEFumFo";

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

TEST(testingRun, diddy_explicit)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long Symbols(65);//A

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;

	int testCount = 0;

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
	string string2 = "sHHAo.wahEFumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));


	//Relevant parts of algP.run
	CompactionData cData(sequenceArray.size());

	//Runs through all entries from second last to first
	for (long i = priorityQueue.size() - 2; i >= 0; i--)
	{
		while (priorityQueue[i])
		{
			PairRecord * tmpPairRecord = nullptr;
			long sequenceIndex = -1;

			tmpPairRecord = priorityQueue[i];
			sequenceIndex = tmpPairRecord->arrayIndexFirst;

			//Remove current pair from priority queue
			if (tmpPairRecord->nextPair)
			{
				priorityQueue[i] = tmpPairRecord->nextPair;
				priorityQueue[i]->previousPair = nullptr;
			}
			else
				priorityQueue[i] = nullptr;
			tmpPairRecord->previousPair = nullptr;
			tmpPairRecord->nextPair = nullptr;

			//Find the count of the pair to be replaced and update counter for compaction
			if (c.compact)
			{
				long idx = sequenceIndex;
				long s1 = sequenceArray[idx]->symbol;
				long s2 = sequenceArray[idx + 1]->symbol != 0 ? sequenceArray[idx + 1]->symbol : sequenceArray[idx + 1]->next->symbol;
				cData.replaceCount += activePairs[s1][s2].pairRecord->count;
			}

			//Replace all pairs
			long indexSymbolLeft = -1;
			long indexSymbolRight = -1;
			long indexSymbolPrevious = -1;
			long indexSymbolPreviousPrevious = -1;
			long indexSymbolNext = -1;
			long indexSymbolNextNext = -1;

			long oldSequenceIndex = sequenceIndex;

			//Firstpass - start
			SymbolRecord * nextSymbol = sequenceArray[sequenceIndex];
			bool skip = false;

			do
			{
				indexSymbolLeft = -1;
				indexSymbolRight = -1;
				indexSymbolPrevious = -1;
				indexSymbolPreviousPrevious = -1;
				indexSymbolNext = -1;

				sequenceIndex = nextSymbol->index;
				//Store the pointer to the next symbol now, as the current symbol is changed as we go
				nextSymbol = nextSymbol->next;

				if (sequenceIndex == 20)
					int x = 0;
				if (sequenceIndex == 26)
					int x = 0;
				if (sequenceIndex == 36)
					int x = 0;

				algP.establishContext(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceIndex,
					sequenceArray);


				//Left pair
				algP.checkCountLeft(
					indexSymbolPreviousPrevious,
					indexSymbolPrevious,
					indexSymbolLeft,
					indexSymbolRight,
					activePairs,
					sequenceArray,
					Symbols,
					skip,
					c);

				//Right pair
				algP.checkCountRight(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolNext,
					indexSymbolNextNext,
					activePairs,
					sequenceArray,
					Symbols,
					c);

			} while (nextSymbol);
			//Firstpass - end

			skip = false;

			sequenceIndex = oldSequenceIndex;
			nextSymbol = sequenceArray[sequenceIndex];

			do
			{
				indexSymbolLeft = -1;
				indexSymbolRight = -1;
				indexSymbolPrevious = -1;
				indexSymbolNext = -1;

				sequenceIndex = nextSymbol->index;
				//Store the pointer to the next symbol now, as the current symbol is changed as we go
				nextSymbol = nextSymbol->next;


				if (sequenceIndex == 20)
					int x = 0;
				if (sequenceIndex == 26)
					int x = 0;
				if (sequenceIndex == 36)
					int x = 0;

				algP.establishContext(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceIndex,
					sequenceArray);

				algP.replaceInstanceOfPair(
					indexSymbolLeft,
					indexSymbolRight,
					indexSymbolPrevious,
					indexSymbolNext,
					sequenceArray,
					dictionary,
					activePairs,
					priorityQueue,
					Symbols,
					skip,
					c);

			} while (nextSymbol);

			int sanechk = t.SanityCheck(sequenceArray, priorityQueue, activePairs);
			string sanechk2 = "";
			if (sanechk != 0)
			{
				sanechk2 = t.SanityCheckThreadingPointersDetailed(sequenceArray);
				cout << "INSANE: " << sanechk2 << endl;
			}
				

			//Compaction
			if (c.compact)
			{
				if (cData.replaceCount > cData.compactTotal)
				{
					algP.compact(sequenceArray, activePairs, priorityQueue);
					cData.updateCompactTotal();
				}
			}

			//Pick new symbol
			algP.newSymbol(Symbols);

			//Tests

			if (testCount == 0)
			{
				ASSERT_EQ("singingAo.wahAiddyAiddyAumAiddyAo", t.SequenceToString(sequenceArray));

				ASSERT_EQ(0, t.SanityCheck(sequenceArray, priorityQueue, activePairs));
			}
				

			if (testCount == 1)
				ASSERT_EQ("singingAo.wahBddyBddyAumBddyAo", t.SequenceToString(sequenceArray));

			if (testCount == 2)
				ASSERT_EQ("singingAo.wahCdyCdyAumCdyAo", t.SequenceToString(sequenceArray));

			if (testCount == 3)
				ASSERT_EQ("singingAo.wahDyDyAumDyAo", t.SequenceToString(sequenceArray));

			if (testCount == 4)
				ASSERT_EQ("singingAo.wahEEAumEAo", t.SequenceToString(sequenceArray));

			if (testCount == 5)
				ASSERT_EQ("singingAo.wahEFumFo", t.SequenceToString(sequenceArray));

			if (testCount == 6)
				ASSERT_EQ("sGgGgAo.wahEFumFo", t.SequenceToString(sequenceArray));

			if (testCount == 7)
				ASSERT_EQ("sHHAo.wahEFumFo", t.SequenceToString(sequenceArray));

			testCount++;
		}
	}



	ASSERT_EQ(string2, t.SequenceToString(sequenceArray));
}