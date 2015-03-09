#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(decoder, diddyAll)
{
	using namespace google;
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

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
	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	dense_hash_map <long, dense_hash_map<long, long>> indices;
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

	ifstream bitstreamDict(compressedDictionary, ios::binary);


	//TODO: test decoding of everything at once
}