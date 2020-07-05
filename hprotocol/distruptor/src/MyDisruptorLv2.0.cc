#include <stdio.h>

#include <atomic>
#include <thread>

/*
patch
uint64_t->uint64_t
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

	uint64_t ringbuffer[RING_BUFFER_SIZE];

	Disruptor2() :
		next(-1),
		cursor(-1),
		seq(-1),
		pos(-1) {}
};


static uint64_t checkTransaction[RING_BUFFER_SIZE];


struct Producer2 {

	uint64_t _getIdx = -1;

	uint64_t claim(Disruptor2 &dis) {

		//old값 리턴한다. 그래서 +1 하는구나
		uint64_t getIdx;
		getIdx = dis.next.fetch_add(1) + 1;
		getIdx = (RING_BUFFER_SIZE - 1) & getIdx;

		return getIdx;
	}

	uint64_t commit(Disruptor2 &dis, uint64_t idx) {

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

	uint64_t push(Disruptor2 &dis, uint64_t data) {

		_getIdx = claim(dis);
		dis.ringbuffer[_getIdx] = data;

		commit(dis, _getIdx);

		return 0;
	}

};

struct Consumer2 {
	
	uint64_t _getIdx = -1;

	uint64_t waitfor(Disruptor2 &dis) {
		

		//NOTE: init dis.seq, dis.next -1 (0xFFFFFF) so , +1 set to zero.
		uint64_t view_seq = dis.seq + 1;
		uint64_t view_next = dis.next + 1;


		//exception: when producer and consumer is same for each.
		do{
			if(view_seq < view_next){
				break;
			}

			std::this_thread::yield();

			view_next = dis.next + 1;

		}while(1);

		//capture next
		uint64_t capture_next = dis.next;

		do{

			if(capture_next == dis.cursor){
				break;
			}

			std::this_thread::yield();

		}while(1);

		//old값 리턴한다. 그래서 +1 하는구나
		_getIdx = (dis.seq.fetch_add(1) + 1) & (RING_BUFFER_SIZE - 1);

		return _getIdx;
	}

	uint64_t commit(Disruptor2 &dis, uint64_t idx) {

		do {

			uint64_t getIdx = (dis.pos + 1) & (RING_BUFFER_SIZE - 1);
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

	uint64_t pop(Disruptor2 &dis) {

		uint64_t data;

		uint64_t idx = waitfor(dis);
		data = dis.ringbuffer[idx];

		commit(dis, idx);


		checkTransaction[idx] += data;

		return data;
	}
};

static Disruptor2 distruptor;
static Producer2 producer1;
static Consumer2 consumer1;
static std::atomic<bool> latch(false);

static void runConsumer(Disruptor2 &dis, Consumer2 &con, uint64_t thread_id) {

	uint64_t i = 0;

	while (!latch);

	do {

		i = con.pop(dis);
		//std::this_thread::yield();
		printf("                      consumer tid : %d data:%d\n", thread_id, i);

	} while (dis.pos < (RING_BUFFER_SIZE - 1) * 1);
}

static void runProducer(Disruptor2 &dis, Producer2 &pro, uint64_t thread_id) {

	uint64_t i = 0;

	while (!latch);

	do {

		pro.push(dis, i);
		//std::this_thread::yield();
		printf("producer tid : %d , data:%d\n", thread_id, i);

		i++;

	} while (dis.next < (RING_BUFFER_SIZE - 1) * 1);
}

int test_MyDisruptor2() {

	printf("start MyDisruptor2 TEST CASE\n");

	//promise : buffer of disruptor is full by producer
	std::thread p1(runProducer, std::ref(distruptor), std::ref(producer1), 1);
	std::thread c1(runConsumer, std::ref(distruptor), std::ref(consumer1), 2);

	latch = true;

	p1.join();
	c1.join();

	return 1;

	// uint64_t isSuccess = 1;
	// for (uint64_t i = 0; i < RING_BUFFER_SIZE; i++) {

	// 	if (checkTransaction[i] != 1) {
	// 		isSuccess = 0;

	// 		break;
	// 	}
	// }

	// if (isSuccess) {
	// 	printf("transaction success\n");
	// }
	// else {
	// 	printf("transaction fail\n");
	// }

}
