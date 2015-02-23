#include "stdafx.h"
#include "Huffman.h"


Huffman::Huffman()
{
}


Huffman::~Huffman()
{
}

void Huffman::getFrequencies(
	vector<SymbolRecord*> & sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> & frequencies,
	int &cardinality)
{
	for each (auto symbolRecord in sequenceArray)
	{
		if (symbolRecord->symbol != 0)
		{
			if (!frequencies[symbolRecord->symbol]){
				frequencies[symbolRecord->symbol] = new HuffmanNode(symbolRecord->symbol, 0);
				++cardinality;
			}
			frequencies[symbolRecord->symbol]->frequency++;
		}		
	}
}

void Huffman::setupPriorityQueue(
	unordered_map<unsigned int, HuffmanNode *> & frequencies,
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq)
{
	//Setup priority queue for symbol frequencies
	for each (auto symbol in frequencies)
	{
		pq.push(symbol.second);
	}
}

void Huffman::collapseTree(priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> & pq)
{
	HuffmanNode * tmpLeftNode;
	HuffmanNode * tmpRightNode;
	unsigned int symbol = 0;
	while (pq.size() > 2)
	{
		tmpLeftNode = pq.top();
		pq.pop();
		tmpRightNode = pq.top();
		pq.pop();

		HuffmanNode * newNode =
			new HuffmanNode(
			symbol,
			tmpLeftNode->frequency + tmpRightNode->frequency,
			tmpLeftNode,
			tmpRightNode);

		pq.push(newNode);
	}
}

void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild)
{
	char zero = '0';
	char one = '1';
	if (leftChild->symbol == 0)
	{
		leftChild->code += zero;
		leftChild->leftChild->code = leftChild->code;
		leftChild->rightChild->code = leftChild->code;

		unravel(leftChild->leftChild, leftChild->rightChild);
		delete leftChild;
	}
	else
	{
		leftChild->code += zero;
	}
	if (rightChild->symbol == 0)
	{
		rightChild->code += one;
		rightChild->leftChild->code = rightChild->code;
		rightChild->rightChild->code = rightChild->code;

		unravel(rightChild->leftChild, rightChild->rightChild);
		delete rightChild;
	}
	else
	{
		rightChild->code += one;
	}
}

void Huffman::sift(int currentNodeIndex,
	int heapSize,
	int *codeLengths)
{
	
	int leftChildIndex = ((currentNodeIndex + 1) * 2) - 1;
	int rightChildIndex = (((currentNodeIndex + 1) * 2) + 1) - 1;

	if (leftChildIndex >= heapSize) //Stop the recursion
		return;

	int parentFrequency = codeLengths[codeLengths[currentNodeIndex]];
	int leftChildFrequency = codeLengths[codeLengths[leftChildIndex]];
	int rightChildFrequency = codeLengths[codeLengths[rightChildIndex]];

	if (rightChildIndex < heapSize &&
		leftChildFrequency > rightChildFrequency)
		//Right child is smaller than left
	
	{
		if (parentFrequency > rightChildFrequency)
		{
			//Swap with right child
			int tmpIndex = codeLengths[currentNodeIndex];
			codeLengths[currentNodeIndex] = codeLengths[rightChildIndex];
			codeLengths[rightChildIndex] = tmpIndex;

			sift(rightChildIndex, heapSize, codeLengths);
			
		}
	}
	else if (parentFrequency > leftChildFrequency)
		//Left is smaller than right or right does not exist, and left is smaller than parent
	{
		//Swap with left child
		int tmpIndex = codeLengths[currentNodeIndex];
		codeLengths[currentNodeIndex] = codeLengths[leftChildIndex];
		codeLengths[leftChildIndex] = tmpIndex;

		sift(leftChildIndex, heapSize, codeLengths);
	}
}

void Huffman::initCodeLengthsArray(
	int cardinality,
	int *codeLengths,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes)
{
	int i = 0;
	for each (auto node in huffmanCodes)
	{
		codeLengths[cardinality + i] = node.second->frequency;
		codeLengths[i] = cardinality + i; //Index of a symbol Points to the symbol's frequency
		++i;
	}
}

void Huffman::initMinHeap(
	int heapSize,
	int *codeLengths)
{
	int currentNodeIndex = heapSize - 1; //Last node
	currentNodeIndex = currentNodeIndex / 2; //Parent of last node

	while (currentNodeIndex >= 0)
	{
		sift(currentNodeIndex, heapSize, codeLengths);
		--currentNodeIndex;
	}
}

void Huffman::phaseTwo(
	int heapSize,
	int *codeLengths)
{
	int m1;
	int m2;

	while (heapSize > 1)
	{
		//a)
		m1 = codeLengths[0];													//Take symbol with smallest frequency
		codeLengths[0] = codeLengths[heapSize - 1];								//Pull last element to front of heap
		--heapSize;																

		//b)
		sift(0, heapSize, codeLengths);											//Sift the last element down through the heap
		m2 = codeLengths[0];													//Take symbol with next smallest frequency

		//c)
		codeLengths[(heapSize - 1) + 1] = codeLengths[m1] + codeLengths[m2];	//Create new frequency for combination of two smallest frequencies
		codeLengths[0] = (heapSize - 1) + 1;									//"Create" new symbol pointing to the new frequency
		codeLengths[m1] = (heapSize - 1) + 1;									//Point to new symbol
		codeLengths[m2] = (heapSize - 1) + 1;									//Point to new symbol

		//d)
		sift(0, heapSize, codeLengths);											//Sift the new element down through the heap
	}
}

void Huffman::phaseThree(
	int cardinality,
	int *codeLengths)
{
	codeLengths[1] = 0;															//Represents the root with code length one

	for (int i = 2; i < cardinality * 2; i++)
	{
		codeLengths[i] = codeLengths[codeLengths[i]] + 1;						//Nodes will get codes of length one greater than their parents
	}
}

void Huffman::getCodeLengths(
	int cardinality,
	int *codeLengths,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes)
{
	int heapSize = cardinality;
	//Phase 1	
	initCodeLengthsArray(cardinality, codeLengths, huffmanCodes);
	initMinHeap(heapSize, codeLengths);
	//Phase 1  - end

	phaseTwo(heapSize, codeLengths);

	phaseThree(cardinality, codeLengths);
}

void Huffman::encode(
	vector<SymbolRecord*> &sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes)
{	
	int cardinality = 0;
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	getFrequencies(sequenceArray, huffmanCodes, cardinality); //+ cardinality of compressed sequence
	int *codeLengths = new int[cardinality * 2]; //Code lengths will appear in positions [cardinality - (2*cardinality -1)]
	
	getCodeLengths(cardinality, codeLengths, huffmanCodes);
	
	//TODO: Create actual canonical Huffman codes
}