#pragma once
class TestSuite
{
public:
	//Timing
	boost::chrono::nanoseconds t_initialization;
	boost::chrono::nanoseconds t_repair;
	boost::chrono::nanoseconds t_huffmanEncoding;
	boost::chrono::nanoseconds t_encodeSequence;
	boost::chrono::nanoseconds t_writeHuffmanDictionary;
	boost::chrono::nanoseconds t_setupDictionary;
	boost::chrono::nanoseconds t_writeDictionary;

	boost::chrono::nanoseconds t_readDictionary;
	boost::chrono::nanoseconds t_decompression;

	//Memory
	//m_initialization;
	// m_repair;
	// m_huffmanEncoding;
	// m_huffmanDictionary;
	// m_normalDictionary;
	// m_readDictionary;
	// m_decompression;

	//Compression
	long compression = 0;

	//Statistics
	long s_maxPairs = 0;
	long s_avgNrOfPhrases = 0;
	long s_longestPhrase = 0;
	long s_avgPhraseLength = 0;
	int s_nrOfBlocks = 0;
	std::string s_filename = "";

	MyTimer testTimer;

	TestSuite();
	~TestSuite();

	void WriteToFileEncoding();
};

