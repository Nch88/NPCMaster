// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int rePair(string input, bool verbose, bool extraVerbose, bool timer)
{	
	Initializer init;

	return init.SequenceArray(input, verbose, extraVerbose, timer);
}

int main(int argc, char* argv[])
{	
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
	//extraVerbose = true;

	

	string input1 = "diddy.txt";
	string input2 = "duplicates.txt";
	string input3 = "world192.txt";
	string input4 = "bible.txt";
	string input5 = "E.coli";
	string input6 = "duplicatesLong.txt";
	string input7 = "duplicatesLong2.txt";
	string input8 = "duplicatesLong3.txt";
	string input9 = "duplicatesLong4.txt";
	string input10 = "dna.50MB";
	string input11 = "english.50MB";

	input = input10;

	return rePair(input, verbose, extraVerbose, timer);
}

