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
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs)
{
	char newSymbol;
	char oldSymbol;
	string pair;
	int index = 0;

	shared_ptr<PairRecord> tmpRecord;
	shared_ptr<SymbolRecord> previousOccurence;
	shared_ptr<SymbolRecord> newOccurence;

	ifstream file(filename);

	if (file.is_open())
	{
		file >> noskipws >> oldSymbol;
		sequenceArray->push_back(make_shared<SymbolRecord>(oldSymbol, index++));

		while (file >> noskipws >> newSymbol)
		{
			sequenceArray->push_back(make_shared<SymbolRecord>(newSymbol, index++));
			stringstream ss;
			ss << oldSymbol << newSymbol;
			ss >> pair;

			tmpRecord = (*activePairs)[pair];
			if (!tmpRecord)
			{
				(*activePairs)[pair] = make_shared<PairRecord>();
				tmpRecord = (*activePairs)[pair];
			}

			if (tmpRecord->getCount() == 0) //First occurence of active pair
			{
				tmpRecord->pair = pair;
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
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
{
	int priorityIndex; //Pair count - 2, PQ only counts active pairs
	shared_ptr<PairRecord> tmpRecord;

	for each (auto it in (*activePairs))
	{
		if (it.second->count >= 2)
		{			
			if (it.second->count > priorityQueueSize)
				priorityIndex = priorityQueueSize - 1;

			else
				priorityIndex = it.second->count - 2;


			if ((*priorityQueue)[priorityIndex] == NULL)
				(*priorityQueue)[priorityIndex] = (it.second);

			else
			{
				tmpRecord = (*priorityQueue)[priorityIndex];
				while (tmpRecord->nextPair)
				{
					tmpRecord = tmpRecord->nextPair;
				}
				tmpRecord->nextPair = (it.second);
				it.second->previousPair = tmpRecord;
				it.second->nextPair = NULL;
				/*(*priorityQueue)[priorityIndex]->previousPair = (it.second);
				it.second->nextPair = (*priorityQueue)[priorityIndex];
				(*priorityQueue)[priorityIndex] = (it.second);*/
			}
		}
	}	
}