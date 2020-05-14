#include <stdio.h>

#include <gtest/gtest.h>

static int my_add(int a, int b)
{
	return a + b;
}

TEST(tdd_gtest, basic_gtest)
{
	ASSERT_EQ(2, my_add(1, 1));
}


int main(int argc, char **argv) {

  	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}