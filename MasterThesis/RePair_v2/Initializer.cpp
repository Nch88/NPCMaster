#include "stdafx.h"
#include "Initializer.h"

using namespace std;
using namespace google;

Initializer::Initializer()
{
}

Initializer::~Initializer()
{
}

void Initializer::resetCompleted(
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	int blockSize)
{
	

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i])
		{
			delete sequenceArray[i];
			sequenceArray[i] = nullptr;
		}
	}
	sequenceArray.clear();

	for each (auto leftSymbol in activePairs)
	{
		for each (auto rightSymbol in leftSymbol.second)
		{
			delete rightSymbol.second.pairRecord;
		}
	}
	activePairs.clear();
}

void Initializer::resetForNextBlock(
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*> & priorityQueue,
	unordered_set<long> & terminals,
	dense_hash_map<long, Pair> &dictionary)
{
	//Reset for next block
	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i])
		{
			sequenceArray[i]->next = nullptr;
			sequenceArray[i]->previous = nullptr;
			sequenceArray[i]->symbol = 0;
		}
	}

	for (int i = 0; i < priorityQueue.size(); i++)
	{
		priorityQueue[i] = nullptr;
	}

	for each (auto leftSymbol in activePairs)
	{
		for each (auto rightSymbol in leftSymbol.second)
		{
			delete rightSymbol.second.pairRecord;
			rightSymbol.second.indexFirst = -1;
			rightSymbol.second.seenOnce = false;
		}
	}
	activePairs.clear();

	terminals.clear();
	
	dictionary.clear();
}

void Initializer::setupPairRecord(
	long leftSymbol,
	long rightSymbol,
	int offset,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray)
{
	PairTracker * currentTracker;
	SymbolRecord * previousOccurence;
	SymbolRecord * newOccurence;
	if (activePairs[leftSymbol].empty())
	{
		activePairs[leftSymbol].set_empty_key(-1);
		activePairs[leftSymbol].set_deleted_key(-2);
	}
	currentTracker = & activePairs[leftSymbol][rightSymbol];
	/*if (!currentTracker)
	{
		activePairs[leftSymbol][rightSymbol] = *(new PairTracker());
		currentTracker = & activePairs[leftSymbol][rightSymbol];
	}*/

	if (currentTracker->seenOnce)
	{
		currentTracker->pairRecord = new PairRecord();

		currentTracker->pairRecord->count = 2;
		currentTracker->pairRecord->arrayIndexFirst = currentTracker->indexFirst; //First symbol in active pair
		currentTracker->pairRecord->arrayIndexLast = offset;
		currentTracker->pairRecord->nextPair = NULL;
		currentTracker->pairRecord->previousPair = NULL;

		sequenceArray[currentTracker->pairRecord->arrayIndexFirst]->next =
			sequenceArray[currentTracker->pairRecord->arrayIndexLast];
		sequenceArray[currentTracker->pairRecord->arrayIndexLast]->previous =
			sequenceArray[currentTracker->pairRecord->arrayIndexFirst];


		/*previousOccurence = &sequenceArray[currentTracker->pairRecord->arrayIndexFirst];
		newOccurence = &sequenceArray[currentTracker->pairRecord->arrayIndexLast];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;*/

		currentTracker->indexFirst = -1;
		currentTracker->seenOnce = false;
	}
	else if (currentTracker->pairRecord)
	{
		currentTracker->pairRecord->count++;

		previousOccurence = sequenceArray[currentTracker->pairRecord->arrayIndexLast];
		newOccurence = sequenceArray[offset];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		currentTracker->pairRecord->arrayIndexLast = offset;
	}
	else
	{
		currentTracker->seenOnce = true;
		currentTracker->indexFirst = offset;
	}
}

