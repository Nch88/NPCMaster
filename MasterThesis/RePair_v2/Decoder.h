#pragma once

class Decoder
{
public:
	Decoder();
	~Decoder();
	void Decoder::reverseCantor(unsigned long& in, unsigned long& out1, unsigned long& out2);
	void Decoder::writeSymbols(vector<CompactPair>& pairs, int index, std::ofstream& out, std::vector<unsigned long>& terms,unsigned long rdepth);
	void Decoder::writeSymbol(vector<CompactPair>& pairs, int index, ofstream& outstream, vector<unsigned long>& terms, unsigned long rdepth);
	std::string Decoder::getDictionaryName(std::string in);
	std::string Decoder::getOutfileName(std::string in);
	void Decoder::decode(std::string inFile);
};

