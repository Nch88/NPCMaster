#include "stdafx.h"

using namespace google;

Huffman::Huffman()
{
}


Huffman::~Huffman()
{
}

void Huffman::getFrequencies(
	vector<SymbolRecord*> & sequenceArray,
	dense_hash_map<unsigned long , HuffmanNode> & frequencies,
	unsigned long  &cardinality,
	Conditions &c)
{
		for each (auto &symbolRecord in sequenceArray)
		{
			if (symbolRecord->symbol != 0)
			{
				frequencies[symbolRecord->symbol].frequency++;
				if (frequencies[symbolRecord->symbol].frequency == 1)
				{
					++cardinality;
					if (c.test)
						c.ts->addMemory("huffEncFreq", c.ts->huffmanNodeWords);
				}
					
			}
		}
		if (cardinality <= 0)
		{
			cerr << "Huffman::getFrequencies cardinality is " + to_string(cardinality) << endl;
		}	
}


void Huffman::sift(
	int currentNodeIndex,
	int heapSize,
	int *codeLengths)
{
	
	int leftChildIndex = ((currentNodeIndex + 1) * 2) - 1;
	int rightChildIndex = (((currentNodeIndex + 1) * 2) + 1) - 1;

	if (leftChildIndex >= heapSize)												//Stop the recursion
		return;
	if (heapSize == 2)
		int x = 0;

	int frequencyIndex = codeLengths[currentNodeIndex];
	int parentFrequency = codeLengths[frequencyIndex];
	frequencyIndex = codeLengths[leftChildIndex];
	int leftChildFrequency = codeLengths[frequencyIndex];
	int rightChildFrequency = leftChildFrequency;
	if (rightChildIndex < heapSize)
	{
		frequencyIndex = codeLengths[rightChildIndex];
		rightChildFrequency = codeLengths[frequencyIndex];
	}
		

	if (rightChildIndex < heapSize &&
		leftChildFrequency > rightChildFrequency)
																				//Right child is smaller than left
	
	{
		if (parentFrequency > rightChildFrequency)
		{
																				//Swap with right child
			int tmpIndex = codeLengths[currentNodeIndex];
			codeLengths[currentNodeIndex] = codeLengths[rightChildIndex];
			codeLengths[rightChildIndex] = tmpIndex;

			sift(rightChildIndex, heapSize, codeLengths);
			
		}
	}
	else if (parentFrequency > leftChildFrequency)
																				//Left is smaller than right or right does not exist, 
																				//and left is smaller than parent
	{
																				//Swap with left child
		int tmpIndex = codeLengths[currentNodeIndex];
		codeLengths[currentNodeIndex] = codeLengths[leftChildIndex];
		codeLengths[leftChildIndex] = tmpIndex;

		sift(leftChildIndex, heapSize, codeLengths);
	}
}

void Huffman::initCodeLengthsArray(
	int cardinality,
	int *codeLengths,
	dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes)
{
		if (cardinality <= 0)
			cerr << ("Huffman::initCodeLengthsArray cardinality is " + to_string(cardinality)) << endl;

		int i = 0;
		for each (auto node in huffmanCodes)
		{
			codeLengths[cardinality + i] = node.second.frequency;
			codeLengths[i] = cardinality + i;										//Index of a symbol Points to the symbol's frequency
			++i;
		}
}

void Huffman::initMinHeap(
	int heapSize,
	int *codeLengths)
{
		if (heapSize <= 0)
			cerr << ("Huffman::initMinHeap heapSize is " + to_string(heapSize)) << endl;

		int currentNodeIndex = heapSize - 1;										//Last node
		currentNodeIndex = currentNodeIndex / 2;									//Parent of last node

		while (currentNodeIndex >= 0)
		{
			sift(currentNodeIndex, heapSize, codeLengths);
			--currentNodeIndex;
		}
	
}

void Huffman::collapseHuffmanTree(
	int heapSize,
	int *codeLengths)
{
		if (heapSize <= 0)
			cerr << ("Huffman::initMinHeap heapSize is " + to_string(heapSize)) << endl;

		int m1;
		int m2;

		while (heapSize > 1)
		{
			//a)
			m1 = codeLengths[0];													//Take symbol with smallest frequency
			codeLengths[0] = codeLengths[heapSize - 1];								//Pull last element to front of heap
			--heapSize;

			//b)
			sift(0, heapSize, codeLengths);											//Sift the last element down through the heap
			m2 = codeLengths[0];													//Take symbol with next smallest frequency

			//c)
			codeLengths[(heapSize - 1) + 1] = codeLengths[m1] + codeLengths[m2];	//Create new frequency for combination of two smallest frequencies
			codeLengths[0] = (heapSize - 1) + 1;									//"Create" new symbol pointing to the new frequency
			codeLengths[m1] = (heapSize - 1) + 1;									//Point to new symbol
			codeLengths[m2] = (heapSize - 1) + 1;									//Point to new symbol

			//d)
			sift(0, heapSize, codeLengths);											//Sift the new element down through the heap
		}
	
}

