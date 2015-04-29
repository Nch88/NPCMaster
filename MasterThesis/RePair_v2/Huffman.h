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
		dense_hash_map<long, HuffmanNode> & frequencies,
		long &cardinality,
		Conditions &c);
	void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild);
	void Huffman::sift(
		int currentNodeIndex,
		int heapSize,
		int *codeLengths);
	void Huffman::initCodeLengthsArray(
		int cardinality,
		int *codeLengths,
		dense_hash_map<long, HuffmanNode> &huffmanCodes);
	void Huffman::initMinHeap(
		int heapSize,
		int *codeLengths);
	void Huffman::collapseHuffmanTree(
		int heapSize,
		int *codeLengths);
	void Huffman::expandHuffmanTree(
		long cardinality,
		int *codeLengths,
		long &maxLength);
	void Huffman::getCodeLengths(
		long cardinality,
		int *codeLengths,
		dense_hash_map<long, HuffmanNode> &huffmanCodes,
		long &maxLength);
	string Huffman::codeToString(int intCode, int length);
	void Huffman::generateCanonicalHuffmanCodes(
		long cardinality,
		long maxLength,
		int *codeLengths,
		long *firstCode,
		long *numl,
		dense_hash_map<long, HuffmanNode> &huffmanCodes,
		dense_hash_map<long, dense_hash_map<long, long>> &huffmanToSymbol,
		Conditions &c);
	void encode(vector<SymbolRecord*> & sequenceArray,
		dense_hash_map<long, HuffmanNode> &huffmanCodes,
		long *&firstCode,
		long *&numl,
		long &maxLength,
		dense_hash_map<long, dense_hash_map<long, long>> &huffmanToSymbol,
		Conditions &c);
	void Huffman::fillBitset(int rawChunk, bitset<32> *chunk);
	void Huffman::fillBitset(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, bitset<32> *chunk);
	void Huffman::fillString(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, string &chunk);
	void Huffman::readFromGammaCodes(
		long symbolsToRead,
		ifstream &bitstream,
		GammaCode &gc,
		string &chunk,
		string &prefix,
		vector<long> &intValues);

	///<summary>
	///Decodes a dictionary from Huffman codes to indices into the dictionary of generations needed to decode a 
	///sequence of Huffman encoded characters.
	///</summary>
	///<param name="bitstream">Input: The stream of Huffman dictionary entries.</param>
	///<param name="firstCodes">Output: An array of values of the first code for each length of code constructed from Huffman dictionary headers.</param>
	///<param name="symbolIndices">Output: A table to look up dictionary indices from Huffman encoded characters.</param>
	void Huffman::decodeDictionary(
		ifstream &bitstream,
		long *&firstCodes,
		dense_hash_map<long, dense_hash_map<long, long>> &symbolIndices);

	///<summary>
	///Decodes a block of compressed Huffman codes based on the available Huffman dictionary, 
	///converting a code to an index into the dictionary of generations
	///</summary>
	///<param name="firstCode">Input: Array with values of the first code for each length of code starting from length 1.</param>
	///<param name="bitstream">Input: The stream of Huffman encoded characters.</param>
	///<param name="symbolIndices">Input: A table to look up dictionary indices from Huffman encoded characters.</param>
	///<param name="symbolIndexSequence">Output: The sequence of dictionary indices needed to reconstruct the original sequence.</param>
	void Huffman::decode(
		long *firstCode,
		ifstream &bitstream,
		dense_hash_map<long, dense_hash_map<long, long>> &symbolIndices,
		vector<long> &symbolIndexSequence);
};

