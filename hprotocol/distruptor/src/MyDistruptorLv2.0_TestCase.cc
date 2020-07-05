#include <gtest/gtest.h>



#define TESTCASE_NAME1 once_distruptor_lv3
#define TESTCASE_NAME2 loop_distruptor_lv3
#define TEST_FUNCTION  test_MyDisruptor2

int TEST_FUNCTION();

#if 1

TEST(TESTCASE_NAME1, pub4_sub1_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION());
}

////////////////////////////////////////////////////////
#endif