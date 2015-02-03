#include "stdafx.h"
#include "PairRecord.h"


PairRecord::PairRecord()
{
	count = 0;
}

PairRecord::PairRecord(long indexFirst, long indexLast)
{
	count = 0;
	arrayIndexFirst = indexFirst;
	arrayIndexLast = indexLast;
	previousPair = NULL;
	nextPair = NULL;
}

PairRecord::~PairRecord()
{
}
