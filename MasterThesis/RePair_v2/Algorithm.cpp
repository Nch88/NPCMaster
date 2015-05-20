#include "stdafx.h"
#include "Algorithm.h"

using namespace std;
using namespace google;

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

int Algorithm::run(
	string &filename,
	ifstream & file,
	Conditions &c,
	Initializer &init,
	AlgorithmP &algP,
	MyTimer &t,
	int blockSize,
	dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*> & priorityQueue,
	unsigned long  & symbols)
{
	int priorityQueueSize;
	bool firstBlock = true;
	Huffman h;
	Outputter out;
	dense_hash_map<unsigned long , HuffmanNode *> huffmanCodes;
	unordered_set<unsigned long > terminals;
	cout << "Compressing file: " << filename << endl;

	while (file.is_open())
	{
		if (c.test)
		{
			c.ts->s_nrOfBlocks++;
		}
		if (c.verbose)
		{
			cout << " - Verbose: Initializing block" << endl;
		}
		if (c.timing)
		{
			t.start();
		}
		if (c.test)
		{
			c.ts->testTimer.start();
		}
		//sequenceArray.reserve(blockSize);
		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);

		if (c.timing)
		{
			t.stop();
			cout << " - Timing: Init of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		priorityQueueSize = sqrt(sequenceArray.size());
		priorityQueue.resize(priorityQueueSize);
		if (c.test)
		{
			c.ts->addMemory("initPrio", priorityQueueSize);

			//For calculating averages across blocks
			if (c.ts->s_nrOfBlocks == 1)
			{
				c.ts->s_fullBlockSize = c.ts->s_currentBlockSize;
			}
			else
			{
				c.ts->s_lastBlockSize = c.ts->s_currentBlockSize;
			}
		}
			
		if (c.timing)
		{
			t.start();
		}
		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
		if (c.test)
		{
			c.ts->testTimer.stop();
			c.ts->t_initialization += c.ts->testTimer.getTimeNano();
		}
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: priority queue initialized in " << t.getTime() << " ms" << endl;
		}

		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			cout << " - Verbose: Starting repair compression" << endl;
		}
		if (c.test)
		{
			c.ts->testTimer.start();
		}
		algP.run(
			sequenceArray,
			activePairs,
			priorityQueue,
			symbols,
			c);			
		if (c.test)
		{
			c.ts->testTimer.stop();
			c.ts->t_repair += c.ts->testTimer.getTimeNano();
		}
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: repair compression done in " << t.getTime() << " ms" << endl;
		}

		init.resetBeforeOutput(activePairs, priorityQueue);

		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			cout << " - Verbose: Starting Huffman encoding and outputting" << endl;
		}
		
		out.all(
			filename,
			firstBlock,
			sequenceArray,
			c);
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: Huffman encoding and outputting files done in " << t.getTime() << " ms" << endl;
		}

		firstBlock = false;
		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			cout << " - Verbose: Resetting for next block" << endl;
		}
		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue);
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: Reset of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		file.peek();
		if (file.eof())
			file.close();
		if (c.test)
		{
			c.ts->resetForNextBlock();
		}
	}
	if (c.test)
	{
		c.ts->calculateAverages();
	}
	cout << "Completed compression of file: " << filename << endl;
	init.resetCompleted(blockSize, activePairs, sequenceArray);
	return 0;
}