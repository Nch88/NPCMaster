#include "stdafx.h"
#include "Huffman.h"


Huffman::Huffman()
{
}


Huffman::~Huffman()
{
}

void Huffman::getFrequencies(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, int> & frequencies)
{
	for each (auto symbolRecord in sequenceArray)
	{
		frequencies[symbolRecord->symbol]++;
	}
}

bool Huffman::compareNode()
{

}

void Huffman::encode(vector<SymbolRecord*> & sequenceArray)
{
	unordered_map<unsigned int, int> frequencies;
	priority_queue<

	getFrequencies(sequenceArray, frequencies);
}