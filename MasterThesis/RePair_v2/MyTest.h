#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	int MyTest::SanityCheck(
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*>& priorityQueue, unordered_map<unsigned int,
		unordered_map<unsigned int, PairTracker >> &activePairs);
	string MyTest::SanityCheckThreadingPointersDetailed(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SanityCheckPairRecordsDetailed(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue);
	int MyTest::SanityCheckThreadingPointers(vector<SymbolRecord*> & sequenceArray);
	int MyTest::SanityCheckPairRecords(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue, unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs);
	void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, long numbers[], int count);
	void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, string input, int size);
	string MyTest::SequenceToString(vector<SymbolRecord*> & sequenceArray);
	string MyTest::SequenceToCompleteString(vector<SymbolRecord*> & sequenceArray);
	void MyTest::ActivePairs(string msg, unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs);
	bool MyTest::inPriorityQueue(
		PairRecord * pairRecord,
		vector<PairRecord*> & priorityQueue);
	bool MyTest::inPriorityQueueAtPosition(
		PairRecord * pairRecord,
		vector<PairRecord*> & priorityQueue,
		long index);
};

