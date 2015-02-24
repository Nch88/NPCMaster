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
		unordered_map<unsigned int, HuffmanNode *> & frequencies,
		int &cardinality);
	void Huffman::setupPriorityQueue(
		unordered_map<unsigned int, HuffmanNode *> & frequencies,
		priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq);
	void Huffman::collapseTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq);
	void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild);
	void Huffman::sift(int currentNodeIndex,
		int cardinality,
		int *codeLengths);
	void Huffman::initCodeLengthsArray(
		int cardinality,
		int *codeLengths,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes);
	void Huffman::initMinHeap(
		int heapSize,
		int *codeLengths);
	void Huffman::collapseHuffmanTree(
		int heapSize,
		int *codeLengths);
	void Huffman::expandHuffmanTree(
		int cardinality,
		int *codeLengths,
		int &maxLength);
	void Huffman::getCodeLengths(
		int cardinality,
		int *codeLengths,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		int &maxLength);
	void Huffman::generateCanonicalHuffmanCodes(
		int cardinality,
		int maxLength,
		int *codeLengths,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes);
	void encode(vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes);
};

