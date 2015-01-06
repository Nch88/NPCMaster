#include "stdafx.h"

#pragma once
class PairRecord
{
	int count;
	int arrayIndexFirst;
	int arrayIndexLast;

public:
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