void Huffman::expandHuffmanTree(
	unsigned long  cardinality,
	int *codeLengths,
	unsigned long  &maxLength)
{
		codeLengths[1] = 0;															//Represents the root with code length one
		maxLength = 0;
		for (int i = 2; i < cardinality * 2; i++)
		{
			codeLengths[i] = codeLengths[codeLengths[i]] + 1;						//Nodes will get codes of length one greater than their parents
			if (codeLengths[i] > maxLength)
				maxLength = codeLengths[i];
		}

		if (maxLength <= 0)
			cerr << ("Huffman::expandHuffmanTree, maxlength is " + to_string(maxLength)) << endl;
	
}

void Huffman::getCodeLengths(
	unsigned long  cardinality,
	int *codeLengths,
	dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes,
	unsigned long  &maxLength)																//Assigns a value to maxLength as an output
{
	int heapSize = cardinality;
	//Phase 1	
	initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);
	initMinHeap(heapSize, codeLengths);
	//Phase 1  - end

	collapseHuffmanTree(heapSize, codeLengths);

	expandHuffmanTree(cardinality, codeLengths, maxLength);
}

string Huffman::codeToString(int intCode, int length)
{
		if (length <= 0)
			cerr << ("Huffman::codeToString, length is " + to_string(length)) << endl;

		string stringCode = "";
		for (int i = length - 1; i >= 0; --i)
		{
			int v = intCode & (1 << i);
			if (v == 0)
				stringCode += "0";
			else
				stringCode += "1";
		}
		return stringCode;
	
}

void Huffman::generateCanonicalHuffmanCodes(
	unsigned long  cardinality,
	unsigned long  maxLength,
	int *codeLengths,
	unsigned long  *firstCode,
	unsigned long  *numl,
	dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &huffmanToSymbol,
	Conditions &c)
{
		if (maxLength <= 0)
			cerr << ("Huffman::generateCanonicalHuffmanCodes, Maxlength is " + to_string(maxLength)) << endl;

		for (unsigned long  i = 0; i < maxLength; i++)											//Init codelengths with zero
			numl[i] = 0;

		for (unsigned long  i = cardinality; i < cardinality * 2; i++)							//Count number of codes with same length
			++numl[codeLengths[i] - 1];

		firstCode[maxLength - 1] = 0;

		for (int i = maxLength - 2; i >= 0; --i)									//Calculates value of first code for each code length
			firstCode[i] = (firstCode[i + 1] + numl[i + 1]) / 2;

		int *nextCode = new int[maxLength];

		if (c.test)
			c.ts->addMemory("huffEncNextCodes", maxLength);

		for (int i = 0; i < maxLength; i++)
			nextCode[i] = firstCode[i];

		unsigned long  codes = 0;
		for (auto &huffmanNode : huffmanCodes)									//For each symbol, look up its code by its length in the nextcode structure 
		{
			int codeLength = codeLengths[cardinality + codes];
			string code = codeToString(nextCode[codeLength - 1], codeLength);
			huffmanNode.second.code.assign(code);

			if (c.test)
				c.ts->addMemory("huffEncHuffmanCodes", codeLength / 4.0); //Because we count in words and not bytes.

			if (huffmanToSymbol[codeLength].empty())
			{
				huffmanToSymbol[codeLength].set_empty_key(-1);
				huffmanToSymbol[codeLength].set_deleted_key(-2);
			}
			huffmanToSymbol[codeLength][nextCode[codeLength - 1]] = huffmanNode.first;
			if (c.test)
				c.ts->addMemory("huffEncHuffmanToSymbol", 4);
			++nextCode[codeLength - 1];
			++codes;
		}

		delete[] nextCode;
	
}

