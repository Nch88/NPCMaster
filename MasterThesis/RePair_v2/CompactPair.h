#pragma once
class CompactPair
{
public:
	long leftSymbol;
	long rightSymbol;

	CompactPair();
	CompactPair(unsigned long leftSymbol, unsigned long rightSymbol);
	CompactPair::CompactPair(Pair &p);
	~CompactPair();
};