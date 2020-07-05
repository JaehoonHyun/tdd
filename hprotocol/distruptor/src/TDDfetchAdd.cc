#include <stdio.h>
#include <time.h>
#include <fcntl.h>

#include <atomic>
#include <thread>


/*
patch
int->uint64_t
producer have a _getIdx

todo:
-. consumer의 batch기능을 딴돈의 절반만 가져가 정책을 이용해서 구현
-. fault tolerance 기능을 파일 시스템을 이용해서 구현

next :
-. distruptor 추상화
-. IPC on shared memory

features :
-. sub thread가 많아질수록 퍼포먼스는 떨어진다.
이유는 프로세서의 리소스는 한정되어있으므로, 스레드가 많아질수록 경합을 하게 되고, 생산하는 녀석보다 소비하는 녀석이 많으면, 쓸데없는 프로세서 리소스 낭비함.

*/

#define CACHE_LINE_SIZE  64


static int *checkTransaction;

struct Disruptor4 {

	//for producer
	std::atomic<uint64_t> _next alignas(CACHE_LINE_SIZE);   //reserved
	std::atomic<uint64_t> _cursor alignas(CACHE_LINE_SIZE); //commit 

															//for consumer
	std::atomic<uint64_t> _seq alignas(CACHE_LINE_SIZE); //reserved
	std::atomic<uint64_t> _pos alignas(CACHE_LINE_SIZE); //commit

	int *_ringbuffer;
	int _ringbuffer_size;

	Disruptor4(int ring_buffer_size) :
		_next(-1),
		_cursor(-1),
		_seq(-1),
		_pos(-1),
		_ringbuffer(new int[ring_buffer_size]),
		_ringbuffer_size(ring_buffer_size) {}


};

struct Producer4 {

	uint64_t _getIdx = -1;
	static std::atomic<uint64_t> count;

	uint64_t claim(Disruptor4 &dis, uint64_t getIdx) {

		uint64_t ringIdx = (dis._ringbuffer_size - 1) & getIdx;

		do {

			if (dis._pos + 1 + dis._ringbuffer_size > getIdx) {
				break;
			}
			else {
				std::this_thread::yield();
			}

		} while (1);

		return ringIdx;
	}

	int commit(Disruptor4 &dis, uint64_t idx) {

		do {

			if (idx == dis._cursor + 1) {
				break;
			}
			else {
				std::this_thread::yield();

			}

		} while (1);

		dis._cursor.fetch_add(1);

		return 0;
	}

	int push(Disruptor4 &dis, uint64_t getIdx, int data) {

		uint64_t ringIdx;

		_getIdx = getIdx;



		ringIdx = claim(dis, _getIdx);
		dis._ringbuffer[ringIdx] = data;
		commit(dis, _getIdx);

		return 0;
	}

};

struct Consumer4 {

	uint64_t _getIdx = -1;

	uint64_t waitfor(Disruptor4 &dis, uint64_t getIdx) {


		do {

			if (dis._cursor + 1 > getIdx) {
				break;
			}
			else {
				std::this_thread::yield();
			}

		} while (1);

		return dis._cursor;
	}

	int commit(Disruptor4 &dis, uint64_t idx, uint64_t count) {

		//단점 : 가장 마지막에 가져가려는 녀석이 수행완료 되어야 나머지 애들도 commit 할 수 있다.
		do {

			if (dis._pos + count == idx) {
				break;
			}
			else {
				std::this_thread::yield();

			}

		} while (1);

		dis._pos.fetch_add(count);

		return 0;
	}

	int singlePop(Disruptor4 &dis, uint64_t getIdx) {

		int data;

		uint64_t ringIdx;


		_getIdx = getIdx;
		waitfor(dis, _getIdx);

		ringIdx = (dis._ringbuffer_size - 1) & getIdx;

		data = dis._ringbuffer[ringIdx];
		dis._ringbuffer[ringIdx] = 0;

		commit(dis, _getIdx, 1);

		return data;
	}

