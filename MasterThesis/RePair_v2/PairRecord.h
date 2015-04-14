#pragma once
class PairRecord
{
public:
	int count;
	long arrayIndexFirst;
	PairRecord * previousPair;
	PairRecord * nextPair;

	PairRecord();
	PairRecord(long indexFirst);
	~PairRecord();
};

