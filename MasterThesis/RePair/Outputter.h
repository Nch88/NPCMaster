#include "stdafx.h"

using namespace std;
#pragma once
class Outputter
{
public:
	Outputter();
	~Outputter();

	string createName(string inputFile, string addName);
	void compressedFile(
		string inputFile,
		unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
		bool firstBlock);
	void dictionary(
		string inputFile,
		unique_ptr<unordered_map<unsigned int, Pair>>& dictionary,
		bool firstBlock);
};
