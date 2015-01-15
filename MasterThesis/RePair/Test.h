#include "stdafx.h"

#pragma once
class Test
{
public:
	Test();
	~Test();

	void Sequence(string msg, unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray);
	void SequenceWithIndex(string msg, unique_ptr<vector<unique_ptr<SymbolRecord>>>& sequenceArray);
	void Dictionary(string msg, unique_ptr<unordered_map<char, string>>& dictionary);
	void PriorityQueueSpecificCount(
		string msg,
		unique_ptr<vector<unique_ptr<PairRecord>>>& priorityQueue,
		int i);
	void Context(
		string msg,
		SymbolRecord* symbolLeft,
		SymbolRecord* symbolRight,
		SymbolRecord* symbolPrevious,
		SymbolRecord* symbolNext);
};

