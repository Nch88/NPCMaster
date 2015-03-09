#pragma once
class CompactPair
{
public:
	long leftSymbol;
	long rightSymbol;

	CompactPair();
	CompactPair(long leftSymbol, long rightSymbol);
	CompactPair::CompactPair(Pair &p);
	~CompactPair();
};