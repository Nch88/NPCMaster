#include "stdafx.h"

#pragma once
class PairTracker
{
public:
	PairTracker();
	~PairTracker();

	bool seenOnce;
	long indexFirst;
	shared_ptr<PairRecord> pairRecord;
};

