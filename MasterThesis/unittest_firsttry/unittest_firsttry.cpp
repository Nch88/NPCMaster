#include "gtest\gtest.h"
#include "RePair\stdafx.h"

TEST(test, testFirstTry)
{
	test t;

	t.inc(3);

	EXPECT_EQ(3, t.read());

	
}