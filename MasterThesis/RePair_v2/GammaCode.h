#pragma once

class GammaCode
{
public:
	void GammaCode::decodeGammaString(std::string &prefix, 
		std::string &gamma,
		std::vector<unsigned int> &output, 
		unsigned int count);
	unsigned int GammaCode::binaryToInt(std::string binary);
	unsigned int GammaCode::gammaToInt(std::string binary);
	std::string getBinaryCode(unsigned int input);
	std::string getGammaCode(unsigned int input);
	void makeFinalString(std::vector<CompactPair*>& pairVector,
		std::unordered_set<unsigned int>& terminals,
		std::string& terminalsGamma,
		std::string& finalString);
	void encode(std::vector<CompactPair*>& pairVector, 
		std::unordered_set<unsigned int>& terminals, 
		std::string& terminalsGamma, 
		std::string& leftElementsGamma,
		std::string& rightElementsBinary);
	void decode(std::vector<CompactPair*>& pairVector,
		std::unordered_set<unsigned int>& terminals,
		std::string& terminalsGamma,
		std::string& finalString);
};