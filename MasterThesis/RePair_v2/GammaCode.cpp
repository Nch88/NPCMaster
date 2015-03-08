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
	while (gamma[unary] == '1')
	{
		++unary;
	} 
	++unary;

	unsigned int binary;
	if (unary == 1)
		binary = 0;
	else
	{
		string substring = gamma.substr(unary, (unary - 1));
		binary = binaryToInt(substring);
	}

	//Set i to the index of the start of the next number
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

//TODO: Figure out why right elements vector is too long
void GammaCode::encode(std::vector<vector<CompactPair*>*>& pairs,
	unordered_set<unsigned int>& terminals,
	string& terminalsGamma,
	vector<string>& leftElementsGammas,
	vector<string>& rightElementsBinaries,
	vector<vector<CompactPair*>*>& generationVectors)
{
	int generations = generationVectors.size();
	int genP1 = 0;
	unsigned int firstElement = 0;
	string fstElmtGamma = "";

	//Sort terminals
	vector<unsigned int> terminalVector;
	//terminalVector.resize(terminals.size());
	//terminalVector.assign(terminals.begin(), terminals.end());
	for each (auto entry in terminals)
	{
		terminalVector.push_back(entry);
	}
	sort(terminalVector.begin(), terminalVector.end());
	string tmpGammaCode = "";
	//Gamma code for terminals
	for (int iP1 = 0; iP1 < terminalVector.size(); ++iP1)
	{
		tmpGammaCode.assign(getGammaCode(terminalVector[iP1]));
		terminalsGamma += tmpGammaCode;
	}

	long bitLengthRightValue = terminalVector.size();
	long bitLengthRight = floor(log2(bitLengthRightValue)) + 1; //Generation 1 can point to any terminal

	//For each generation
	for (genP1 = 0; genP1 < generations; ++genP1)
	{

		//Gamma code for left elements
		firstElement = (*pairs[genP1])[0]->leftSymbol;
		fstElmtGamma = getGammaCode(firstElement);
		leftElementsGammas.push_back(fstElmtGamma);
		for (int i = 0; i < (*pairs[genP1]).size() - 1; ++i)
		{
			tmpGammaCode.assign(getGammaCode((*pairs[genP1])[i + 1]->leftSymbol - (*pairs[genP1])[i]->leftSymbol));
			leftElementsGammas[genP1] += tmpGammaCode;
		}

		//Binary code for right elements
		string s = "";
		rightElementsBinaries.push_back("");
		for (int i = 0; i < (*pairs[genP1]).size(); ++i)
		{			
			s.assign(getBinaryCode((*pairs[genP1])[i]->rightSymbol));

			
			for (int k = 0; k < (bitLengthRight - s.length()); ++k)
			{
				rightElementsBinaries[genP1] += '0';
			}
			rightElementsBinaries[genP1] += s;
		}

		bitLengthRightValue += generationVectors[genP1]->size();
		bitLengthRight = floor(log2(bitLengthRightValue)) + 1; //Size of all generation below
	}
}

void GammaCode::makeFinalString(vector<vector<CompactPair*>*>& pairs,
	unordered_set<unsigned int>& terminals,
	string& finalString,
	vector<vector<CompactPair*>*> generationVectors)
{
	string *terminalsGamma = new string("");

	vector<string> *lefts = new vector<string>();
	vector<string> *rights = new vector<string>();
	string tHeader = "", header = "";
	encode(pairs, terminals, *terminalsGamma, *lefts, *rights, generationVectors);

	//Set terminal header
	tHeader = getGammaCode(terminals.size());

	//First we add terminals to the final output
	finalString = tHeader + *terminalsGamma;

	//Then a header w/ number of generations
	finalString += getGammaCode(generationVectors.size());

	//Then for each generation
	int maxIndex = terminals.size() - 1;
	for (int i = 0; i < generationVectors.size(); ++i)
	{
		//Header is size of generation + max possible index found in that generation
		header = getGammaCode(generationVectors[i]->size()) + getGammaCode(maxIndex);
		
		string leftPart = ((*lefts)[i]);
		string rightPart = ((*rights)[i]);

		finalString += (header + leftPart + rightPart);

		//Increase maxindex by the size of the generation
		maxIndex += generationVectors[i]->size();
	}

	delete terminalsGamma;
	delete lefts;
	delete rights;
}

