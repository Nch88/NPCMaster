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
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
	long symbols(initialSymbolValue);//256

	AlgorithmP algP;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;

	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
	ifstream file(inFile);
	bool firstBlock = true;

	string compressedDictionary = getDictionaryName(inFile);
	ifstream bitstreamDict(compressedDictionary, ios::binary);
	ifstream bitstream(inFile, ios::binary);
	ofstream outstream(getOutfileName(inFile));

	vector<CompactPair> decodedPairs;
	vector<long> decodedTerms;
	dense_hash_map<long, dense_hash_map<long, long>> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	long *firstCodes;
	vector<long> symbolIndexSequence;
	dense_hash_map<long, string> expandedDictionary;
	expandedDictionary.set_empty_key(-1);
	expandedDictionary.set_deleted_key(-2);
	
	//DEBUG
	cout << "\nProgress:[";

	while (!bitstream.eof())
	{
		//Read dictionary
		gc.decodeDictionaryFile(decodedPairs, decodedTerms, bitstreamDict);
		finalDict.expandDictionary(decodedPairs, decodedTerms, expandedDictionary);

		//DEBUG
		/*for each (auto var in expandedDictionary)
		{
			cout << "\nEntry: " << var.first << " -> " << var.second << ".\n";
		}*/

		//Read huffman dictionary
		h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);

		//DEBUG
		/*for each (auto var in symbolIndices)
		{
			for each (auto var2 in var.second)
			{
				cout << "\nEntry: ( " << var.first << " , " << var2.first << " ) -> " << var2.second << ".\n";
			}
		}*/

		//DEBUG
		cout << '#';

		//Read block
		h.decode(firstCodes, bitstream, symbolIndices, symbolIndexSequence);

		//Decode and write
		for each (long n in symbolIndexSequence)
		{
			outstream << expandedDictionary[n];
		}

		//DEBUG
		cout << '#';
	}

	//DEBUG
	cout << ']' << endl;

	bitstreamDict.close();
	bitstream.close();
	outstream.close();
}
