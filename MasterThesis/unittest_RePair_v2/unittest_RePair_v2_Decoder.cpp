//#include "gtest\gtest.h"
//#include "RePair_v2\stdafx.h"
//
//using namespace std;
//
//TEST(decoder, diddyAll)
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
//
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
//		activePairs,
//		priorityQueue,
//		c);
//
//	string compressedFile = out.addFilenameEnding(filename, ".NPC");
//	string compressedDictionary = out.addFilenameEnding(filename, ".dict.NPC");
//
//	//Read dictionary
//	ifstream bitstreamDict(compressedDictionary, ios::binary);
//	vector<CompactPair> decodedPairs;
//	vector<unsigned long> decodedTerms;
//	gc.decodeDictionaryFile(bitstreamDict,decodedPairs, decodedTerms);
//	dense_hash_map<unsigned long, string> expandedDict;
//	expandedDict.set_empty_key(-1);
//	expandedDict.set_deleted_key(-2);
//	finalDict.expandDictionary(decodedPairs, decodedTerms, expandedDict);
//
//	//Read huffman dictionary
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> symbolIndices;
//	symbolIndices.set_empty_key(-1);
//	symbolIndices.set_deleted_key(-2);
//	unsigned long *firstCodes;
//	h.decodeDictionary(bitstreamDict, firstCodes, symbolIndices);
//
//	//Read file
//	vector<unsigned long> symbolIndexSequence;
//	ifstream instream(compressedFile, ios::binary);
//	h.decode(firstCodes, instream, symbolIndices, symbolIndexSequence);
//	instream.close();
//	string finalOutput;
//	finalOutput.assign("");
//	long cur;
//	for (int i = 0; i < symbolIndexSequence.size(); ++i)
//	{
//		cur = symbolIndexSequence[i];
//		if (cur < decodedTerms.size())
//			finalOutput += decodedTerms[cur];
//		else
//			finalOutput += expandedDict[cur - decodedTerms.size()];
//	}
//
//	/*cout << endl << "Final sequence:" << endl << "{ ";
//	for each (auto var in symbolIndexSequence)
//	{
//		cout << var << ", ";
//	}
//	cout << "}";
//	cout << endl << endl;
//
//	cout << endl << "Expanded dictionary:" << endl;
//	for each (auto var in expandedDict)
//	{
//		cout << endl << var.first << " -> " << var.second;
//	}
//	cout << endl << endl;*/
//
//	ASSERT_EQ(string1, finalOutput);
//}
//
///*
//TEST(decoder, ecoli_mini)
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
//	string input1 = "E.coli_mini";
//
//	int priorityQueueSize;
//	int blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	vector<CompactPair> pairs;
//	dense_hash_map <unsigned long, dense_hash_map<unsigned long, unsigned long>> indices;
//	indices.set_empty_key(-1);
//	indices.set_deleted_key(-2);
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
//	algo.run(
//		filename,
//		file,
//		c,
//		init,
//		algP,
//		timer,
//		blockSize,
//		activePairs,
//		sequenceArray,
//		priorityQueue,
//		symbols);
//	checkStream.close();
//	
//	std::cout << "Starting decoding" << endl;
//	dec.decode(compressedFile);
//
//	unsigned long badChar = 0;
//
//	bool result = t.compareFiles(input1, decompressedFile, badChar);
//	ASSERT_TRUE(result);
//}
//*/
//TEST(decoder, getDictionaryName)
//{
//	Decoder dc;
//	ASSERT_EQ("abc.dict.NPC", dc.getDictionaryName("abc.NPC"));
//	ASSERT_EQ("error", dc.getDictionaryName("blabla"));
//}