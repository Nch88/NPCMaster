#include "stdafx.h"

#pragma once
class Test
{
public:
	Test();
	~Test();

	void Dictionary(string msg, unordered_map<char, string> * dictionary);
	void SequenceWithIndex(string msg, vector<SymbolRecord*> * sequenceArray);
	void Sequence(string msg, vector<SymbolRecord*> * sequenceArray);
};

