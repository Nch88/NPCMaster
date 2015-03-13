#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(decoder, diddyAll)
{
	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	dense_hash_map<long, Pair> dictionary;
	dictionary.set_empty_key(-1);
	dictionary.set_deleted_key(-2);
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
	indices.set_empty_key(-1);
	indices.set_deleted_key(-2);
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
	dense_hash_map<long, string> expandedDict;
	expandedDict.set_empty_key(-1);
	expandedDict.set_deleted_key(-2);
	finalDict.expandDictionary(decodedPairs, decodedTerms, expandedDict);

	//Read huffman dictionary
	dense_hash_map<long, dense_hash_map<long, long>> symbolIndices;
	symbolIndices.set_empty_key(-1);
	symbolIndices.set_deleted_key(-2);
	long *firstCodes;
	h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);

	//Read file
	vector<long> symbolIndexSequence;
	ifstream outstream(compressedFile, ios::binary);
	h.decode(firstCodes, outstream, symbolIndices, symbolIndexSequence);
	string finalOutput;
	finalOutput.assign("");
	long cur;
	for (int i = 0; i < symbolIndexSequence.size(); ++i)
	{
		cur = symbolIndexSequence[i];
		if (cur < decodedTerms.size())
			finalOutput += decodedTerms[cur];
		else
			finalOutput += expandedDict[cur - decodedTerms.size()];
	}
	ASSERT_EQ(string1, finalOutput);
}

TEST(decoder, getDictionaryName)
{
	Decoder dc;
	ASSERT_EQ("abc.dict.NPC", dc.getDictionaryName("abc.NPC"));
	ASSERT_EQ("error", dc.getDictionaryName("blabla"));
}