void Initializer::addToSequenceArray(
	vector<SymbolRecord*> & sequenceArray,
	char & symbol,
	long & index,
	int & symbolCount,
	unordered_set<long>& terminals)
{
	terminals.emplace(symbol);
	if (index < sequenceArray.size())
	{
		sequenceArray[index]->symbol = (long)symbol;
	}
	else
	{
		sequenceArray.push_back(new SymbolRecord((long)symbol, index));
	}	
	index++;
	symbolCount++;
}

int Initializer::SequenceArray(
	Conditions c,
	ifstream & file,
	int & blockSize,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	unordered_set<long>& terminals)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int symbolCount = 0;
	long index = 0;
	bool skippedPair = false;
	MyTimer t;
	c.timing = false;

	if (file >> noskipws >> previousSymbol && previousSymbol)
	{
		addToSequenceArray(sequenceArray, previousSymbol, index, symbolCount, terminals);

		if (file >> noskipws >> leftSymbol && leftSymbol)
		{
			addToSequenceArray(sequenceArray, leftSymbol, index, symbolCount, terminals);
			
			setupPairRecord(
				(long)previousSymbol,
				(long)leftSymbol,
				0,
				activePairs,
				sequenceArray);
			
		}
		while (symbolCount < blockSize && file >> noskipws >> rightSymbol && rightSymbol)
		{
			if (c.timing)
			{
				t.start();
				cout << " - Timing: Timing push back onto Sequence array" << endl;
			}
			addToSequenceArray(sequenceArray, rightSymbol, index, symbolCount, terminals);
			if (c.timing)
			{
				t.stop();
				long long tmp = t.getTime();
				if (tmp > 1)
					cout << " - Timing: Time of push back onto Sequence array took " << tmp << " ms" << endl;
			}
			

			if (leftSymbol == rightSymbol &&
				leftSymbol == previousSymbol &&
				!skippedPair)
			{
				skippedPair = true;
				previousSymbol = leftSymbol;
				leftSymbol = rightSymbol;
			}
			else
			{
				if (c.timing)
				{
					t.start();
					cout << " - Timing: Timing setup pair record" << endl;
				}
				setupPairRecord(
				(long)leftSymbol,
				(long)rightSymbol,
				index - 2,
				activePairs,
				sequenceArray);
				if (c.timing)
				{
					t.stop();
					long long tmp = t.getTime();
					if (tmp > 1)
						cout << " - Timing: Time of setting up pair record took " << tmp << " ms" << endl;
				}

				skippedPair = false;
				previousSymbol = leftSymbol;
				leftSymbol = rightSymbol;
			}			
		}

		if (symbolCount != blockSize)
		{
			file.close();
		}
	}
	else
		file.close();

	return 0;
}

void Initializer::PriorityQueue(int priorityQueueSize,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<PairRecord*> & priorityQueue,
	Conditions & c)
{
	int priorityIndex; //Pair count - 2, PQ only counts active pairs
	PairRecord * tmpRecord;

	if (c.verbose)
	{
		cout << " - Verbose: Initializing priority queue" << endl;
	}
	

	for each (auto leftSymbol in activePairs)
	{
		for each (auto rightSymbol in leftSymbol.second)
		{
			rightSymbol.second.seenOnce = false;
			if (rightSymbol.second.pairRecord)
			{
				if (rightSymbol.second.pairRecord->count > priorityQueueSize)
					priorityIndex = priorityQueueSize - 1;

				else
					priorityIndex = rightSymbol.second.pairRecord->count - 2;


				if (priorityQueue[priorityIndex] == nullptr)
					priorityQueue[priorityIndex] = rightSymbol.second.pairRecord;

				else
				{
					tmpRecord = priorityQueue[priorityIndex];
					
					tmpRecord->previousPair = rightSymbol.second.pairRecord;
					priorityQueue[priorityIndex] = rightSymbol.second.pairRecord;
					rightSymbol.second.pairRecord->nextPair = tmpRecord;
					rightSymbol.second.pairRecord->previousPair = nullptr;
				}
			}
		}
	}

	
	if (c.verbose)
	{
		cout << " - Verbose: Initialized priority queue" << endl;
	}

}