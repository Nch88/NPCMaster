#include "stdafx.h"

#pragma once
class PairRecord
{
public:
	int count;
	int arrayIndexFirst;
	int arrayIndexLast;
	std::string pair;
	PairRecord* previousPair;
	PairRecord* nextPair;


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

