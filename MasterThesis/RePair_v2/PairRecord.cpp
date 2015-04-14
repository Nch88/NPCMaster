#include "stdafx.h"
#include "PairRecord.h"


PairRecord::PairRecord()
{
	count = 0;
	previousPair = nullptr;
	nextPair = nullptr;
}

PairRecord::PairRecord(long indexFirst)
{
	count = 0;
	arrayIndexFirst = indexFirst;
	previousPair = nullptr;
	nextPair = nullptr;
}

PairRecord::~PairRecord()
{
	previousPair = nullptr;
	nextPair = nullptr;
}
