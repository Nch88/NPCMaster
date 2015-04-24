#include "stdafx.h"
#include "MyTest.h"


MyTest::MyTest()
{
}


MyTest::~MyTest()
{
}

int MyTest::SanityCheck(
	vector<SymbolRecord*> & sequenceArray,
	vector<PairRecord*>& priorityQueue, dense_hash_map<long,
	dense_hash_map<long, PairTracker >> &activePairs)
{
	return SanityCheckThreadingPointers(sequenceArray) + SanityCheckPairRecords(sequenceArray, priorityQueue, activePairs);
}

int MyTest::SanityCheckThreadingPointers(vector<SymbolRecord*> & sequenceArray)
{
	bool sane = true;
	for (int i = 0; i < sequenceArray.size(); i++)//each (SymbolRecord* p in sequenceArray)
	{
		SymbolRecord* p = sequenceArray[i];
		if (p->next)
			sane = sane && (p->next->index > p->index) && (p->symbol == 0 || p->symbol == p->next->symbol);
		if (p->previous)
			sane = sane && (p->previous->index < p->index) && (p->symbol == 0 || p->symbol == p->previous->symbol);
		if (p->symbol == 0 && ((i>0 && sequenceArray[i-1]->symbol != 0)||((i<sequenceArray.size()-1) && sequenceArray[i+1]->symbol != 0)))
		//If this is an empty symbol next to a non-empty symbol
		{
			if (p->next)
			{
				sane = sane && (p->next->symbol != 0);
				for (int j = i + 1; j < p->next->index; j++)
					sane = sane && (sequenceArray[j]->symbol == 0);
			}
			if (p->previous)
			{
				sane = sane && (p->previous->symbol != 0);
				for (int j = p->previous->index + 1; j < i; j++)
					sane = sane && (sequenceArray[j]->symbol == 0);
			}
		}
	}
	if (!sane)
		return 100;
	return 0;
}

string MyTest::SanityCheckThreadingPointersDetailed(vector<SymbolRecord*> & sequenceArray)
{
	string output = "\n";
	for (int i = 0; i < sequenceArray.size(); i++)//each (SymbolRecord* p in sequenceArray)
	{
		SymbolRecord* p = sequenceArray[i];
		if (p->next)
		{
			if (p->next->index < p->index)
			{
				output += "Error in next-pointer at index ";
				output += to_string(i);
				output += ": index pointed to is lower than current.\n\n";
			}
			if (p->symbol != 0 && p->symbol != p->next->symbol)
			{
				output += "Error in next-pointer at index ";
				output += to_string(i);
				output += ": next symbol is not the same.\n\n";
			}
		}
		if (p->previous)
		{
			if (p->previous->index > p->index)
			{
				output += "Error in previous-pointer at index ";
				output += to_string(i);
				output += ": index pointed to is higher than current.\n\n";
			}
			if (p->symbol != 0 && p->symbol != p->previous->symbol)
			{
				output += "Error in previous-pointer at index ";
				output += to_string(i);
				output += ": previous symbol is not the same.\n\n";
			}
		}
		if (p->symbol == 0 && ((i>0 && sequenceArray[i - 1]->symbol != 0) || ((i<sequenceArray.size() - 1) && sequenceArray[i + 1]->symbol != 0)))
			//If this is an empty symbol next to a non-empty symbol
		{
			if (p->next)
			{
				if (p->next->symbol == 0)
				{
					output += "Error in next-pointer of empty symbol at index ";
					output += to_string(i);
					output += ": Empty symbol next to non-empty symbol should not point to another empty as next.\n\n";
				}
				for (int j = i + 1; j < p->next->index; j++)
				{
					if (sequenceArray[j]->symbol != 0)
					{
						output += "Error in next-pointer of empty symbol at index ";
						output += to_string(i);
						output += ": target is not the next non-empty symbol.\n\n";
					}
				}
			}
			if (p->previous)
			{
				if (p->previous->symbol == 0)
				{
					output += "Error in previous-pointer of empty symbol at index ";
					output += to_string(i);
					output += ": Empty symbol next to non-empty symbol should not point to another empty as previous.\n\n";
				}
				for (int j = p->previous->index + 1; j < i; j++)
				{
					if (sequenceArray[j]->symbol != 0)
					{
						output += "Error in previous-pointer of empty symbol at index ";
						output += to_string(i);
						output += ": target is not the last non-empty symbol\n\n";
					}
				}
			}
		}
	}
	return output;
}

string MyTest::SanityCheckPairRecordsDetailed(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue)
{
	SymbolRecord* sr;
	string result = "";
	//Check priority queue
	for (int i = 0; i < priorityQueue.size(); i++)
	{
		if (priorityQueue[i])
		{
			PairRecord* current = priorityQueue[i];
			int pairCount = 0;
			do
			{
				pairCount++;
				if ((i < priorityQueue.size() - 1 && current->count != i + 2) || current->count < i + 2)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "Count does not match queue number.";
				}/*
				if (current->arrayIndexFirst > current->arrayIndexLast)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "ArrayIndexFirst greater than ArrayIndexLast.";
				}*/

				//Check index first & index last
				sr = sequenceArray[current->arrayIndexFirst];
				if (sr->previous != nullptr)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "Element pointed to by ArrayIndexFirst has previous element.";
				}
				if (sr->next == nullptr)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "Element pointed to by ArrayIndexFirst has no next element.";
				}
				/*sr = sequenceArray[current->arrayIndexLast];
				if (sr->previous == nullptr)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "Element pointed to by ArrayIndexLast has no previous element.";
				}
				if (sr->next != nullptr)
				{
					result += "\nError in priority queue number " + to_string(i) + " at entry number " + to_string(pairCount) + ":";
					result += "Element pointed to by ArrayIndexLast has next element.";
				}*/

				current = current->nextPair;
			} while (current);
		}
	}
	return result + "\n\n";
}

