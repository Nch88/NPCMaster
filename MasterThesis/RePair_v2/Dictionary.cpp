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

int Dictionary::findGenerations(
	long symbol, 
	dense_hash_map<long, long>& symbolToGen, 
	unordered_set<long>& terminals)
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
		long* address = (long*)symbol;
		int d1 = findGenerations(address[0], symbolToGen, terminals);
		int d2 = findGenerations(address[1], symbolToGen, terminals);
		int gen = max(d1, d2) + 1;
		symbolToGen[symbol] = gen;
		return gen;
	}
}

void Dictionary::createSupportStructures(
	vector<SymbolRecord*> & sequenceArray,
	unordered_set<long>& terminals,
	dense_hash_map<long,long>& symbolToGen,
	vector<vector<long*>>& pairVectors)
{
	//Create the symbol to gen table and count the number of generations
	int genCount = 0;
	unordered_set<long> roots;
	for each (SymbolRecord* record in sequenceArray)
	{
		if (record->symbol > initialSymbolValue)
			roots.emplace(record->symbol);
	}
	for each (long s in roots)
	{
		int d = findGenerations(s, symbolToGen, terminals);
		genCount = max(d, genCount);
	}

	//Create pairVectors
	pairVectors.reserve(genCount);
	for (int i = 0; i < genCount; ++i)
	{
		vector<long*> v;
		pairVectors.push_back(v);
	}
	for each (auto kvpair in symbolToGen)
	{
		//Push the address of each pair to their respective generation vectors
		pairVectors[kvpair.second - 1].push_back((long*)(kvpair.first));
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