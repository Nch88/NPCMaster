#include "stdafx.h"
#include "PairRecord.h"


PairRecord::PairRecord()
{
	count = 0;
	skippedPair = false;
}

PairRecord::PairRecord(long indexFirst, long indexLast)
{
	count = 0;
	arrayIndexFirst = indexFirst;
	arrayIndexLast = indexLast;
	previousPair = NULL;
	nextPair = NULL;
	skippedPair = false;
}


PairRecord::~PairRecord()
{
}


void PairRecord::inc()
{
	count++;
}

void PairRecord::dec()
{
	count--;
}

void PairRecord::setIndexFirst(long index)
{
	arrayIndexFirst = index;
}

void PairRecord::setIndexLast(long index)
{
	arrayIndexLast = index;
}

int PairRecord::getCount()
{
	return count;
}

long PairRecord::getIndexFirst()
{
	return arrayIndexFirst;
}

long PairRecord::getIndexLast()
{
	return arrayIndexLast;
}