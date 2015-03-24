#pragma once

using namespace std;
using namespace google;

class Initializer
{
public:
	Initializer();
	~Initializer();

	///<summary>
	///Resets all the major structure after compression is done, deleting allocated memory.
	///</summary>
	///<param name="blockSize">Input: The size of the current block of data.</param>
	///<param name="activePairs">Output: Holds the active pair records that we want to delete.</param>
	///<param name="sequenceArray">Output: Holds the symbol records that we want to delete.</param>
	void Initializer::resetCompleted(
		int blockSize,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray);

	///<summary>
	///Resets all the major structure after compression of a block is done, only some memory is deallocated the rest is reused.
	///</summary>
	///<param name="activePairs">Output: Memory for pair records is deallocated as we will not need those records again.</param>
	///<param name="sequenceArray">Output: Entries are reset so they can be reused, no memory is deallocated.</param>
	///<param name="priorityQueue">Output: Resets all pointers to pair records.</param>
	///<param name="terminals">Output: Clears the recorded terminal symbols.</param>
	///<param name="dictionary">Output: Clears the recorded dictionary entries.</param>
	void Initializer::resetForNextBlock(
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		vector<PairRecord*> & priorityQueue,
		unordered_set<long> & terminals,
		dense_hash_map<long, Pair> &dictionary);

	///<summary>
	///Adds a symbol to the sequence array. If a record does not yet exist, memory is allocated for a new one.
	///</summary>
	///<param name="symbol">Input: The symbol to be added to the sequence.</param>
	///<param name="index">Input/Output: Index into the sequence array of where to add the symbol. It is incremented by one to reflect the insertion.</param>
	///<param name="symbolCount">Output: Incremented to reflect the addition of another symbol.</param>
	///<param name="sequenceArray">Output: Array of symbol records to which the new symbol is added.</param>
	///<param name="terminals">Output: The new symbol is added to the set of terminals encountered.</param>
	void addToSequenceArray(		
		unsigned char & symbol,
		long & index,
		int & symbolCount,
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<long>& terminals);

	///<summary>
	///Initializes the sequence array and active pairs structures by reading input characters one by one and adding them as we go.
	///</summary>
	///<param name="c">Input: Represents conditions for use in the program like compression, verbose, timing etc.</param>
	///<param name="file">Input: The open file stream to the input file.</param>
	///<param name="blockSize">Input: The selected block size, which determines how much data to read.</param>
	///<param name="activePairs">Output: Contains all pairs that appear twice or more in the input data.</param>
	///<param name="sequenceArray">Output: Contains the sequence of input characters are they were read from the stream.</param>
	///<param name="terminals">Output: Contains all of the different characters from the input data.</param>
	int SequenceArray(
		Conditions c,
		ifstream & file,
		int & blockSize,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray,
		unordered_set<long>& terminals);

	///<summary>
	///Based on the number of occurences a new record for a pair of characters is created or the count for the old one incremented.
	///</summary>
	///<param name="leftSymbol">Input: The left part of the symbol pair.</param>
	///<param name="rightSymbol">Input: The right part of the symbol pair.</param>
	///<param name="index">Input: The index into the sequence where the left part of the pair is located.</param>
	///<param name="activePairs">Output: Structure that holds all records of active pairs.</param>
	///<param name="sequenceArray">Output: Threading between instances of a pair is updated when new instances are seen.</param>
	void setupPairRecord(
		long leftSymbol,
		long rightSymbol,
		int index,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<SymbolRecord*> & sequenceArray);

	///<summary>
	///Scans though all active pairs and add them to a priority queue based on their frequency in the current block of data.
	///The priority queue has roughly sqrt(n) entries, the first for pairs with frequency 2 and the last for pairs
	///with frequencies roughly greater than sqrt(n).
	///</summary>
	///<param name="activePairs">Input: Structure of active pairs which are to be added to priority queue.</param>
	///<param name="priorityQueue">Output: Vector of active pairs sorted after frequency of occurance.</param>
	///<param name="c">Input: Conditions used by the program like verbose, timing etc.</param>
	void PriorityQueue(
		int priorityQueueSize,
		dense_hash_map<long, dense_hash_map<long, PairTracker>> &activePairs,
		vector<PairRecord*> & priorityQueue,
		Conditions & c);
};