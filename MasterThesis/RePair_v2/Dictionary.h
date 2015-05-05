#pragma once

#include "stdafx.h"

//NamedPair is for used by the createFinalPairVectors function.
struct NamedPair
{
	unsigned long leftSymbol;
	unsigned long rightSymbol;
	unsigned long nameLeft;
	unsigned long nameRight;
};

struct ComPairD
{
	dense_hash_map<unsigned long, Pair>* dic;

	bool operator() (unsigned long fst, unsigned long snd)
	{
		if ((*dic)[fst].leftSymbol < (*dic)[snd].leftSymbol)
			return true;
		else if ((*dic)[fst].leftSymbol == (*dic)[snd].leftSymbol)
			return (*dic)[fst].rightSymbol < (*dic)[snd].rightSymbol;
		else
			return false;
	}
};

class Dictionary
{
public:
	///<summary>
	///Convert a RePair dictionary to a vector of pairs for each generation. 
	///Each element of a pair is an index into either the pair vectors themselves or the sorted list of terminals.
	///In this form the dictionary can be stored efficiently using zero-order gamma codes.
	///</summary>
	///<param name="dictionary">Input: The dictionary created by RePair.</param>
	///<param name="terminals">Input: The set of terminals.</param>
	///<param name="terminals">Output: A sorted vector of the terminals.</param>
	///<param name="pairVectors">Output: The pairs of indices, split into seperate generations.</param>
	///<param name="indices">Output: The index of each pair in pairVectors.</param>
	///<param name="terminalIndices">Output: The index of each terminal.</param>
	///<param name="generationVectors">Output: The output from createGenerationVectors.</param>
	void generateCompactDictionary(
		google::dense_hash_map<unsigned long, Pair>& dictionary,
		std::unordered_set<unsigned long>& terminals,
		std::vector<unsigned long>& terminalVector,
		std::vector<vector<unsigned long>>& pairVectors,
		google::dense_hash_map<unsigned long, unsigned long> &indices,
		Conditions &c);

	///<summary>Split the entries in a RePair dictionary into generations</summary>
	///<param name="dictionary">Input: The dictionary created by RePair</param>
	///<param name="generationVectors">Output: The pairs of symbols that each dictionary entry corresponds to, 
	///split into a vector for each generation</param>
	void Dictionary::createGenerationVectors2(
		dense_hash_map<unsigned long, Pair>& dictionary,
		vector<vector<unsigned long>>& generationVectors,
		Conditions &c);
	
	int Dictionary::findTerminalIndex(vector<unsigned long >& terminals, unsigned long  key);

	int Dictionary::findNonTerminalIndex(vector<CompactPair>& gen, CompactPair& key);

	void Dictionary::switchToOrdinalNumbers(
		unordered_set<unsigned long >& terminals,
		dense_hash_map<unsigned long, Pair>& dictionary,
		vector<vector<unsigned long>>& pairVectors,
		vector<unsigned long >& terminalVector,
		dense_hash_map<unsigned long, unsigned long> &indices,
		Conditions &c);

	///<summary>Find the sequence of terminals corresponding to one non-terminal. Used by expandDictionary.</summary>
	///<param name="symbolIndex">Input: The index (in decodedPairs) of the current pair</param>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals</param>
	///<param name="expandedDict">Input: The dictionary currently being constructed</param>
	///<param name="finalOutput">Output: The sequence of terminals</param>
	void Dictionary::decodeSymbol(
		long symbolIndex,
		vector<CompactPair> &decodedPairs,
		vector<unsigned long> &decodedTerms,
		dense_hash_map<unsigned long, string> &expandedDict,
		string &finalOutput);

	///<summary>Find the sequence of terminals corresponding to each non-terminal.</summary>
	///<param name="decodedPairs">Input: The vector of pairs produced by GammaCode::decodeDictionaryFile.</param>
	///<param name="decodedTerms">Input: A sorted vector of all the terminals.</param>
	///<param name="expandedDict">Output: A dictionary from each non-terminal to the corresponding string of terminals.</param>
	void Dictionary::expandDictionary(
		vector<CompactPair> &decodedPairs,
		vector<unsigned long> &decodedTerms,
		dense_hash_map<unsigned long, string> &expandedDict);
};