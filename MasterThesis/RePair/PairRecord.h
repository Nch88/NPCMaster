#include "stdafx.h"

using namespace std;
#pragma once
class PairRecord
{
public:
	int count;
	int arrayIndexFirst;
	int arrayIndexLast;
	bool skippedPair;
	std::string pair;
	shared_ptr<PairRecord> previousPair;
	shared_ptr<PairRecord> nextPair;


	PairRecord();
	PairRecord(int indexFirst, int indexLast);
	~PairRecord();

	void inc();
	void dec();

	void setIndexFirst(int indexFirst);
	void setIndexLast(int indexLast);

	int getCount();
	int getIndexFirst();
	int getIndexLast();
};

