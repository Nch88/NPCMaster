#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(decoder, diddyAll)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
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
	unordered_map <long, unordered_map<long, long>> indices;
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
	vector<long> decodedTerms;
	gc.decodeDictionaryFile(decodedPairs, decodedTerms, bitstreamDict);

	int location = bitstreamDict.tellg();

	//Read huffman dictionary
	unordered_map<long, unordered_map<long, long>> symbolIndices;
	long *firstCodes;
	h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);

	//Read file
	vector<long> symbolIndexSequence;
	ifstream outstream(compressedFile, ios::binary);
	h.decode(firstCodes, outstream, symbolIndices, symbolIndexSequence);
	string finalOutput;
	finalOutput.assign("");
	for (int i = 0; i < symbolIndexSequence.size(); ++i)
	{
		finalDict.decodeSymbol(symbolIndexSequence[i], decodedPairs, decodedTerms, finalOutput);
	}
	ASSERT_EQ(string1,finalOutput);
}

TEST(decoder,decodeLargeFile)
{
	unordered_map<long, unordered_map<long, PairTracker>> activePairs;
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unordered_map<long, Pair> dictionary;
	long symbols(initialSymbolValue);//256

	Initializer init;
	Conditions c;
	AlgorithmP algP;
	Algorithm algo;
	MyTimer timer;
	MyTest t;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;
	Decoder dc;

	string input1 = "bible.txt";

	int priorityQueueSize;
	int blockSize;
	blockSize = 1048576;
	unordered_set<long> terminals;
	vector<CompactPair> pairs;
	unordered_map <long, unordered_map<long, long>> indices;
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	c.verbose = true;

	algo.run(filename, file, c, init, algP, timer, blockSize, activePairs, sequenceArray, priorityQueue, dictionary, symbols);

	dc.decode("bible.txt.NPC");
	int x = 0;
}

TEST(decoder, getDictionaryName)
{
	Decoder dc;
	ASSERT_EQ("abc.dict.NPC", dc.getDictionaryName("abc.NPC"));
	ASSERT_EQ("error", dc.getDictionaryName("blabla"));
}