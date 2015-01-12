// RePair.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	unordered_map<string, PairRecord> activePairs;
	vector<SymbolRecord*> sequenceArray;
	
	Initializer init;

	init.SequenceArray("diddy.txt", &sequenceArray, &activePairs);

	int priorityQueueSize;

	priorityQueueSize = sqrt(sequenceArray.size());

	vector<PairRecord*> priorityQueue(priorityQueueSize);
	
	init.PriorityQueue(priorityQueueSize, &activePairs, &priorityQueue);
	
	if (priorityQueue[priorityQueue.size() - 1] != NULL)
	{
		cout << "not null" << endl;
	}
	else
	{
		cout << "null" << endl;

		for (int i = priorityQueue.size() - 2; i >= 0; i--)
		{
			if (priorityQueue[i] != NULL)
			{

			}
		}
	}

	return 0;
}

