#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(decoder, diddyAll)
{
	unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<unsigned int, Pair> dictionary;
	unsigned int symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;

	string input1 = "diddy.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<unsigned int> terminals;
	vector<CompactPair> pairs;
	unordered_map <unsigned int, unordered_map<unsigned int, unsigned int>> indices;
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	init.SequenceArray(
		c,
		file,
		blockSize,
		activePairs,
		sequenceArray,
		terminals);

	priorityQueueSize = sqrt(sequenceArray.size());
	priorityQueue.resize(priorityQueueSize);
	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);

	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
	string string2 = "sHHAo.wahFEumFo";

	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));

	algP.run(
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		symbols,
		c);

	out.all(
		filename,
		firstBlock,
		sequenceArray,
		dictionary,
		activePairs,
		priorityQueue,
		terminals,
		c);

	string compressedFile = out.addFilenameEnding(filename, ".NPC");
	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");

	//Read dictionary
	ifstream bitstreamDict(compressedDictionary, ios::binary);
	vector<CompactPair> decodedPairs;
	unordered_set<unsigned int> decodedTermSet;
	gc.decodeDictionaryFile(decodedPairs, decodedTermSet, bitstreamDict);

	//Read huffman dictionary
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>> symbolIndices;
	h.decodeDictionary(bitstreamDict, symbolIndices);

	//Read file
	ifstream bitstreamFile(compressedFile, ios::binary);
}