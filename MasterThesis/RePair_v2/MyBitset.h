#pragma once

using namespace std;
class MyBitset
{
public:
	bitset<1> bits;
	int nrOfBits = 0;

	MyBitset();
	~MyBitset();

	void MyBitset::push_back(int bit);
};

