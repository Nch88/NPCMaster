#include "gtest\gtest.h"
#include "RePair_v2\stdafx.h"

using namespace std;

TEST(createCompactDictionary, createGenerationVectors_diddy)
{
	AlgorithmP algo;
	Dictionary dc;

	dense_hash_map<long, Pair> dictionary;
	Pair A('.', 'd', 1);
	dictionary[300] = A;
	Pair B('d', 'd', 1);
	dictionary[301] = B;
	Pair C(300, 'i', 2);
	dictionary[302] = C;
	Pair D(301, 'y', 2);
	dictionary[303] = D;
	Pair E(302, 303, 3);
	dictionary[304] = E;
	Pair F('i', 'n', 1);
	dictionary[305] = F;
	Pair G(300, 'o', 2);
	dictionary[306] = G;
	Pair H(305, 'g', 2);
	dictionary[307] = H;

	vector<vector<CompactPair>> generationVectors;
	dc.createGenerationVectors(dictionary, generationVectors);

	vector<CompactPair*> gen0;
	gen0.push_back(new CompactPair(46, 100));
	gen0.push_back(new CompactPair(100, 100));
	gen0.push_back(new CompactPair(105, 110));
	vector<CompactPair*> gen1;
	gen1.push_back(new CompactPair(300, 105));
	gen1.push_back(new CompactPair(300, 111));
	gen1.push_back(new CompactPair(301, 121));
	gen1.push_back(new CompactPair(305, 103));
	vector<CompactPair*> gen2;
	gen2.push_back(new CompactPair(302, 303));

	for (int i = 0; i < generationVectors[0].size(); ++i)
	{
		ASSERT_TRUE((generationVectors[0])[i].leftSymbol == gen0[i]->leftSymbol);
		ASSERT_TRUE((generationVectors[0])[i].rightSymbol == gen0[i]->rightSymbol);
	}
	for (int i = 0; i < generationVectors[1].size(); ++i)
	{
		ASSERT_TRUE((generationVectors[1])[i].leftSymbol == gen1[i]->leftSymbol);
		ASSERT_TRUE((generationVectors[1])[i].rightSymbol == gen1[i]->rightSymbol);
	}
	for (int i = 0; i < generationVectors[2].size(); ++i)
	{
		ASSERT_TRUE((generationVectors[2])[i].leftSymbol == gen2[i]->leftSymbol);
		ASSERT_TRUE((generationVectors[2])[i].rightSymbol == gen2[i]->rightSymbol);
	}
}

TEST(createCompactDictionary, createFinalPairVector)
{
	AlgorithmP algo;
	Dictionary dc;

	dense_hash_map<long, Pair> dictionary;
	Pair A('.', 'd', 1);
	dictionary[300] = A;
	Pair B('d', 'd', 1);
	dictionary[301] = B;
	Pair C(300, 'i', 2);
	dictionary[302] = C;
	Pair D(301, 'y', 2);
	dictionary[303] = D;
	Pair E(302, 303, 3);
	dictionary[304] = E;
	Pair F('i', 'n', 1);
	dictionary[305] = F;
	Pair G(300, 'o', 2);
	dictionary[306] = G;
	Pair H(305, 'g', 2);
	dictionary[307] = H;

	vector<vector<CompactPair>> generationVectors;
	dc.createGenerationVectors(dictionary, generationVectors);

	vector<long> terminals = { 's', 'i', 'n', 'g', '.', 'd', 'o', 'w', 'a', 'h', 'y', 'u', 'm' };

	vector<vector<CompactPair>> pairs;
	dense_hash_map<long, dense_hash_map<long, long>> indices;
	dense_hash_map<long, long> tIndices;
	dc.createFinalPairVectors(dictionary, generationVectors, pairs, terminals, indices, tIndices);

	vector<vector<CompactPair>> expected;
	vector<CompactPair> v1, v2, v3;
	expected.push_back(v1);
	expected.push_back(v2);
	expected.push_back(v3);
	expected[0].push_back(CompactPair(4, 5));
	expected[0].push_back(CompactPair(5, 5));
	expected[0].push_back(CompactPair(1, 2));
	expected[1].push_back(CompactPair(13, 1));
	expected[1].push_back(CompactPair(13, 6));
	expected[1].push_back(CompactPair(14, 10));
	expected[1].push_back(CompactPair(15, 3));
	expected[2].push_back(CompactPair(16, 18));

	//Check pairs
	for (int i = 0; i < pairs.size(); ++i)
	{
		for (int j = 0; j < pairs[i].size(); ++j)
		{
			ASSERT_EQ(expected[i][j].leftSymbol, (pairs[i])[j].leftSymbol);
			ASSERT_EQ(expected[i][j].rightSymbol, (pairs[i])[j].rightSymbol);
		}
	}
}

TEST(createCompactDictionary, generateCompactDictionary)
{
	AlgorithmP algo;
	Dictionary dc;

	dense_hash_map<long, Pair> dictionary;
	Pair A('.', 'd', 1);
	dictionary[300] = A;
	Pair B('d', 'd', 1);
	dictionary[301] = B;
	Pair C(300, 'i', 2);
	dictionary[302] = C;
	Pair D(301, 'y', 2);
	dictionary[303] = D;
	Pair E(302, 303, 3);
	dictionary[304] = E;
	Pair F('i', 'n', 1);
	dictionary[305] = F;
	Pair G(300, 'o', 2);
	dictionary[306] = G;
	Pair H(305, 'g', 2);
	dictionary[307] = H;

	unordered_set<long> terminals = { 's', 'i', 'n', 'g', '.', 'd', 'o', 'w', 'a', 'h', 'y', 'u', 'm' };

	vector<vector<CompactPair>> pairs;

	dense_hash_map<long, dense_hash_map<long, long>> indices;
	dense_hash_map<long, long> tIndices;

	vector<vector<CompactPair>> generationVectors;
	dc.generateCompactDictionary(dictionary, terminals, pairs, indices, tIndices ,generationVectors);

	vector<vector<CompactPair>> expected;
	vector<CompactPair> v1, v2, v3;
	expected.push_back(v1);
	expected.push_back(v2);
	expected.push_back(v3);
	expected[0].push_back(CompactPair(0, 2));
	expected[0].push_back(CompactPair(2, 2));
	expected[0].push_back(CompactPair(5, 7));
	expected[1].push_back(CompactPair(13, 5));
	expected[1].push_back(CompactPair(13, 8));
	expected[1].push_back(CompactPair(14, 12));
	expected[1].push_back(CompactPair(15, 3));
	expected[2].push_back(CompactPair(16, 18));

	//Check pairs
	for (int i = 0; i < pairs.size(); ++i)
	{
		for (int j = 0; j < pairs[i].size(); ++j)
		{
			ASSERT_EQ(expected[i][j].leftSymbol, (pairs[i])[j].leftSymbol);
			ASSERT_EQ(expected[i][j].rightSymbol, (pairs[i])[j].rightSymbol);
		}
	}

	//Check indices
	ASSERT_EQ(13, (indices['.'])['d']);
	ASSERT_EQ(14, (indices['d'])['d']);
	ASSERT_EQ(15, (indices['i'])['n']);
	ASSERT_EQ(16, (indices[300])['i']);
	ASSERT_EQ(17, (indices[300])['o']);
	ASSERT_EQ(18, (indices[301])['y']);
	ASSERT_EQ(19, (indices[305])['g']);
	ASSERT_EQ(20, (indices[302])[303]);
}