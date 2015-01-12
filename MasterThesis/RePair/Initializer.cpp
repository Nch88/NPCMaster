#include "stdafx.h"
#include "Initializer.h"

using namespace std;

Initializer::Initializer()
{
}


Initializer::~Initializer()
{
}


void Initializer::SequenceArray(string filename,
	vector<SymbolRecord*> * sequenceArray,
	unordered_map<string, PairRecord> * activePairs)
{
	char newSymbol;
	char oldSymbol;
	string pair;
	int index = 0;

	PairRecord* tmpRecord;
	SymbolRecord* previousOccurence;
	SymbolRecord* newOccurence;

	ifstream file(filename);

	if (file.is_open())
	{
		file >> noskipws >> oldSymbol;
		sequenceArray->push_back(new SymbolRecord(oldSymbol, index++));

		while (file >> noskipws >> newSymbol)
		{
			sequenceArray->push_back(new SymbolRecord(newSymbol, index++));
			stringstream ss;
			ss << oldSymbol << newSymbol;
			ss >> pair;

			tmpRecord = &(*activePairs)[pair];
			tmpRecord->pair = pair;

			if (tmpRecord->getCount() == 0) //First occurence of active pair
			{
				tmpRecord->inc();
				tmpRecord->setIndexFirst(sequenceArray->size() - 2); //First symbol in active pair
				tmpRecord->setIndexLast(sequenceArray->size() - 2);
				tmpRecord->nextPair = NULL;
				tmpRecord->previousPair = NULL;
			}
			else
			{
				tmpRecord->inc();

				previousOccurence = (*sequenceArray)[tmpRecord->getIndexLast()];
				newOccurence = (*sequenceArray)[sequenceArray->size() - 2];

				previousOccurence->next = newOccurence;
				newOccurence->previous = previousOccurence;

				tmpRecord->setIndexLast(sequenceArray->size() - 2);
			}

			oldSymbol = newSymbol;
		}

		file.close();
	}
}

void Initializer::PriorityQueue(int priorityQueueSize,
	unordered_map<string, PairRecord> * activePairs,
	vector<PairRecord*> * priorityQueue)
{
	int priorityIndex; //Pair count - 2, PQ only counts active pairs


	for (unordered_map<string, PairRecord>::iterator it = (*activePairs).begin(); it != (*activePairs).end(); it++)
	{
		if (it->second.count >= 2)
		{
			if (it->second.count > priorityQueueSize)
				priorityIndex = priorityQueueSize - 1;

			else
				priorityIndex = it->second.count - 2;


			if ((*priorityQueue)[priorityIndex] == NULL)
				(*priorityQueue)[priorityIndex] = &(it->second);

			else
			{
				(*priorityQueue)[priorityIndex]->previousPair = &(it->second);
				it->second.nextPair = (*priorityQueue)[priorityIndex];
				(*priorityQueue)[priorityIndex] = &(it->second);
			}
		}
	}
}