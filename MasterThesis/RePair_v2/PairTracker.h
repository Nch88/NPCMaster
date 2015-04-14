#pragma once
class PairTracker
{
public:
	bool seenOnce;
	PairRecord * pairRecord;

	PairTracker();
	~PairTracker();
};

