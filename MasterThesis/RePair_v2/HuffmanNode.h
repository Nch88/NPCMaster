#pragma once
class HuffmanNode
{
public:
	long symbol;
	int frequency;
	string code;
	HuffmanNode * leftChild = nullptr;
	HuffmanNode * rightChild = nullptr;

	HuffmanNode();
	HuffmanNode(long symbol, int frequency);	
	HuffmanNode(
		long symbol, 
		int frequency, 
		HuffmanNode *& leftChild, 
		HuffmanNode *& rightChild);
	~HuffmanNode();

	
};

