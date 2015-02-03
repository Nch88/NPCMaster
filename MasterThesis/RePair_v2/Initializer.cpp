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
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord> & sequenceArray)
{
	PairTracker * currentTracker;
	SymbolRecord previousOccurence;
	SymbolRecord newOccurence;

	currentTracker = & activePairs[leftSymbol][rightSymbol];
	if (!currentTracker)
	{
		activePairs[leftSymbol][rightSymbol] = *(new PairTracker());
		currentTracker = & activePairs[leftSymbol][rightSymbol];
	}

	if (currentTracker->seenOnce)
	{
		currentTracker->pairRecord = new PairRecord();

		currentTracker->pairRecord->count = 2;
		currentTracker->pairRecord->arrayIndexFirst = currentTracker->indexFirst; //First symbol in active pair
		currentTracker->pairRecord->arrayIndexLast = sequenceArray.size() - offset;
		currentTracker->pairRecord->nextPair = NULL;
		currentTracker->pairRecord->previousPair = NULL;

		previousOccurence = sequenceArray[currentTracker->pairRecord->arrayIndexFirst];
		newOccurence = sequenceArray[currentTracker->pairRecord->arrayIndexLast];

		previousOccurence.next = &newOccurence;
		newOccurence.previous = &previousOccurence;

		currentTracker->indexFirst = -1;
		currentTracker->seenOnce = false;
	}
	else if (currentTracker->pairRecord)
	{
		currentTracker->pairRecord->count++;

		previousOccurence = sequenceArray[currentTracker->pairRecord->arrayIndexLast];
		newOccurence = sequenceArray[sequenceArray.size() - offset];

		previousOccurence.next = &newOccurence;
		newOccurence.previous = &previousOccurence;

		currentTracker->pairRecord->arrayIndexLast = sequenceArray.size() - offset;
	}
	else
	{
		currentTracker->seenOnce = true;
		currentTracker->indexFirst = sequenceArray.size() - offset;
	}
}

int Initializer::SequenceArray(
	Conditions c,
	ifstream & file,
	int & blockSize,
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord> & sequenceArray)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int symbolCount = 0;
	int index = 0;
	bool skippedPair = false;

	if (file >> noskipws >> previousSymbol)
	{
		sequenceArray.push_back(*(new SymbolRecord((unsigned int)previousSymbol, index++)));
		symbolCount++;

		if (file >> noskipws >> leftSymbol)
		{
			sequenceArray.push_back(*(new SymbolRecord((unsigned int)leftSymbol, index++)));
			symbolCount++;

			setupPairRecord(
				(unsigned int)previousSymbol,
				(unsigned int)leftSymbol,
				2,
				activePairs,
				sequenceArray);
		}
		while (symbolCount < blockSize && file >> noskipws >> rightSymbol)
		{
			sequenceArray.push_back(*(new SymbolRecord((unsigned int)rightSymbol, index++)));
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
				setupPairRecord(
				(unsigned int)leftSymbol,
				(unsigned int)rightSymbol,
				2,
				activePairs,
				sequenceArray);

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

	return 0;
}