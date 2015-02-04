#include "stdafx.h"
#include "Initializer.h"

using namespace std;

Initializer::Initializer()
{
}

Initializer::~Initializer()
{
}

void Initializer::resetForNextBlock(
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord*> & sequenceArray,
	int blockSize)
{
	//Reset for next block
	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i])
		{
			if (i == blockSize - 10)
			{
				int x = 9;
			}
			delete sequenceArray[i];
			sequenceArray[i] = nullptr;
		}
	}
	
	/*sequenceArray.clear();
	sequenceArray.resize(blockSize);*/

	for each (auto leftSymbol in activePairs)
	{
		for each (auto rightSymbol in leftSymbol.second)
		{
			delete rightSymbol.second.pairRecord;
		}
	}
	activePairs.clear();
}

void Initializer::setupPairRecord(
	unsigned int leftSymbol,
	unsigned int rightSymbol,
	int offset,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord*> & sequenceArray)
{
	PairTracker * currentTracker;
	SymbolRecord * previousOccurence;
	SymbolRecord * newOccurence;

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

int Initializer::SequenceArray(
	Conditions c,
	ifstream & file,
	int & blockSize,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord*> & sequenceArray)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int symbolCount = 0;
	long index = 0;
	bool skippedPair = false;
	MyTimer t;
	c.timing = false;
	if (file >> noskipws >> previousSymbol)
	{
		sequenceArray[index] = new SymbolRecord((unsigned int)previousSymbol, index);
		index++;
		symbolCount++;

		if (file >> noskipws >> leftSymbol)
		{
			sequenceArray[index] = new SymbolRecord((unsigned int)leftSymbol, index);
			index++;
			symbolCount++;

			
			setupPairRecord(
				(unsigned int)previousSymbol,
				(unsigned int)leftSymbol,
				0,
				activePairs,
				sequenceArray);
			
		}
		while (symbolCount < blockSize && file >> noskipws >> rightSymbol)
		{
			if (c.timing)
			{
				t.start();
				cout << "	Timing push back onto Sequence array" << endl;
			}
			sequenceArray[index] = new SymbolRecord((unsigned int)rightSymbol, index);
			index++;
			if (c.timing)
			{
				t.stop();
				long long tmp = t.getTime();
				if (tmp > 1)
					cout << "	Time of push back onto Sequence array took " << tmp << " ms" << endl;
			}
			symbolCount++;

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
					cout << "	Timing setup pair record" << endl;
				}
				setupPairRecord(
				(unsigned int)leftSymbol,
				(unsigned int)rightSymbol,
				index - 2,
				activePairs,
				sequenceArray);
				if (c.timing)
				{
					t.stop();
					long long tmp = t.getTime();
					if (tmp > 1)
						cout << "	Time of setting up pair record took " << tmp << " ms" << endl;
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