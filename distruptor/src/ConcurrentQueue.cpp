#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

#include <time.h>

/*
	원형큐에 key로 동시성을 보장하게 되면, 기아현상이 발생함
*/
std::atomic<int> key;




#define OPEN 0
#define CLOSE 1
#define THREAD_COUNT 10
#define RING_BUFFER_SIZE 4096

static int ringbuffer[RING_BUFFER_SIZE];
static int transactionSet[RING_BUFFER_SIZE];
static int thread_produce_in[THREAD_COUNT];
static int thread_consume_in[THREAD_COUNT];


static int checkTransaction[RING_BUFFER_SIZE];

static void lock() {
	
	do {
		
		int expected = OPEN;

		if (key.compare_exchange_strong(expected,CLOSE)) {
			break;
		}
		else {
			std::this_thread::yield();
		}

	} while (1);
}

static void unlock() {

	do {

		int expected = CLOSE;

		if (key.compare_exchange_strong(expected, OPEN)) {
			break;
		}
		else {
			std::this_thread::yield();
		}

	} while (1);
}


std::atomic<uint64_t> front;
std::atomic<uint64_t> rear;

struct Producer3 {


	int push(int data) {
		
		lock();
		
		if (front - rear != RING_BUFFER_SIZE) {

			ringbuffer[(RING_BUFFER_SIZE - 1) & front ] = data;
			front++;
		}

		unlock();
		return 0;
	}

};

struct Consumer3 {


	int pop() {

		int data;
		int idx;


		lock();
		
		if (!(front > rear)) {
			unlock();
			return -1;
		}
		
		
		idx = (RING_BUFFER_SIZE - 1) & rear;
		data = ringbuffer[idx];
		ringbuffer[idx] = 0;
		checkTransaction[idx] += data;
		rear++;
		

		unlock();



		return data;
	}
};

static Producer3 producer1;
static Producer3 producer2;

static Consumer3 consumer1;
static Consumer3 consumer2;

static std::atomic<bool> latch(false);
//static std::atomic<uint64_t> consumer_count;
//static std::atomic<uint64_t> producer_count;

static int bundleSet = 2;

static void runConsumer(Consumer3 &con, int thread_id) {

	while (!latch);

	// std::this_thread::sleep_for(std::chrono::milliseconds(10));

	while (rear < (RING_BUFFER_SIZE)* bundleSet - 1) {
		con.pop();
		//consumer_count.fetch_add(1);
		//printf("                      consume thread_id : %d\n", thread_id);
	}
}



static void runProducer(Producer3 &pro, int thread_id) {

	while (!latch);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	while (front < (RING_BUFFER_SIZE)* bundleSet - 1) {
		pro.push(1);
		//producer_count.fetch_add(1);
		//printf("produce thread_id : %d\n", thread_id);
	}
}

int sum;

void add(int count, int thread_id) {

	while (!latch);


	for (int i = 0; i < count; i++) {
		lock();
		sum += 1;

		if (thread_id % 2 == 0) {
			printf("thread : %d\n", thread_id);
		}
		else {
			printf("           thread : %d\n", thread_id);
		}
		unlock();
	}
}

void test5() {

	printf("start test5\n");

#if 1

	clock_t start = clock();

	std::thread t1(runConsumer, std::ref(consumer1), 1);
	std::thread t2(runConsumer, std::ref(consumer2), 2);

	std::thread t3(runProducer, std::ref(producer1), 3);
	std::thread t4(runProducer, std::ref(producer2), 4);


	latch = true;

	t1.join();
	t2.join();

	t3.join();
	t4.join();

	clock_t end = clock();

	printf("%0.5f\n", (float)(end - start) / CLOCKS_PER_SEC);

	int isSuccess = 1;
	for (int i = 0; i < RING_BUFFER_SIZE; i++) {

		if (checkTransaction[i] != bundleSet) {
			isSuccess = 0;

			break;
		}
	}

	if (isSuccess) {
		printf("transaction success\n");
	}
	else {
		printf("transaction fail\n");
	}
#else

	std::thread t1(add, 10000, 1);
	std::thread t2(add, 10000, 2);

	latch = true;


	t1.join();
	t2.join();

#endif

}

