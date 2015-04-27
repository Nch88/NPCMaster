// RePair_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace google;

void getArg(char *& arg, string &result)
{
	result = "";

	while (*arg != '\0')
	{
		result += *arg;
		++arg;
	}
}

int setMode(string &mode)
{
	if (mode == "e" || mode == "encoding")
		return 1;
	if (mode == "d" || mode == "decoding")
		return 2;
	return 0;
}

int asciiToInt(const int &v)
{
	switch (v)
	{
	case 48:
			return 0;
	case 49:
		return 1;
	case 50:
		return 2;
	case 51:
		return 3;
	case 52:
		return 4;
	case 53:
		return 5;
	case 54:
		return 6;
	case 55:
		return 7;
	case 56:
		return 8;
	case 57:
		return 9;

	default:
		return -1;
		break;
	}
}

int stringToInt(string &arg, int &result)
{
	int size = arg.size();
	result = 0;
	if (size > 2000000000)
		return 2;

	for (int i = 0; i < size; i++)
	{
		if ((int)arg[i] >= 48 && (int)arg[i] <= 57)						//Check that the arg is a number
		{
			result += (asciiToInt((int)arg[i]) * (pow(10, size - i - 1)));			//Add the value according to base 10 interpretation
		}
		else
			return 1;
	}
	return 0;
}

int interpretParameter(char *&arg, Conditions &c, int &blockSize)
{
	string argS;
	getArg(arg, argS);

	if (argS == "v" || argS == "verbose")
		c.verbose = true;
	else if (argS == "ev" || argS == "extraverbose")
	{
		c.verbose = true;
		c.extraVerbose = true;
	}
	else if (argS == "t" || argS == "timing")
		c.timing = true;
	else if (argS == "c" || argS == "compact")
		c.compact = true;
	else if (argS == "test")
		c.test = true;
	else
	{		
		int mbs = 1;
		int error = stringToInt(argS, mbs);
		if (error != 0)
		{
			if (error == 1)
			{
				cerr << "Interpret as block size failed, bad parameter." << endl;
				return 7;
			}
			if (error == 2)
			{
				cerr << "Desired multiple of 1MB for block size approaches limit of int." << endl;
				return 8;
			}
			
		}
		if (mbs <= 1000)
			blockSize = blockSize * mbs;
		else
			cout << "Block size is too large, using default of 1MB." << endl;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	string filename;
	string mode;
	int encodingDecoding = 0;
	bool verbose = false;
	bool extraVerbose = false;
	bool timer = false;
	

	if (argc <= 2)
	{
		cout << "No file input, exiting." << endl;
		return 4;
	}
	getArg(argv[1], filename);
	getArg(argv[2], mode);
	encodingDecoding = setMode(mode);

	if (encodingDecoding == 1)
		//Do encoding
	{
		dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> activePairs;
		activePairs.set_empty_key(-1);
		activePairs.set_deleted_key(-2);

		vector<SymbolRecord*> sequenceArray;
		vector<PairRecord*> priorityQueue;
		dense_hash_map<unsigned long , Pair> dictionary;
		dictionary.set_empty_key(-1);
		dictionary.set_deleted_key(-2);

		unsigned long  symbols(initialSymbolValue);

		Algorithm algorithm;
		AlgorithmP algP;
		Initializer init;
		Conditions c;
		MyTimer t;
		int r = 1;
		int blockSize = 1048576;

		//Interpret additional arguments that might be present
		for (int i = 3; i < argc; i++)
		{
			interpretParameter(argv[i], c, blockSize);
		}

		if (c.test)
		{
			c.ts = new TestSuite();
			c.ts->s_filename.assign(filename);
		}

		ifstream file(filename);

		if (file.is_open())
		{
			r = algorithm.run(
				filename,
				file,
				c,
				init,
				algP,
				t,
				blockSize,
				activePairs,
				sequenceArray,
				priorityQueue,
				symbols);

			if (c.test)
			{
				c.ts->WriteToFileEncoding();
			}
		}
		else
		{
			cout << "Problem opening file: " << filename << endl;
			return 5;
		}
		return r;
	}
	else if (encodingDecoding == 2)
		//Do decoding
	{
		if (argc > 3)
			cout << "Ignoring all arguments past the first two, not allowed for decoding." << endl;
		Decoder dec;
		dec.decode(filename);
	}
	else
	{
		cout << "Mode not set correct, exiting." << endl;
		return 6;
	}
}

