#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

bool compareFiles(string file1, string file2, unsigned long &badChar)
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

bool compareFilesExtended(string file1, string file2, string &fromFile1, string &fromFile2)
{
	ifstream stream1(file1);
	ifstream stream2(file2);
	fromFile1 = "";
	fromFile2 = "";
	char chunk1;
	char chunk2;

	if (stream1.is_open() && stream2.is_open())
	{
		while (stream1 >> noskipws >> chunk1 && stream2 >> noskipws >> chunk2)
		{
			fromFile1 += chunk1;
			fromFile2 += chunk2;
			if (chunk1 != chunk2)
			{
				while (stream1 >> noskipws >> chunk1 && stream2 >> noskipws >> chunk2 &&
					fromFile1.size() < 64)
				{
					fromFile1 += chunk1;
					fromFile2 += chunk2;
				}
				return false;
			}
				
			if (fromFile1.size() > 32)
			{
				fromFile1 = fromFile1.substr(3, fromFile1.size());
				fromFile2 = fromFile2.substr(3, fromFile2.size());
			}
		}
		stream1.peek();
		stream2.peek();
		if (stream1.eof() && stream2.eof())
			return true;
	}
	return false;
}

//TEST(decoder, diddy_Nicolai)
//{
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unsigned long symbols;
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//	MyTest t;
//	Huffman h;
//	Outputter out;
//	Dictionary finalDict;
//	GammaCode gc;
//	Decoder dec;
//
//	//c.compact = true;
//	c.verbose = true;
//	string input1 = "diddy.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	vector<vector<unsigned long*>> pairs;
//	string filename = input1;
//	ifstream file(filename);
//	bool firstBlock = true;
//
//	init.SequenceArray(
//		c,
//		file,
//		blockSize,
//		activePairs,
//		sequenceArray);
//
//	priorityQueueSize = sqrt(sequenceArray.size());
//	priorityQueue.resize(priorityQueueSize);
//	init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//	string string1 = "singing.do.wah.diddy.diddy.dum.diddy.do";
//	string string2 = "sHHAo.wahFEumFo";
//
//	algP.run(
//		sequenceArray,
//		activePairs,
//		priorityQueue,
//		symbols,
//		c);
//
//	out.all(
//		filename,
//		firstBlock,
//		sequenceArray,
//		c);
//
//	string compressedFile = out.addFilenameEnding(filename, ".NPC");
//	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
//
//	string decompressedFile = dec.getOutfileName(compressedFile);
//
//	dec.decode(compressedFile);
//
//	unsigned long badChunk = 0;
//
//	if (compareFiles(input1, decompressedFile, badChunk))
//		ASSERT_TRUE(true);
//	else
//		ASSERT_TRUE(false);
//
//
//
//}

//TEST(decoder, bible_Nicolai)
//{
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	unsigned long symbols;
//
//	Initializer init;
//	Conditions c;
//	Algorithm algo;
//	AlgorithmP algP;
//	MyTest t;
//	MyTimer timer;
//	Huffman h;
//	Outputter out;
//	Dictionary finalDict;
//	GammaCode gc;
//	Decoder dec;
//
//	//c.compact = true;
//	c.verbose = true;
//	string input1 = "bible.txt";
//
//	c.compact = true;
//	c.verbose = true;
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	vector<vector<unsigned long*>> pairs;
//	string filename = input1;
//	ifstream file(filename);
//	bool firstBlock = true;
//
//	string compressedFile = out.addFilenameEnding(filename, ".NPC");
//	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
//
//	string decompressedFile = dec.getOutfileName(compressedFile);
//
//	ifstream checkStream(compressedFile);
//
//	
//	if (!checkStream.is_open())
//	{
//		algo.run(
//			filename,
//			file,
//			c,
//			init,
//			algP,
//			timer,
//			blockSize,
//			activePairs,
//			sequenceArray,
//			priorityQueue,
//			symbols);
//		checkStream.close();
//	}	
//	checkStream.close();
//
//	std::cout << "Starting decoding" << endl;
//	dec.decode(compressedFile);
//
//	unsigned long badChar = 0;
//
//	if (compareFiles(input1, decompressedFile, badChar))
//		ASSERT_TRUE(true);
//	else
//		ASSERT_TRUE(false);
//}


