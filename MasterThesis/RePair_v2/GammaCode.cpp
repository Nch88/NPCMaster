#include "stdafx.h"
#include "GammaCode.h"

string GammaCode::getBinaryCode(unsigned int input)
{
	string s = "";
	int i = 31;
	while (i >= 0 && (input & (1 << i)) == 0)
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

string GammaCode::getGammaCode(unsigned int input)
{
	string s = "";

	//Unary code for first part
	int firstPart = floor(log2(input));
	for (int i = 0; i < firstPart - 1; ++i)
	{
		s += '1';
	}
	s += '0';

	//Binary code for rest
	int secondPart = input - pow(2.0, floor(log2(input)));
	s += getBinaryCode(secondPart);
	return s;
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
	std::string& terminalsGamma,
	std::string& finalString)
{
	string header = "", left = "", right = "";
	encode(pairs, terminals, terminalsGamma, left, right);
	
	//Current header is just the nr of pairs
	//For the generationwise version, header should be nr of pairs in generation, then max index.
	//This can be written as gamma codes with the padding appended instead of prepended.
	header += getBinaryCode(pairs.size());

	//Pad header to make the length 32 bit
	string prefix = "";
	while (header.length() + prefix.length() < 32)
	{
		prefix += '0';
	}
	header = prefix + header;

	finalString = header + left + right;
}

void GammaCode::decode(vector<CompactPair*>& pairs,
	unordered_set<unsigned int>& terminals,
	string& terminalsGamma,
	string& leftElementsGamma,
	string& rightElementsBinary)
{

}