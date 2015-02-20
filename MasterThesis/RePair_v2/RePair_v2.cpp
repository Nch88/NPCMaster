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
	AlgorithmP algP;
	Initializer init;
	Conditions c;
	c.timing = false;
	c.verbose = true;
	MyTimer t;
	int r = 0;

	string input1 = "diddy.txt";
	string input2 = "E.coli";
	string input3 = "dna.50MB";
	string input4 = "crashtestdummy.txt";
	string input5 = "world192.txt";
	string input6 = "bible.txt";

	filename = input2;
	

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
			dictionary,
			symbols);
	}
	else
	{
		cout << "Problem opening file: " << filename << endl;
		return 1;
	}
	
	return r;
}

