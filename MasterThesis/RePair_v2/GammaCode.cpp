#include "stdafx.h"
#include "GammaCode.h"



unsigned long  GammaCode::binaryToInt(string binary)
{
	if (binary.size() == 0)
		cerr << ("GammaCode::binaryToInt: Empty string received") << endl;
	if (binary == "")
		return 0;
	unsigned long  result = 0;
	int i = binary.size() - 1;
	while (i >= 0)
	{
		if (binary[i] == '1')
			result += pow(2, ((binary.size() - 1) - i));
		else if (binary[i] != '0')
			cerr << ("GammaCode::binaryToInt: Invalid string received") << endl;
		--i;
	}
	return result;
}

string GammaCode::getBinaryCode(unsigned long  input)
{
	if (input < 0)
		cerr << ("GammaCode::getBinaryCode: negative number received") << endl;
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

unsigned long  GammaCode::readGammaCodeHeader(string& gamma, int& i)
{
	if (gamma.size() == 0)
		cerr << ("GammaCode::readGammaCodeHeader: Empty string received") << endl;
	int unary = 0;
	while (gamma[unary] == '1')
	{
		++unary;
	} 
	++unary;

	unsigned long  binary;
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

unsigned long  GammaCode::gammaToInt(string gamma)
{
	if (gamma.size() == 0)
		cerr << ("GammaCode::gammaToInt: Empty string received") << endl;
	int unary = 0;
	while (gamma[unary] == '1')
	{
		++unary;
	} 
	++unary;

	if (gamma.size() != 2 * unary - 1)
	{
		cerr << ("GammaCode::gammaToInt: Non-gamma code received") << endl;
		return -1;
	}
		

	unsigned long  binary;
	if (unary >= gamma.size())
		binary = 0;
	else
		binary = binaryToInt(gamma.substr(unary, string::npos));

	return pow(2, unary - 1) + binary - 1;
}

void GammaCode::decodeGammaString(string &prefix, string &gamma, vector<unsigned long > &output, unsigned long  count)
{
	if (count < 1)
		cerr << ("GammaCode::decodeGammaString: Invalid count received") << endl;
	//Start is the index of the start of the current number
	int index = 0, start = 0;

	string input = prefix + gamma, substring = "";
	prefix = "";
	unsigned long  unary, binary;

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
			if (start < input.size())
				prefix = input.substr(start, string::npos);
			else
				prefix = "";
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

string GammaCode::getGammaCode(unsigned long  in)
{
	if (in < 0)
		cerr << ("GammaCode::get GammaCode: Negative number received") << endl;
	//Adjust for 0-origin
	unsigned long  input = in + 1;
	
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

void GammaCode::encode(std::vector<vector<CompactPair>>& pairs,
	vector<unsigned long >& terminalVector,
	string& terminalsGamma,
	vector<string>& leftElementsGammas,
	vector<string>& rightElementsBinaries)
{
	if (pairs.size() == 0)
		cerr << ("GammaCode::encode: Empty pair vector received") << endl;
	if (terminalVector.size() == 0)
		cerr << ("GammaCode::encode: Empty terminal set received") << endl;
	int generations = pairs.size();
	int genP1 = 0;
	unsigned long  firstElement = 0;
	string fstElmtGamma = "";

	//Gamma code for terminals
	string tmpGammaCode = "";
	for (int iP1 = 0; iP1 < terminalVector.size(); ++iP1)
	{
		tmpGammaCode.assign(getGammaCode(terminalVector[iP1]));
		terminalsGamma += tmpGammaCode;
	}

	unsigned long  bitLengthRightValue = terminalVector.size() - 1;
	unsigned long  bitLengthRight = floor(log2(bitLengthRightValue)) + 1; //Generation 1 can point to any terminal

	//For each generation
	for (genP1 = 0; genP1 < generations; ++genP1)
	{

		//Gamma code for left elements
		firstElement = (pairs[genP1])[0].leftSymbol;
		fstElmtGamma = getGammaCode(firstElement);
		leftElementsGammas.push_back(fstElmtGamma);
		for (int i = 0; i < (pairs[genP1]).size() - 1; ++i)
		{
			tmpGammaCode.assign(getGammaCode(pairs[genP1][i + 1].leftSymbol - (pairs[genP1])[i].leftSymbol));
			leftElementsGammas[genP1] += tmpGammaCode;
		}

		//Binary code for right elements
		string s = "";
		rightElementsBinaries.push_back("");
		for (int i = 0; i < (pairs[genP1]).size(); ++i)
		{			
			s.assign(getBinaryCode((pairs[genP1])[i].rightSymbol));
			
			for (int k = 0; k < (bitLengthRight - s.length()); ++k)
			{
				rightElementsBinaries[genP1] += '0';
			}
			rightElementsBinaries[genP1] += s;
		}

		bitLengthRightValue += pairs[genP1].size();
		bitLengthRight = floor(log2(bitLengthRightValue)) + 1; //Size of all generation below
	}
}

void GammaCode::makeFinalString(
	vector<vector<CompactPair>>& pairs,
	vector<unsigned long >& terminalVector,
	string& finalString)
{
	string *terminalsGamma = new string("");

	vector<string> lefts;
	vector<string> rights;
	string tHeader = "", header = "";
	encode(pairs, terminalVector, *terminalsGamma, lefts, rights);

	//Set terminal header
	tHeader = getGammaCode(terminalVector.size());

	//First we add terminals to the final output
	finalString = tHeader + *terminalsGamma;

	//Then a header w/ number of generations
	finalString += getGammaCode(pairs.size());

	//Then for each generation
	int maxIndex = terminalVector.size() - 1;
	for (int i = 0; i < pairs.size(); ++i)
	{
		//Header is size of generation + max possible index found in that generation
		header = getGammaCode(pairs[i].size()) + getGammaCode(maxIndex);
		
		string leftPart = ((lefts)[i]);
		string rightPart = ((rights)[i]);

		finalString += (header + leftPart + rightPart);

		//Increase maxindex by the size of the generation
		maxIndex += pairs[i].size();
	}

	delete terminalsGamma;
}

void GammaCode::readNextNumbers(int n, vector<unsigned long > &values, ifstream &bitstream, string &prefix)
{
	if (n < 1)
		cerr << ("GammaCode::readNextNumbers: Cannot read less than 1 number") << endl;
	if (!bitstream.is_open())
		cerr << ("GammaCode::readNextNumbers: Stream is not open") << endl;
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
			bitstream.peek();
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

void GammaCode::processBinary(int binarySize, int count, string chunk, vector<unsigned long > &values, string &prefix)
{
	if (binarySize < 1)
		cerr << ("GammaCode::processBinary: Binary size must be at least 1") << endl;
	if (count < 1)
		cerr << ("GammaCode::processBinary: Cannot read less than 1 number") << endl;
	chunk.assign(prefix + chunk);
	prefix = "";

	int i = 0;
	string subString = "";
	//Add as many binary numbers as possible until we run out of data or reach count
	while (i + binarySize <= chunk.size() && values.size() < count)
	{
		subString.assign(chunk.substr(i, binarySize));
		values.push_back(binaryToInt(subString));
		i += binarySize;
	}

	//If anything is left of the chunk, save it as prefix
	if (i != chunk.size())
	{
		prefix.assign(chunk.substr(i, string::npos));
	}		
}

void GammaCode::readNextBinaries(int binarySize, int count, vector<unsigned long > &values, ifstream &bitstream, string &prefix)
{
	if (binarySize < 1)
		cerr << ("GammaCode::readNextBinaries: Binary size must be at least 1") << endl;
	if (count < 1)
		cerr << ("GammaCode::readNextBinaries: Cannot read less than 1 number") << endl;
	processBinary(binarySize, count, "", values, prefix);
	if (values.size() != count)
	{

		if (bitstream.is_open())
		{
			char rawChunk1 = 0;
			char rawChunk2 = 0;
			char rawChunk3 = 0;
			char rawChunk4 = 0;
			Huffman huff;
			string chunk;
			chunk.assign("");
			while (values.size() != count)
			{
				bitstream.peek();
				if (!bitstream.eof())
				{
					bitstream.get(rawChunk1);
					bitstream.get(rawChunk2);
					bitstream.get(rawChunk3);
					bitstream.get(rawChunk4);

					huff.fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);
				}
				else
					chunk.assign("");

				processBinary(binarySize, count, chunk, values, prefix);
			}
		}
	}
}

void GammaCode::decodeDictionaryFile(
	ifstream &bitstream,
	vector<CompactPair>& pairs,
	vector<unsigned long >& terminals)
{
	vector<unsigned long > values;
	string prefix = "";

	//Read header for terminals
	readNextNumbers(1, values, bitstream, prefix);
	if (values.empty())
		cerr << ("Error in decoding: File not found or empty") << endl;
	int count = values[0];
	
	if (count < 1)
		cerr << ("GammaCode::decodeDictionaryFile: Terminal count is " + to_string(count)) << endl;
	values.clear();

	//Read terminals
	readNextNumbers(count, values, bitstream, prefix);
	for (auto entry : values)	
		terminals.push_back(entry);
	
	values.clear();

	//Read number of generations
	readNextNumbers(1, values, bitstream, prefix);
	int generationCount = (values)[0];
	
	if (generationCount < 1)
		cerr << ("GammaCode::decodeDictionaryFile: Generation count is " + to_string(generationCount)) << endl;
	values.clear();

	int binarySize, i;
	unsigned long  leftVal;
	vector<unsigned long > left;
	for (int g = 0; g < generationCount; ++g)
	{
		//Read generation header
		readNextNumbers(2, values, bitstream, prefix);
		count = (values)[0];
		
		binarySize = 1 + floor(log2((values)[1]));//Second nr. is the max index m, so binary size is 1 + floor(log2(m))
		
		values.clear();
		if (count < 1)
			cerr << ("GammaCode::decodeDictionaryFile: Pair count less than 1 in generation " + to_string(g)) << endl;
		if (binarySize < 1)
			cerr << ("GammaCode::decodeDictionaryFile: Binary size is " + to_string(binarySize)) << endl;

		//Read left values and store them in 'left'
		readNextNumbers(count, left, bitstream, prefix);

		//Read right element binaries and write pairs
		leftVal = 0;
		i = 0;
		while (i < count)
		{
			readNextBinaries(binarySize, count, values, bitstream, prefix);
			for (int j = 0; j < values.size(); ++j)
			{
				leftVal += (left)[i];
				CompactPair c(leftVal, (values)[j]);
				pairs.push_back(c);
				
				++i;
			}
			values.clear();
		}
		left.clear();
	}	
}