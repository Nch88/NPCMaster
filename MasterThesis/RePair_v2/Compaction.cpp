#include "stdafx.h"
#include "Compaction.h"

CompactionData::CompactionData(long aSize)
{
	arraySize = aSize;
	updateCompactTotal();
}

CompactionData::~CompactionData()
{
}
