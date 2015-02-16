#include "stdafx.h"
#pragma once

class CompareNodes
{
	bool reverse;
public:
	CompareNodes(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (HuffmanNode *& leftnode, HuffmanNode *& rightnode) const
	{
		if (reverse)
			return (leftnode->frequency < rightnode->frequency);
		else
			return (leftnode->frequency > rightnode->frequency);
	}
};

class Huffman
{
public:
	Huffman();
	~Huffman();


	void Huffman::getFrequencies(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> & frequencies);
	void Huffman::setupPriorityQueue(
		unordered_map<unsigned int, HuffmanNode *> & frequencies,
		priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq);
	void Huffman::collapseTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq);
	void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild);
	void encode(vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes);
};

