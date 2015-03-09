#pragma once
class HuffmanNode
{
public:
	long symbol;
	int frequency;
	string code;
	HuffmanNode * leftChild;
	HuffmanNode * rightChild;

	HuffmanNode();
	HuffmanNode(long symbol, int frequency);	
	HuffmanNode(
		long symbol, 
		int frequency, 
		HuffmanNode *& leftChild, 
		HuffmanNode *& rightChild);
	~HuffmanNode();

	
};

