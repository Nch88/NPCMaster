#include "stdafx.h"
#include "PairRecord.h"


PairRecord::PairRecord()
{
	count = 0;
}

PairRecord::PairRecord(int indexFirst, int indexLast)
{
	count = 0;
	arrayIndexFirst = indexFirst;
	arrayIndexLast = indexLast;
}


PairRecord::~PairRecord()
{
	if (nextPair)
	{
		delete nextPair;
		nextPair = 0;
	}
	if (previousPair)
	{
		delete previousPair;
		previousPair = 0;
	}
}


void PairRecord::inc()
{
	count++;
}

void PairRecord::dec()
{
	count--;
}

void PairRecord::setIndexFirst(int index)
{
	arrayIndexFirst = index;
}

void PairRecord::setIndexLast(int index)
{
	arrayIndexLast = index;
}

int PairRecord::getCount()
{
	return count;
}

int PairRecord::getIndexFirst()
{
	return arrayIndexFirst;
}

int PairRecord::getIndexLast()
{
	return arrayIndexLast;
}