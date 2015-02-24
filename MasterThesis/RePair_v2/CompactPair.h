#pragma once
class CompactPair
{
public:
	unsigned int leftSymbol;
	unsigned int rightSymbol;

	CompactPair();
	CompactPair(unsigned int leftSymbol, unsigned int rightSymbol);
	CompactPair::CompactPair(Pair &p);
	~CompactPair();
};