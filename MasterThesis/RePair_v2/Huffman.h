#include "stdafx.h"
#pragma once
class Huffman
{
public:
	Huffman();
	~Huffman();


	void Huffman::getFrequencies(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, HuffmanNode> & frequencies);
	void Huffman::collapseTree(priority_queue<HuffmanNode, vector<HuffmanNode>, compareNodes> & pq);
	void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild);
	void encode(vector<SymbolRecord*> & sequenceArray);
};

class compareNodes
{
	bool reverse;
	public:
	compareNodes(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const HuffmanNode& leftnode, const HuffmanNode& rightnode) const
	{
		if (reverse) 
			return (leftnode.frequency > rightnode.frequency);
		else 
			return (leftnode.frequency < rightnode.frequency);
	}
};