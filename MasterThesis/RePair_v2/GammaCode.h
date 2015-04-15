#pragma once

class GammaCode
{
public:
	///<summary>Appends the prefix and gamma strings, then reads gamma codes from the start of the resulting string
	/// and adding the corresponding numbers to 'output' until the string runs out or 'count' numbers has been added.
	/// Anything left over from the string is saved in 'prefix'</summary>
	///<param name="prefix">Input/Output: A string of gamma code data. Added to the start of 'gamma', then used to store any unconsumed input.</param>
	///<param name="gamma">Input: A string of gamma code data to read from.</param>
	///<param name="output">Output: The numbers read from prefix and gamma are stored here.</param>
	///<param name="count">Input: The number of gamma codes to read.</param>
	void GammaCode::decodeGammaString(
		std::string &prefix, 
		std::string &gamma,
		std::vector<long> &output, 
		long count);

	///<summary>Interprets a string of 1's and 0's as a binary number, and converts it to a long.</summary>
	///<param name="binary">Input: A string of 1's and 0's.</param>
	long GammaCode::binaryToInt(std::string binary);

	///<summary>Reads one gamma code from a string. Returns the corresponding number, 
	/// and sets 'index' to the index of the first char after the code that has been read.</summary>
	///<param name="gamma">Input: A string of 1's and 0's to read from.</param>
	///<param name="index">Output: Set to the index of the first char after the first gamma code in the input.</param>
	long GammaCode::readGammaCodeHeader(std::string& gamma, int& index);

	///<summary>Interprets a string as a gamma code, and returns it as a long. Behavior is undefined if the input is not a valid gamma code.</summary>
	///<param name="gamma">Input: A string of 1's and 0's. Must be exactly one valid gamma code.</param>
	long GammaCode::gammaToInt(std::string gamma);

	///<summary>Returns the binary version of a number as a string of 1's and 0's.</summary>
	///<param name="input">Input: A non-negative number.</param>
	std::string getBinaryCode(long input);

	///<summary>Returns the gamma code for a number as a string of 1's and 0's.</summary>
	///<param name="input">Input: A non-negative number.</param>
	std::string getGammaCode(long input);

	///<summary>Encodes a dictionary in pairvector form as a string of gamma codes.</summary>
	///<param name="pairVector">Input: A vector of vectors of CompactPairs, as produced by Dictionary::generateCompactDictionary.</param>
	///<param name="terminalVector">Input: A sorted vector of the terminals used in the dictionary.</param>
	///<param name="finalString">Output: The dictionary in gamma code form.</param>
	void makeFinalString(
		std::vector<std::vector<CompactPair>>& pairVector,
		std::vector<long>& terminalVector,
		std::string& finalString);

	///<summary>Internal function used by makeFinalString.</summary>
	void encode(
		std::vector<std::vector<CompactPair>>& pairVector,
		std::vector<long>& terminalVector,
		std::string& terminalsGamma,
		std::vector<std::string>& leftElementsGammas,
		std::vector<std::string>& rightElementsBinaries);

	///<summary>Internal function used by decodeDictionaryFile.</summary>
	void GammaCode::readNextNumbers(
		int n, 
		std::vector<long> &values, 
		std::ifstream &bitstream, 
		std::string &prefix);

	///<summary>Internal function used by decodeDictionaryFile.</summary>
	void GammaCode::processBinary(	
		int binarySize, 
		int count, 
		std::string chunk, 
		std::vector<long> &values, 
		std::string &prefix);

	///<summary>Internal function used by decodeDictionaryFile.</summary>
	void GammaCode::readNextBinaries(
		int binarySize, 
		int count, 
		std::vector<long> &values, 
		std::ifstream &bitstream, 
		std::string &prefix);

	///<summary>Creates a pair vector and a terminal vector based on a filestream in binary mode. The file is expected to contain a dictionary in gamma code form.</summary>
	///<param name="bitstream">Input: An open ifstream in binary mode.</param>
	///<param name="pairVector">Output: A dictionary in the form of a vector of CompactPairs. 
	/// Each member of a pair is an index into either the terminal vector or the pair vector itself.</param>
	///<param name="terminals">Output: A sorted vector of the terminals used in the dictionary.</param>
	void GammaCode::decodeDictionaryFile(
		std::ifstream &bitstream,
		std::vector<CompactPair>& pairVector,
		std::vector<long>& terminals);
};