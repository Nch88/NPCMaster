#include "stdafx.h"
#include "test.h"


test::test()
{
	test::c = 0;
}

void test::inc(int nr)
{
	test::c += nr;
}

void test::dec(int nr)
{
	test::c -= nr;
}

int test::read()
{
	return test::c;
}