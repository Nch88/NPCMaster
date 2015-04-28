#pragma once
class HuffmanNode
{
public:
	unsigned long  symbol;
	int frequency; //Used
	string code;
	HuffmanNode * leftChild = nullptr;
	HuffmanNode * rightChild = nullptr;

	HuffmanNode();
	HuffmanNode(unsigned long  symbol, int frequency);	
	HuffmanNode(
		unsigned long  symbol, 
		int frequency, 
		HuffmanNode *& leftChild, 
		HuffmanNode *& rightChild);
	~HuffmanNode();

	
};

