#include "stdafx.h"
#include "Decoder.h"

Decoder::Decoder(){}

Decoder::~Decoder(){}

void Decoder::writeSymbols(vector<CompactPair>& pairs, int index, ofstream& out, vector<unsigned long>& terms)
{
	writeSymbol(pairs,pairs[index].leftSymbol, out, terms);
	writeSymbol(pairs,pairs[index].rightSymbol, out, terms);
}

void Decoder::writeSymbol(vector<CompactPair>& pairs, int index, ofstream& outstream, vector<unsigned long>& terms)
{
	if (index < terms.size())
	{
		unsigned long part1, part2, part3;
		Cantor::reverseCantor(terms[index], part1, part2, part3);
		if (part3 != 0)
		{
			char c[] = { (char)part1, (char)part2, (char)part3 };
			string s(c, 3);
			outstream << s;
		}
		else if (part2 != 0)
		{
			char c[] = { (char)part1, (char)part2 };
			string s(c, 2);
			outstream << s;
		}
		else
		{
			char c[] = { (char)part1 };
			string s(c, 1);
			outstream << s;
		}
	}
	else //non-terminal
	{
		writeSymbols(pairs, index - terms.size(), outstream, terms);
	}
}

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
	vector<unsigned long > decodedTerms;
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	unsigned long  *firstCodes;
	vector<unsigned long > symbolIndexSequence;
	dense_hash_map<unsigned long , string> expandedDictionary;
	expandedDictionary.set_empty_key(-1);
	expandedDictionary.set_deleted_key(-2);
	
	std::cout << "\nProgress:[";	

	//Each iteration represents a block
	while (!bitstream.eof())
	{
		std::cout << '#';

		//Read dictionary
		gc.decodeDictionaryFile(bitstreamDict, decodedPairs, decodedTerms);
		
		//THIS IS EATING ALL MY MEMORY!!!!!! WHYYYYYYY!!!!!!!!!!!!!!!!!
		//finalDict.expandDictionary(decodedPairs, decodedTerms, expandedDictionary);

		//Read huffman dictionary
		h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);			

		//Read block
		h.decode(firstCodes, bitstream, symbolIndices, symbolIndexSequence);

		//Decode and write
		for (int i = 0; i < symbolIndexSequence.size(); ++i)
		{
			writeSymbol(decodedPairs, symbolIndexSequence[i], outstream, decodedTerms);
		}
		
		//Reset for next block
		delete firstCodes;
		firstCodes = nullptr;

		decodedPairs.clear();
		decodedTerms.clear();
		symbolIndices.clear();
		symbolIndexSequence.clear();
		expandedDictionary.clear();

		std::cout << '#';
		bitstream.peek();		
	}

	std::cout << ']' << endl;

	bitstreamDict.close();
	bitstream.close();
	outstream.close();
}
