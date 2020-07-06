#include <stdio.h>
#include <time.h>
#include <atomic>
#include <thread>

#include <gtest/gtest.h>

#include "inc/MyDisruptorLv3.h"



int test8(int, int, int);


#define TESTCASE_NAME1 once_distruptor_lv3
#define TESTCASE_NAME2 loop_distruptor_lv3
#define TEST_FUNCTION  test8

#if 1

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


///////////////////////////////////////////////////


TEST(fan_in, pub4_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 256));
}


TEST(fan_in, pub8_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 1, 256));
}

TEST(fan_in, pub16_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(16, 1, 256));
}

TEST(fan_in, pub32_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(32, 1, 256));
}

///////////////////////////////////////////////////


TEST(fan_out, pub1_sub1_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 256));
}


TEST(fan_out, pub1_sub2_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 1, 256));
}

TEST(fan_out, pub1_sub4_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(16, 1, 256));
}

TEST(fan_out, pub1_sub8_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(32, 1, 256));
}


////////////////////////////////////////////////////////

#if 0
TEST(TESTCASE_NAME2, pub2_sub1_queue4096) {
	for (int i = 0; i < 100; i++)
		ASSERT_EQ(1, TEST_FUNCTION(2, 2, 64));
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
#endif

////////////////////////////////////////////////////////

#if 0

TEST(TESTCASE_NAME3, pub2_sub2_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 128));
}

TEST(TESTCASE_NAME3, pub2_sub2_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 256));
}

TEST(TESTCASE_NAME3, pub2_sub2_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 1024));
}

TEST(TESTCASE_NAME3, pub2_sub2_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(2, 2, 4096));
}

#endif

//////////////////////////////////////////////////////////////////////
#if 0


TEST(TESTCASE_NAME4, pub4_sub4_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 128));
}

TEST(TESTCASE_NAME4, pub4_sub4_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 256));
}

TEST(TESTCASE_NAME4, pub4_sub4_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 1024));
}

TEST(TESTCASE_NAME4, pub4_sub4_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(4, 4, 4096));
}

#endif
////////////////////////////////////////////////////////

#if 0
TEST(TESTCASE_NAME5, pub8_sub8_queue128) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 128));
}

TEST(TESTCASE_NAME5, pub8_sub8_queue256) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 256));
}

TEST(TESTCASE_NAME5, pub8_sub8_queue1024) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 1024));
}

TEST(TESTCASE_NAME5, pub8_sub8_queue4096) {
	ASSERT_EQ(1, TEST_FUNCTION(8, 8, 4096));
}
#endif

////////////////////////////////////////////////////////


// TEST(TESTCASE_NAME1, pub4_sub1_queue128) {
// 	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 128));
// }

// TEST(TESTCASE_NAME1, pub4_sub1_queue256) {
// 	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 256));
// }

// TEST(TESTCASE_NAME1, pub4_sub1_queue1024) {
// 	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 1024));
// }

// TEST(TESTCASE_NAME1, pub4_sub1_queue4096) {
// 	ASSERT_EQ(1, TEST_FUNCTION(4, 1, 4096));
// }

////////////////////////////////////////////////////////
#endif


static int bundleSet = 1000;
static std::atomic<bool> latch(false);

static void runProducer(Disruptor3 &dis, Producer3 &pro, int thread_id) {

	while (!latch);

	//_sleep(10);

	//생산할거다.
	//동시에 진입할 수 있다. 더 생산할 수 있다. 
	do {

		//일로 들어오는 순간 내가 가져가야할 index가 결정된다.
		uint64_t getIdx = dis._next.fetch_add(1) + 1;
		
		if (getIdx < (dis._ringbuffer_size) * bundleSet) {
			pro.Push(dis, getIdx, 1);
			//printf("produce thread_id : %d\n", thread_id);
		}
		else {
			break;
		}
	} while (1);

}

static void runConsumer(Disruptor3 &dis, Consumer3 &con, int thread_id) {

	while (!latch);

	// std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	


	//동시에 소비할 수 있다.
	//소비를 못할 경우 블러킹 걸림
	do {

		//일로 들어오는 순간 내가 가져가야할 index가 결정된다.
		uint64_t getIdx;
		getIdx = dis._seq.fetch_add(1, std::memory_order_release);
		getIdx += 1;


		//thread A, B가 같은 ringIdx일수도있다.

		uint64_t ringIdx = (dis._ringbuffer_size - 1) & getIdx;

		if (getIdx < (dis._ringbuffer_size) * bundleSet) {

			//그래도 Pop할 때 blocking되서 , 같은 ringIdx가 2번 실행되어야하는데...
			con.Pop(dis, getIdx);

			//checkTransaction[ringIdx] += con.Pop(dis, getIdx);
			//printf("                      consume thread_id : %d %d\n", thread_id, checkTransaction[ringIdx]);
		}
		else {
			break;
		}
	} while (1);
		
}


int test8(int pro_count, int con_count, int queue_size) {


	Consumer3 *consumer = new Consumer3[con_count];
	Producer3 *producer = new Producer3[pro_count];

	std::thread *con_thread = new std::thread[con_count];
	std::thread *pro_thread = new std::thread[pro_count];

	Disruptor3 distruptor(queue_size);

	checkTransaction = new int[queue_size];

	latch = false;
	gCount = 0;

	for (int i = 0; i < queue_size; i++) {
		checkTransaction[i] = 0;
	}

	// printf("start test8\n");

	/* promise : buffer of disruptor is full by producer */

	// clock_t start = clock();
	for (int i = 0; i < con_count; i++) {
		con_thread[i] = std::thread(runConsumer, std::ref(distruptor), std::ref(consumer[i]), i);
	}

	for (int i = 0; i < pro_count; i++) {
		pro_thread[i] = std::thread(runProducer, std::ref(distruptor), std::ref(producer[i]), i);
	}

	latch = true;
	
	for (int i = 0; i < con_count; i++) {
		con_thread[i].join();
	}

	for (int i = 0; i < pro_count; i++) {
		pro_thread[i].join();
	}
	// clock_t end = clock();
	// printf("%0.5f\n", (float)(end - start) / CLOCKS_PER_SEC);

	/* verfiy */
	int isSuccess = 1;
#if 0
	/*for (int i = 0; i < distruptor._ringbuffer_size; i++) {

		if (checkTransaction[i] != bundleSet) {
			isSuccess = 0;

			break;
		}
	}*/
	/*if (!isSuccess) {
		for (int i = 0; i < distruptor._ringbuffer_size; i++) {
			printf("%d ", checkTransaction[i]);
		}
		printf("\n");
	}*/
#endif

	uint64_t countSum = 0;
	for (int i = 0; i < con_count; i++) {
		countSum += consumer[i].getCount();
	}

	if (countSum != queue_size * bundleSet) {
		isSuccess = 0;
	}

	if (isSuccess) {
		//printf("transaction success\n");
		return 1;
	}
	else {
		//printf("transaction fail\n");
	
		return 0;
	}


	delete[] producer;
	delete[] consumer;

	delete[] pro_thread;
	delete[] con_thread;

	delete[] checkTransaction;

	delete[] distruptor._ringbuffer;

}