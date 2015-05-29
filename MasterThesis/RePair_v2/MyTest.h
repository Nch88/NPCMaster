#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	int MyTest::SanityCheck(
		vector<SymbolRecord*> & sequenceArray,
		vector<pair<PairRecord*,PairRecord*>> & priorityQueue, dense_hash_map<unsigned long ,
		dense_hash_map<unsigned long , PairTracker >> &activePairs);
	string MyTest::SanityCheckThreadingPointersDetailed(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SanityCheckPairRecordsDetailed(vector<SymbolRecord*> & sequenceArray, vector<pair<PairRecord*,PairRecord*>> & priorityQueue);
	int MyTest::SanityCheckThreadingPointers(vector<SymbolRecord*> & sequenceArray);
	int MyTest::SanityCheckPairRecords(vector<SymbolRecord*> & sequenceArray, vector<pair<PairRecord*,PairRecord*>> & priorityQueue, dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs);
	bool MyTest::SanityCheckPriorityQueue(vector<pair<PairRecord*, PairRecord*>> & priorityQueue);
	void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, unsigned long  numbers[], int count);
	void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, string input, int size);
	string MyTest::SequenceToString(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SequenceToCompleteString(vector<SymbolRecord*> & sequenceArray);
	void MyTest::ActivePairs(string msg, dense_hash_map<unsigned long , dense_hash_map<unsigned long , PairTracker>>& activePairs);
	bool MyTest::inPriorityQueue(
		PairRecord * pairRecord,
		vector<pair<PairRecord*,PairRecord*>> & priorityQueue);
	bool MyTest::inPriorityQueueAtPosition(
		PairRecord * pairRecord,
		vector<pair<PairRecord*,PairRecord*>> & priorityQueue,
		long index);
	bool compareFiles(std::string file1, std::string file2, unsigned long  &badChar);
	bool MyTest::prefixIsGood(string &prefix);
};

