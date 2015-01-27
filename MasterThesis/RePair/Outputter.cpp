#include "stdafx.h"
#include "Outputter.h"

using namespace std;

Outputter::Outputter()
{
}


Outputter::~Outputter()
{
}

string Outputter::createName(string inputFile, string addName)
{
	string outFile = "";
	int i = 0;
	int empty = 0;

	while (inputFile[i] != '.')
		outFile += inputFile[i++];

	outFile += addName;
	
	while (inputFile[i] != empty)
		outFile += inputFile[i++];

	return outFile;
}

void Outputter::compressedFile(
	string inputFile, 
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "Compressed");

	if (firstBlock)
		myfile.open(outFile, ios::trunc);
	else
		myfile.open(outFile, ios::app);

	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != 0)
			myfile << (*sequenceArray)[i]->symbol;
	}
	myfile << UINT_MAX;
	myfile.close();

	if (firstBlock)
		cout << "created compressed file: " << outFile << endl;
}

void Outputter::dictionary(
	string inputFile,
	unique_ptr<unordered_map<unsigned int, Pair>>& dictionary,
	bool firstBlock)
{
	ofstream myfile;
	string outFile = createName(inputFile, "CompressedDictionary");

	if (firstBlock)
		myfile.open(outFile, ios::trunc);
	else
		myfile.open(outFile, ios::app);

	for each (auto pair in (*dictionary))
	{
		myfile << pair.first << " " << pair.second.leftSymbol << "" << pair.second.rightSymbol << endl;
	}
	myfile << UINT_MAX << endl;
	myfile.close();

	if (firstBlock)
		cout << "created dictionary file: " << outFile << endl;
}