//void GammaCode::decode(vector<CompactPair*>& pairs,
//	unordered_set<unsigned int>& terminals,
//	string& inputString)
//{
//	//Terminals
//	vector<unsigned int> t;
//	int startIndex = 0;
//	int count = readGammaCodeHeader(inputString, startIndex);
//	string pairString = "";
//	decodeGammaString(pairString, inputString.substr(startIndex, string::npos), t, count);
//	terminals = *(new unordered_set<unsigned int>(t.begin(), t.end()));
//
//	//Read header
//	startIndex = 0;
//	count = readGammaCodeHeader(pairString, startIndex);
//
//	vector<unsigned int> left;
//	string prefix = "", cur;
//	decodeGammaString(prefix, pairString.substr(startIndex,string::npos), left, count);
//	int rightElemSize = floor(log2(count)) + 1;
//	int i = 0;
//	unsigned int leftVal = 0;
//	while (prefix.size() > 0)
//	{
//		leftVal += left[i];
//
//		cur = prefix.substr(0, rightElemSize);
//		if (prefix.size() > rightElemSize)
//			prefix = prefix.substr(rightElemSize, string::npos);
//		else
//			prefix = "";
//		CompactPair *c = new CompactPair(leftVal,binaryToInt(cur));
//		pairs.push_back(c);
//
//		++i;
//	}
//}

void GammaCode::readNextNumbers(int n, vector<unsigned int> &values, ifstream &bitstream, string &prefix)
{
	string emptyString = "";
	this->decodeGammaString(prefix, emptyString, values, n);
	if (values.size() == n)
		return;
	if (bitstream.is_open())
	{
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		Huffman huff;
		string chunk = "";

		while (values.size() < n)
		{
			if (!bitstream.eof())
			{
				bitstream.get(rawChunk1);
				bitstream.get(rawChunk2);
				bitstream.get(rawChunk3);
				bitstream.get(rawChunk4);

				huff.fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
			}
			else
				chunk = "";

			this->decodeGammaString(prefix, chunk, values, n);
		}
	}
}

void GammaCode::readNextBinaries(int binarySize, int count, vector<unsigned int> &values, ifstream &bitstream, string &prefix)
{
	if (bitstream.is_open())
	{
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		Huffman huff;
		string chunk = "", subString = "";

		if (!bitstream.eof())
		{
			bitstream.get(rawChunk1);
			bitstream.get(rawChunk2);
			bitstream.get(rawChunk3);
			bitstream.get(rawChunk4);

			huff.fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
		}
		else
			chunk = "";

		//Prepend prefix
		chunk = prefix + chunk;

		int i = 0;
		//Add as many binary numbers as possible until we run out of data or reach count
		while (i + binarySize < chunk.size() && values.size() < count)
		{
			subString = chunk.substr(i, binarySize);
			values.push_back(this->binaryToInt(subString));
			i += binarySize;
		}

		//If anything is left of the chunk, save it as prefix
		if (i != chunk.size())
		{
			prefix = chunk.substr(i, string::npos);
		}
	}
}

void GammaCode::decodeDictionaryFile(vector<CompactPair*>& pairs,
	unordered_set<unsigned int>& terminals,
	ifstream &bitstream)
{
	vector<unsigned int> *values = new vector<unsigned int>();
	string prefix = "";

	//Read header for terminals
	readNextNumbers(1, *values, bitstream, prefix);
	int count = (*values)[0];
	values->clear();

	//Read terminals
	readNextNumbers(count, *values, bitstream, prefix);
	terminals = *(new unordered_set<unsigned int>(values->begin(), values->end()));
	values->clear();

	//Read number of generations
	readNextNumbers(1, *values, bitstream, prefix);
	int generationCount = (*values)[0];
	values->clear();

	int binarySize, i;
	unsigned int leftVal;
	vector<unsigned int> *left = new vector<unsigned int>();
	for (int g = 0; g < generationCount; ++g)
	{
		//Read generation header
		readNextNumbers(2, *values, bitstream, prefix);
		count = (*values)[0];
		binarySize = 1 + floor(log2((*values)[1]));//Second nr. is the max index m, so binary size is 1 + floor(log2(m))
		values->clear();

		//Read left values and store them in 'left'
		readNextNumbers(count, *left, bitstream, prefix);

		//Read right element binaries and write pairs
		leftVal = 0;
		i = 0;
		while (i < count)
		{
			readNextBinaries(binarySize, count, *values, bitstream, prefix);
			for (int j = 0; j < values->size(); ++j)
			{
				leftVal += (*left)[i];
				CompactPair *c = new CompactPair(leftVal, (*values)[j]);
				pairs.push_back(c);
				++i;
			}
			values->clear();
		}
		left->clear();
	}

	delete values;
	delete left;
}