void Huffman::encode(
	vector<SymbolRecord*> &sequenceArray,
	dense_hash_map<unsigned long , HuffmanNode> &huffmanCodes,
	unsigned long  *&firstCode,
	unsigned long  *&numl,
	unsigned long  &maxLength,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &huffmanToSymbol,
	Conditions &c)
{	
	unsigned long  cardinality = 0;
	getFrequencies(sequenceArray, huffmanCodes, cardinality, c);					//+ cardinality of compressed sequence
	int *codeLengths = new int[cardinality * 2];	
	if (c.test)
		c.ts->addMemory("huffEncCodeLength", cardinality * 2);
	getCodeLengths(cardinality, codeLengths, huffmanCodes, maxLength);

	firstCode = new unsigned long [maxLength];
	numl = new unsigned long [maxLength];
	if (c.test)
	{
		if (maxLength > c.ts->s_huffmanCodeLength_max && c.ts->firstBlock)
		{
			c.ts->s_huffmanCodeLength_max = maxLength;
		}		
		c.ts->addMemory("huffEncFirstCodes", maxLength);
		c.ts->addMemory("huffEncNrOfCodes", maxLength);
	}
	generateCanonicalHuffmanCodes(cardinality, maxLength, codeLengths, firstCode, numl, huffmanCodes, huffmanToSymbol, c);

	delete[] codeLengths;
}

void Huffman::fillBitset(int rawChunk, bitset<32> *chunk)
{
	for (int i = 0; i < 32; i++)
	{
		int v = rawChunk & (1 << i);
		if (v == 0)
			chunk->set(i, false);
		else
			chunk->set(i, true);
	}
}

void Huffman::fillBitset(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, bitset<32> *chunk)
{	
	char rawChunk = rawChunk4;
	
	for (int i = 0; i < 32; i++)
	{
		if (i == 8)
			rawChunk = rawChunk3;
		if (i == 16)
			rawChunk = rawChunk2;
		if (i == 24)
			rawChunk = rawChunk1;

		int v = rawChunk & (1 << (i % 8));					//Read one bit from the current char sized chunk
		if (v == 0)
			chunk->set(i, false);
		else
			chunk->set(i, true);
	}	
}

void Huffman::fillString(char rawChunk1, char rawChunk2, char rawChunk3, char rawChunk4, string &chunk)
{
	char rawChunk = rawChunk1;
	chunk = "";

	for (int i = 0; i < 32; i++)
	{
		if (i == 8)
			rawChunk = rawChunk2;
		if (i == 16)
			rawChunk = rawChunk3;
		if (i == 24)
			rawChunk = rawChunk4;

		int v = rawChunk & (1 << (7 - (i % 8)));									//Read one bit from the current char sized chunk
		if (v == 0)
			chunk += '0';
		else
			chunk += '1';
	}
}

void Huffman::readFromGammaCodes(
	unsigned long  symbolsToRead,
	ifstream &bitstream,
	GammaCode &gc,
	string &chunk,
	string &prefix,
	vector<unsigned long > &intValues)
{
	char rawChunk1 = 0;
	char rawChunk2 = 0;
	char rawChunk3 = 0;
	char rawChunk4 = 0;

	string temp = "";
	if (symbolsToRead < 1)
		cerr << ("Huffman::readFromGammaCodes calls GammaCode::decodeGammaString: with " + to_string(symbolsToRead)) << endl;
	gc.decodeGammaString(prefix, temp, intValues, symbolsToRead);

	while (intValues.size() < symbolsToRead)
	{
		bitstream.peek();
		if (!bitstream.eof())
		{
			bitstream.get(rawChunk1);
			bitstream.get(rawChunk2);
			bitstream.get(rawChunk3);
			bitstream.get(rawChunk4);
			fillString(rawChunk1, rawChunk2, rawChunk3, rawChunk4, chunk);

			
			//testofs << chunk << "\n";
			
		}
		else
			chunk = "";

		gc.decodeGammaString(prefix, chunk, intValues, symbolsToRead);
		
	}
}


