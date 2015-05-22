#include "stdafx.h"
#include "Cantor.h"

namespace Cantor
{

	unsigned long cantor2(unsigned long& fst, unsigned long& snd)
	{
		return ((0.5 * (((double)fst) + ((double)snd)) * (((double)fst) + ((double)snd) + 1.0)) + ((double)snd));
	}

	void reverseCantor2(unsigned long& z, unsigned long& x, unsigned long& y)
	{
		double w = floor((sqrt(8.0 * ((double)z) + 1.0) - 1.0) / 2.0);
		unsigned long t = (pow(w, 2.0) + w) / 2.0;
		y = z - t;
		x = w - y;
	}

	void reverseCantor(unsigned long& in, unsigned long& out1, unsigned long& out2, unsigned long& out3)
	{
		unsigned long tmp;
		reverseCantor2(in, tmp, out3);
		reverseCantor2(tmp, out1, out2);
	}

	string reverseCantorS(unsigned long& in)
	{
		unsigned long tmp, fst, snd, thrd;
		reverseCantor2(in, tmp, thrd);
		reverseCantor2(tmp, fst, snd);
		if (thrd != 0)
		{
			char c[] = { (char)fst, (char)snd, (char)thrd };
			string s(c, 3);
			return s;
		}
		else if (snd != 0)
		{
			char c[] = { (char)fst, (char)snd };
			string s(c, 2);
			return s;
		}
		else
		{
			char c[] = { (char)fst };
			string s(c, 1);
			return s;
		}
	}

	unsigned long cantor(unsigned long& fst, unsigned long& snd, unsigned long& thrd)
	{
		unsigned long c1 = cantor2(fst, snd);
		return cantor2(c1, thrd);
	}

	unsigned long cantorC(unsigned char& fst, unsigned char& snd, unsigned char& thrd)
	{
		unsigned long f = (unsigned long)fst;
		unsigned long s = (unsigned long)snd;
		unsigned long t = (unsigned long)thrd;
		unsigned long c1 = cantor2(f, s);
		return cantor2(c1, t);
	}

	bool isTerminal(unsigned long& input)
	{
		unsigned long fst, snd;
		reverseCantor2(input, fst, snd);
		return !(snd == 256);
	}

	bool tryGetNonTerminal(unsigned long& input, unsigned long result)
	{
		unsigned long fst, snd;
		reverseCantor2(input, fst, snd);
		result = (snd == 256) ? fst : -1;
		return (snd == 256);
	}

	unsigned long getNonTerminal(unsigned long input)
	{
		unsigned long fst, snd;
		reverseCantor2(input, fst, snd);
		return (snd == 256) ? fst : -1;
	}

	unsigned long addressMerge(unsigned long in)
	{

	}
}