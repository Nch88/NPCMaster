#pragma once
class HuffmanNode
{
public:
	int frequency; //Used
	string code;

	HuffmanNode();
	HuffmanNode(unsigned long  symbol, int frequency);	
	HuffmanNode(
		unsigned long  symbol, 
		int frequency, 
		HuffmanNode *& leftChild, 
		HuffmanNode *& rightChild);
	~HuffmanNode();

	
};

