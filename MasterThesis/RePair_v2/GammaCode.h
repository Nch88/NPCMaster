#pragma once

class GammaCode
{
public:
	void GammaCode::decodeGammaString(std::string &prefix, 
		std::string &gamma,
		std::vector<unsigned int> &output, 
		unsigned int count);
	unsigned int GammaCode::binaryToInt(std::string binary);
	unsigned int GammaCode::readGammaCodeHeader(std::string& gamma, int& i);
	unsigned int GammaCode::gammaToInt(std::string binary);
	std::string getBinaryCode(unsigned int input);
	std::string getGammaCode(unsigned int input);
	void makeFinalString(std::vector<std::vector<CompactPair*>*>& pairVector,
		std::unordered_set<unsigned int>& terminals,
		std::string& finalString,
		std::vector<std::vector<CompactPair*>*> generationVectors);
	void encode(std::vector<std::vector<CompactPair*>*>& pairVector,
		std::unordered_set<unsigned int>& terminals,
		std::string& terminalsGamma,
		std::vector<std::string>& leftElementsGammas,
		std::vector<std::string>& rightElementsBinaries,
		std::vector<std::vector<CompactPair*>*> generationVectors);
	void decode(std::vector<std::vector<CompactPair*>*>& pairVector,
		std::unordered_set<unsigned int>& terminals,
		std::string& inputString);
	void GammaCode::readNextNumbers(int n, std::vector<unsigned int> &values, std::ifstream &bitstream, std::string &prefix);
	void GammaCode::readNextBinaries(int binarySize, std::vector<unsigned int> &values, std::ifstream &bitstream, std::string &prefix);
	void GammaCode::decodeDictionaryFile(std::vector<CompactPair*>& pairs,
		std::unordered_set<unsigned int>& terminals,
		std::string& inputString,
		std::ifstream &bitstream);
};