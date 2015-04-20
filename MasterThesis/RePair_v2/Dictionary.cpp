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
	unordered_set<unsigned long >& terminals)
{
	if (symbol < initialSymbolValue)
	{
		//This is a terminal. Add it to the term set and return 0.
		terminals.emplace(symbol);
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
		int d1 = findGenerations(address[0], symbolToGen, terminals);
		int d2 = findGenerations(address[1], symbolToGen, terminals);
		int gen = max(d1, d2) + 1;
		symbolToGen[symbol] = gen;
		return gen;
	}
}

void Dictionary::createSupportStructures(
	vector<SymbolRecord*> & sequenceArray,
	unordered_set<unsigned long >& terminals,
	dense_hash_map<unsigned long ,unsigned long >& symbolToGen,
	vector<vector<unsigned long *>>& pairVectors)
{
	//Create the symbol to gen table and count the number of generations
	int genCount = 0;
	unordered_set<unsigned long > roots;
	for each (SymbolRecord* record in sequenceArray)
	{
		if (record->symbol > initialSymbolValue)
			roots.emplace(record->symbol);
		else
			terminals.emplace(record->symbol);
	}
	//roots should be H + A + F + E
	for each (unsigned long  s in roots)
	{
		int d = findGenerations(s, symbolToGen, terminals);
		genCount = max(d, genCount);
	}

	//Create pairVectors
	pairVectors.reserve(genCount);
	for (int i = 0; i < genCount; ++i)
	{
		vector<unsigned long *> v;
		pairVectors.push_back(v);
	}
	for each (auto kvpair in symbolToGen)
	{
		//Push the address of each pair to their respective generation vectors
		pairVectors[kvpair.second - 1].push_back((unsigned long *)(kvpair.first));
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

int bSearchP(vector<unsigned long *>& terminals, int first, int last, unsigned long * key)
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
	vector<unsigned long >& terminalVector)
{
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

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
	for (int i = 0; i < pairVectors.size() - 1; ++i)
		offsets.push_back(offsets[i] + pairVectors[i].size());
	
	for (int gen = 1; gen < pairVectors.size(); ++gen)
	{
		for (int i = 0; i < pairVectors[gen].size(); ++i)
		{
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