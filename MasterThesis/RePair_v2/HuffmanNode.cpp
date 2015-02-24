#include "stdafx.h"
#include "HuffmanNode.h"


HuffmanNode::HuffmanNode()
{
	this->symbol = 0;
	this->frequency = 0;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->code = 0;
}

HuffmanNode::HuffmanNode(unsigned int symbol, int frequency)
{
	this->symbol = symbol;
	this->frequency = frequency;
	this->leftChild = nullptr;
	this->rightChild = nullptr;
	this->code = 0;
}
HuffmanNode::HuffmanNode(
	unsigned int symbol,
	int frequency,
	HuffmanNode *& leftChild,
	HuffmanNode *& rightChild)
{
	this->symbol = symbol;
	this->frequency = frequency;
	this->leftChild = leftChild;
	this->rightChild = rightChild;
	this->code = 0;
}

HuffmanNode::~HuffmanNode()
{
}

