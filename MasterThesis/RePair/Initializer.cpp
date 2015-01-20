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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs)
{
	shared_ptr<PairTracker> tmpTracker;
	shared_ptr<SymbolRecord> previousOccurence;
	shared_ptr<SymbolRecord> newOccurence;

	tmpTracker = (*activePairs)[leftSymbol][rightSymbol];
	if (!tmpTracker)
	{
		(*activePairs)[leftSymbol][rightSymbol] = make_shared<PairTracker>();
		tmpTracker = (*activePairs)[leftSymbol][rightSymbol];
	}

	if (tmpTracker->seenOnce)
	{
		tmpTracker->pairRecord = make_shared<PairRecord>();

		tmpTracker->pairRecord->pair.leftSymbol = leftSymbol;
		tmpTracker->pairRecord->pair.rightSymbol = rightSymbol;
		tmpTracker->pairRecord->count += 2;
		tmpTracker->pairRecord->arrayIndexFirst = tmpTracker->indexFirst; //First symbol in active pair
		tmpTracker->pairRecord->setIndexLast(sequenceArray->size() - offset);
		tmpTracker->pairRecord->nextPair = NULL;
		tmpTracker->pairRecord->previousPair = NULL;

		previousOccurence = (*sequenceArray)[tmpTracker->pairRecord->arrayIndexFirst];
		newOccurence = (*sequenceArray)[tmpTracker->pairRecord->arrayIndexLast];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		tmpTracker->indexFirst = -1;
		tmpTracker->seenOnce = false;
	}
	else if (tmpTracker->pairRecord)
	{
		tmpTracker->pairRecord->inc();

		previousOccurence = (*sequenceArray)[tmpTracker->pairRecord->getIndexLast()];
		newOccurence = (*sequenceArray)[sequenceArray->size() - offset];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		tmpTracker->pairRecord->setIndexLast(sequenceArray->size() - offset);
	}
	else
	{
		tmpTracker->seenOnce = true;
		tmpTracker->indexFirst = sequenceArray->size() - offset;
	}
}

void Initializer::checkSymbol(char symbol, unique_ptr<unordered_map<char, bool>>& symbolMap)
{
	if ((int)symbol >= 128)	
		(*symbolMap)[symbol] = true;	
}

void Initializer::SequenceArray(string filename,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
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
	unique_ptr<unordered_map<char, unordered_map<char, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue)
{
	int priorityIndex; //Pair count - 2, PQ only counts active pairs
	shared_ptr<PairRecord> tmpRecord;

	for each (auto leftSymbol in (*activePairs))
	{
		for each (auto it in leftSymbol.second)
		{
			it.second->seenOnce = false;
			if (it.second->pairRecord && it.second->pairRecord->count >= 2)
			{
				if (it.second->pairRecord->count > priorityQueueSize)
					priorityIndex = priorityQueueSize - 1;

				else
					priorityIndex = it.second->pairRecord->count - 2;


				if ((*priorityQueue)[priorityIndex] == NULL)
					(*priorityQueue)[priorityIndex] = (it.second->pairRecord);

				else
				{
					tmpRecord = (*priorityQueue)[priorityIndex];
					while (tmpRecord->nextPair)
					{
						tmpRecord = tmpRecord->nextPair;
					}
					tmpRecord->nextPair = (it.second->pairRecord);
					it.second->pairRecord->previousPair = tmpRecord;
					it.second->pairRecord->nextPair = NULL;
				}
			}
		}
	}	
}