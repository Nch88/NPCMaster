#pragma once
class PairTracker
{
public:
	bool seenOnce;
	long indexFirst;
	PairRecord * pairRecord;

	PairTracker();
	~PairTracker();
};

