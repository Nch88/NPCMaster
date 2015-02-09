#pragma once
class HuffmanNode
{
public:
	unsigned int symbol;
	int frequncy;
	vector<bool> code;

	HuffmanNode();
	HuffmanNode(unsigned int symbol, int frequncy);
	~HuffmanNode();
};

