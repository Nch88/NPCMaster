//#include "gtest\gtest.h"
//#include "RePair_v2\stdafx.h"
//
//using namespace std;
//
//TEST(testInitialization, diddyTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(65);
//
//	Initializer init;
//	Conditions c;
//	c.timing = false;
//	int priorityQueueSize;
//
//	string input1 = "diddy.txt";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{		
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);		
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		//Test sequence array
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			ASSERT_EQ(i, sequenceArray[i]->index);
//			if (sequenceArray[i]->next)
//			{
//				sequenceArray[i]->next->symbol;
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				if (sequenceArray[i]->symbol == 105 && //in
//					sequenceArray[i + 1]->symbol == 110)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 2);
//				}
//				if (sequenceArray[i]->symbol == 110 && //ng
//					sequenceArray[i + 1]->symbol == 103)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 2);
//				}
//				if (sequenceArray[i]->symbol == 100 && //do
//					sequenceArray[i + 1]->symbol == 111)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 2);
//				}
//				if (sequenceArray[i]->symbol == 46 && //.d
//					sequenceArray[i + 1]->symbol == 100)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 6);
//				}
//				if (sequenceArray[i]->symbol == 100 && //di
//					sequenceArray[i + 1]->symbol == 105)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 3);
//				}
//				if (sequenceArray[i]->symbol == 105 && //id
//					sequenceArray[i + 1]->symbol == 100)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 3);
//				}
//				if (sequenceArray[i]->symbol == 100 && //dd
//					sequenceArray[i + 1]->symbol == 100)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 3);
//				}
//				if (sequenceArray[i]->symbol == 100 && //dy
//					sequenceArray[i + 1]->symbol == 121)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 3);
//				}
//			}
//		}
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{			
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//			
//		}
//		ASSERT_EQ(9, pairCount);
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}
//
//TEST(testInitialization, duplicateTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(65);
//
//	Initializer init;
//	Conditions c;
//	int priorityQueueSize;
//
//	string input1 = "duplicates.txt";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		ASSERT_FALSE(sequenceArray[1]->next);
//		ASSERT_TRUE(sequenceArray[0]->next);
//		ASSERT_FALSE(sequenceArray[2]->next);
//		ASSERT_TRUE(sequenceArray[2]->previous);
//		ASSERT_FALSE(sequenceArray[5]->next);
//		ASSERT_FALSE(sequenceArray[6]->next);
//		ASSERT_TRUE(sequenceArray[6]->previous);
//
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//		
//		//Test sequence array
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			if (sequenceArray[i]->next)
//			{
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				if (sequenceArray[i]->symbol == 97 && //aa
//					sequenceArray[i + 1]->symbol == 97)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 2);
//				}
//				if (sequenceArray[i]->symbol == 98 && //bb
//					sequenceArray[i + 1]->symbol == 98)
//				{
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count == 2);
//				}				
//			}
//		}
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}
//
//TEST(testInitialization, worldTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(256);
//
//	Initializer init;
//	Conditions c;
//	int priorityQueueSize;
//
//	string input1 = "world192.txt";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		ASSERT_FALSE(sequenceArray[1]->next);
//		ASSERT_TRUE(sequenceArray[0]->next);
//		ASSERT_FALSE(sequenceArray[61]->next);
//		ASSERT_TRUE(sequenceArray[60]->next);
//
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			if (sequenceArray[i]->next)
//			{
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count >= 2);
//			}
//		}
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}
//
//TEST(testInitialization, bibleTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(256);
//
//	Initializer init;
//	Conditions c;
//	int priorityQueueSize;
//
//	string input1 = "bible.txt";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		ASSERT_TRUE(sequenceArray[10]->next);
//		ASSERT_TRUE(sequenceArray[60]->next);
//
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			if (sequenceArray[i]->next)
//			{
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count >= 2);
//			}
//		}
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}
//
//TEST(testInitialization, ecoliTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(256);
//
//	Initializer init;
//	Conditions c;
//	int priorityQueueSize;
//
//	string input1 = "E.coli";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		ASSERT_TRUE(sequenceArray[3]->next);
//		ASSERT_FALSE(sequenceArray[3]->previous);
//		ASSERT_TRUE(sequenceArray[5]->next);
//		ASSERT_TRUE(sequenceArray[5]->previous);
//		ASSERT_FALSE(sequenceArray[4]->next);
//		ASSERT_TRUE(sequenceArray[9]->next);
//		ASSERT_TRUE(sequenceArray[9]->previous);
//		ASSERT_TRUE(sequenceArray[44]->next);
//		ASSERT_TRUE(sequenceArray[9]->previous);
//
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//		ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			if (sequenceArray[i]->next)
//			{
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count >= 2);
//			}
//		}
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}
//
//TEST(testInitialization, ecoliLoopTest)
//{
//	string filename;
//	int blockSize;
//	blockSize = 1048576;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(256);
//
//	Initializer init;
//	Conditions c;
//	c.timing = false;
//	MyTimer t;
//	int priorityQueueSize;
//
//	string input1 = "diddy.txt";
//	string input2 = "E.coli";
//	string input3 = "dna.50MB";
//
//	filename = input2;
//
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		while (file.is_open())
//		{			
//			init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//			priorityQueueSize = sqrt(sequenceArray.size());
//			priorityQueue.resize(priorityQueueSize);
//			init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//			if (sequenceArray.size() > 0)
//			{
//				ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//				ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//			}
//
//			for (int i = 0; i < sequenceArray.size(); i++)
//			{
//				if (sequenceArray[i]->next)
//				{
//					ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//					ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//					ASSERT_TRUE(sequenceArray[i] == sequenceArray[i]->next->previous);
//
//					ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count >= 2);
//				}
//			}
//
//			PairRecord * tmpPair;
//			int pairCount = 0;
//			//Test priority queue
//			for (int i = 0; i < priorityQueue.size(); i++)
//			{
//				if (priorityQueue[i])
//				{
//					tmpPair = priorityQueue[i];
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//					while (tmpPair->nextPair)
//					{
//						ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//						tmpPair = tmpPair->nextPair;
//						if (i < priorityQueue.size() - 1)
//							ASSERT_EQ(i + 2, tmpPair->count);
//						else
//							ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//						pairCount++;
//					}
//				}
//
//			}
//			
//			init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
//		}
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//	}	
//}
//
//TEST(testInitialization, dna50mbTest)
//{
//	string filename;
//	int blockSize;
//
//	dense_hash_map<long, dense_hash_map<long, PairTracker>> activePairs;
//	vector<SymbolRecord*> sequenceArray;
//	vector<PairRecord*> priorityQueue;
//	//dense_hash_map<long, Pair> dictionary;
//	long symbols(256);
//
//	Initializer init;
//	Conditions c;
//	int priorityQueueSize;
//
//	string input1 = "dna.50MB";
//
//	filename = input1;
//	blockSize = 1048576;
//
//	ifstream file(filename);
//
//	if (file.is_open())
//	{
//		init.SequenceArray(c, file, blockSize, activePairs, sequenceArray);
//
//		priorityQueueSize = sqrt(sequenceArray.size());
//		priorityQueue.resize(priorityQueueSize);
//		init.PriorityQueue(priorityQueueSize, activePairs, priorityQueue, c);
//
//		ASSERT_TRUE(sequenceArray[4]->next);
//		ASSERT_FALSE(sequenceArray[4]->previous);
//		ASSERT_TRUE(sequenceArray[3113]->next);
//		ASSERT_TRUE(sequenceArray[3113]->previous);
//		ASSERT_FALSE(sequenceArray[3114]->next);
//		ASSERT_FALSE(sequenceArray[3114]->previous);
//		ASSERT_TRUE(sequenceArray[3115]->next);
//		ASSERT_TRUE(sequenceArray[3115]->previous);
//		ASSERT_FALSE(sequenceArray[3116]->next);
//		ASSERT_FALSE(sequenceArray[3116]->previous);
//		ASSERT_TRUE(sequenceArray[3117]->next);
//		ASSERT_TRUE(sequenceArray[3117]->previous);
//
//		ASSERT_TRUE(sequenceArray[3113]->next == sequenceArray[3115]);
//		ASSERT_TRUE(sequenceArray[3115]->previous == sequenceArray[3113]);
//
//		if (sequenceArray.size() > 0)
//		{
//			ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->next);
//			ASSERT_FALSE(sequenceArray[sequenceArray.size() - 1]->previous);
//		}
//
//		for (int i = 0; i < sequenceArray.size(); i++)
//		{
//			if (sequenceArray[i]->next)
//			{
//				ASSERT_EQ(sequenceArray[i]->symbol, sequenceArray[i]->next->symbol);
//				ASSERT_EQ(sequenceArray[i + 1]->symbol, sequenceArray[sequenceArray[i]->next->index + 1]->symbol);
//
//				ASSERT_TRUE(sequenceArray[i], sequenceArray[i]->next->previous);
//
//				ASSERT_TRUE(activePairs[sequenceArray[i]->symbol][sequenceArray[i + 1]->symbol].pairRecord->count >= 2);
//			}
//		}
//
//		PairRecord * tmpPair;
//		int pairCount = 0;
//		//Test priority queue
//		for (int i = 0; i < priorityQueue.size(); i++)
//		{
//			if (priorityQueue[i])
//			{
//				tmpPair = priorityQueue[i];
//				if (i < priorityQueue.size() - 1)
//					ASSERT_EQ(i + 2, tmpPair->count);
//				else
//					ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//				pairCount++;
//				while (tmpPair->nextPair)
//				{
//					ASSERT_EQ(tmpPair, tmpPair->nextPair->previousPair);
//					tmpPair = tmpPair->nextPair;
//					if (i < priorityQueue.size() - 1)
//						ASSERT_EQ(i + 2, tmpPair->count);
//					else
//						ASSERT_TRUE(priorityQueue.size() < tmpPair->count);
//					pairCount++;
//				}
//			}
//
//		}
//		//Reset for next block
//		init.resetForNextBlock(activePairs, sequenceArray, priorityQueue, blockSize);
//	}
//	else
//	{
//		cout << "Problem opening file: " << filename << endl;
//		ASSERT_FALSE(true);
//	}
//}