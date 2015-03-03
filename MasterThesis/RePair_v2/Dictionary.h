#pragma once

#include "stdafx.h"

class Dictionary
{
public:
	void generateCompactDictionary(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::unordered_set<unsigned int>& terminals,
		std::vector<CompactPair*>& pairVector,
		std::unordered_map<unsigned int, 
		std::unordered_map<unsigned int, unsigned int>*> &indices,
		unordered_map<unsigned int, unsigned int> *terminalIndices);
	void Dictionary::createFinalPairVector(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::vector<vector<CompactPair*>>& generationVectors,
		std::vector<CompactPair*>& pairVector,
		std::vector<unsigned int>& terminals,
		std::unordered_map<unsigned int, 
		std::unordered_map<unsigned int, unsigned int>*> &indices,
		unordered_map<unsigned int, unsigned int> *terminalIndices);
	void Dictionary::createGenerationVectors(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::vector<std::vector<CompactPair*>>& generationVectors);
};