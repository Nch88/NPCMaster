#pragma once
class PairRecord
{
public:
	int count;
	long arrayIndexFirst;
	long arrayIndexLast;
	PairRecord * previousPair;
	PairRecord * nextPair;

	PairRecord();
	PairRecord(long indexFirst, long indexLast);
	~PairRecord();
};

