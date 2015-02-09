#pragma once
class Huffman
{
public:
	Huffman();
	~Huffman();

	void Huffman::getFrequencies(
		vector<SymbolRecord*> & sequenceArray,
		unordered_map<unsigned int, int> & frequencies);
	void encode(vector<SymbolRecord*> & sequenceArray);
};

