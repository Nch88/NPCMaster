#include "stdafx.h"
#include "Initializer.h"

using namespace std;

Initializer::Initializer()
{
}


Initializer::~Initializer()
{
}

void Initializer::setupPairRecord(
	char leftSymbol,
	char rightSymbol,
	int offset,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs)
{
	shared_ptr<PairRecord> tmpRecord;
	shared_ptr<SymbolRecord> previousOccurence;
	shared_ptr<SymbolRecord> newOccurence;
	string pair;
	stringstream ss;
	ss << leftSymbol << rightSymbol;
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
		tmpRecord->setIndexFirst(sequenceArray->size() - offset); //First symbol in active pair
		tmpRecord->setIndexLast(sequenceArray->size() - offset);
		tmpRecord->nextPair = NULL;
		tmpRecord->previousPair = NULL;
	}
	else
	{
		tmpRecord->inc();

		previousOccurence = (*sequenceArray)[tmpRecord->getIndexLast()];
		newOccurence = (*sequenceArray)[sequenceArray->size() - offset];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		tmpRecord->setIndexLast(sequenceArray->size() - offset);
	}
}

void Initializer::checkSymbol(char symbol, unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	if ((int)symbol >= 128)	
		(*symbolMap)[symbol] = true;	
}

void Initializer::SequenceArray(string filename,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<string, shared_ptr<PairRecord>>>& activePairs,
	unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int index = 0;
	bool skippedPair = false;

	ifstream file(filename);

	if (file.is_open())
	{
		if (file >> noskipws >> previousSymbol)
		{
			sequenceArray->push_back(make_shared<SymbolRecord>(previousSymbol, index++));
			checkSymbol(previousSymbol, symbolMap);

			if (file >> noskipws >> leftSymbol)
			{
				sequenceArray->push_back(make_shared<SymbolRecord>(leftSymbol, index++));
				checkSymbol(leftSymbol, symbolMap);

				setupPairRecord(
					previousSymbol,
					leftSymbol,
					2,
					sequenceArray,
					activePairs);
			}
		}

		while (file >> noskipws >> rightSymbol)
		{
			sequenceArray->push_back(make_shared<SymbolRecord>(rightSymbol, index++));
			checkSymbol(rightSymbol, symbolMap);

			if (leftSymbol == rightSymbol && 
				leftSymbol == previousSymbol &&
				!skippedPair)
			{
				skippedPair = true;
				previousSymbol = leftSymbol;
				leftSymbol = rightSymbol;
				continue;
			}
			setupPairRecord(
				leftSymbol,
				rightSymbol,
				2,
				sequenceArray,
				activePairs);

			skippedPair = false;
			previousSymbol = leftSymbol;
			leftSymbol = rightSymbol;
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