#include "stdafx.h"
#include "HuffmanNode.h"


HuffmanNode::HuffmanNode()
{
	this->frequency = 0;
	this->code = "";
}

HuffmanNode::HuffmanNode(int frequency)
{
	this->frequency = frequency;
	this->code = "";
}

HuffmanNode::~HuffmanNode()
{
}

