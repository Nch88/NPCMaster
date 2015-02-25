#pragma once

class GammaCode
{
public:
	string getBinaryCode(unsigned int input);
	string getGammaCode(unsigned int input);
	void makeFinalString(std::vector<CompactPair*>& pairs,
		std::unordered_set<unsigned int>& terminals,
		std::string& terminalsGamma,
		std::string& finalString);
	void encode(std::vector<CompactPair*>& pairs, 
		std::unordered_set<unsigned int>& terminals, 
		std::string& terminalsGamma, 
		std::string& leftElementsGamma,
		std::string& rightElementsBinary);
	void decode(std::vector<CompactPair*>& pairs,
		std::unordered_set<unsigned int>& terminals,
		std::string& terminalsGamma,
		std::string& leftElementsGamma,
		std::string& rightElementsBinary);
};