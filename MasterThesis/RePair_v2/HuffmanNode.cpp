#include "stdafx.h"
#include "HuffmanNode.h"


HuffmanNode::HuffmanNode()
{
	this->frequency = 0;
	this->code = "";
}

HuffmanNode::HuffmanNode(unsigned long  symbol, int frequency)
{
	this->frequency = frequency;
	this->code = "";
}
HuffmanNode::HuffmanNode(
	unsigned long  symbol,
	int frequency,
	HuffmanNode *& leftChild,
	HuffmanNode *& rightChild)
{
	this->frequency = frequency;
	this->code = "";
}

HuffmanNode::~HuffmanNode()
{
}

