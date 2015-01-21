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
	unsigned int leftSymbol,
	unsigned int rightSymbol,
	int offset,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs)
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

void Initializer::SequenceArray(string filename,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs,
	Conditions& c)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int index = 0;
	bool skippedPair = false;
	MyTimer t;

	if (c.verbose)
	{
		cout << "Initializing sequence array and setting up active pairs" << endl;
	}
	if (c.timing)
	{
		t.start();
	}

	ifstream file(filename);

	if (file.is_open())
	{
		if (file >> noskipws >> previousSymbol)
		{
			sequenceArray->push_back(make_shared<SymbolRecord>((unsigned int)previousSymbol, index++));

			if (file >> noskipws >> leftSymbol)
			{
				sequenceArray->push_back(make_shared<SymbolRecord>((unsigned int)leftSymbol, index++));

				setupPairRecord(
					(unsigned int)previousSymbol,
					(unsigned int)leftSymbol,
					2,
					sequenceArray,
					activePairs);
			}
		}

		while (file >> noskipws >> rightSymbol)
		{
			sequenceArray->push_back(make_shared<SymbolRecord>((unsigned int)rightSymbol, index++));

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
				(unsigned int)leftSymbol,
				(unsigned int)rightSymbol,
				2,
				sequenceArray,
				activePairs);

			skippedPair = false;
			previousSymbol = leftSymbol;
			leftSymbol = rightSymbol;
		}
		file.close();
	}
	else
	{
		if (c.verbose)
		{
			cout << "Problem opening file: " << filename << endl;
		}
	}
	if (c.timing)
	{
		t.stop();
		cout << "sequence array and active pairs initialized in " << t.getTime() << " ms" << endl;
	}
	if (c.verbose)
	{
		cout << "Initialized sequence array with size: " << sequenceArray->size() << endl;
	}
	if (c.extraVerbose)
	{
		int count = 0;
		for each (auto leftSymbol in (*activePairs))
		{
			for each (auto pair in leftSymbol.second)
			{
				count++;
			}
		}
		cout << "Initialized active pairs with: " << count << " pairs" << endl;
	}
	else if (c.verbose)
	{
		cout << "Initialized active pairs with more than: " << activePairs->size() << " pairs" << endl;
	}
}

void Initializer::PriorityQueue(int priorityQueueSize,
	unique_ptr<unordered_map<unsigned int, unordered_map<unsigned int, shared_ptr<PairTracker>>>>& activePairs,
	unique_ptr<vector<shared_ptr<PairRecord>>>& priorityQueue,
	Conditions& c)
{
	int priorityIndex; //Pair count - 2, PQ only counts active pairs
	shared_ptr<PairRecord> tmpRecord;
	MyTimer t;

	if (c.verbose)
	{
		cout << "Initializing priority queue" << endl;
	}
	if (c.timing)
	{
		t.start();
	}

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
					/*while (tmpRecord->nextPair)
					{
						tmpRecord = tmpRecord->nextPair;
					}
					tmpRecord->nextPair = (it.second->pairRecord);*/

					
					/*it.second->pairRecord->previousPair = tmpRecord;
					it.second->pairRecord->nextPair = NULL;*/

					tmpRecord->previousPair = it.second->pairRecord;
					(*priorityQueue)[priorityIndex] = it.second->pairRecord;
					it.second->pairRecord->nextPair = tmpRecord;
					it.second->pairRecord->previousPair = NULL;
				}
			}
		}
	}	

	if (c.timing)
	{
		t.stop();
		cout << "priority queue initialized in " << t.getTime() << " ms" << endl;
	}
	if (c.verbose)
	{
		cout << "Initialized priority queue" << endl;
	}
	
}