#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	int MyTest::SanityCheck(
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue, dense_hash_map<long,
		dense_hash_map<long, PairTracker >> &activePairs);
	string MyTest::SanityCheckThreadingPointersDetailed(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SanityCheckPairRecordsDetailed(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue);
	int MyTest::SanityCheckThreadingPointers(vector<SymbolRecord*> & sequenceArray);
	int MyTest::SanityCheckPairRecords(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue, dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs);
	void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, long numbers[], int count);
	void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, string input, int size);
	string MyTest::SequenceToString(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SequenceToCompleteString(vector<SymbolRecord*> & sequenceArray);
	void MyTest::ActivePairs(string msg, dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs);
	bool MyTest::inPriorityQueue(
		PairRecord * pairRecord,
		vector<PairRecord*> & priorityQueue);
	bool MyTest::inPriorityQueueAtPosition(
		PairRecord * pairRecord,
		vector<PairRecord*> & priorityQueue,
		long index);
};

