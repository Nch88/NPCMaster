#pragma once

class Decoder
{
public:
	Decoder();
	~Decoder();
	void Decoder::reverseCantor(unsigned long& in, unsigned long& out1, unsigned long& out2);
	std::string Decoder::getDictionaryName(std::string in);
	std::string Decoder::getOutfileName(std::string in);
	void Decoder::decode(std::string inFile);
};

