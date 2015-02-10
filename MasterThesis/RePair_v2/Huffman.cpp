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
	unordered_map<unsigned int, HuffmanNode> & frequencies)
{
	for each (auto symbolRecord in sequenceArray)
	{
		if (frequencies[symbolRecord->symbol].symbol == 0)
			frequencies[symbolRecord->symbol].symbol = symbolRecord->symbol;
		frequencies[symbolRecord->symbol].frequency++;
	}
}

void Huffman::collapseTree(priority_queue<HuffmanNode, vector<HuffmanNode>, compareNodes> & pq)
{
	HuffmanNode * tmpLeftNode;
	HuffmanNode * tmpRightNode;
	while (pq.size() > 2)
	{
		tmpLeftNode = &pq.top();
		pq.pop();
		tmpRightNode = &pq.top();
		pq.pop();

		HuffmanNode * newNode =
			new HuffmanNode(
			0,
			tmpLeftNode->frequency + tmpRightNode->frequency,
			tmpLeftNode,
			tmpRightNode);

		pq.push(*newNode);
	}
}

void Huffman::unravel(HuffmanNode *& leftChild, HuffmanNode *& rightChild)
{
	if (leftChild->symbol == 0)
	{
		leftChild->code.push_back(false);
		leftChild->leftChild->code = leftChild->code;
		leftChild->rightChild->code = leftChild->code;

		unravel(leftChild->leftChild, leftChild->rightChild);
		delete leftChild;
	}
	else
	{
		leftChild->code.push_back(false);
	}
	if (rightChild->symbol == 0)
	{
		rightChild->code.push_back(true);
		rightChild->leftChild->code = rightChild->code;
		rightChild->rightChild->code = rightChild->code;

		unravel(rightChild->leftChild, rightChild->rightChild);
		delete rightChild;
	}
	else
	{
		rightChild->code.push_back(true);
	}
}

void Huffman::encode(vector<SymbolRecord*> & sequenceArray)
{
	unordered_map<unsigned int, HuffmanNode> frequencies;
	priority_queue<HuffmanNode, vector<HuffmanNode>, compareNodes> pq;
	getFrequencies(sequenceArray, frequencies);
	
	//Setup priority queue for symbol frequencies
	for each (auto symbol in frequencies)
	{		
		pq.push(symbol.second);
	}

	//Collapse the 'tree' until two nodes are left
	collapseTree(pq);

	//Unravel children of root
	HuffmanNode * leftChild = &pq.top();
	pq.pop();
	HuffmanNode * rightChild = &pq.top();
	pq.pop();

	//TODO: Call unravel and then replace symbols with Huffman codes in sequence array
}