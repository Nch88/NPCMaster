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
	string filename,
	ifstream & file,
	Conditions c,
	Initializer init,
	AlgorithmP algP,
	MyTimer t,
	int blockSize,
	dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*> & priorityQueue,
	dense_hash_map<long, Pair> & dictionary,
	long & symbols)
{
	int priorityQueueSize;
	bool firstBlock = true;
	Huffman h;
	Outputter out;
	dense_hash_map<long, HuffmanNode *> huffmanCodes;
	unordered_set<long> terminals;
	std::cout << "Compressing file: " << filename << endl;

	int count = 1;

	while (file.is_open())
	{
		if (c.verbose)
		{
			std::cout << " - Verbose: Initializing block" << endl;
		}
		if (c.timing)
		{
			t.start();
		}
		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray, terminals);

		if (c.timing)
		{
			t.stop();
			std::cout << " - Timing: Init of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		priorityQueueSize = sqrt(sequenceArray.size());
		priorityQueue.resize(priorityQueueSize);
		if (c.timing)
		{
			t.start();
		}
		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
		if (c.timing)
		{
			t.stop();
			std::cout << " - Timing: priority queue initialized in " << t.getTime() << " ms" << endl;
		}

		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			std::cout << " - Verbose: Starting repair compression" << endl;
		}
		algP.run(
			sequenceArray,
			dictionary,
			activePairs,
			priorityQueue,
			terminals,
			symbols,
			c);			

		//DEBUG
		if (c.pairCount > 0)
		{
			cout << "Avg time for check count left: " << c.checkCountLeft / c.pairCount << " ns" << endl;
			cout << "Avg time for check count right: " << c.checkCountRight / c.pairCount << " ns" << endl;
			cout << "Avg time for decrement count left: " << c.decrementCountLeft / c.pairCount << " ns" << endl;
			cout << "Avg time for decrement count right: " << c.decrementCountRight / c.pairCount << " ns" << endl;
			cout << "Avg time for increment count left: " << c.incrementCountLeft / c.pairCount << " ns" << endl;
			cout << "Avg time for increment count right: " << c.incrementCountRight / c.pairCount << " ns" << endl;
			cout << "Avg time for replace pair: " << c.replacePair / c.pairCount << " ns" << endl;
		}
		else
			cout << "Problem timing program." << endl;

		if (c.timing)
		{
			t.stop();
			std::cout << " - Timing: repair compression done in " << t.getTime() << " ms" << endl;
		}

		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			std::cout << " - Verbose: Starting Huffman encoding and outputting" << endl;
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
			std::cout << " - Timing: Huffman encoding and outputting files done in " << t.getTime() << " ms" << endl;
		}

		firstBlock = false;
		if (c.timing)
		{
			t.start();
		}
		if (c.verbose)
		{
			std::cout << " - Verbose: Resetting for next block" << endl;
		}
		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, terminals, dictionary);
		if (c.timing)
		{
			t.stop();
			std::cout << " - Timing: Reset of Sequence array and active pairs took " << t.getTime() << " ms" << endl;
		}
		file.peek();
		if (file.eof())
			file.close();

		if (c.extraVerbose)
		{
			std::cout << "Finished block " << count << endl;
		}
		count++;
	}
	std::cout << "Completed compression of file: " << filename << endl;
	init.resetCompleted(blockSize, activePairs, sequenceArray);
	return 0;
}