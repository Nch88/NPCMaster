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

bool comPairP(unsigned long * p1, unsigned long * p2)
{
	//compare two pointers to pairs in the phrase table by comparing left symbols, then right symbols
	if (p1[0] < p2[0])
		return true;
	else if (p1[0] == p2[0])
		return p1[1] < p2[1];
	else
		return false;
}

int Dictionary::findGenerations(
	unsigned long  symbol, 
	dense_hash_map<unsigned long , unsigned long >& symbolToGen, 
	unordered_set<unsigned long >& terminals,
	Conditions &c)
{
	if (symbol < initialSymbolValue)
	{
		//This is a terminal. Add it to the term set and return 0.
		if (symbol != 0)
		{
			terminals.emplace(symbol);			
		}
			
		return 0;
	}
	else if (symbolToGen[symbol] != 0)
	{
		//We have seen this before
		return symbolToGen[symbol];
	}
	else
	{
		unsigned long * address = (unsigned long *)symbol;
		int d1 = findGenerations(address[0], symbolToGen, terminals, c);
		int d2 = findGenerations(address[1], symbolToGen, terminals, c);
		int gen = max(d1, d2) + 1;
		symbolToGen[symbol] = gen;
		if (c.test)
		{
			c.ts->addMemory("norDicSymbolToGen", c.ts->symbolToGenWords);
		}
		return gen;
	}
}

