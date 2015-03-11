#include "stdafx.h"

bool comPair(CompactPair fst, CompactPair snd)
{
	//compare two pairs by comparing left symbols, then right symbols
	if (fst.leftSymbol < snd.leftSymbol)
		return true;
	else if (fst.leftSymbol == snd.leftSymbol)
		return fst.rightSymbol < snd.rightSymbol;
	else
		return false;
}

//This is the main dictionary function. It fills the pair vector based on dictionary + terminals.
void Dictionary::generateCompactDictionary(
	dense_hash_map<long, Pair>& dictionary,
	unordered_set<long>& terminals,
	vector<vector<CompactPair>>& pairVectors,
	dense_hash_map<long, dense_hash_map<long, long>> &indices,
	dense_hash_map<long, long> &terminalIndices,
	vector<vector<CompactPair>> &generationVectors)
{
	vector<long> terminalVector;
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

	//Split map by generation
	createGenerationVectors(dictionary, generationVectors);

	createFinalPairVectors(dictionary, generationVectors, pairVectors, terminalVector, indices, terminalIndices);
}

void Dictionary::createFinalPairVectors(
	dense_hash_map<long, Pair>& dictionary,
	vector<vector<CompactPair>>& generationVectors,
	vector<vector<CompactPair>>& pairVectors,
	vector<long>& terminals,
	dense_hash_map<long, dense_hash_map<long, long>> &indices,
	dense_hash_map<long, long> &terminalIndices)
{
	//Record indices of terminals
	for (int i = 0; i < terminals.size(); ++(i))
	{
		terminalIndices[terminals[i]] = i;
	}

	int offset = terminals.size();

	//For each generation
	for (int gen = 0; gen < generationVectors.size(); ++gen)
	{
		vector<CompactPair> vec;
		pairVectors.push_back(vec);
		for (int j = 0; j < generationVectors[gen].size(); ++j)
		{
			//Find the new indices of the two symbols in this pair
			long leftSymbol = generationVectors[gen][j].leftSymbol;

			long leftIndex;

			//Check for terminal symbol or composite symbol
			if (leftSymbol < initialSymbolValue) //Terminal
			{
				leftIndex = terminalIndices[leftSymbol];
			}
			else //Composite
			{
				long leftSymbolLeftPart = dictionary[leftSymbol].leftSymbol;
				long leftSymbolRightPart = dictionary[leftSymbol].rightSymbol;
				leftIndex = indices[leftSymbolLeftPart][leftSymbolRightPart];
			}

			long rightSymbol = generationVectors[gen][j].rightSymbol;
			long rightIndex;

			//Check for terminal symbol or composite symbol
			if (rightSymbol < initialSymbolValue) //Terminal
			{
				rightIndex = terminalIndices[rightSymbol];
			}
			else //Composite
			{
				long rightSymbolLeftPart = dictionary[rightSymbol].leftSymbol;
				long rightSymbolRightPart = dictionary[rightSymbol].rightSymbol;
				rightIndex = indices[rightSymbolLeftPart][rightSymbolRightPart];
			}

			//Make a pair out of the indices we found, then push it to the vector
			CompactPair p(leftIndex, rightIndex);
			pairVectors[gen].push_back(p);
		}

		////Figure out the dictionary names of each pair
		//dense_hash_map<long, dense_hash_map<long, long>> dictionaryNames;
		//dictionaryNames.set_empty_key(-1);
		//dictionaryNames.set_deleted_key(-2);
		//for (int i = 0; i < pairVectors[gen].size(); ++i)
		//{
		//	CompactPair temp(pairVectors[gen][i].leftSymbol, pairVectors[gen][i].rightSymbol);
		//	dictionaryNames[]
		//}

		//Sort the new vector
		sort(pairVectors[gen].begin(), pairVectors[gen].end(),comPair);

		//Record the new indices
		for (int i = 0; i < pairVectors[gen].size(); ++i)
		{
			if (indices[pairVectors[gen][i].leftSymbol].empty())
			{
				indices[pairVectors[gen][i].leftSymbol].set_empty_key(-1);
				indices[pairVectors[gen][i].leftSymbol].set_deleted_key(-2);
			}
			indices[pairVectors[gen][i].leftSymbol][pairVectors[gen][i].rightSymbol] = offset + i;
		}

		//Update the offset
		offset += pairVectors[gen].size();
	}
}

void Dictionary::createGenerationVectors(
	dense_hash_map<long, Pair>& dictionary,
	vector<vector<CompactPair>>& generationVectors)
{
	//Distribute pairs in vectors
	for each (std::pair<const long, Pair> p in dictionary)
	{
		//Expand the outer vector if necessary
		while (p.second.generation > generationVectors.size())
		{
			vector<CompactPair> v;
			generationVectors.push_back(v);
		}

		//Add this pair to a vector
		CompactPair cp(p.second.leftSymbol, p.second.rightSymbol);
		generationVectors[p.second.generation - 1].push_back(cp);
	}
}

void Dictionary::decodeSymbol(
	long &symbolIndex, 
	vector<CompactPair> &decodedPairs,
	vector<long> &decodedTerms,
	string &finalOutput)
{
	if (symbolIndex < decodedTerms.size())
		finalOutput += decodedTerms[symbolIndex];
	else
	{
		//Recursively decode left and right symbol
		decodeSymbol(decodedPairs[symbolIndex - decodedTerms.size()].leftSymbol, decodedPairs, decodedTerms, finalOutput);
		decodeSymbol(decodedPairs[symbolIndex - decodedTerms.size()].rightSymbol, decodedPairs, decodedTerms, finalOutput);
	}
}

void Dictionary::expandDictionary(
	vector<CompactPair> &decodedPairs, 
	vector<long> &decodedTerms, 
	dense_hash_map<long, string> &expandedDict)
{
	string s;
	for (long i = 0; i < decodedPairs.size(); ++i)
	{
		s.assign("");
		decodeSymbol(i, decodedPairs, decodedTerms, s);
		expandedDict[i].assign(s);
	}
}