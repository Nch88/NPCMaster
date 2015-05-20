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
	dense_hash_map<unsigned long, Pair>& dictionary,
	unordered_set<unsigned long>& terminals,
	vector<unsigned long>& terminalVector,
	vector<vector<unsigned long>>& pairVectors,
	dense_hash_map<unsigned long, unsigned long> &indices,
	Conditions &c)
{
	//Split dictionary by generation
	createGenerationVectors2(dictionary, pairVectors, c);

	switchToOrdinalNumbers(terminals, dictionary, pairVectors, terminalVector, indices, c);
}

void Dictionary::createGenerationVectors2(
	dense_hash_map<unsigned long, Pair>& dictionary,
	vector<vector<unsigned long>>& generationVectors,
	Conditions &c)
{
	//Distribute pairs in vectors
	for each (std::pair<const unsigned long, Pair> p in dictionary)
	{
		//Expand the outer vector if necessary
		while (p.second.generation > generationVectors.size())
		{
			vector<unsigned long> v;
			generationVectors.push_back(v);
		}

		//Add this pair to a vector
		generationVectors[p.second.generation - 1].push_back(p.first);

		if (c.test)
		{
			c.ts->addMemory("norDicPairVectors", c.ts->pairVectorsWords);
		}
	}
}

int bSearch(vector<unsigned long >& terminals, int first, int last, unsigned long  key)
{
	while (first <= last) {
		int mid = (first + last) / 2;  // compute mid point.
		if (key > terminals[mid])
			first = mid + 1;  // repeat search in top half.
		else if (key < terminals[mid])
			last = mid - 1; // repeat search in bottom half.
		else
			return mid;     // found it. return position /////
	}
	return -(first + 1);    // failed to find key
}

int bSearchP(vector<CompactPair>& genVector, int first, int last, CompactPair key)
{
	while (first <= last) {
		int mid = (first + last) / 2;  // compute mid point.
		if (comPair(genVector[mid],key)) //If key > mid
			first = mid + 1;  // repeat search in top half.
		else if (comPair(key, genVector[mid]))
			last = mid - 1; // repeat search in bottom half.
		else
			return mid;     // found it. return position /////
	}
	return -(first + 1);    // failed to find key
}

int Dictionary::findTerminalIndex(vector<unsigned long >& terminals, unsigned long  key)
{
	return bSearch(terminals, 0, terminals.size() - 1, key);
}

int Dictionary::findNonTerminalIndex(vector<CompactPair>& gen, CompactPair& key)
{
	return bSearchP(gen, 0, gen.size() - 1, key);
}

void Dictionary::switchToOrdinalNumbers(
	unordered_set<unsigned long >& terminals,
	dense_hash_map<unsigned long, Pair>& dictionary,
	vector<vector<unsigned long>>& pairVectors,
	vector<unsigned long >& terminalVector,
	dense_hash_map<unsigned long, unsigned long> &indices,
	Conditions &c)
{
	terminalVector.assign(terminals.begin(), terminals.end());
	std::sort(terminalVector.begin(), terminalVector.end());

	if (c.test)
	{
		c.ts->addMemory("norDicTerminalVector", terminalVector.size() * c.ts->terminalsWords);
	}

	//Replace the terminal symbols in the dictionary with ordinal numbers and sort them
	for (int i = 0; i < pairVectors[0].size(); ++i)
	{
		dictionary[pairVectors[0][i]].leftSymbol = findTerminalIndex(terminalVector, dictionary[pairVectors[0][i]].leftSymbol);
		dictionary[pairVectors[0][i]].rightSymbol = findTerminalIndex(terminalVector, dictionary[pairVectors[0][i]].rightSymbol);
	}

	ComPairD cpd;
	cpd.dic = &dictionary;
	std::sort(pairVectors[0].begin(), pairVectors[0].end(), cpd);

	unsigned long offset = terminals.size();

	for (int i = 0; i < pairVectors[0].size(); ++i)
	{
		indices[pairVectors[0][i]] = offset + i;
		if (c.test)
		{
			c.ts->addMemory("norDicIndices", c.ts->indicesWords);
		}
	}

	offset += pairVectors[0].size();

	if (c.test)
	{
		if (c.ts->firstBlock)
		{
			if (pairVectors.size() > c.ts->s_nrOfGenerationsMax)
			{
				c.ts->s_nrOfGenerationsMax = pairVectors.size();
			}
			c.ts->s_nrOfGenerations += pairVectors.size();
		}
	}

	for (int gen = 1; gen < pairVectors.size(); ++gen)
	{
		for (int i = 0; i < pairVectors[gen].size(); ++i)
		{
			if (c.test)
			{
				if (c.ts->firstBlock)
				{
					c.ts->s_nrOfPhrases++;
					if (pairVectors[gen].size() > c.ts->s_largestGenerationCountMax)
					{
						c.ts->s_largestGenerationCountMax = pairVectors[gen].size();
						c.ts->s_largestGenerationMax = gen;
					}
					if (pairVectors[gen].size() > c.ts->s_largestGenerationCount)
					{
						c.ts->s_largestGenerationCount = pairVectors[gen].size();
						c.ts->s_largestGeneration = gen;
					}
				}
			}

			//First symbol
			if (dictionary[pairVectors[gen][i]].leftSymbol >= initialSymbolValue)
			{
				//Non-terminal
				
				dictionary[pairVectors[gen][i]].leftSymbol = indices[dictionary[pairVectors[gen][i]].leftSymbol];
				
			}
			else
			{
				//Terminal
				
				dictionary[pairVectors[gen][i]].leftSymbol = findTerminalIndex(terminalVector, dictionary[pairVectors[gen][i]].leftSymbol);
				
			}

			//Second symbol
			if (dictionary[pairVectors[gen][i]].rightSymbol >= initialSymbolValue)
			{
				//Non-terminal
				dictionary[pairVectors[gen][i]].rightSymbol = indices[dictionary[pairVectors[gen][i]].rightSymbol];
				
			}
			else
			{
				//Terminal
				
				dictionary[pairVectors[gen][i]].rightSymbol = findTerminalIndex(terminalVector, dictionary[pairVectors[gen][i]].rightSymbol);
			
			}

			if (dictionary[pairVectors[gen][i]].leftSymbol < 0 || dictionary[pairVectors[gen][i]].rightSymbol < 0)
				//Error, one of the symbols was not found
				throw new exception();
		}
		std::sort(pairVectors[gen].begin(), pairVectors[gen].end(), cpd);

		for (int i = 0; i < pairVectors[gen].size(); ++i)
		{
			indices[pairVectors[gen][i]] = offset + i;
			if (c.test)
			{
				c.ts->addMemory("norDicIndices", c.ts->indicesWords);
			}
		}

		offset += pairVectors[gen].size();
	}

	if (c.test)
	{
		if (c.ts->firstBlock)
		{
			c.ts->s_avgNrOfPhrases = c.ts->s_nrOfPhrases / c.ts->s_nrOfGenerations;
		}
	}
}

void Dictionary::decodeSymbol(
	long symbolIndex, 
	vector<CompactPair> &decodedPairs,
	vector<unsigned long> &decodedTerms,
	dense_hash_map<unsigned long, string> &expandedDict,
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
	vector<unsigned long> &decodedTerms,
	dense_hash_map<unsigned long, string> &expandedDict)
{
	string s;
	for (long i = 0; i < decodedPairs.size(); ++i)
	{
		s.assign("");
		decodeSymbol(i, decodedPairs, decodedTerms, expandedDict, s);
		expandedDict[i].assign(s);
	}
}