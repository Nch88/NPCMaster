// RePair_v2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;
using namespace google;


int main(int argc, char* argv[])
{
	string filename;
	int blockSize;
	blockSize = 1048576;


	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);

	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);

	long symbols(initialSymbolValue);

	Algorithm algorithm;
	AlgorithmP algP;
	Initializer init;
	Conditions c;
	c.timing = true;
	c.verbose = false;
	MyTimer t;
	int r = 0;

	string input1 = "diddy.txt";
	string input2 = "E.coli";
	string input3 = "dna.50MB";
	string input4 = "crashtestdummy.txt";
	string input5 = "world192.txt";
	string input6 = "bible.txt";

	filename = input1;
	

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
	
	//Clean up of large structures is handled by the program when it exits.
	return r;
}

