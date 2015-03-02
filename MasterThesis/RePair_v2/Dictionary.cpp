#include "Dictionary.h"

bool comPair(CompactPair* fst, CompactPair* snd)
{
	//compare two pairs by comparing left symbols, then right symbols
	if (fst->leftSymbol < snd->leftSymbol)
		return true;
	else if (fst->leftSymbol == snd->leftSymbol)
		return fst->rightSymbol < snd->rightSymbol;
	else
		return false;
}

//This is the main dictionary function. It fills the pair vector based on dictionary + terminals.
void Dictionary::generateCompactDictionary(
	unordered_map<unsigned int, Pair>& dictionary,
	unordered_set<unsigned int>& terminals,
	vector<CompactPair*>& pairVector,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &indices)
{
	vector<unsigned int> terminalVector;
	terminalVector.assign(terminals.begin(), terminals.end());
	sort(terminalVector.begin(), terminalVector.end());

	//Split map by generation
	vector<vector<CompactPair*>> generationVectors = *(new vector<vector<CompactPair*>>());
	createGenerationVectors(dictionary, generationVectors);

	createFinalPairVector(dictionary, generationVectors, pairVector, terminalVector, indices);
}

void Dictionary::createFinalPairVector(
	unordered_map<unsigned int, Pair>& dictionary,
	vector<vector<CompactPair*>>& generationVectors,
	vector<CompactPair*>& pairVector,
	vector<unsigned int>& terminals,
	unordered_map<unsigned int, unordered_map<unsigned int, unsigned int>*> &indices)
{
	//Find the indices of the terminals
	unordered_map<unsigned int, unsigned int> *terminalIndices = new unordered_map<unsigned int, unsigned int>();

	for (int i = 0; i < terminals.size(); ++(i))
	{
		(*terminalIndices)[terminals[i]] = i;
	}
	//Generation 1
	for (int i = 0; i < generationVectors[0].size(); ++(i))
	{
		//Find the new indices of the two symbols in this pair
		unsigned int leftIndex = ((*terminalIndices)[generationVectors[0][i]->leftSymbol]);
		unsigned int rightIndex = ((*terminalIndices)[generationVectors[0][i]->rightSymbol]);

		//Make a pair out of the indices we found, then push it to the vector
		CompactPair *p = new CompactPair(leftIndex, rightIndex);
		pairVector.push_back(p);

		//Record the index of this symbol
		if (!(indices)[generationVectors[0][i]->leftSymbol])
			(indices)[generationVectors[0][i]->leftSymbol] = new unordered_map<unsigned int, unsigned int>();
		(*(indices)[generationVectors[0][i]->leftSymbol])[generationVectors[0][i]->rightSymbol] = i + terminals.size();
	}
	//Generation 2+
	int offset = terminals.size() + generationVectors[0].size();
	if (generationVectors.size() > 1)
	{
		for (int i = 1; i < generationVectors.size(); ++i)
		{
			for (int j = 0; j < generationVectors[i].size(); ++j)
			{
				//Find the new indices of the two symbols in this pair
				unsigned int leftSymbol = generationVectors[i][j]->leftSymbol;

				unsigned int leftIndex;

				//Check for terminal symbol or composite symbol
				if (leftSymbol < initialSymbolValue) //Terminal
				{
					leftIndex = (*terminalIndices)[leftSymbol];
				}
				else //Composite
				{
					unsigned int leftSymbolLeftPart = dictionary[leftSymbol].leftSymbol;
					unsigned int leftSymbolRightPart = dictionary[leftSymbol].rightSymbol;
					leftIndex = (*(indices)[leftSymbolLeftPart])[leftSymbolRightPart];
				}

				unsigned int rightSymbol = generationVectors[i][j]->rightSymbol;
				unsigned int rightIndex;

				//Check for terminal symbol or composite symbol
				if (rightSymbol < initialSymbolValue) //Terminal
				{
					rightIndex = (*terminalIndices)[rightSymbol];
				}
				else //Composite
				{
					unsigned int rightSymbolLeftPart = dictionary[rightSymbol].leftSymbol;
					unsigned int rightSymbolRightPart = dictionary[rightSymbol].rightSymbol;
					rightIndex = (*(indices)[rightSymbolLeftPart])[rightSymbolRightPart];
				}

				//Make a pair out of the indices we found, then push it to the vector
				CompactPair *p = new CompactPair(leftIndex, rightIndex);
				pairVector.push_back(p);

				//Record the index of this symbol
				if (!(indices)[leftSymbol])
					(indices)[leftSymbol] = new unordered_map<unsigned int, unsigned int>();
				(*(indices)[leftSymbol])[rightSymbol] = offset + j;
			}
			//Update the offset
			offset += generationVectors[i].size();
		}
	}
	//Delete stuff
	delete terminalIndices;

}

void Dictionary::createGenerationVectors(
	unordered_map<unsigned int, Pair>& dictionary,
	vector<vector<CompactPair*>>& generationVectors)
{
	//Distribute pairs in vectors
	for each (std::pair<const unsigned int, Pair> p in dictionary)
	{
		//Expand the outer vector if necessary
		while (p.second.generation > generationVectors.size())
		{
			vector<CompactPair*> v = *(new vector<CompactPair*>());
			generationVectors.push_back(v);
		}

		//Add this pair to a vector
		CompactPair *cp = new CompactPair(p.second.leftSymbol, p.second.rightSymbol);
		generationVectors[p.second.generation - 1].push_back(cp);
	}

	//Sort the vectors
	for (int i = 0; i < generationVectors.size(); i++)
	{
		sort(generationVectors[i].begin(), generationVectors[i].end(), comPair);
	}
}