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
	long leftSymbol,
	long rightSymbol,
	int offset,
	unique_ptr<vector<shared_ptr<SymbolRecord>>>& sequenceArray,
	unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs)
{
	shared_ptr<PairTracker> currentTracker;
	shared_ptr<SymbolRecord> previousOccurence;
	shared_ptr<SymbolRecord> newOccurence;

	currentTracker = (*activePairs)[leftSymbol][rightSymbol];
	if (!currentTracker)
	{
		(*activePairs)[leftSymbol][rightSymbol] = make_shared<PairTracker>();
		currentTracker = (*activePairs)[leftSymbol][rightSymbol];
	}

	if (currentTracker->seenOnce)
	{
		currentTracker->pairRecord = make_shared<PairRecord>();

		currentTracker->pairRecord->pair.leftSymbol = leftSymbol;
		currentTracker->pairRecord->pair.rightSymbol = rightSymbol;
		currentTracker->pairRecord->count = 2;
		currentTracker->pairRecord->arrayIndexFirst = currentTracker->indexFirst; //First symbol in active pair
		currentTracker->pairRecord->setIndexLast(sequenceArray->size() - offset);
		currentTracker->pairRecord->nextPair = NULL;
		currentTracker->pairRecord->previousPair = NULL;

		previousOccurence = (*sequenceArray)[currentTracker->pairRecord->arrayIndexFirst];
		newOccurence = (*sequenceArray)[currentTracker->pairRecord->arrayIndexLast];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		currentTracker->indexFirst = -1;
		currentTracker->seenOnce = false;
	}
	else if (currentTracker->pairRecord)
	{
		currentTracker->pairRecord->inc();

		previousOccurence = (*sequenceArray)[currentTracker->pairRecord->getIndexLast()];
		newOccurence = (*sequenceArray)[sequenceArray->size() - offset];

		previousOccurence->next = newOccurence;
		newOccurence->previous = previousOccurence;

		currentTracker->pairRecord->setIndexLast(sequenceArray->size() - offset);
	}
	else
	{
		currentTracker->seenOnce = true;
		currentTracker->indexFirst = sequenceArray->size() - offset;
	}
}

int Initializer::SequenceArray(string filename,
	bool verbose,
	bool extraVerbose,
	bool timer)
{
	char previousSymbol;
	char leftSymbol;
	char rightSymbol;
	int index = 0;
	int blockSize = 1048576;
	int symbolCount = 0;
	bool skippedPair = false;
	bool firstBlock = true;
	MyTimer t;

	AlgorithmP algP;
	MyTest test;
	Outputter out;
	Conditions c(verbose, extraVerbose, timer);

	auto dictionary = make_unique<dense_hash_map<long, Pair>>();
	auto activePairs = make_unique<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>();
	auto sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
	auto Symbols = make_unique<long>(256);
	
	ifstream file(filename);

	if (file.is_open())
	{
		while (file.is_open())
		{
			if (c.verbose)
			{
				cout << "Initializing sequence array and setting up active pairs" << endl;
			}
			if (c.timing)
			{
				t.start();
			}

			if (file >> noskipws >> previousSymbol)
			{
				sequenceArray->push_back(make_shared<SymbolRecord>((long)previousSymbol, index++));
				symbolCount++;

				if (file >> noskipws >> leftSymbol)
				{
					sequenceArray->push_back(make_shared<SymbolRecord>((long)leftSymbol, index++));
					symbolCount++;

					setupPairRecord(
						(long)previousSymbol,
						(long)leftSymbol,
						2,
						sequenceArray,
						activePairs);
				}
			}

			while (symbolCount < blockSize && file >> noskipws >> rightSymbol)
			{
				sequenceArray->push_back(make_shared<SymbolRecord>((long)rightSymbol, index++));
				symbolCount++;

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
					(long)leftSymbol,
					(long)rightSymbol,
					2,
					sequenceArray,
					activePairs);

				skippedPair = false;
				previousSymbol = leftSymbol;
				leftSymbol = rightSymbol;
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

			if (symbolCount >= blockSize ||
				(!(file >> noskipws >> rightSymbol) &&
				sequenceArray->size() > 0))
			{
				if (sequenceArray->size() == 0)
				{
					cout << "Problem reading input file, terminating" << endl;
					return 1;
				}
				
				int priorityQueueSize;

				priorityQueueSize = sqrt(sequenceArray->size());

				auto priorityQueue = make_unique<vector<shared_ptr<PairRecord>>>(priorityQueueSize);
				PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

				//See fig. 4, algorithm P
				if (c.verbose)
				{
					cout << "Running Re-Pair compression algorithm" << endl;
				}

				algP.run(
					sequenceArray,
					dictionary,
					activePairs,
					priorityQueue,
					Symbols,
					c);

				out.compressedFile(filename, sequenceArray, firstBlock);
				out.dictionary(filename, dictionary, firstBlock);

				if (c.verbose)
				{
					cout << "Finished compressing block of size: " << blockSize << " bytes" << endl;
				}

				//Reset, then read new block
				symbolCount = 0;
				index = 0;
				firstBlock = false;
				dictionary.release();
				activePairs.release();
				sequenceArray.release();
				priorityQueue.release();
				dictionary = make_unique<dense_hash_map<long, Pair>>();
				activePairs = make_unique<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>();
				sequenceArray = make_unique<vector<shared_ptr<SymbolRecord>>>();
				//Symbols = make_unique<long>(256);
			}
			else
				file.close();
		}
	}
	else
	{
		if (c.verbose)
		{
			cout << "Problem opening file: " << filename << endl;
		}
	}
	cout << "Finished compressing file: " << filename << endl;
	return 0;
}

void Initializer::PriorityQueue(int priorityQueueSize,
	unique_ptr<dense_hash_map<long, dense_hash_map<long, shared_ptr<PairTracker>>>>& activePairs,
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