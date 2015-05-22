#pragma once

class Decoder
{
public:
	Decoder();
	~Decoder();
	void Decoder::writeSymbols(vector<CompactPair>& pairs, int index, std::ofstream& out, std::vector<unsigned long>& terms);
	void Decoder::writeSymbol(vector<CompactPair>& pairs, int index, ofstream& outstream, vector<unsigned long>& terms);
	std::string Decoder::getDictionaryName(std::string in);
	std::string Decoder::getOutfileName(std::string in);
	void Decoder::decode(std::string inFile);
};

