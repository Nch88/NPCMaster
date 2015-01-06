// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char newSymbol;
	char oldSymbol;
	string pair;
	PairRecord* tmpRecord;
	SymbolRecord previousOccurence;
	SymbolRecord newOccurence;

	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;

	ifstream file("diddy.txt");

	if (file.is_open())
	{
		file >> noskipws >> oldSymbol;
		sequenceArray.push_back(new SymbolRecord(oldSymbol));

		while (file >> noskipws >> newSymbol)
		{
			sequenceArray.push_back(new SymbolRecord(newSymbol));
			stringstream ss;
			ss << oldSymbol << newSymbol;
			ss >> pair;
			
			tmpRecord = &activePairs[pair];

			if (tmpRecord->getCount() == 0) //First occurence of active pair
			{
				tmpRecord->inc();
				tmpRecord->setIndexFirst(sequenceArray.size() - 2); //First symbol in active pair
				tmpRecord->setIndexLast(sequenceArray.size() - 2);
			}
			else
			{
				tmpRecord->inc();
				

				previousOccurence = *sequenceArray[tmpRecord->getIndexLast()];
				newOccurence = *sequenceArray[sequenceArray.size() - 2];

				previousOccurence.setNext(&newOccurence);
				newOccurence.setPrevious(&previousOccurence);

				tmpRecord->setIndexLast(sequenceArray.size() - 2);
			}

			oldSymbol = newSymbol;
		}

		file.close();
	}

	for (unordered_map<string, PairRecord>::iterator it = activePairs.begin(); it != activePairs.end(); it++)
	{
		cout << "Pair: " << it->first << " with count:  " << it->second.getCount() << endl;
	}

	return 0;
}

