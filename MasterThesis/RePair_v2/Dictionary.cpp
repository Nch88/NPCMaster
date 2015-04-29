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

bool comPairN(NamedPair fst, NamedPair snd)
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
	vector<long>& terminalVector,
	vector<vector<CompactPair>>& pairVectors,
	dense_hash_map<long, dense_hash_map<long, long>> &indices,
	dense_hash_map<long, long> &terminalIndices,
	Conditions &c)
{
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

	if (c.test)
	{
		c.ts->addMemory("norDicTerminalVector", terminalVector.size() * c.ts->terminalsWords);
	}

	//Split map by generation
	createGenerationVectors(dictionary, pairVectors, c);

	createFinalPairVectors(dictionary, terminalVector, pairVectors, indices, terminalIndices, c);
}

void Dictionary::createFinalPairVectors(
	dense_hash_map<long, Pair>& dictionary,
	vector<long>& terminals,
	vector<vector<CompactPair>>& pairVectors,
	dense_hash_map<long, dense_hash_map<long, long>> &indices,
	dense_hash_map<long, long> &terminalIndices,
	Conditions &c)
{
	//Record indices of terminals
	for (int i = 0; i < terminals.size(); ++(i))
	{
		terminalIndices[terminals[i]] = i;
		if (c.test)
		{
			c.ts->addMemory("norDicTerminalIndices", c.ts->terminalIndicesWords);
		}
	}

	int offset = terminals.size();

	//For each generation
	for (int gen = 0; gen < pairVectors.size(); ++gen)
	{
		vector<NamedPair> vec;
		for (int j = 0; j < pairVectors[gen].size(); ++j)
		{
			//Find the new indices of the two symbols in this pair
			long leftSymbol = pairVectors[gen][j].leftSymbol;

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

			long rightSymbol = pairVectors[gen][j].rightSymbol;
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

			//Make a pair out of the indices we found
			NamedPair p = { leftIndex, rightIndex, leftSymbol, rightSymbol };
			vec.push_back(p);

			if (c.test)
			{
				c.ts->addMemory("norDicNamedPairVector", c.ts->namedPairWords);
			}
		}

		//Sort the new vector
		sort(vec.begin(), vec.end(), comPairN);

		//Change the values in pairVectors to the new indices
		for (int i = 0; i < vec.size(); ++i)
		{
			pairVectors[gen][i].leftSymbol = vec[i].leftSymbol;
			pairVectors[gen][i].rightSymbol = vec[i].rightSymbol;
		}

		//Record the new indices
		for (int i = 0; i < vec.size(); ++i)
		{
			if (indices[vec[i].nameLeft].empty())
			{
				indices[vec[i].nameLeft].set_empty_key(-1);
				indices[vec[i].nameLeft].set_deleted_key(-2);
			}
			indices[vec[i].nameLeft][vec[i].nameRight] = offset + i;
			if (c.test)
			{
				c.ts->addMemory("norDicIndices", c.ts->indicesWords);
			}
		}

		//Update the offset
		offset += pairVectors[gen].size();
	}
}

void Dictionary::createGenerationVectors(
	dense_hash_map<long, Pair>& dictionary,
	vector<vector<CompactPair>>& generationVectors,
	Conditions &c)
{
	//Distribute pairs in vectors
	for each (std::pair<const long, Pair> p in dictionary)
	{
		//Expand the outer vector if necessary
		while (p.second.generation > generationVectors.size())
		{
			vector<CompactPair> v;
			generationVectors.push_back(v);
			if (c.test)
			{
				c.ts->addMemory("norDicPairVector", c.ts->pairVectorsOuterWords);
			}
		}

		//Add this pair to a vector
		CompactPair cp(p.second.leftSymbol, p.second.rightSymbol);
		generationVectors[p.second.generation - 1].push_back(cp);
		if (c.test)
		{
			c.ts->addMemory("norDicPairVector", c.ts->pairVectorsInnerWords);
		}
	}
}

void Dictionary::decodeSymbol(
	long symbolIndex, 
	vector<CompactPair> &decodedPairs,
	vector<long> &decodedTerms,
	dense_hash_map<long, string> &expandedDict,
	string &finalOutput)
{
	//Handle left part
	long indexLeft = decodedPairs[symbolIndex].leftSymbol;
	if (indexLeft < decodedTerms.size())
		finalOutput += decodedTerms[indexLeft];
	else
	{
		//Decode left symbol
		finalOutput += expandedDict[indexLeft - decodedTerms.size()];
	}

	//Handle right part
	long indexRight = decodedPairs[symbolIndex].rightSymbol;
	if (indexRight < decodedTerms.size())
		finalOutput += decodedTerms[indexRight];
	else
	{
		//Decode right symbol
		finalOutput += expandedDict[indexRight - decodedTerms.size()];
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
		decodeSymbol(i, decodedPairs, decodedTerms, expandedDict, s);
		expandedDict[i].assign(s);
	}
}