//#include "gtest\gtest.h"
//#include "RePair_v2\stdafx.h"
//
//using namespace std;
//
//TEST(outputter, diddyHuffmanCode)
//{
//	using namespace google;
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
//
//	string input1 = "diddy.txt";
//
//	bool skip = false;
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	string filename = input1;
//	ifstream file(filename);
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
//
//	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
//
//	algP.run(
//		sequenceArray,
//		activePairs,
//		priorityQueue,
//		symbols,
//		c);
//
//	dense_hash_map<unsigned long, HuffmanNode> huffmanCodes;
//	huffmanCodes.set_empty_key(-1);
//	huffmanCodes.set_deleted_key(-2);
//	unsigned long *firstCode = nullptr;
//	unsigned long *numl = nullptr;
//	unsigned long maxLength = 0;
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long,unsigned long>> huffmanToSymbol;
//	huffmanToSymbol.set_empty_key(-1);
//	huffmanToSymbol.set_deleted_key(-2);
//	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);
//
//	string filenameout = out.addFilenameEnding(input1, ".NPC");
//	ofstream myfile;
//	myfile.open(filenameout, ios::binary);
//
//	out.huffmanEncoding(
//		filenameout,
//		myfile,
//		sequenceArray,
//		huffmanCodes,
//		true);
//
//	//Actual test
//	string expected1 = "00000100100001110101010100001000";
//	string expected2 = "00111001100111111110101000000000";
//	string expected3 = "10000000000000000000000000001001";
//	
//	ifstream ifs;
//	ifs.open("Compressed_diddy.txt", ios::binary);
//	string result = "";
//	string totalResult = "";
//	char byte;
//	bitset<8> *bits;
//	int count = 0;
//
//	if (ifs.is_open())
//	{		
//		while (ifs.get(byte))
//		{
//			bits = new bitset<8>(byte);
//
//			for (int i = bits->size() - 1; i >= 0; --i)
//			{
//				if ((*bits)[i] == 0)
//					result += "0";
//				else
//					result += "1";
//			}
//			if (result.size() == 32 && count == 0)
//			{
//				ASSERT_EQ(expected1, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			if (result.size() == 32 && count == 1)
//			{
//				ASSERT_EQ(expected2, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			if (result.size() == 32 && count == 2)
//			{
//				ASSERT_EQ(expected3, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			delete bits;
//		}
//	}
//	ASSERT_EQ(expected1 + expected2 +expected3, totalResult);
//}
//
//TEST(outputter, randomHuffmanCode)
//{
//	using namespace google;
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, PairTracker>> activePairs;
//	activePairs.set_empty_key(-1);
//	activePairs.set_deleted_key(-2);
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	long symbols;
//
//	Initializer init;
//	Conditions c;
//	AlgorithmP algP;
//	MyTest t;
//	Huffman h;
//	Outputter out;
//
//	string input1 = "huffmanEncodeTest.txt";
//
//	bool skip = false;
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<long> terminals;
//	string filename = input1;
//
//	dense_hash_map<unsigned long, HuffmanNode> huffmanCodes;
//	huffmanCodes.set_empty_key(-1);
//	huffmanCodes.set_deleted_key(-2);
//	unsigned long *firstCode = nullptr;
//	unsigned long *numl = nullptr;
//	unsigned long maxLength = 0;
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> huffmanToSymbol;
//	huffmanToSymbol.set_empty_key(-1);
//	huffmanToSymbol.set_deleted_key(-2);
//
//	//test stuff
//	sequenceArray.push_back(new SymbolRecord(55329, 0));
//	sequenceArray.push_back(new SymbolRecord(0, 1));
//	sequenceArray.push_back(new SymbolRecord(0, 2));
//	sequenceArray.push_back(new SymbolRecord(0, 3));
//	sequenceArray.push_back(new SymbolRecord(0, 4));
//	sequenceArray.push_back(new SymbolRecord(103, 5));
//	sequenceArray.push_back(new SymbolRecord(97, 6));
//
//	HuffmanNode node1; node1.code = "1101000110";
//	HuffmanNode node2; node2.code = "001010100110110";
//	HuffmanNode node3; node3.code = "00000000010010110";
//
//	string expresult =	"01101000110001010100110110000000";
//	expresult +=		"00001001011000000000000000000000";
//	expresult +=		"10000000000000000000000000010100";
//
//	huffmanCodes[55329] = node1;
//	huffmanCodes[103] = node2;
//	huffmanCodes[97] = node3;
//
//	string filenameout = out.addFilenameEnding(input1, ".NPC");
//	ofstream myfile;
//	myfile.open(filenameout, ios::binary);
//
//	out.huffmanEncoding(
//		filenameout,
//		myfile,
//		sequenceArray,
//		huffmanCodes,
//		true);
//	myfile.close();
//
//	//Actual test
//
//	ifstream ifs;
//	ifs.open(filenameout, ios::binary);
//	string result = "";
//	string totalResult = "";
//	char byte;
//	bitset<8> *bits;
//	int count = 0;
//
//	if (ifs.is_open())
//	{
//		while (ifs.get(byte))
//		{
//			bits = new bitset<8>(byte);
//
//			for (int i = bits->size() - 1; i >= 0; --i)
//			{
//				if ((*bits)[i] == 0)
//					result += "0";
//				else
//					result += "1";
//			}
//
//			if (result.size() == 32)
//			{
//				totalResult += result;
//				result = "";
//			}
//		}
//	}
//
//	ASSERT_EQ(expresult, totalResult);
//}
//
///*
//TEST(outputter, diddyHuffmanDictionary)
//{
//	using namespace google;
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
//
//	string input1 = "diddy.txt";
//
//	bool skip = false;
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	vector<vector<CompactPair>> pairs;
//	string filename = input1;
//	ifstream file(filename);
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
//	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
//
//	algP.run(
//		sequenceArray,
//		activePairs,
//		priorityQueue,
//		symbols,
//		c);
//
//	vector<unsigned long> terminalVector;
//	dense_hash_map<unsigned long, unsigned long> StG;
//	StG.set_empty_key(-1);
//	vector<vector<unsigned long *>> pairVectors;
//
//	finalDict.createDictionary(sequenceArray, terminals, StG, pairVectors, terminalVector);
//
//	dense_hash_map<unsigned long, HuffmanNode> huffmanCodes;
//	huffmanCodes.set_empty_key(-1);
//	huffmanCodes.set_deleted_key(-2);
//	unsigned long *firstCode = nullptr;
//	unsigned long *numl = nullptr;
//	unsigned long maxLength = 0;
//	dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> huffmanToSymbol;
//	huffmanToSymbol.set_empty_key(-1);
//	huffmanToSymbol.set_deleted_key(-2);
//	h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);
//
//	string outstring = "testHuffmanDictionary";
//	ofstream myfile;
//	myfile.open(outstring, ios::binary);
//
//	out.huffmanDictionary(
//		outstring,
//		myfile,
//		maxLength,
//		firstCode,
//		numl,
//		pairVectors,
//		StG,
//		terminalVector,
//		huffmanToSymbol);
//
//	myfile.close();
//	//Actual test
//	string expected1 = "11001010101100111001110011111000";
//	string expected2 = "01111000111110010111011111000101";
//	string expected3 = "10011110011100111001001110100111";
//	string expected4 = "01101111001000000000000000000000";
//
//	ifstream ifs;
//	ifs.open(outstring, ios::binary);
//	string result = "";
//	string totalResult = "";
//	char byte;
//	bitset<8> *bits;
//	int count = 0;
//
//	GammaCode gc;
//
//	if (ifs.is_open())
//	{
//		while (ifs.get(byte))
//		{
//			bits = new bitset<8>(byte);
//
//			for (int i = bits->size() - 1; i >= 0; --i)
//			{
//				if ((*bits)[i] == 0)
//					result += "0";
//				else
//					result += "1";
//			}
//			if (result.size() == 32 && count == 0)
//			{
//				ASSERT_EQ(expected1, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			if (result.size() == 32 && count == 1)
//			{
//				ASSERT_EQ(expected2, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			if (result.size() == 32 && count == 2)
//			{
//				ASSERT_EQ(expected3, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			if (result.size() == 32 && count == 3)
//			{
//				ASSERT_EQ(expected4, result);
//				++count;
//				totalResult += result;
//				result = "";
//			}
//			delete bits;
//		}
//	}
//	ASSERT_EQ(expected1 + expected2 + expected3 + expected4, totalResult);
//	vector<unsigned long> resultVector;
//	string prefix = "";
//	gc.decodeGammaString(prefix, totalResult, resultVector, 21);
//
//	ASSERT_EQ(21, resultVector.size());
//
//	ASSERT_EQ(4, resultVector[0]);
//	ASSERT_EQ(0, resultVector[1]);
//	ASSERT_EQ(2, resultVector[2]);
//	ASSERT_EQ(0, resultVector[3]);
//	ASSERT_EQ(4, resultVector[4]);
//
//	ASSERT_EQ(4, resultVector[5]);
//	ASSERT_EQ(4, resultVector[6]);
//
//	ASSERT_EQ(16, resultVector[7]);
//	ASSERT_EQ(8, resultVector[8]);
//	ASSERT_EQ(20, resultVector[9]);
//	ASSERT_EQ(6, resultVector[10]);
//
//	ASSERT_EQ(8, resultVector[11]);
//	ASSERT_EQ(0, resultVector[12]);
//
//	ASSERT_EQ(4, resultVector[13]);
//	ASSERT_EQ(10, resultVector[14]);
//	ASSERT_EQ(1, resultVector[15]);
//	ASSERT_EQ(9, resultVector[16]);
//	ASSERT_EQ(0, resultVector[17]);
//	ASSERT_EQ(11, resultVector[18]);
//	ASSERT_EQ(13, resultVector[19]);
//	ASSERT_EQ(19, resultVector[20]);
//
//	ifs.close();
//}*/
//
//TEST(outputter, diddyAll)
//{
//	using namespace google;
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
//
//	string input1 = "diddy.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	vector<CompactPair> pairs;
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
//
//	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
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
//	ifstream ifs;
//	ifs.open(compressedFile, ios::binary);
//	ASSERT_TRUE(ifs.is_open());
//	ifs.close();
//
//	ifs.open(compressedDictionary, ios::binary);
//	ASSERT_TRUE(ifs.is_open());
//	ifs.close();
//}
//
//TEST(outputter, readAndWriteDictionary_diddy)
//{
//	using namespace google;
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
//	string outstring = "testWriteDictionaryDiddy";
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
//	ASSERT_EQ(string1, t.SequenceToString(sequenceArray));
//
//	algP.run(
//		sequenceArray,
//		activePairs,
//		priorityQueue,
//		symbols,
//		c);
//
//	vector<unsigned long> terminalVector;
//	dense_hash_map<unsigned long, unsigned long > symbolToGen;
//	symbolToGen.set_empty_key(-1);
//
//	finalDict.createDictionary(sequenceArray, terminals, symbolToGen, pairs, terminalVector);
//
//	ofstream myfile;
//	myfile.open(outstring, ios::binary);
//
//	out.dictionary2(outstring, myfile, pairs, terminalVector, true);
//	myfile.close();
//
//	vector<CompactPair> decodedPairs;
//	vector<unsigned long> decodedTerms;
//	ifstream bitstream(outstring, ios::binary);
//
//	//Read file
//	gc.decodeDictionaryFile(bitstream, decodedPairs, decodedTerms);
//
//	bool isInOriginalPairVector;
//	for (const auto p : decodedPairs)
//	{
//		isInOriginalPairVector = false;
//		for (const vector<unsigned long*> gen : pairs)
//		{
//			for (const auto p2 : gen)
//			{
//				if (p2[0] == p.leftSymbol && p2[1] == p.rightSymbol)
//					isInOriginalPairVector = true;
//			}
//		}
//		ASSERT_TRUE(isInOriginalPairVector);
//	}
//
//	int combinedSize = 0;
//	for (const vector<unsigned long*> gen : pairs)
//	{
//		combinedSize += gen.size();
//	}
//	ASSERT_EQ(combinedSize, decodedPairs.size());
//	bitstream.close();
//	vector<unsigned long> terms(terminals.begin(),terminals.end());
//	sort(terms.begin(), terms.end());
//
//	ASSERT_EQ(terms, decodedTerms);
//}
//
////TEST(outputter, dictionary)
////{
////	Outputter out;
////	string file = "outputDictionary.test";
////	string file2 = "outputDictionary2.test";
////	string file3 = "outputDictionary3.test";
////	string file4 = "outputDictionary4.test";
////	bool firstBlock = true;
////	MyTimer timer;
////
////	ofstream myfile;
////	myfile.open(file, ios::binary);
////
////	ofstream myfile2;
////	myfile2.open(file2, ios::binary);
////
////	ofstream myfile3;
////	myfile3.open(file3, ios::binary);
////
////	ofstream myfile4;
////	myfile4.open(file4, ios::binary);
////
////
////	string testString(800000, 'a');
////	timer.start();
////	out.dictionary(file, myfile, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////	string testString2(1600000, 'b');
////	firstBlock = false;
////	timer.start();
////	out.dictionary(file, myfile, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString2.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////	string testString3(3200000, 'c');
////	firstBlock = false;
////	timer.start();
////	out.dictionary(file, myfile, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString3.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////
////	//!"""!!!!!!!!!!!!!!!!!!!!!!
////
////	string testString4(800000, 'a');
////	firstBlock = true;
////	timer.start();
////	out.dictionary(file2, myfile2, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString4.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////	string testString5(16000000, 'b');
////	firstBlock = false;
////	timer.start();
////	out.dictionary(file3, myfile3, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString5.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////	string testString6(320000000, 'c');
////	firstBlock = false;
////	timer.start();
////	out.dictionary(file4, myfile4, testString, firstBlock);
////	timer.stop();
////	cout << "Wrote string of size " << testString6.size() << " chars to file in " << timer.getTime() << " ms" << endl;
////
////
////	ASSERT_TRUE(true);
////}
//
///*
//TEST(outputter, all_world192)
//{
//	using namespace google;
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
//	MyTimer timer;
//
//	string input1 = "diddy.txt";
//	string input2 = "E.coli";
//	string input3 = "dna.50MB";
//	string input4 = "crashtestdummy.txt";
//	string input5 = "world192.txt";
//	string input6 = "bible.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//	unordered_set<unsigned long> terminals;
//	string filename = input5;
//	ifstream file(filename);
//	bool firstBlock = true;
//
//	//Create names for output files
//	string compressedFilename = out.addFilenameEnding(filename, ".NPC");
//	string compressedDictionaryName = out.addFilenameEnding(filename, ".dict.NPC");
//
//	ofstream ofs_compressed;
//	if (firstBlock)
//		ofs_compressed.open(compressedFilename, ios::binary | ios::trunc);
//	else
//		ofs_compressed.open(compressedFilename, ios::binary | ios::app);
//
//	ofstream ofs_dictionary;
//	if (firstBlock)
//		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::trunc);
//	else
//		ofs_dictionary.open(compressedDictionaryName, ios::binary | ios::app);
//	
//	int loopcount = 1;
//
//	while (file.is_open())
//	{		
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//		
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);		
//		
//		algP.run(
//			sequenceArray,
//			activePairs,
//			priorityQueue,
//			symbols,
//			c);		
//		long apsize = 0;
//		for (auto &entry : activePairs)
//		{
//			for (auto &entry2 : entry.second)
//			{
//				++apsize;
//			}
//		}
//		cout << "	Loop " << loopcount <<": Sequence array size: " << sequenceArray.size() << endl;
//		cout << "	Loop " << loopcount << ": Active pairs size: " << apsize << endl;
//		cout << "	Loop " << loopcount << ": Terminals size: " << terminals.size() << endl;
//
//		if (loopcount == 2)
//		{
//			int x = 0;
//		}
//		//Out.all explicit		
//
//		//Do Huffman encoding
//		dense_hash_map<unsigned long, HuffmanNode> huffmanCodes;
//		huffmanCodes.set_empty_key(-1);
//		huffmanCodes.set_deleted_key(-2);
//		unsigned long *firstCode = nullptr;
//		unsigned long *numl = nullptr;
//		unsigned long maxLength = 0;
//		dense_hash_map<unsigned long, dense_hash_map<unsigned long, unsigned long>> huffmanToSymbol;
//		huffmanToSymbol.set_empty_key(-1);
//		huffmanToSymbol.set_deleted_key(-2);
//		
//		if (loopcount == 1)
//		{
//			timer.start();
//		}
//		if (loopcount == 2)
//		{
//			timer.start();
//		}
//		if (loopcount == 3)
//		{
//			timer.start();
//		}
//		h.encode(sequenceArray, huffmanCodes, firstCode, numl, maxLength, huffmanToSymbol);
//		if (loopcount == 1)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 2)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 3)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//		long htssize = 0;
//		for (auto &entry : huffmanToSymbol)
//		{
//			for (auto &entry2 : entry.second)
//			{
//				++htssize;
//			}
//		}
//		cout << "	Loop " << loopcount << ": huffmanToSymbol size: " << htssize << endl;
//
//		//Write Huffman encoded sequence to file
//		if (loopcount == 1)
//		{
//			timer.start();
//		}
//		if (loopcount == 2)
//		{
//			timer.start();
//		}
//		if (loopcount == 3)
//		{
//			timer.start();
//		}
//		out.huffmanEncoding(
//			compressedFilename,
//			ofs_compressed,
//			sequenceArray,
//			huffmanCodes,
//			firstBlock);
//		if (loopcount == 1)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 2)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 3)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman encoding: " << timer.getTime() << " ms" << endl;
//		}
//
//		//Encode generations for dictionary
//		Dictionary finalDict;
//		vector<vector<unsigned long*>> pairs;
//
//		if (loopcount == 1)
//		{
//			timer.start();
//		}
//		if (loopcount == 2)
//		{
//			timer.start();
//		}
//		if (loopcount == 3)
//		{
//			timer.start();
//		}
//		dense_hash_map<unsigned long, unsigned long> StG;
//		StG.set_empty_key(-1);
//		vector<unsigned long> termVector;
//		finalDict.createDictionary(sequenceArray, terminals, StG, pairs, termVector);
//		if (loopcount == 1)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  create dictionary: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 2)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  create dictionary: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 3)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  create dictionary: " << timer.getTime() << " ms" << endl;
//		}
//		long psize = 0;
//		for (auto &entry : pairs)
//		{
//			for (auto &entry2 : entry)
//			{
//				++psize;
//			}
//		}
//		cout << "	Loop " << loopcount << ": pairs size: " << psize << endl;
//
//		//Write dictionary to file
//		GammaCode gc;
//		string output = "";
//
//		if (loopcount == 1)
//		{
//			timer.start();
//		}
//		if (loopcount == 2)
//		{
//			timer.start();
//		}
//		if (loopcount == 3)
//		{
//			timer.start();
//		}
//		
//		cout << "	Loop " << loopcount << ": Output string size: " << output.size() << endl;
//		out.dictionary2(
//			compressedDictionaryName,
//			ofs_dictionary,
//			pairs,
//			termVector,
//			firstBlock);
//		if (loopcount == 1)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write dictionary of generations: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 2)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write dictionary of generations: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 3)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write dictionary of generations: " << timer.getTime() << " ms" << endl;
//		}
//
//		//Write Huffman dictionary to file
//		if (loopcount == 1)
//		{
//			timer.start();
//		}
//		if (loopcount == 2)
//		{
//			timer.start();
//		}
//		if (loopcount == 3)
//		{
//			timer.start();
//		}
//		out.huffmanDictionary(
//			compressedDictionaryName,
//			ofs_dictionary,
//			maxLength,
//			firstCode,
//			numl,
//			pairs,
//			StG,
//			termVector,
//			huffmanToSymbol);
//		if (loopcount == 1)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman dictionary: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 2)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman dictionary: " << timer.getTime() << " ms" << endl;
//		}
//		if (loopcount == 3)
//		{
//			timer.stop();
//			cout << "	Loop " << loopcount << ":  write Huffman dictionary: " << timer.getTime() << " ms" << endl;
//		}
//
//		//Clean up
//		delete[] firstCode;
//		delete[] numl;
//		output = "";
//
//		//out.all explicit - end
//
//		firstBlock = false;		
//		if (loopcount == 1)
//		{
//			int x = 0;
//		}
//		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue); 
//		
//		++loopcount;
//	}
//}
//*/