	uint64_t multiPop(Disruptor4 &dis, uint64_t startIdx, uint64_t endIdx, int *&arr) {
		int data;

		uint64_t ringIdx;
		uint64_t producedIdx;

		uint64_t iter;
		uint64_t count;

		producedIdx = waitfor(dis, startIdx);

		iter = startIdx;
		count = 0;

		while (iter <= endIdx) {

			//modular operation
			ringIdx = (dis._ringbuffer_size - 1) & iter;

			//pop
			arr[ringIdx] += dis._ringbuffer[ringIdx];

			//clear
			dis._ringbuffer[ringIdx] = 0;


			iter++;
			count++;
		}

		_getIdx = endIdx;

		commit(dis, _getIdx, count);

		return _getIdx;
	}


};


static int bundleSet = 1;
static int g_queue_size;

static std::atomic<bool> latch(false);
static std::atomic<uint64_t> gCount;

static void runConsumer(Disruptor4 &dis, Consumer4 &con, int thread_id) {

	while (!latch);

	//_sleep(10);


	uint64_t startIdx;
	uint64_t ringIdx;
	do {

		//seq를 read and write 한다면? 동시성 깨질 수 있음
		//bundleSet == 1 일 때만, 안 깨지는건 머임
		startIdx = dis._seq.fetch_add(1) + 1;
		//uint64_t expected;
		//do {
		//	
		//	expected = dis._seq;

		//	if (dis._seq.compare_exchange_strong(expected, expected + 1)) {
		//		break;
		//	}
		//	else {
		//		expected = dis._seq;
		//	}

		//} while (1);

		//startIdx = expected;

		//startIdx가 같은 값일 수 있음.
		if (startIdx < (g_queue_size) * bundleSet) {
			
			ringIdx = (g_queue_size - 1) & startIdx;

			//모듈러 연산했는데 같은 값일 수 있다. -> 없는데.......
			
			//여기서 동시성이 깨진다. 
			//깨질 수 있다.
			//thread A [ 4 reserved],
			//thread B [ 6 7 8 ... 63 0 1 2 3 4 reserved ]
			//가 되는 시나리오 존재
			//그리고, checkTransaction은 atomic 보장이 안되기 때문에, 카운팅이 씹힐 수 있음.

			checkTransaction[ringIdx] += 1;

			//여기는 원하는 만큼 돈다
			gCount++;


			//프린트를 찍으면 원하는데로 동작함.
			//printf("%d, %d, %d\n", thread_id, ringIdx, startIdx);
			/*for (volatile int i = 0; i < 20000; i++) {

			}*/
		}
		else {
			break;
		}
		
		std::this_thread::yield();

	} while (1);


}



static void runProducer(Disruptor4 &dis, Producer4 &pro, int thread_id) {


}


int test10(int pro_count, int con_count, int queue_size, int bundle_set_) {


	Consumer4 *consumer = new Consumer4[con_count];
	Producer4 *producer = new Producer4[pro_count];

	std::thread *con_thread = new std::thread[con_count];
	std::thread *pro_thread = new std::thread[pro_count];

	Disruptor4 distruptor(1);

	checkTransaction = new int[queue_size];

	latch = false;
	bundleSet = bundle_set_;
	g_queue_size = queue_size;
	gCount = 0;

	for (int i = 0; i < queue_size; i++) {
		checkTransaction[i] = 0;
	}

	printf("start test10\n");

	//init


	//promise : buffer of disruptor is full by producer

	clock_t start = clock();

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


	clock_t end = clock();

	printf("%0.5f\n", (float)(end - start) / CLOCKS_PER_SEC);

	int isSuccess = 1;
	for (int i = 0; i < g_queue_size; i++) {

		if (checkTransaction[i] != bundleSet) {
			isSuccess = 0;

			break;
		}
	}

	if (!isSuccess) {
		for (int i = 0; i < g_queue_size; i++) {
			printf("%d ", checkTransaction[i]);
		}
		printf("\n");
	}

	printf("%d\n", gCount.load());
	printf("%d\n", distruptor._seq.load());

	delete[] producer;
	delete[] consumer;

	delete[] pro_thread;
	delete[] con_thread;

	delete[] checkTransaction;

	delete[] distruptor._ringbuffer;

	if (isSuccess) {
		//printf("transaction success\n");
		return 1;
	}
	else {
		//printf("transaction fail\n");

		return 0;
	}


}
