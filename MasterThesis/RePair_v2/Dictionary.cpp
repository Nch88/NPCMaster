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
	unordered_map<long, Pair>& dictionary,
	unordered_set<long>& terminals,
	vector<vector<CompactPair>>& pairVectors,
	unordered_map<long, unordered_map<long, long>> &indices,
	unordered_map<long, long> &terminalIndices,
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
	unordered_map<long, Pair>& dictionary,
	vector<vector<CompactPair>>& generationVectors,
	vector<vector<CompactPair>>& pairVectors,
	vector<long>& terminals,
	unordered_map<long, unordered_map<long, long>> &indices,
	unordered_map<long, long> &terminalIndices)
{
	for (int i = 0; i < terminals.size(); ++(i))
	{
		(terminalIndices)[terminals[i]] = i;
	}
	//Generation 1
	vector<CompactPair> vec;
	pairVectors.push_back(vec);
	for (int i = 0; i < generationVectors[0].size(); ++(i))
	{
		//Find the new indices of the two symbols in this pair
		long leftIndex = ((terminalIndices)[(generationVectors[0])[i].leftSymbol]);
		long rightIndex = ((terminalIndices)[(generationVectors[0])[i].rightSymbol]);

		//Make a pair out of the indices we found, then push it to the vector
		CompactPair p(leftIndex, rightIndex);
		pairVectors[0].push_back(p);

		//Record the index of this symbol
		((indices)[(generationVectors[0])[i].leftSymbol])[(generationVectors[0])[i].rightSymbol] = i + terminals.size();
	}
	//Generation 2+
	int offset = terminals.size() + generationVectors[0].size();
	if (generationVectors.size() > 1)
	{
		for (int i = 1; i < generationVectors.size(); ++i)
		{
			vector<CompactPair> vec;
			pairVectors.push_back(vec);
			for (int j = 0; j < generationVectors[i].size(); ++j)
			{
				//Find the new indices of the two symbols in this pair
				long leftSymbol = (generationVectors[i])[j].leftSymbol;

				long leftIndex;

				//Check for terminal symbol or composite symbol
				if (leftSymbol < initialSymbolValue) //Terminal
				{
					leftIndex = (terminalIndices)[leftSymbol];
				}
				else //Composite
				{
					long leftSymbolLeftPart = dictionary[leftSymbol].leftSymbol;
					long leftSymbolRightPart = dictionary[leftSymbol].rightSymbol;
					leftIndex = ((indices)[leftSymbolLeftPart])[leftSymbolRightPart];
				}

				long rightSymbol = (generationVectors[i])[j].rightSymbol;
				long rightIndex;

				//Check for terminal symbol or composite symbol
				if (rightSymbol < initialSymbolValue) //Terminal
				{
					rightIndex = (terminalIndices)[rightSymbol];
				}
				else //Composite
				{
					long rightSymbolLeftPart = dictionary[rightSymbol].leftSymbol;
					long rightSymbolRightPart = dictionary[rightSymbol].rightSymbol;
					rightIndex = ((indices)[rightSymbolLeftPart])[rightSymbolRightPart];
				}

				//Make a pair out of the indices we found, then push it to the vector
				CompactPair p(leftIndex, rightIndex);
				pairVectors[i].push_back(p);

				//Record the index of this symbol
				((indices)[leftSymbol])[rightSymbol] = offset + j;
			}
			//Update the offset
			offset += generationVectors[i].size();
		}
	}
}

void Dictionary::createGenerationVectors(
	unordered_map<long, Pair>& dictionary,
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

	//Sort the vectors
	for (int i = 0; i < generationVectors.size(); i++)
	{
		sort(generationVectors[i].begin(), generationVectors[i].end(), comPair);
	}
}

void Dictionary::decodeSymbol(
	long &symbolIndex, 
	vector<CompactPair> &decodedPairs,
	vector<long> &decodedTerms,
	string &finalOutput)
{
	if (symbolIndex < initialSymbolValue)
		finalOutput += decodedTerms[symbolIndex];
	else
	{
		//Recursively decode left and right symbol
		decodeSymbol(decodedPairs[symbolIndex].leftSymbol, decodedPairs, decodedTerms, finalOutput);
		decodeSymbol(decodedPairs[symbolIndex].rightSymbol, decodedPairs, decodedTerms, finalOutput);
	}
}