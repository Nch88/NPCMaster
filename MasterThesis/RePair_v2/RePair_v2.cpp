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
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(256);

	Algorithm algorithm;
	Initializer init;
	Conditions c;
	c.timing = false;
	c.verbose = true;
	MyTimer t;
	int r = 0;

	string input1 = "diddy.txt";
	string input2 = "E.coli";
	string input3 = "dna.50MB";

	filename = input2;
	

	ifstream file(filename);

	if (file.is_open())
	{		
		r = algorithm.run(
			filename,
			file,
			c,
			init,
			t,
			blockSize,
			activePairs,
			sequenceArray,
			priorityQueue);
	}
	else
	{
		cout << "Problem opening file: " << filename << endl;
		return 1;
	}
	
	return r;
}

