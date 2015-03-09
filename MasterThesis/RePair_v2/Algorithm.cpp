#include "stdafx.h"
#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm()
{
}


Algorithm::~Algorithm()
{
}

int Algorithm::run(
	string filename,
	ifstream & file,
	Conditions c,
	Initializer init,
	AlgorithmP algP,
	MyTimer t,
	int blockSize,
	unordered_map<long, unordered_map<long, PairTracker>> & activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*> & priorityQueue,
	unordered_map<long, Pair> & dictionary,
	long & symbols)
{
	int priorityQueueSize;
	bool firstBlock = true;
	Huffman h;
	Outputter out;
	unordered_map<long, HuffmanNode *> huffmanCodes;
	unordered_set<long> terminals;
	cout << "Compressing file: " << filename << endl;

	while (file.is_open())
	{
		if (c.verbose)
		{
			cout << " - Verbose: Initializing block" << endl;
		}
		if (c.timing)
		{
			t.start();
			cout << " - Timing: init of Sequence array and active pairs" << endl;
		}
		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray, terminals);

		if (c.timing)
		{
			t.stop();
			cout << " - Timing: Init of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		priorityQueueSize = sqrt(sequenceArray.size());
		priorityQueue.resize(priorityQueueSize);
		if (c.timing)
		{
			t.start();
			cout << " - Timing: init of priority queue" << endl;
		}
		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: priority queue initialized in " << t.getTime() << " ms" << endl;
		}

		if (c.timing)
		{
			t.start();
			cout << " - Timing: repair compression" << endl;
		}
		if (c.verbose)
		{
			cout << " - Verbose: Starting repair compression" << endl;
		}
		algP.run(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			terminals,
			symbols,
			c);
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: repair compression done in " << t.getTime() << " ms" << endl;
		}

		if (c.timing)
		{
			t.start();
			cout << " - Timing: Huffman encoding and outputting files" << endl;
		}
		if (c.verbose)
		{
			cout << " - Verbose: Starting Huffman encoding and outputting" << endl;
		}
		out.all(
			filename,
			firstBlock,
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			terminals,
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
			cout << " - Timing: reset of Sequence array and active pairs" << endl;
		}
		if (c.verbose)
		{
			cout << " - Verbose: Resetting for next block" << endl;
		}
		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
		if (c.timing)
		{
			t.stop();
			cout << " - Timing: Reset of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
	}
	cout << "Completed compression of file: " << filename << endl;
	
	return 0;
}