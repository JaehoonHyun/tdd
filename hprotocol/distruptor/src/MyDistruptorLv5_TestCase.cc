#if 0

#include <gtest/gtest.h>

int test11(int, int, int);


#define TESTCASE_NAME1 once_distruptor_lv5
#define TESTCASE_NAME2 loop_distruptor_lv5
#define TEST_FUNCTION  test11



TEST(TESTCASE_NAME1, pub1_sub1_queue64) {
	ASSERT_EQ(1, TEST_FUNCTION(1, 1, 64));
}


TEST(TESTCASE_NAME1, pub2_sub1_queue64) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 1, 64));
}

TEST(TESTCASE_NAME1, pub1_sub2_queue64) {
	ASSERT_EQ(1, TEST_FUNCTION(1, 2, 64));
}

TEST(TESTCASE_NAME1, pub2_sub2_queue64) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 64));
}

////////////////////////////////////////////////////////

TEST(TESTCASE_NAME1, pub4_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 256));
}


TEST(TESTCASE_NAME1, pub8_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 1, 256));
}

TEST(TESTCASE_NAME1, pub4_sub2_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 2, 256));
}

TEST(TESTCASE_NAME1, pub8_sub2_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 2, 256));
}

////////////////////////////////////////////////////////


TEST(TESTCASE_NAME2, pub2_sub1_queue4096) {
	for (int i = 0; i < 100; i++)
		ASSERT_EQ(1, TEST_FUNCTION(2, 1, 4096));
}


TEST(TESTCASE_NAME2, pub4_sub1_queue4096) {
	for (int i = 0; i < 100; i++)
		ASSERT_EQ(1, TEST_FUNCTION(4, 1, 4096));
}

TEST(TESTCASE_NAME2, pub8_sub1_queue4096) {
	for (int i = 0; i < 100; i++)
		ASSERT_EQ(1, TEST_FUNCTION(8, 1, 4096));
}

TEST(TESTCASE_NAME2, pub16_sub1_queue4096) {
	for (int i = 0; i < 100; i++)
		ASSERT_EQ(1, TEST_FUNCTION(16, 1, 4096));
}

////////////////////////////////////////////////////////


TEST(TESTCASE_NAME1, pub2_sub2_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 128));
}

TEST(TESTCASE_NAME1, pub2_sub2_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 256));
}

TEST(TESTCASE_NAME1, pub2_sub2_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 1024));
}

TEST(TESTCASE_NAME1, pub2_sub2_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 4096));
}

//////////////////////////////////////////////////////////////////////


TEST(TESTCASE_NAME1, pub4_sub4_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 128));
}

TEST(TESTCASE_NAME1, pub4_sub4_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 256));
}

TEST(TESTCASE_NAME1, pub4_sub4_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 1024));
}

TEST(TESTCASE_NAME1, pub4_sub4_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 4096));
}


//////////////////////////////////////////////////////////////////////


TEST(TESTCASE_NAME1, pub8_sub8_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 128));
}

TEST(TESTCASE_NAME1, pub8_sub8_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 256));
}

TEST(TESTCASE_NAME1, pub8_sub8_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 1024));
}

TEST(TESTCASE_NAME1, pub8_sub8_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 4096));
}

////////////////////////////////////////////////////////


TEST(TESTCASE_NAME1, pub4_sub1_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 128));
}

TEST(TESTCASE_NAME1, pub4_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 256));
}

TEST(TESTCASE_NAME1, pub4_sub1_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 1024));
}

TEST(TESTCASE_NAME1, pub4_sub1_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 4096));
}

////////////////////////////////////////////////////////
#endif