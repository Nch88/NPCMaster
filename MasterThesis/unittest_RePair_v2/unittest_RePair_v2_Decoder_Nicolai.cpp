#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

bool compareFiles(string file1, string file2, long &badChar)
{
	ifstream stream1(file1);
	ifstream stream2(file2);
	badChar = 0;
	char chunk1;
	char chunk2;

	if (stream1.is_open() && stream2.is_open())
	{
		while (stream1 >> noskipws >> chunk1 && stream2 >> noskipws >> chunk2)
		{
			++badChar;
			if (chunk1 != chunk2)
				return false;
		}
		stream1.peek();
		stream2.peek();
		if (stream1.eof() && stream2.eof())
			return true;
	}
	return false;
}

TEST(decoder, diddy_Nicolai)
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
	Decoder dec;

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

	string decompressedFile = dec.getOutfileName(compressedFile);

	dec.decode(compressedFile);

	long badChunk = 0;

	if (compareFiles(input1, decompressedFile, badChunk))
		ASSERT_TRUE(true);
	else
		ASSERT_TRUE(false);



}

TEST(decoder, bible_Nicolai)
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
	Algorithm algo;
	AlgorithmP algP;
	MyTest t;
	MyTimer timer;
	Huffman h;
	Outputter out;
	Dictionary finalDict;
	GammaCode gc;
	Decoder dec;

	string input1 = "bible.txt";

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

	string compressedFile = out.addFilenameEnding(filename, ".NPC");
	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");

	string decompressedFile = dec.getOutfileName(compressedFile);

	ifstream checkStream(compressedFile);

	
	if (!checkStream.is_open())
	{
		algo.run(
			filename,
			file,
			c,
			init,
			algP,
			timer,
			blockSize,
			activePairs,
			sequenceArray,
			priorityQueue,
			dictionary,
			symbols);
		checkStream.close();
	}	
	checkStream.close();

	std::cout << "Starting decoding" << endl;
	dec.decode(compressedFile);

	long badChar = 0;

	if (compareFiles(input1, decompressedFile, badChar))
		ASSERT_TRUE(true);
	else
		ASSERT_TRUE(false);
}