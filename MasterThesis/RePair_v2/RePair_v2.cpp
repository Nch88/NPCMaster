// RePair_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	string filename;
	int blockSize;

	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord> sequenceArray;
	//unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(256);

	Initializer init;
	Conditions c;

	string input1 = "diddy.txt";

	filename = input1;
	blockSize = 1048576;

	ifstream file(filename);

	if (file.is_open())
	{
		while (file.is_open())
		{
			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
		}
	}
	else
	{
		cout << "Problem opening file: " << filename << endl;
		return 1;
	}
	return 0;
}

