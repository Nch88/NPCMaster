//#include "gtest\gtest.h"
//#include "RePair_v2\stdafx.h"
//
//using namespace std;
//
//TEST(createDictionary, findGenerations)
//{
//	Dictionary d;
//
//	//     (_,_)
//	//     /   \
//	// (c,b)   (b,a)
//
//	unsigned long* l1 = new unsigned long[2];
//	unsigned long* l2 = new unsigned long[2];
//	unsigned long* l3 = new unsigned long[2];
//	l1[0] = (unsigned long)l2;
//	l1[1] = (unsigned long)l3;
//	l2[0] = 'c';
//	l2[1] = 'b';
//	l3[0] = 'b';
//	l3[1] = 'a';
//
//	dense_hash_map<unsigned long, unsigned long> StG;
//	StG.set_empty_key(-1);
//	unordered_set<unsigned long> terms;
//
//	d.findGenerations((unsigned long)l1,StG,terms);
//
//	ASSERT_EQ(3, terms.size());
//	ASSERT_EQ(2, StG[(unsigned long)l1]);
//	ASSERT_EQ(1, StG[(unsigned long)l2]);
//	ASSERT_EQ(1, StG[(unsigned long)l3]);
//}
//
//TEST(createDictionary, createSupportStructures_diddy)
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
//	Dictionary dict;
//	AlgorithmP algP;
//	MyTest t;
//
//	string input1 = "diddy.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//
//	string filename = input1;
//	ifstream file(filename);
//
//	unordered_set<unsigned long> terminals;
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
//	//string string2 = "sDDAo.wahHGumHo";
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
//	algP.compact(sequenceArray, activePairs, priorityQueue);
//
//	dense_hash_map<unsigned long, unsigned long> StG;
//	StG.set_empty_key(-1);
//	vector<vector<unsigned long*>> pairs;
//
//	dict.createSupportStructures(sequenceArray, terminals, StG, pairs);
//
//	//Some preliminary asserts in case the basic stuff goes wrong
//	ASSERT_EQ(13,terminals.size());
//	ASSERT_EQ(6,pairs.size());
//	ASSERT_EQ(2,pairs[0].size());
//	ASSERT_EQ(2,pairs[1].size());
//	ASSERT_EQ(1,pairs[2].size());
//	ASSERT_EQ(1,pairs[3].size());
//	ASSERT_EQ(1,pairs[4].size());
//	ASSERT_EQ(1,pairs[5].size());
//
//	//Test the output by carefully constructing the complete string from the phrase table + pair vectors
//	string d;
//	char ch1, ch2, ch3, ch4, ch5, ch6;
//	if (((char)(pairs[1][1][1])) == 'g')
//	{
//		ch1 = (char)(((unsigned long*)(pairs[1][1][0]))[0]);
//		ch2 = ((char)(((unsigned long*)(pairs[1][1][0]))[1]));
//		ch3 = ((char)pairs[1][1][1]);
//		d = string(1,ch1) + string(1,ch2) + string(1,ch3);
//	}
//	else
//	{
//		ch1 = ((char)(((unsigned long*)(pairs[1][0][0]))[0]));
//		ch2 = ((char)(((unsigned long*)(pairs[1][0][0]))[1]));
//		ch3 = ((char)pairs[1][0][1]);
//		d = string(1, ch1) + string(1, ch2) + string(1, ch3);
//	}
//	string a;
//	if (((char)pairs[0][0][0]) == '.')
//	{
//		ch1 = ((char)pairs[0][0][0]);
//		ch2 = ((char)pairs[0][0][1]);
//		a = string(1, ch1) + string(1, ch2);
//	}
//	else
//	{
//		ch1 = ((char)pairs[0][1][0]);
//		ch2 = ((char)pairs[0][1][1]);
//		a = string(1, ch1) + string(1, ch2);
//	}
//	string g; 
//	ch1 = ((char)pairs[4][0][0]);
//	ch2 = ((char)((unsigned long*)(pairs[4][0][1]))[0]);
//	ch3 = ((char)(((unsigned long*)((unsigned long*)(pairs[4][0][1]))[1]))[0]);
//	ch4 = ((char)((unsigned long*)(((unsigned long*)((unsigned long*)(pairs[4][0][1]))[1]))[1])[0]);
//	ch5 = ((char)((unsigned long*)(((unsigned long*)((unsigned long*)((unsigned long*)(pairs[4][0][1]))[1])[1]))[1])[0]);
//	ch6 = ((char)((unsigned long*)(((unsigned long*)((unsigned long*)((unsigned long*)(pairs[4][0][1]))[1])[1]))[1])[1]);
//	g = string(1, ch1) + string(1, ch2) + string(1, ch3) + string(1, ch4) + string(1, ch5) + string(1, ch6);
//	
//	//Lazyness
//	string h = a + g;
//
//	string result = "s" + d + d + a + "o.wah" + h + g + "um" + h + "o";
//
//	ASSERT_EQ(string1,result);
//}
//
//TEST(createDictionary, switchToOrdinalNumbers_diddy)
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
//	Dictionary dict;
//	AlgorithmP algP;
//	MyTest t;
//
//	string input1 = "diddy.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//
//	string filename = input1;
//	ifstream file(filename);
//
//	unordered_set<unsigned long> terminals;
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
//	//string string2 = "sDDAo.wahHGumHo";
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
//	algP.compact(sequenceArray, activePairs, priorityQueue);
//
//	dense_hash_map<unsigned long, unsigned long> StG;
//	StG.set_empty_key(-1);
//	vector<vector<unsigned long*>> pairs;
//
//	dict.createSupportStructures(sequenceArray, terminals, StG, pairs);
//
//	vector<unsigned long> termVector;
//
//	/*cout << endl << "Non-Terminals: " << endl << "   A        B        C        D        E        F        G        H" << endl;
//	if (((char)pairs[0][0][0]) == '.')
//		cout << (unsigned long)(pairs[0][0]) << "  " << (unsigned long)(pairs[0][1]) << "  ";
//	else
//		cout << (unsigned long)(pairs[0][1]) << "  " << (unsigned long)(pairs[0][0]) << "  ";
//
//	if (((char)(pairs[1][1][1])) == 'g')
//		cout << (unsigned long)(pairs[1][0]) << "  " << (unsigned long)(pairs[1][1]) << "  ";
//	else
//		cout << (unsigned long)(pairs[1][1]) << "  " << (unsigned long)(pairs[1][0]) << "  ";
//
//	cout << (unsigned long)(pairs[2][0]) << "  " << (unsigned long)(pairs[3][0]) << "  " << (unsigned long)(pairs[4][0]) << "  " << (unsigned long)(pairs[5][0]) << "  ";*/
//
//	dict.switchToOrdinalNumbers(terminals, StG, pairs, termVector);
//
//	/*string s;
//	cout << "\n\n" << endl << "Terminals:";
//	for each (auto var in termVector)
//	{
//		cout << "   " << (char)var;
//	}
//	cout << endl << "Number:   ";
//	for each (auto var in termVector)
//	{
//		s = to_string(var);
//		while (s.size() < 4)
//			s = " " + s;
//		cout << s;
//	}
//	cout << endl << "T-Indices:";
//	for (int i = 0; i < termVector.size(); ++i)
//	{
//		s = to_string(i);
//		while (s.size() < 4)
//			s = " " + s;
//		cout << s;
//	}
//	cout << "\n" << endl;
//	for (int gen = 0; gen < pairs.size(); ++gen)
//	{
//		cout << endl;
//		cout << "Gen " << (gen + 1) << ":";
//		for each (auto var in pairs[gen])
//		{
//			cout << " (" << var[0] << "," << var[1] << ")";
//		}
//	}*/
//
//	ASSERT_EQ(6, pairs.size());
//
//	//Gen 1
//	ASSERT_EQ(2, pairs[0].size());
//	ASSERT_EQ(0, pairs[0][0][0]);
//	ASSERT_EQ(2, pairs[0][0][1]);
//	ASSERT_EQ(5, pairs[0][1][0]);
//	ASSERT_EQ(7, pairs[0][1][1]);
//
//	//Gen 2
//	ASSERT_EQ(2, pairs[1].size());
//	ASSERT_EQ(12, pairs[1][0][0]);
//	ASSERT_EQ(13, pairs[1][0][1]);
//	ASSERT_EQ(14, pairs[1][1][0]);
//	ASSERT_EQ(3, pairs[1][1][1]);
//
//	//Gen 3
//	ASSERT_EQ(1, pairs[2].size());
//	ASSERT_EQ(2, pairs[2][0][0]);
//	ASSERT_EQ(15, pairs[2][0][1]);
//
//	//Gen 4
//	ASSERT_EQ(1, pairs[3].size());
//	ASSERT_EQ(2, pairs[3][0][0]);
//	ASSERT_EQ(17, pairs[3][0][1]);
//
//	//Gen 5
//	ASSERT_EQ(1, pairs[4].size());
//	ASSERT_EQ(5, pairs[4][0][0]);
//	ASSERT_EQ(18, pairs[4][0][1]);
//
//	//Gen 6
//	ASSERT_EQ(1, pairs[5].size());
//	ASSERT_EQ(13, pairs[5][0][0]);
//	ASSERT_EQ(19, pairs[5][0][1]);
//}
//
//TEST(createDictionary, writeThenReadDictionary_diddy)
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
//	Dictionary dict;
//	AlgorithmP algP;
//	MyTest t;
//	Outputter outputter;
//	GammaCode gc;
//
//	string input1 = "diddy.txt";
//
//	int priorityQueueSize;
//	int blockSize;
//	blockSize = 1048576;
//
//	string filename = input1;
//	ifstream file(filename);
//
//	unordered_set<unsigned long> terminals;
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
//	//string string2 = "sDDAo.wahHGumHo";
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
//	algP.compact(sequenceArray, activePairs, priorityQueue);
//
//	dense_hash_map<unsigned long, unsigned long> StG;
//	StG.set_empty_key(-1);
//	vector<vector<unsigned long*>> pairs;
//
//	dict.createSupportStructures(sequenceArray, terminals, StG, pairs);
//
//	vector<unsigned long> termVector(terminals.size());
//
//	dict.switchToOrdinalNumbers(terminals, StG, pairs, termVector);
//
//	ofstream ofs;
//	string cDName = "DictionaryTestDiddy.dict.NPC";
//	ofs.open(cDName, ios::binary | ios::trunc);
//
//	bool fB = true;
//
//	outputter.dictionary2(cDName, ofs, pairs, termVector, fB);
//
//	ofs.close();
//
//	ifstream bitstreamDict(cDName, ios::binary);
//	vector<CompactPair> decodedPairs;
//	vector<unsigned long > decodedTerms;
//	dense_hash_map<unsigned long, string> expandedDictionary;
//	expandedDictionary.set_empty_key(-1);
//
//	gc.decodeDictionaryFile(bitstreamDict, decodedPairs, decodedTerms);
//
//	dict.expandDictionary(decodedPairs, decodedTerms, expandedDictionary);
//
//	bitstreamDict.close();
//
//	string result = "";
//	//finalSeq is "sDDAo.wahHGumHo"
//	vector<unsigned long> finalSeq{9,16,16,13,8,0,11,1,4,20,19,10,6,20,8};
//	for each (long l in finalSeq)
//	{
//		if (l < decodedTerms.size())
//			result += decodedTerms[l];
//		else
//			result += expandedDictionary[l - decodedTerms.size()];
//	}
//
//	ASSERT_EQ("singing.do.wah.diddy.diddy.dum.diddy.do", result);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//TEST(expandDictionary, diddy)
//{
//	Dictionary dict;
//
//	//Make decodedPairs
//	vector<CompactPair> dPairs;
//	dPairs.push_back(CompactPair(0, 2));
//	dPairs.push_back(CompactPair(5, 7));
//	dPairs.push_back(CompactPair(12, 13));
//	dPairs.push_back(CompactPair(14, 3));
//	dPairs.push_back(CompactPair(2, 15));
//	dPairs.push_back(CompactPair(2, 17));
//	dPairs.push_back(CompactPair(5, 18));
//	dPairs.push_back(CompactPair(13, 19));
//
//	//Make terminals
//	vector<unsigned long> dTerms;
//	dTerms.push_back(46);
//	dTerms.push_back(97);
//	dTerms.push_back(100);
//	dTerms.push_back(103);
//	dTerms.push_back(104);
//	dTerms.push_back(105);
//	dTerms.push_back(109);
//	dTerms.push_back(110);
//	dTerms.push_back(111);
//	dTerms.push_back(115);
//	dTerms.push_back(117);
//	dTerms.push_back(119);
//	dTerms.push_back(121);
//
//	dense_hash_map<unsigned long, string> expDict;
//	expDict.set_empty_key(-1);
//	expDict.set_deleted_key(-2);
//
//	dict.expandDictionary(dPairs, dTerms, expDict);
//
//	string expected = "singing.do.wah.diddy.diddy.dum.diddy.do";
//	string output = "";
//
//	vector<long> symbolIndexSequence;
//	symbolIndexSequence.push_back(9);
//	symbolIndexSequence.push_back(16);
//	symbolIndexSequence.push_back(16);
//	symbolIndexSequence.push_back(13);
//	symbolIndexSequence.push_back(8);
//	symbolIndexSequence.push_back(0);
//	symbolIndexSequence.push_back(11);
//	symbolIndexSequence.push_back(1);
//	symbolIndexSequence.push_back(4);
//	symbolIndexSequence.push_back(20);
//	symbolIndexSequence.push_back(19);
//	symbolIndexSequence.push_back(10);
//	symbolIndexSequence.push_back(6);
//	symbolIndexSequence.push_back(20);
//	symbolIndexSequence.push_back(8);
//
//	long cur;
//	for (int i = 0; i < symbolIndexSequence.size(); ++i)
//	{
//		cur = symbolIndexSequence[i];
//		if (cur < dTerms.size())
//			output += dTerms[cur];
//		else
//			output += expDict[cur - dTerms.size()];
//	}
//
//	ASSERT_EQ(expected, output);
//}