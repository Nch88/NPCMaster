#include "stdafx.h"
#include "Decoder.h"

Decoder::Decoder(){}

Decoder::~Decoder(){}

string Decoder::getDictionaryName(string in)
{
	if (in.substr(in.size() - 4, 4) == ".NPC")
		return in.substr(0, in.size() - 4) + ".dict.NPC";
	else
		return "error";
}

string Decoder::getOutfileName(string in)
{
	if (in.substr(in.size() - 4, 4) == ".NPC")
		return in.substr(0, in.size() - 4) + ".decoded";
	else
		return "error";
}

void Decoder::decode(string inFile)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

	AlgorithmP algP;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;

	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	unordered_map <long, unordered_map<long, long>> indices;
	ifstream file(inFile);
	bool firstBlock = true;

	string compressedDictionary = getDictionaryName(inFile);
	ifstream bitstreamDict(compressedDictionary, ios::binary);
	ifstream bitstream(inFile, ios::binary);
	ofstream outstream(getOutfileName(inFile));

	vector<CompactPair> decodedPairs;
	vector<long> decodedTerms;
	unordered_map<long, unordered_map<long, long>> symbolIndices;
	long *firstCodes;
	vector<long> symbolIndexSequence;
	unordered_map<long, string> expandedDictionary;
	
	while (!bitstream.eof())
	{
		//Read dictionary
		gc.decodeDictionaryFile(decodedPairs, decodedTerms, bitstreamDict);
		finalDict.expandDictionary(decodedPairs, decodedTerms, expandedDictionary);

		//Read huffman dictionary
		h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);

		//Read block
		h.decode(firstCodes, bitstream, symbolIndices, symbolIndexSequence);

		//Decode and write
		for each (long n in symbolIndexSequence)
		{
			outstream << expandedDictionary[n];
		}
	}

	bitstreamDict.close();
	bitstream.close();
	outstream.close();
}
