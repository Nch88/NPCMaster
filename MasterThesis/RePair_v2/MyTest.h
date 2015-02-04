#pragma once
class MyTest
{
public:
	MyTest();
	~MyTest();

	string MyTest::SequenceToString(vector<SymbolRecord>& sequenceArray);
	void MyTest::ActivePairs(string msg, unordered_map<unsigned int, unordered_map<unsigned int, PairTracker>>& activePairs);
};