void Dictionary::createSupportStructures(
	vector<SymbolRecord*> & sequenceArray,
	unordered_set<unsigned long >& terminals,
	dense_hash_map<unsigned long ,unsigned long >& symbolToGen,
	vector<vector<unsigned long *>>& pairVectors,
	Conditions &c)
{
	//Create the symbol to gen table and count the number of generations
	int genCount = 0;
	unordered_set<unsigned long > roots;
	for each (SymbolRecord* record in sequenceArray)
	{
		if (record->symbol > initialSymbolValue)
		{
			roots.emplace(record->symbol);
			if (c.test)
				c.ts->addMemory("norDicRoots", c.ts->rootsWords);
		}
			
		else if (record->symbol != 0)
		{
			terminals.emplace(record->symbol);			
		}
			
	}
	
	for each (unsigned long  s in roots)
	{
		int d = findGenerations(s, symbolToGen, terminals, c);
		genCount = max(d, genCount);
	}

	if (c.test)
		c.ts->addMemory("norDicTerminals", terminals.size() * c.ts->terminalsWords);

	//Create pairVectors
	pairVectors.reserve(genCount);
	if (c.test)
	{
		c.ts->addMemory("norDicPairVectors", genCount);
	}
	for (int i = 0; i < genCount; ++i)
	{
		vector<unsigned long *> v;
		pairVectors.push_back(v);
	}
	for each (auto kvpair in symbolToGen)
	{
		//Push the address of each pair to their respective generation vectors
		pairVectors[kvpair.second - 1].push_back((unsigned long *)(kvpair.first));
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

bool greaterP(unsigned long* a, unsigned long* b)
{
	//True if the pair at a comes after the pair at b
	return (a[0] > b[0] || (a[0] == b[0] && a[1] > b[1]));
}

int bSearchP(vector<unsigned long *>& genVector, int first, int last, unsigned long * key)
{
	while (first <= last) {
		int mid = (first + last) / 2;  // compute mid point.
		if (greaterP(key,genVector[mid]))
			first = mid + 1;  // repeat search in top half.
		else if (greaterP(genVector[mid],key))
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

int Dictionary::findNonTerminalIndex(vector<unsigned long *>& gen, unsigned long * key)
{
	return bSearchP(gen, 0, gen.size() - 1, key);
}

void Dictionary::switchToOrdinalNumbers(
	unordered_set<unsigned long >& terminals,
	dense_hash_map<unsigned long , unsigned long >& symbolToGen,
	vector<vector<unsigned long *>>& pairVectors,
	vector<unsigned long >& terminalVector,
	Conditions &c)
{
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

	if (c.test)
	{
		if (c.ts->firstBlock)
		{
			if (terminalVector.size() > c.ts->s_nrOfTerminalsMax)
			{
				c.ts->s_nrOfTerminalsMax = terminalVector.size();
			}
			c.ts->s_nrOfTerminals += terminalVector.size();
		}
	}

	if (c.test)
	{
		c.ts->addMemory("norDicTerminalVector", terminalVector.size() * c.ts->terminalsWords);
	}

	//Replace the terminal symbols in the phrase table with ordinal numbers and sort them
	for (int i = 0; i < pairVectors[0].size(); ++i)
	{
		pairVectors[0][i][0] = findTerminalIndex(terminalVector, pairVectors[0][i][0]);
		pairVectors[0][i][1] = findTerminalIndex(terminalVector, pairVectors[0][i][1]);
		if (pairVectors[0][i][0] < 0 || pairVectors[0][i][1] < 0)
			//Error, one of the terms was not found
			throw new exception();
	}
	sort(pairVectors[0].begin(), pairVectors[0].end(), comPairP);

	//Make a vector of offsets
	vector<int> offsets;
	offsets.push_back(terminals.size());
	if (c.test)
	{
		c.ts->addMemory("norDicOffsets", terminals.size() * c.ts->offsetWords);
	}
	for (int i = 0; i < pairVectors.size() - 1; ++i)
	{
		offsets.push_back(offsets[i] + pairVectors[i].size());
		if (c.test)
		{
			c.ts->addMemory("norDicOffsets", c.ts->offsetWords);
		}
	}
		
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
			if (pairVectors[gen][i][0] > initialSymbolValue)
			{
				//Non-terminal
				int gen1 = symbolToGen[pairVectors[gen][i][0]];
				pairVectors[gen][i][0] = offsets[gen1 - 1] + findNonTerminalIndex(pairVectors[gen1 - 1], (unsigned long *)pairVectors[gen][i][0]);
			}
			else
			{
				//Terminal
				pairVectors[gen][i][0] = findTerminalIndex(terminalVector, pairVectors[gen][i][0]);
			}

			//Second symbol
			if (pairVectors[gen][i][1] > initialSymbolValue)
			{
				//Non-terminal
				int gen2 = symbolToGen[pairVectors[gen][i][1]];
				pairVectors[gen][i][1] = offsets[gen2 - 1] + findNonTerminalIndex(pairVectors[gen2 - 1], (unsigned long *)pairVectors[gen][i][1]);
			}
			else
			{
				//Terminal
				pairVectors[gen][i][1] = findTerminalIndex(terminalVector, pairVectors[gen][i][1]);
			}

			if (pairVectors[gen][i][0] < 0 || pairVectors[gen][i][1] < 0)
				//Error, one of the symbols was not found
				throw new exception();
		}
		sort(pairVectors[gen].begin(), pairVectors[gen].end(), comPairP);
	}

	if (c.test)
	{
		if (c.ts->firstBlock)
		{
			c.ts->s_avgNrOfPhrases = c.ts->s_nrOfPhrases / c.ts->s_nrOfGenerations;
		}		
	}
}

void Dictionary::createDictionary(
	vector<SymbolRecord*> & sequenceArray,
	unordered_set<unsigned long >& terminals,
	dense_hash_map<unsigned long, unsigned long >& symbolToGen,
	vector<vector<unsigned long *>>& pairVectors,
	vector<unsigned long>& terminalVector,
	Conditions &c)
{
	createSupportStructures(sequenceArray, terminals, symbolToGen, pairVectors, c);

	if (c.test)
	{
		if (c.ts->firstBlock)
		{
			c.ts->m_norDic_supportStructures_total += c.ts->m_norDic_total;
			c.ts->m_norDic_total -= c.ts->m_norDic_roots_max;
		}		
	}

	switchToOrdinalNumbers(terminals, symbolToGen, pairVectors, terminalVector, c);
}


void Dictionary::decodeSymbol(
	unsigned long  symbolIndex, 
	vector<CompactPair> &decodedPairs,
	vector<unsigned long > &decodedTerms,
	dense_hash_map<unsigned long , string> &expandedDict,
	string &finalOutput)
{
	//Handle left part
	unsigned long  indexLeft = decodedPairs[symbolIndex].leftSymbol;
	if (indexLeft < decodedTerms.size())
		finalOutput += decodedTerms[indexLeft];
	else
	{
		//Decode left symbol
		finalOutput += expandedDict[indexLeft - decodedTerms.size()];
	}

	//Handle right part
	unsigned long  indexRight = decodedPairs[symbolIndex].rightSymbol;
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
	vector<unsigned long > &decodedTerms, 
	dense_hash_map<unsigned long , string> &expandedDict)
{
	string s;
	for (unsigned long  i = 0; i < decodedPairs.size(); ++i)
	{
		s.assign("");
		decodeSymbol(i, decodedPairs, decodedTerms, expandedDict, s);
		expandedDict[i].assign(s);
	}
}