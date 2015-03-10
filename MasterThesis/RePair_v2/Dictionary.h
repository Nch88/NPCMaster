#pragma once

#include "stdafx.h"

class Dictionary
{
public:
	void generateCompactDictionary(
		std::unordered_map<long, Pair>& dictionary,
		std::unordered_set<long>& terminals,
		std::vector<vector<CompactPair>>& pairVectors,
		std::unordered_map<long, std::unordered_map<long, long>> &indices,
		std::unordered_map<long, long> &terminalIndices,
		std::vector<std::vector<CompactPair>> &generationVectors);
	void Dictionary::createFinalPairVectors(
		std::unordered_map<long, Pair>& dictionary,
		std::vector<std::vector<CompactPair>>& generationVectors,
		std::vector<std::vector<CompactPair>>& pairVectors,
		std::vector<long>& terminals,
		std::unordered_map<long,std::unordered_map<long, long>> &indices,
		std::unordered_map<long, long> &terminalIndices);
	void Dictionary::createGenerationVectors(
		std::unordered_map<long, Pair>& dictionary,
		std::vector<std::vector<CompactPair>>& generationVectors);
	void Dictionary::decodeSymbol(
		long &symbolIndex,
		vector<CompactPair> &decodedPairs,
		vector<long> &decodedTerms,
		string &finalOutput);
	void Dictionary::expandDictionary(
		vector<CompactPair> &decodedPairs,
		vector<long> &decodedTerms,
		unordered_map<long, string> &expandedDict);
};