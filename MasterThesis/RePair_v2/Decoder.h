#pragma once

class Decoder
{
public:
	Decoder();
	~Decoder();
	std::string Decoder::getDictionaryName(std::string in);
	std::string Decoder::getOutfileName(std::string in);
	void Decoder::decode(std::string inFile);
};

