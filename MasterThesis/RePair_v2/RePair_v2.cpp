// RePair_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;



int main(int argc, char* argv[])
{
	string filename;
	int blockSize;
	blockSize = 1048576;

	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	//unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(256);

	Initializer init;
	Conditions c;
	c.timing = false;
	c.verbose = true;
	MyTimer t;

	string input1 = "diddy.txt";
	string input2 = "E.coli";
	string input3 = "dna.50MB";

	filename = input2;
	

	ifstream file(filename);

	if (file.is_open())
	{
		while (file.is_open())
		{
			if (c.timing)
			{
				t.start();
				cout << "Timing init of Sequence array and active pairs" << endl;
			}
			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);

			if (c.timing)
			{
				t.stop();
				cout << "Init of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
			}

			if (c.timing)
			{
				t.start();
				cout << "Timing reset of Sequence array and active pairs" << endl;
			}
			init.resetForNextBlock(activePairs, sequenceArray, blockSize);
			if (c.timing)
			{
				t.stop();
				cout << "Reset of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
			}
		}
	}
	else
	{
		cout << "Problem opening file: " << filename << endl;
		return 1;
	}
	return 0;
}

