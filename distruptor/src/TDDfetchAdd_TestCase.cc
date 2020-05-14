#include <gtest/gtest.h>

int test10(int, int, int, int);


#define TESTCASE_NAME1 once_tdd_fetchAdd
#define TESTCASE_NAME2 loop_tdd_fetchAdd
#define TEST_FUNCTION  test10

#if 0

TEST(TESTCASE_NAME1, pub1_sub4_queue100000) {
	ASSERT_EQ(1, TEST_FUNCTION(1, 4, 8192 * 256, 1));
}


//it can be fail...
TEST(TESTCASE_NAME1, pub1_sub4_queue64) {
	ASSERT_EQ(1, TEST_FUNCTION(1, 4, 64, 100000));
}

#endif

////////////////////////////////////////////////////////