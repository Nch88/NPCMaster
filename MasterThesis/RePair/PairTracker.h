#include "stdafx.h"

#pragma once
class PairTracker
{
public:
	PairTracker();
	~PairTracker();

	bool seenOnce;
	int indexFirst;
	shared_ptr<PairRecord> pairRecord;
};

