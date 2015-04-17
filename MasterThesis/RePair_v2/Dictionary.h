#pragma once

#include "stdafx.h"

class Dictionary
{
public:
	int Dictionary::findGenerations(
		unsigned long  symbol, 
		google::dense_hash_map<unsigned long , unsigned long >& symbolToGen,
		std::unordered_set<unsigned long >& terminals);

	///<summary>Create the symbol to generation table and the pair vectors.</summary>
	void Dictionary::createSupportStructures(
		std::vector<SymbolRecord*> & sequenceArray,
		std::unordered_set<unsigned long >& terminals,
		google::dense_hash_map<unsigned long , unsigned long >& symbolToGen,
		std::vector<std::vector<unsigned long *>>& pairVectors);

	int Dictionary::findTerminalIndex(vector<unsigned long >& terminals, unsigned long  key);

	int Dictionary::findNonTerminalIndex(vector<unsigned long *>& gen, unsigned long * key);

	///<summary>Replace the data in the phrase table with ordinal numbers.</summary>
	void Dictionary::switchToOrdinalNumbers(
		std::unordered_set<unsigned long >& terminals,
		google::dense_hash_map<unsigned long , unsigned long >& symbolToGen,
		vector<vector<unsigned long *>>& pairVectors,
		std::vector<unsigned long >& terminalVector);
	
	///<summary>Find the sequence of terminals corresponding to one non-terminal. Used by expandDictionary.</summary>
	///<param name="symbolIndex">Input: The index (in decodedPairs) of the current pair</param>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals</param>
	///<param name="expandedDict">Input: The dictionary currently being constructed</param>
	///<param name="finalOutput">Output: The sequence of terminals</param>
	void Dictionary::decodeSymbol(
		unsigned long  symbolIndex,
		vector<CompactPair> &decodedPairs,
		vector<unsigned long > &decodedTerms,
		dense_hash_map<unsigned long , string> &expandedDict,
		string &finalOutput);

	///<summary>Find the sequence of terminals corresponding to each non-terminal.</summary>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile.</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals.</param>
	///<param name="expandedDict">Output: A dictionary from each non-terminal to the corresponding string of terminals.</param>
	void Dictionary::expandDictionary(
		vector<CompactPair> &decodedPairs,
		vector<unsigned long > &decodedTerms,
		dense_hash_map<unsigned long , string> &expandedDict);
};