////TEST(decoder, world_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "world192.txt";
////
////	int priorityQueueSize;
////	int blockSize;
////	blockSize = 1048576;
////	unordered_set<unsigned long> terminals;
////	vector<vector<unsigned long*>> pairs;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	if (compareFiles(input1, decompressedFile, badChar))
////		ASSERT_TRUE(true);
////	else
////		ASSERT_TRUE(false);
////}
////
////TEST(decoder, ecoli_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "E.coli";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
////
////TEST(decoder, dna50MB_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "dna.50MB";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
////	testofs << "";
////	testofs.close();
////
////	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
////	testofs2 << "";
////	testofs2.close();
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
////
TEST(decoder,english50MB_Nicolai)
{
	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
	activePairs.set_empty_key(-1);
	activePairs.set_deleted_key(-2);
	vector<SymbolRecord*> sequenceArray;
	vector<PairRecord*> priorityQueue;
	unsigned long symbols;

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

	c.compact = true;
	c.verbose = true;
	string input1 = "english.50MB";

	int blockSize;
	blockSize = 1048576;
	string filename = input1;
	ifstream file(filename);
	bool firstBlock = true;

	string compressedFile = out.addFilenameEnding(filename, ".NPC");
	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");

	string decompressedFile = dec.getOutfileName(compressedFile);

	ifstream checkStream(compressedFile);

	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
	testofs << "";
	testofs.close();

	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
	testofs2 << "";
	testofs2.close();


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
			symbols);
		checkStream.close();
	}
	checkStream.close();

	std::cout << "Starting decoding" << endl;
	dec.decode(compressedFile);

	unsigned long badChar = 0;

	bool result = compareFiles(input1, decompressedFile, badChar);
	ASSERT_TRUE(result);
}
////
////TEST(decoder, sources50MB_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "sources.50MB";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
////	testofs << "";
////	testofs.close();
////
////	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
////	testofs2 << "";
////	testofs2.close();
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
////
////TEST(decoder, dblpxml50MB_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "dblp.xml.50MB";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
////	testofs << "";
////	testofs.close();
////
////	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
////	testofs2 << "";
////	testofs2.close();
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
////
////TEST(decoder, proteins50MB_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "proteins.50MB";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
////	testofs << "";
////	testofs.close();
////
////	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
////	testofs2 << "";
////	testofs2.close();
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
////
////TEST(decoder, pitches50MB_Nicolai)
////{
////	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
////	activePairs.set_empty_key(-1);
////	activePairs.set_deleted_key(-2);
////	vector<SymbolRecord*> sequenceArray;
////	vector<PairRecord*> priorityQueue;
////	unsigned long symbols;
////
////	Initializer init;
////	Conditions c;
////	Algorithm algo;
////	AlgorithmP algP;
////	MyTest t;
////	MyTimer timer;
////	Huffman h;
////	Outputter out;
////	Dictionary finalDict;
////	GammaCode gc;
////	Decoder dec;
////
////	//c.compact = true;
////	c.verbose = true;
////	string input1 = "pitches.50MB";
////
////	int blockSize;
////	blockSize = 1048576;
////	string filename = input1;
////	ifstream file(filename);
////	bool firstBlock = true;
////
////	string compressedFile = out.addFilenameEnding(filename, ".NPC");
////	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
////
////	string decompressedFile = dec.getOutfileName(compressedFile);
////
////	ifstream checkStream(compressedFile);
////
////	ofstream testofs("TestHeadersEncodeFun.txt", ios::binary | ios::trunc);
////	testofs << "";
////	testofs.close();
////
////	ofstream testofs2("TestHeadersDecodeFun.txt", ios::binary | ios::trunc);
////	testofs2 << "";
////	testofs2.close();
////
////
////	if (!checkStream.is_open())
////	{
////		algo.run(
////			filename,
////			file,
////			c,
////			init,
////			algP,
////			timer,
////			blockSize,
////			activePairs,
////			sequenceArray,
////			priorityQueue,
////			symbols);
////		checkStream.close();
////	}
////	checkStream.close();
////
////	std::cout << "Starting decoding" << endl;
////	dec.decode(compressedFile);
////
////	unsigned long badChar = 0;
////
////	bool result = compareFiles(input1, decompressedFile, badChar);
////	ASSERT_TRUE(result);
////}
