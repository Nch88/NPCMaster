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
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> & activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*> & priorityQueue,
	unordered_map<unsigned int, Pair> & dictionary,
	unsigned int & symbols)
{
	int priorityQueueSize;
	bool firstBlock = true;
	Huffman h;
	Outputter out;
	unordered_map<unsigned int, HuffmanNode *> huffmanCodes;
	unordered_set<unsigned int> terminals;
	cout << "Compressing file: " << filename << endl;

	while (file.is_open())
	{
		if (c.verbose)
		{
			cout << "Initializing block" << endl;
		}
		if (c.timing)
		{
			t.start();
			cout << "Timing init of Sequence array and active pairs" << endl;
		}
		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray, terminals);

		if (c.timing)
		{
			t.stop();
			cout << "Init of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		priorityQueueSize = sqrt(sequenceArray.size());
		priorityQueue.resize(priorityQueueSize);
		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

		algP.run(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			terminals,
			symbols,
			c);

																				//TODO: Output dictionary and compressed sequence in Huffman codes
		if (c.timing)
		{
			t.start();
			cout << "Timing reset of Sequence array and active pairs" << endl;
		}
		if (c.verbose)
		{
			cout << "Resetting for next block" << endl;
		}
		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
		if (c.timing)
		{
			t.stop();
			cout << "Reset of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
	}
	cout << "Completed compression of file: " << filename << endl;
	
	return 0;
}