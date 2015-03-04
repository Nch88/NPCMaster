#pragma once

#include "stdafx.h"

class Dictionary
{
public:
	void generateCompactDictionary(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::unordered_set<unsigned int>& terminals,
		std::vector<vector<CompactPair*>*>& pairVectors,
		std::unordered_map<unsigned int, std::unordered_map<unsigned int, unsigned int>*> &indices,
		std::unordered_map<unsigned int, unsigned int> *terminalIndices,
		std::vector<std::vector<CompactPair*>*> generationVectors);
	void Dictionary::createFinalPairVectors(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::vector<std::vector<CompactPair*>*>& generationVectors,
		std::vector<std::vector<CompactPair*>*>& pairVectors,
		std::vector<unsigned int>& terminals,
		std::unordered_map<unsigned int,std::unordered_map<unsigned int, unsigned int>*> &indices,
		std::unordered_map<unsigned int, unsigned int> *terminalIndices);
	void Dictionary::createGenerationVectors(
		std::unordered_map<unsigned int, Pair>& dictionary,
		std::vector<std::vector<CompactPair*>*>& generationVectors);
};