void Huffman::decodeDictionary(
	ifstream &bitstream,
	unsigned long  *&firstCodes,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &symbolIndices)
	//Outputs symbolIndices
{
	GammaCode gc;
	//void GammaCode::gammaToInt (string &prefix, string gamma, vector<unsigned long > actual, unsigned long  count);
	if (bitstream.is_open())
	{
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		string chunk = "";
		string prefix = "";
		unsigned long  maxLength = 0;
		unsigned long  symbolsToRead = 0;
		unsigned long  firstCode = 0;
		unsigned long  lastCode = 0;
		vector<unsigned long > intValues;

		symbolsToRead = 1;

		readFromGammaCodes(
			symbolsToRead,
			bitstream,
			gc,
			chunk,
			prefix,
			intValues);

		maxLength = intValues[0];
		
		if (maxLength <= 0)
			cerr << ("Huffman::decodeDictionary, Maxlength is " + to_string(maxLength)) << endl;

		intValues.clear();
		firstCodes = new unsigned long [maxLength];
		//symbolIndices: code length -> Huffman code -> index
		for (unsigned long  i = 0; i < maxLength; i++)
		{
			//Read the number of codes of length i + 1 and the first code of that length
			symbolsToRead = 2;
			readFromGammaCodes(
				symbolsToRead,
				bitstream,
				gc,
				chunk,
				prefix,
				intValues);

			symbolsToRead = intValues[0];
			
			firstCode = intValues[1];
			
			if (firstCode < 0)
			{
				cerr << ("Huffman::decodeDictionary, firstCode is " + to_string(firstCode)) << endl;
			}
			firstCodes[i] = firstCode;
			if (symbolsToRead > 0)
				lastCode = firstCode + symbolsToRead - 1;						//Find the last code for this size of code,
			//this is used for efficiency when resetting intValues below
			intValues.clear();													//Reset the vector holding values already used

			//Read the corresponding i + 1 sequence indexes
			if (symbolsToRead > 0)
				readFromGammaCodes(
					symbolsToRead,
					bitstream,
					gc,
					chunk,
					prefix,
					intValues);

			
			

			//Add sequence indexes to dictionary based on Huffman code length
			while (intValues.size() > 0)
			{
				if (symbolIndices[i + 1].empty())
				{
					symbolIndices[i + 1].set_empty_key(-1);
					symbolIndices[i + 1].set_deleted_key(-2);
				}
				(symbolIndices)[i + 1][lastCode] = intValues[intValues.size() - 1];
				--lastCode;
				intValues.pop_back();											//Remove index we already processed
			}
		}
	}
}

void Huffman::decode(
	unsigned long  *firstCode,
	ifstream &bitstream,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , unsigned long >> &symbolIndices,
	vector<unsigned long > &symbolIndexSequence)
{
	if (bitstream.is_open())
	{
		int length = 0;
		int value;
		char rawChunk1 = 0;
		char rawChunk2 = 0;
		char rawChunk3 = 0;
		char rawChunk4 = 0;
		bitset<32> *chunk = new bitset<32>();
		bitset<32> *nextChunk = new bitset<32>();
		int bitIndexMax = 30;		
		int currentBitIndex = bitIndexMax;
		int padding = 0;
		bool endOfBlock = false;

		bitstream.get(rawChunk1);													//Read first chunk
		bitstream.get(rawChunk2);
		bitstream.get(rawChunk3);
		bitstream.get(rawChunk4);
		fillBitset(rawChunk1, rawChunk2, rawChunk3, rawChunk4, nextChunk);

		while (!endOfBlock)
		{
			//Read chunks of data from file
			for (int i = 0; i < 32; i++)
			{
				chunk->set(i, nextChunk->test(i));
			}
			
			bitstream.get(rawChunk1);													
			bitstream.get(rawChunk2);
			bitstream.get(rawChunk3);
			bitstream.get(rawChunk4);
			fillBitset(rawChunk1, rawChunk2, rawChunk3, rawChunk4, nextChunk);

			currentBitIndex = bitIndexMax;

			if (nextChunk->test(bitIndexMax + 1))									//Last chunk
			{
				endOfBlock = true;

				//read number of padding bits from last block
				nextChunk->set(bitIndexMax + 1, false);
				padding = nextChunk->to_ulong();
			}
			
			while (currentBitIndex >= padding)
			{
				//Canonical Huffman decoding, init for new symbol
				if (length == 0)
				{
					length = 1;
					value = (*chunk)[currentBitIndex];
					--currentBitIndex;
				}				

				while (value < firstCode[length - 1] && currentBitIndex >= padding)		//Read bits until we find a symbol
				{
					value = 2 * value + (*chunk)[currentBitIndex];
					--currentBitIndex;
					++length;
				}

				if (value >= firstCode[length - 1])
				{
					if (symbolIndices[length].empty())
					{
						symbolIndices[length].set_empty_key(-1);
						symbolIndices[length].set_deleted_key(-2);
					}
					long symbolIndex = (symbolIndices)[length][value];
					symbolIndexSequence.push_back(symbolIndex);
					length = 0;
					value = 0;
				}
			}
		}
		delete chunk;
		delete nextChunk;
	}
}