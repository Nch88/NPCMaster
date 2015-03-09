#pragma once

class GammaCode
{
public:
	void GammaCode::decodeGammaString(std::string &prefix, 
		std::string &gamma,
		std::vector<long> &output, 
		long count);
	long GammaCode::binaryToInt(std::string binary);
	long GammaCode::readGammaCodeHeader(std::string& gamma, int& i);
	long GammaCode::gammaToInt(std::string binary);
	std::string getBinaryCode(long input);
	std::string getGammaCode(long input);
	void makeFinalString(std::vector<std::vector<CompactPair>>& pairVector,
		std::unordered_set<long>& terminals,
		std::string& finalString,
		std::vector<std::vector<CompactPair>> generationVectors);
	void encode(std::vector<std::vector<CompactPair>>& pairVector,
		std::unordered_set<long>& terminals,
		std::string& terminalsGamma,
		std::vector<std::string>& leftElementsGammas,
		std::vector<std::string>& rightElementsBinaries,
		std::vector<std::vector<CompactPair>>& generationVectors);
	void decode(std::vector<std::vector<CompactPair>>& pairVector,
		std::unordered_set<long>& terminals,
		std::string& inputString);
	void GammaCode::readNextNumbers(int n, std::vector<long> &values, std::ifstream &bitstream, std::string &prefix);
	void GammaCode::readNextBinaries(int binarySize, int count, std::vector<long> &values, std::ifstream &bitstream, std::string &prefix);
	void GammaCode::decodeDictionaryFile(std::vector<CompactPair>& pairs,
		std::vector<long>& terminals,
		std::ifstream &bitstream);
};