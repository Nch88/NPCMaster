// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int main(int argc, char* argv[])
{	
	auto dictionary = make_unique<unordered_map<unsigned int, Pair>>();
	auto activePairs = make_unique<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<unsigned int>(256);

	bool verbose = false;
	bool extraVerbose = false;
	bool timer = false;
	string input = "";

	string progName;
	string filename;
	string condition1;
	string condition2;

	/*switch (argc)
	{	
	case 1:
		cout << "No file input, terminating." << endl;
		return 1;
		break;
	case 2:
		filename = *(new string(argv[1]));
		input = filename;
		break;
	case 3:
		filename = *(new string(argv[1]));
		condition1 = *(new string(argv[2]));

		input = filename;

		if (condition1 == "verbose" || condition1 == "v")
			verbose = true;
		else if (condition1 == "eVerbose" || condition1 == "eV")
		{
			verbose = true;
			extraVerbose = true;
		}
		else if (condition1 == "timing" || condition1 == "t")
			timer = true;
		else
			goto default_label;
		break;
	case 4:
		filename = *(new string(argv[1]));
		condition1 = *(new string(argv[2]));
		condition2 = *(new string(argv[3]));

		input = filename;

		if (condition1 == "verbose" || condition1 == "v")
			verbose = true;
		else if (condition1 == "eVerbose" || condition1 == "eV")
		{
			verbose = true;
			extraVerbose = true;
		}		
		else
			goto default_label;

		if (condition2 == "timing" || condition2 == "t")
			timer = true;		
		else
			goto default_label;
		break;
	default:
		default_label:
		cout << "Bad input parameters, parameters can be:" << endl;
		cout << "filename" << endl;
		cout << "'filename' verbose / v" << endl;
		cout << "'filename' eVerbose / eV" << endl;
		cout << "'filename' timing / t" << endl;
		cout << "'filename' v/eV t" << endl;
		return 1;
		break;
	}*/

	verbose = true;
	extraVerbose = true;

	MyTimer t;
			
	Initializer init;
	AlgorithmP algP;
	MyTest test;
	Outputter out;
	Conditions c(verbose, extraVerbose, timer);

	string input1 = "diddy.txt";
	string input2 = "duplicates.txt";
	string input3 = "world192.txt";
	string input4 = "bible.txt";
	string input5 = "E.coli";
	string input6 = "duplicatesLong.txt";
	string input7 = "duplicatesLong2.txt";
	string input8 = "duplicatesLong3.txt";
	string input9 = "duplicatesLong4.txt";

	input = input3;
	

	init.SequenceArray(input, sequenceArray, activePairs,c );

	if (sequenceArray->size() == 0)
	{
		cout << "Problem reading input file, terminating" << endl;
		return 1;
	}
	
	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray->size());

	auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);	

	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);	

	//See fig. 4, algorithm P
	if (c.verbose)
	{
		cout << "Running Re-Pair compression algorithm" << endl;
	}
	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		Symbols,
		c);
	
	out.compressedFile(input, sequenceArray);
	out.dictionary(input, dictionary);

	return 0;
}