int MyTest::SanityCheckPairRecords(vector<SymbolRecord*> & sequenceArray, vector<PairRecord*>& priorityQueue, dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs)
{
	bool sane = true;
	int result = 0;
	SymbolRecord* sr;
	//Check priority queue
	for (int i = 0; i < priorityQueue.size(); i++)
	{
		if (priorityQueue[i])
		{
			PairRecord* current = priorityQueue[i];
			do
			{
				if ((i < priorityQueue.size() - 1 && current->count != i + 2) || current->count < i + 2)
					sane = sane && false;
				
				
				//Check index first & index last
				sr = sequenceArray[current->arrayIndexFirst];
				sane = sane && (sr->previous == nullptr) && (sr->next != nullptr);
				/*sr = sequenceArray[current->arrayIndexLast];
				sane = sane && (sr->next == nullptr) && (sr->previous != nullptr);*/

				current = current->nextPair;
			} while (current);
		}
	}
	if (!sane)
		result = 10;
	sane = true;
	//Check active pairs
	dense_hash_map<long, dense_hash_map<long, PairTracker>>::iterator iterone;
	dense_hash_map<long, PairTracker>::iterator itertwo;
	for (iterone = activePairs.begin(); iterone != activePairs.end(); iterone++)
	{
		for (itertwo = iterone->second.begin(); itertwo != iterone->second.end(); itertwo++)
		{
			if (itertwo->second.pairRecord)
				sane = (itertwo->second.pairRecord->count > 1);
		}
	}
	if (!sane)
		result += 1;
	return result;
}

void MyTest::buildSequenceArray(vector<SymbolRecord*> & sequenceArray, long numbers[], int count)
{
	for (int i = 0; i < count; i++)
	{
		SymbolRecord * p = new SymbolRecord(numbers[i], i);
		sequenceArray.push_back(p);
	}
}

void MyTest::charArrayToSequence(vector<SymbolRecord*> &  sequence, string input, int size)
{
	long * numbers = new long[size];
	for (int i = 0; i < size; i++)
	{
		numbers[i] = (long)input[i];
	}
	buildSequenceArray(sequence, numbers, size);
}

string MyTest::SequenceToCompleteString(vector<SymbolRecord*> & sequenceArray)
{
	string s;

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i]->symbol != (char)0)
			s += (char)sequenceArray[i]->symbol;
		else
			s += '_';
	}
	return s;
}

string MyTest::SequenceToString(vector<SymbolRecord*> & sequenceArray)
{
	//Test
	string s;

	for (int i = 0; i < sequenceArray.size(); i++)
	{
		if (sequenceArray[i]->symbol != (char)0)
			s += (char)sequenceArray[i]->symbol;
	}
	return s;
	//End Test
}

void MyTest::ActivePairs(string msg, dense_hash_map<long, dense_hash_map<long, PairTracker>>& activePairs)
{
	cout << msg << ": ";
	for each (auto leftSymbol in activePairs)
	{
		for each (auto pair in leftSymbol.second)
		{
			if (pair.second.pairRecord)
				cout << "Left: " << leftSymbol.first << " Right: " << pair.first << " Count: " << pair.second.pairRecord->count << endl;
		}
	}
	cout << endl << endl;
}

bool MyTest::inPriorityQueue(
	PairRecord * pairRecord,
	vector<PairRecord*> & priorityQueue)
{
	PairRecord * tmpPairRecord;

	for (int i = 0; i < priorityQueue.size(); i++)
	{
		tmpPairRecord = priorityQueue[i];

		while (tmpPairRecord)
		{
			if (pairRecord == tmpPairRecord)
				return true;
			tmpPairRecord = tmpPairRecord->nextPair;
		}
	}
	return false;
}

bool MyTest::inPriorityQueueAtPosition(
	PairRecord * pairRecord,
	vector<PairRecord*> & priorityQueue,
	long index)
{
	PairRecord * tmpPairRecord;

	
	tmpPairRecord = priorityQueue[index];

	while (tmpPairRecord)
	{
		if (pairRecord == tmpPairRecord)
			return true;
		tmpPairRecord = tmpPairRecord->nextPair;
	}
	
	return false;
}

int MyTest::entriesinPriorityQueueAtPosition(
	vector<PairRecord*> & priorityQueue,
	long index)
{
	PairRecord * tmpPairRecord;
	int c = 0;

	tmpPairRecord = priorityQueue[index];

	while (tmpPairRecord)
	{
		++c;
		tmpPairRecord = tmpPairRecord->nextPair;
	}

	return c;
}

bool MyTest::compareFiles(string file1, string file2, long &badChar)
{
	ifstream stream1(file1);
	ifstream stream2(file2);
	badChar = 0;
	char chunk1;
	char chunk2;

	if (stream1.is_open() && stream2.is_open())
	{
		while (stream1 >> noskipws >> chunk1 && stream2 >> noskipws >> chunk2)
		{
			++badChar;
			if (chunk1 != chunk2)
				return false;
		}
		stream1.peek();
		stream2.peek();
		if (stream1.eof() && stream2.eof())
			return true;
	}
	return false;
}

bool MyTest::prefixIsGood(string &prefix)
{
	for (int i = 0; i < prefix.size(); i++)
	{
		if (prefix[i] != '0')
			return false;
	}
	return true;
}