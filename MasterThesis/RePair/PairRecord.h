#include "stdafx.h"

using namespace std;
#pragma once

class PairRecord
{
public:
	Pair pair;
	int count;
	long arrayIndexFirst;
	long arrayIndexLast;
	bool skippedPair;	
	shared_ptr<PairRecord> previousPair;
	shared_ptr<PairRecord> nextPair;

	PairRecord();
	PairRecord(long indexFirst, long indexLast);
	~PairRecord();

	void inc();
	void dec();

	void setIndexFirst(long indexFirst);
	void setIndexLast(long indexLast);

	int getCount();
	long getIndexFirst();
	long getIndexLast();
};

