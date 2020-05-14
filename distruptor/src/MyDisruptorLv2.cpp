#include <stdio.h>

#include <atomic>
#include <thread>

/*
patch
int->uint64_t
producer have a _getIdx

*/

#define CACHE_LINE_SIZE  64
#define RING_BUFFER_SIZE 64

struct Disruptor2 {

	//for producer
	std::atomic<uint64_t> next alignas(CACHE_LINE_SIZE);
	std::atomic<uint64_t> cursor alignas(CACHE_LINE_SIZE);

	//for consumer
	std::atomic<uint64_t> seq alignas(CACHE_LINE_SIZE);
	std::atomic<uint64_t> pos alignas(CACHE_LINE_SIZE);

	int ringbuffer[RING_BUFFER_SIZE];

	Disruptor2() :
		next(-1),
		cursor(-1),
		seq(-1),
		pos(-1) {}
};


static int checkTransaction[RING_BUFFER_SIZE];


struct Producer2 {

	uint64_t _getIdx = -1;

	uint64_t claim(Disruptor2 &dis) {

		//old값 리턴한다. 그래서 +1 하는구나
		uint64_t getIdx;

		getIdx = dis.next.fetch_add(1) + 1;


		getIdx = (RING_BUFFER_SIZE - 1) & getIdx;



		return getIdx;
	}

	int commit(Disruptor2 &dis, uint64_t idx) {

		do {

			uint64_t getIdx = (RING_BUFFER_SIZE - 1) & (dis.cursor + 1);
			if (getIdx == idx) {
				break;
			}
			else {
				std::this_thread::yield();

			}

		} while (1);

		dis.cursor.fetch_add(1);

		return 0;
	}

	int push(Disruptor2 &dis, int data) {

		_getIdx = claim(dis);
		dis.ringbuffer[_getIdx] = data;

		commit(dis, _getIdx);

		return 0;
	}

};

struct Consumer2 {
	
	uint64_t _getIdx = -1;

	uint64_t waitfor(Disruptor2 &dis) {

		//old값 리턴한다. 그래서 +1 하는구나
		uint64_t getIdx;

		getIdx = dis.seq.fetch_add(1) + 1;

		do {

			if (dis.cursor >= getIdx) {
				break;
			}
			else {
				std::this_thread::yield();
			}

		} while (1);

		getIdx = (RING_BUFFER_SIZE - 1) & getIdx;



		return getIdx;
	}

	int commit(Disruptor2 &dis, uint64_t idx) {

		do {

			uint64_t getIdx = (RING_BUFFER_SIZE - 1) & (dis.pos + 1);
			if (getIdx == idx) {
				break;
			}
			else {
				std::this_thread::yield();

			}

		} while (1);

		dis.pos.fetch_add(1);

		return 0;
	}

	int pop(Disruptor2 &dis) {

		int data;

		_getIdx = waitfor(dis);
		data = dis.ringbuffer[_getIdx];

		commit(dis, _getIdx);


		checkTransaction[_getIdx] += data;

		return data;
	}
};

static Disruptor2 distruptor;

static Producer2 producer1;


static Consumer2 consumer1;
static Consumer2 consumer2;

static std::atomic<bool> latch(false);

static void runConsumer(Disruptor2 &dis, Consumer2 &pro, int thread_id) {

	int i = 0;

	while (!latch);

	do {

		pro.pop(dis);
		i++;
		//std::this_thread::yield();
		printf("thread_id : %d\n", thread_id);

	} while (dis.pos < (RING_BUFFER_SIZE - 1) * 1);
}


void test7() {

	printf("start test7\n");

	//promise : buffer of disruptor is full by producer
	for (int i = 0; i < RING_BUFFER_SIZE; i++) {
		producer1.push(distruptor, 1);
	}

	std::thread t1(runConsumer, std::ref(distruptor), std::ref(consumer1), 1);
	std::thread t2(runConsumer, std::ref(distruptor), std::ref(consumer2), 2);

	

	latch = true;

	t1.join();
	t2.join();

	int isSuccess = 1;
	for (int i = 0; i < RING_BUFFER_SIZE; i++) {

		if (checkTransaction[i] != 1) {
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

}
