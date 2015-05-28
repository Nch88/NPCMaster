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
	int blockSize,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray)
{
	//Reset sequence array when we are done
	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i])
		{
			delete sequenceArray[i];
			sequenceArray[i] = nullptr;
		}
	}
	sequenceArray.clear();

	//Reset active pairs when we are done
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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<pair<PairRecord*,PairRecord*>> & priorityQueue)
{
	//We do not free the memory between blocks as entries will be reused
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
		priorityQueue[i].first = nullptr;
	}

	//Here we need to free memory between blocks
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
}

void Initializer::resetBeforeOutput(
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> &activePairs,
	vector<pair<PairRecord*,PairRecord*>> & priorityQueue)
{

	for (int i = 0; i < priorityQueue.size(); i++)
	{
		priorityQueue[i].first = nullptr;
	}

	//Here we need to free memory between blocks
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
}

void Initializer::setupPairRecord(
	unsigned long  leftSymbol,
	unsigned long  rightSymbol,
	int index,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	Conditions &c)
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
	
	//Pair is seen twice and now considered active
	if (currentTracker->seenOnce)
	{
		currentTracker->pairRecord = new PairRecord();

		currentTracker->pairRecord->count = 2;
		currentTracker->pairRecord->arrayIndexFirst = currentTracker->indexFirst; //First symbol in active pair
		currentTracker->pairRecord->arrayIndexLast = index;
		currentTracker->pairRecord->nextPair = NULL;
		currentTracker->pairRecord->previousPair = NULL;

		sequenceArray[currentTracker->pairRecord->arrayIndexFirst]->next =
			sequenceArray[currentTracker->pairRecord->arrayIndexLast];
		sequenceArray[currentTracker->pairRecord->arrayIndexLast]->previous =
			sequenceArray[currentTracker->pairRecord->arrayIndexFirst];

		currentTracker->indexFirst = -1;
		currentTracker->seenOnce = false;

		if (c.test)
		{
			c.ts->addMemory("initPair", c.ts->pairRecordWords); //Dense hash map uses extra memory
			if (c.ts->firstBlock)
				c.ts->s_maxPairs++;
		}
			
	}
	//Pair is already active, update its record
	else if (currentTracker->pairRecord)
	{
		currentTracker->pairRecord->count++;

		previousOccurence = sequenceArray[currentTracker->pairRecord->arrayIndexLast];
		newOccurence = sequenceArray[index];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		currentTracker->pairRecord->arrayIndexLast = index;
	}
	//First time the pair is seen
	else
	{
		currentTracker->seenOnce = true;
		currentTracker->indexFirst = index;

		if (c.test)
		{
			c.ts->addMemory("initTracker", c.ts->pairTrackerWords); //Dense hash map uses extra memory
		}
	}
}

void Initializer::addToSequenceArray(	
	unsigned char & symbol,
	long & index,
	int & symbolCount,
	vector<SymbolRecord*> & sequenceArray)
{													//Record all terminal symbols
	if (index < sequenceArray.size())
	{
		sequenceArray[index]->symbol = (unsigned long )symbol;
	}
	else
	{
		sequenceArray.push_back(new SymbolRecord((unsigned long )symbol, index));
	}	
	index++;
	symbolCount++;
}

int Initializer::SequenceArray(
	Conditions &c,
	ifstream & file,
	int & blockSize,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray)
{
	unsigned char previousSymbol;
	unsigned char leftSymbol;
	unsigned char rightSymbol;
	int symbolCount = 0;
	long index = 0;
	bool skippedPair = false;
	MyTimer t;
	c.timing = false;

	//We read two symbols ahead to check for sequences of duplicate symbols
	if (file >> noskipws >> previousSymbol && previousSymbol)
	{
		addToSequenceArray(previousSymbol, index, symbolCount, sequenceArray);
		if (c.test)
		{
			c.ts->addMemory("initSeq", c.ts->symbolRecordWords);
			c.ts->c_origSize++;
			c.ts->s_currentBlockSize++;
		}
			

		if (file >> noskipws >> leftSymbol && leftSymbol)
		{
			addToSequenceArray(leftSymbol, index, symbolCount, sequenceArray);
			if (c.test)
			{
				c.ts->addMemory("initSeq", c.ts->symbolRecordWords);
				c.ts->c_origSize++;
				c.ts->s_currentBlockSize++;
			}
			
			setupPairRecord(
				(unsigned long )previousSymbol,
				(unsigned long )leftSymbol,
				0,
				activePairs,
				sequenceArray,
				c);
			
		}
		//Read symbols until we reach the determined block size
		while (symbolCount < blockSize && file >> noskipws >> rightSymbol && rightSymbol)
		{
			
			addToSequenceArray(rightSymbol, index, symbolCount, sequenceArray);
			if (c.test)
			{
				c.ts->addMemory("initSeq", c.ts->symbolRecordWords);
				c.ts->c_origSize++;
				c.ts->s_currentBlockSize++;
			}
			
			
			//Skip if the current symbols is the right part of a pair of identical symbols
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
				
				setupPairRecord(
				(unsigned long )leftSymbol,
				(unsigned long )rightSymbol,
				index - 2,
				activePairs,
				sequenceArray,
				c);
				

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
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<pair<PairRecord*,PairRecord*>> & priorityQueue,
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
			rightSymbol.second.seenOnce = false; //Reset as we need this to be false for later checks
			if (rightSymbol.second.pairRecord)
			{
				if (rightSymbol.second.pairRecord->count > priorityQueueSize)
					priorityIndex = priorityQueueSize - 1;
				else
					priorityIndex = rightSymbol.second.pairRecord->count - 2;

				if (priorityQueue[priorityIndex].first == nullptr)
				{
					priorityQueue[priorityIndex].first = rightSymbol.second.pairRecord;
					priorityQueue[priorityIndex].second = rightSymbol.second.pairRecord;
				}
				else
				{
					tmpRecord = priorityQueue[priorityIndex].first;
					
					tmpRecord->previousPair = rightSymbol.second.pairRecord;
					priorityQueue[priorityIndex].first = rightSymbol.second.pairRecord;
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