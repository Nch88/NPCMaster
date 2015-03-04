#pragma once
#include "stdafx.h"

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
		unsigned int &cardinality);
	void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild);
	void Huffman::sift(
		int currentNodeIndex,
		int heapSize,
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
		unsigned int cardinality,
		int *codeLengths,
		unsigned int &maxLength);
	void Huffman::getCodeLengths(
		unsigned int cardinality,
		int *codeLengths,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		unsigned int &maxLength);
	string Huffman::codeToString(int intCode, int length);
	void Huffman::generateCanonicalHuffmanCodes(
		unsigned int cardinality,
		unsigned int maxLength,
		int *codeLengths,
		unsigned int *firstCode,
		unsigned int *numl,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol);
	void encode(vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, HuffmanNode *> &huffmanCodes,
		unsigned int *&firstCode,
		unsigned int *&numl,
		unsigned int &maxLength,
		unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &huffmanToSymbol);
	void Huffman::fillBitset(int rawChunk, bitset<32> *chunk);
	void Huffman::fillBitset(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, bitset<32> *chunk);
	void Huffman::fillString(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, string &chunk);
	void Huffman::decodeDictionary(
		ifstream &bitstream,
		unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> *symbolIndices);
	void Huffman::decode(
		unsigned int *firstCode,
		string filename,
		unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> *symbolIndices,
		vector<unsigned int> &symbolIndexSequence);
};

