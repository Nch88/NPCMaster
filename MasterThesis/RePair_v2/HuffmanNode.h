#pragma once
class HuffmanNode
{
public:
	unsigned int symbol;
	int frequency;
	int code;
	HuffmanNode * leftChild;
	HuffmanNode * rightChild;

	HuffmanNode();
	HuffmanNode(unsigned int symbol, int frequency);	
	HuffmanNode(
		unsigned int symbol, 
		int frequency, 
		HuffmanNode *& leftChild, 
		HuffmanNode *& rightChild);
	~HuffmanNode();

	
};

