#pragma once

class CompactionData
{
public:
	long compactCount = 0;
	long replaceCount = 0;
	long compactTotal = 0;
	long arraySize = 0;

	CompactionData(long aSize);
	~CompactionData();
	void updateCompactTotal();
};

inline void CompactionData::updateCompactTotal()
{
	compactCount++;
	compactTotal += ceil((pow(3.0, ((double)compactCount - 1.0))*(double)arraySize) / pow(4.0, (double)compactCount));
}
