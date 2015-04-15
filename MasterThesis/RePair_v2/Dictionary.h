#pragma once

#include "stdafx.h"

//NamedPair is for used by the createFinalPairVectors function.
struct NamedPair
{
	long leftSymbol;
	long rightSymbol;
	long nameLeft;
	long nameRight;
};

class Dictionary
{
public:
	int Dictionary::findGenerations(
		long symbol, 
		dense_hash_map<long, long>& symbolToGen,
		unordered_set<long>& terminals);

	///<summary>Create the symbol to generation table and the pair vectors.</summary>
	void Dictionary::createSupportStructures(
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<long>& terminals,
		dense_hash_map<long, long>& symbolToGen,
		vector<vector<long*>>& pairVectors);
	
	///<summary>Find the sequence of terminals corresponding to one non-terminal. Used by expandDictionary.</summary>
	///<param name="symbolIndex">Input: The index (in decodedPairs) of the current pair</param>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals</param>
	///<param name="expandedDict">Input: The dictionary currently being constructed</param>
	///<param name="finalOutput">Output: The sequence of terminals</param>
	void Dictionary::decodeSymbol(
		long symbolIndex,
		vector<CompactPair> &decodedPairs,
		vector<long> &decodedTerms,
		dense_hash_map<long, string> &expandedDict,
		string &finalOutput);

	///<summary>Find the sequence of terminals corresponding to each non-terminal.</summary>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile.</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals.</param>
	///<param name="expandedDict">Output: A dictionary from each non-terminal to the corresponding string of terminals.</param>
	void Dictionary::expandDictionary(
		vector<CompactPair> &decodedPairs,
		vector<long> &decodedTerms,
		dense_hash_map<long, string> &expandedDict);
};