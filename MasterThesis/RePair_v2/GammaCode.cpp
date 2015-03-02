#include "stdafx.h"
#include "GammaCode.h"

unsigned int GammaCode::binaryToInt(string binary)
{
	if (binary == "")
		return 0;
	unsigned int result = 0;
	int i = binary.size() - 1;
	while (i >= 0)
	{
		if (binary[i] == '1')
			result += pow(2, ((binary.size() - 1) - i));
		--i;
	}
	return result;
}

string GammaCode::getBinaryCode(unsigned int input)
{
	string s = "";
	int i = 31;

	//Set i to index of most significant non-zero bit, or to the least significant if input = 0
	while (i > 0 && (input & (1 << i)) == 0)
	{
		--i;
	}

	while (i >= 0)
	{
		if (input & (1 << i))
			s += '1';
		else
			s += '0';
		--i;
	}
	return s;
}

unsigned int GammaCode::readGammaCodeHeader(string& gamma, int& i)
{
	int unary = 0;
	do
	{
		++unary;
	} while (gamma[unary] == '1');

	unsigned int binary;
	if (unary == 1)
		binary = 0;
	else
	{
		string substring = gamma.substr(unary, (unary - 1));
		binary = binaryToInt(substring);
	}

	i = unary + unary - 1;

	return pow(2, unary - 1) + binary - 1;
}

unsigned int GammaCode::gammaToInt(string gamma)
{
	int unary = 0;
	while (gamma[unary] == '1')
	{
		++unary;
	} 
	++unary;

	unsigned int binary = binaryToInt(gamma.substr(unary, string::npos));

	return pow(2, unary - 1) + binary - 1;
}

void GammaCode::decodeGammaString(string &prefix, string &gamma, vector<unsigned int> &output, unsigned int count)
{
	//Start is the index of the start of the current number
	int index = 0, start = 0;

	string input = prefix + gamma, substring = "";
	unsigned int unary, binary;

	while (output.size() < count)
	{
		while (index < input.size() && input[index] == '1')
		{
			++index;
		}

		unary = index + 1 - start;

		if (index + ((int)unary) > input.size())
		{
			//End of input, set remainder and return
			prefix = input.substr(start, string::npos);
			return;
		}
		else
		{
			//We have enough input left
			if ((index + 1) > (index + ((int)unary) - 1))
				binary = 0;
			else
			{
				substring = input.substr(index + 1, (unary - 1));
				binary = binaryToInt(substring);
			}
			output.push_back(pow(2, unary - 1) + binary - 1);
		}
		index += unary;
		start = index;
	}
	if (index == input.size())
		prefix = "";
	else
		prefix = input.substr(index, string::npos);
}

string GammaCode::getGammaCode(unsigned int in)
{
	//Adjust for 0-origin
	unsigned int input = in + 1;
	
	if (input == 1)//Else we would return "00"
		return "0";

	string firstPart = "", secondPart = "", padding = "";

	//Unary code for first part
	int firstPartLength = floor(log2(input));
	for (int i = 0; i < firstPartLength; ++i)
	{
		firstPart += '1';
	}
	firstPart += '0';

	//Binary code for rest
	int secondPartInput = input - pow(2.0, floor(log2(input)));
	int secondPartLength = floor(log2(input));

	//Add padding to get the binary part to be the right length
	secondPart = getBinaryCode(secondPartInput);
	for (int i = secondPart.length(); i < secondPartLength; ++i)
		padding += '0';

	return firstPart + padding + secondPart;
}

void GammaCode::encode(vector<CompactPair*>& pairs,
	unordered_set<unsigned int>& terminals,
	string& terminalsGamma,
	string& leftElementsGamma,
	string& rightElementsBinary)
{
	//Sort terminals
	vector<unsigned int> terminalVector;
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

	//Gamma code for terminals
	for (int i = 0; i < terminalVector.size(); ++i)
	{
		terminalsGamma += getGammaCode(terminalVector[i]);
	}

	//Gamma code for left elements
	leftElementsGamma += getGammaCode(pairs[1]->leftSymbol);
	for (int i = 0; i < pairs.size() - 1; ++i)
	{
		leftElementsGamma += getGammaCode(pairs[i + 1]->leftSymbol - pairs[i]->leftSymbol);
	}

	//Binary code for right elements
	int bitLengthRight = ceil(log2(pairs.size()));//This won't work for one generation at a time
	string s;
	for (int i = 0; i < pairs.size(); ++i)
	{
		s = getBinaryCode(pairs[i]->rightSymbol);
		if (s.length() > bitLengthRight)
			throw new exception("Error in gamma encoding: bit length right not sufficient");
		for (int j = 0; j < (bitLengthRight - s.length()); ++j)
		{
			rightElementsBinary += '0';
		}
		rightElementsBinary += s;
	}
}

void GammaCode::makeFinalString(std::vector<CompactPair*>& pairs,
	std::unordered_set<unsigned int>& terminals,
	std::string& finalString)
{
	string *terminalsGamma = new string();

	string tHeader = "", header = "", left = "", right = "";
	encode(pairs, terminals, *terminalsGamma, left, right);
	
	//Current header is just the nr of pairs
	//For the generationwise version, header should be nr of pairs in generation, then max index.
	//This can be written as gamma codes with the padding appended instead of prepended.

	//Add headers
	tHeader = getGammaCode(terminals.size());
	header = getGammaCode(pairs.size());

	finalString = tHeader + *terminalsGamma + header + left + right;

	delete terminalsGamma;
}

void GammaCode::decode(vector<CompactPair*>& pairs,
	unordered_set<unsigned int>& terminals,
	string& inputString)
{
	//Terminals
	vector<unsigned int> t;
	int startIndex = 0;
	int count = readGammaCodeHeader(inputString, startIndex);
	string pairString = "";
	decodeGammaString(pairString, inputString.substr(startIndex, string::npos), t, count);
	terminals = *(new unordered_set<unsigned int>(t.begin(), t.end()));

	//Read header
	startIndex = 0;
	count = readGammaCodeHeader(pairString, startIndex);

	vector<unsigned int> left;
	string prefix = "", cur;
	decodeGammaString(prefix, pairString.substr(startIndex,string::npos), left, count);
	int rightElemSize = ceil(log2(count));
	int i = 0;
	while (prefix.size() > 0)
	{
		cur = prefix.substr(0, rightElemSize);
		if (prefix.size() > rightElemSize)
			prefix = prefix.substr(rightElemSize, string::npos);
		else
			prefix = "";
		CompactPair *c = new CompactPair(left[i],binaryToInt(cur));
		pairs.push_back(c);
	}
}