#include <stdio.h>

#include <atomic>
#include <thread>

#define CACHE_LINE_SIZE  64
#define RING_BUFFER_SIZE 64

struct Disruptor {

	std::atomic<uint64_t> next alignas(CACHE_LINE_SIZE);
	std::atomic<uint64_t> cursor alignas(CACHE_LINE_SIZE);

	std::atomic<uint64_t> seq;

	int ringbuffer[RING_BUFFER_SIZE];

	Disruptor() :
		next(-1),
		cursor(-1),
		seq(-1) {}
};


int checkTransaction[RING_BUFFER_SIZE];


struct Producer {

	int startIdx = -1;

	int claim(Disruptor &dis) {

		//old값 리턴한다. 그래서 +1 하는구나
		int getIdx = dis.next.fetch_add(1) + 1;


		getIdx = (RING_BUFFER_SIZE - 1) & getIdx;



		return getIdx;
	}

	int commit(Disruptor &dis, int idx) {

		do {

			int getIdx = (RING_BUFFER_SIZE - 1) & (dis.cursor + 1);
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

	int push(Disruptor &dis, int data) {

		int getIdx = claim(dis);
		dis.ringbuffer[getIdx] = data;

		commit(dis, getIdx);

		checkTransaction[getIdx]++;

		return 0;
	}

};

struct Consumer {

};

static Disruptor distruptor;

static Producer producer1;
static Producer producer2;

static Consumer consumer;

static std::atomic<bool> latch(false);

static void runProduce(Disruptor &dis, Producer &pro, int thread_id) {

	int i = 0;

	while (!latch);

	do {

		pro.push(dis, thread_id);
		i++;
		//std::this_thread::yield();
		printf("thread_id : %d\n", thread_id);

	} while (dis.next < (RING_BUFFER_SIZE - 1) * 1);
}


void test6() {

	printf("start test6\n");

	std::thread t1(runProduce, std::ref(distruptor), std::ref(producer1), 1);
	std::thread t2(runProduce, std::ref(distruptor), std::ref(producer2), 2);

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
