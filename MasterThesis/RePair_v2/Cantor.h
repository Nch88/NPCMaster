#pragma once

namespace Cantor
{
	void reverseCantor(unsigned long& in, unsigned long& out1, unsigned long& out2, unsigned long& out3);
	std::string reverseCantorS(unsigned long& in);
	unsigned long cantor(unsigned long& fst, unsigned long& snd, unsigned long& thrd);
	unsigned long cantorC(unsigned char& fst, unsigned char& snd, unsigned char& thrd);
	bool isTerminal(unsigned long& input);
	bool tryGetNonTerminal(unsigned long& input, unsigned long result);
	unsigned long getNonTerminal(unsigned long input);
}