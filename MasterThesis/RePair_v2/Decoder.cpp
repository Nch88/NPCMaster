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
	Huffman h;
	Dictionary finalDict;
	GammaCode gc;

	ifstream file(inFile);
	bool firstBlock = true;

	string compressedDictionary = getDictionaryName(inFile);
	ifstream bitstreamDict(compressedDictionary, ios::binary);
	ifstream bitstream(inFile, ios::binary);
	ofstream outstream(getOutfileName(inFile), ios::binary);

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
	std::cout << "\nProgress:[";
	long count = 0;

	//Each iteration represents a block
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
		std::cout << '#';

		//Read block
		h.decode(firstCodes, bitstream, symbolIndices, symbolIndexSequence);

		//DEBUG
		vector<long> dictKeys;
		vector<string> dictValues;
		for each (auto &entry in expandedDictionary)
		{
			dictKeys.push_back(entry.first);
			dictValues.push_back(entry.second);
			if (entry.second == "atctcga")
				int x = 0;
		}

		//Decode and write
		for each (long n in symbolIndexSequence)
		{
			//DEBUG
			if (count > 4194290)
			{
				int x = 0;
			}
				
			string toWrite;
			if (n < decodedTerms.size())
				toWrite = decodedTerms[n];
			else
				toWrite = expandedDictionary[n - decodedTerms.size()];
			count += toWrite.size();
			outstream << toWrite;
		}
		
		//Reset for next block
		delete firstCodes;
		firstCodes = nullptr;

		decodedPairs.clear();
		decodedTerms.clear();
		symbolIndices.clear();
		symbolIndexSequence.clear();
		expandedDictionary.clear();

		//DEBUG
		std::cout << '#';
		bitstream.peek();
	}

	//DEBUG
	std::cout << ']' << endl;

	bitstreamDict.close();
	bitstream.close();
	outstream.close();
}
