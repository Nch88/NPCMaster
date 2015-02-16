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
	unordered_map<unsigned int, HuffmanNode *> & frequencies)
{
	for each (auto symbolRecord in sequenceArray)
	{
		if (symbolRecord->symbol != 0)
		{
			if (!frequencies[symbolRecord->symbol])
				frequencies[symbolRecord->symbol] = new HuffmanNode(symbolRecord->symbol, 0);
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

void Huffman::encode(
	vector<SymbolRecord*> &sequenceArray,
	unordered_map<unsigned int, HuffmanNode *> &huffmanCodes)
{	
	priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;
	getFrequencies(sequenceArray, huffmanCodes);
	
	setupPriorityQueue(huffmanCodes, pq);

	//Collapse the 'tree' until two nodes are left
	collapseTree(pq);

	//Start with children of root
	HuffmanNode * leftChild = pq.top();
	pq.pop();
	HuffmanNode * rightChild = pq.top();
	pq.pop();

	//Unravel the tree and build the Huffman code
	unravel(leftChild, rightChild);
}