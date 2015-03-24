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
	///<summary>
	///Convert a RePair dictionary to a vector of pairs for each generation. 
	///Each element of a pair is an index into either the pair vectors themselves or the sorted list of terminals.
	///In this form the dictionary can be stored efficiently using zero-order gamma codes.
	///</summary>
	///<param name="dictionary">Input: The dictionary created by RePair.</param>
	///<param name="terminals">Input: The set of terminals</param>
	///<param name="pairVectors">Output: The pairs of indices, split into seperate generations.</param>
	///<param name="indices">Output: The index of each pair in pairVectors</param>
	///<param name="terminalIndices">Output: The index of each terminal</param>
	///<param name="generationVectors">Output: The output from createGenerationVectors.</param>
	void generateCompactDictionary(
		google::dense_hash_map<long, Pair>& dictionary,
		std::unordered_set<long>& terminals,
		std::vector<vector<CompactPair>>& pairVectors,
		google::dense_hash_map<long, google::dense_hash_map<long, long>> &indices,
		google::dense_hash_map<long, long> &terminalIndices);

	///<summary>Change each pair in each generation to be a pair of indices into a hypothetical sequence consisting
	/// of all the terminals followed by all the pairs of the previous generation, each generation sorted by their left elements.</summary>
	///<param name="dictionary">Input: The dictionary created by RePair.</param>
	///<param name="terminals">Input: A sorted vector of terminals</param>
	///<param name="pairVectors">Output: The new pairs of indices, still split into seperate generations.</param>
	///<param name="indices">Output: The index of each pair in pairVectors</param>
	///<param name="terminalIndices">Output: The index of each terminal</param>
	void Dictionary::createFinalPairVectors(
		google::dense_hash_map<long, Pair>& dictionary,
		std::vector<long>& terminals,
		std::vector<std::vector<CompactPair>>& pairVectors,
		google::dense_hash_map<long, google::dense_hash_map<long, long>> &indices,
		google::dense_hash_map<long, long> &terminalIndices);

	///<summary>Split the entries in a RePair dictionary into generations</summary>
	///<param name="dictionary">Input: The dictionary created by RePair</param>
	///<param name="generationVectors">Output: The pairs of symbols that each dictionary entry corresponds to, 
	///split into a vector for each generation</param>
	void Dictionary::createGenerationVectors(
		google::dense_hash_map<long, Pair>& dictionary,
		std::vector<std::vector<CompactPair>>& generationVectors);
	
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