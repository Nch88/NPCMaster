#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, long numbers[], int count);
	void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, char input[], int size);
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

