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

	while (inputFile[i] != '.')
		outFile += inputFile[i++];

	outFile += addName;
	
	while (inputFile[i] != '\0')
		outFile += inputFile[i++];

	return outFile;
}

void Outputter::compressedFile(
	string inputFile, 
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray)
{
	ofstream myfile;
	string outFile = createName(inputFile, "Compressed");

	myfile.open(outFile);

	for (int i = 0; i < sequenceArray->size(); i++)
	{
		if ((*sequenceArray)[i]->symbol != (char)0)
			myfile << (*sequenceArray)[i]->symbol;
	}
	myfile.close();
	cout << "created compressed file: " << outFile << endl;
}

void Outputter::dictionary(
	string inputFile,
	unique_ptr<unordered_map<char, string>>& dictionary)
{
	ofstream myfile;
	string outFile = createName(inputFile, "CompressedDictionary");

	myfile.open(outFile);

	for each (auto pair in (*dictionary))
	{
		myfile << pair.first << " " << pair.second << endl;
	}

	myfile.close();
	cout << "created dictionary file: " << outFile << endl;
}