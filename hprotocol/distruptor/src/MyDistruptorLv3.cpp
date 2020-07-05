#include <stdio.h>
#include <time.h>

#include <atomic>
#include <thread>


/*
patch
int->uint64_t
producer have a _getIdx

features :
-. sub thread가 많아질수록 퍼포먼스는 떨어진다. 
   이유는 프로세서의 리소스는 한정되어있으므로, 스레드가 많아질수록 경합을 하게 되고, 생산하는 녀석보다 소비하는 녀석이 많으면, 쓸데없는 프로세서 리소스 낭비함.

*/

#define CACHE_LINE_SIZE  64


static int *checkTransaction;

//static std::atomic<uint64_t> gCount;
static uint64_t gCount;

struct Disruptor3 {

	//for producer
	std::atomic<uint64_t> _next alignas(CACHE_LINE_SIZE);   //reserved
	std::atomic<uint64_t> _cursor alignas(CACHE_LINE_SIZE); //commit 

	//for consumer
	std::atomic<uint64_t> _seq alignas(CACHE_LINE_SIZE); //reserved
	std::atomic<uint64_t> _pos alignas(CACHE_LINE_SIZE); //commit

	int *_ringbuffer;
	int _ringbuffer_size;

	Disruptor3(int ring_buffer_size) :
		_next(-1),
		_cursor(-1),
		_seq(-1),
		_pos(-1),
		_ringbuffer(new int[ring_buffer_size]),
		_ringbuffer_size(ring_buffer_size){}

	
};




struct Producer3 {

	uint64_t _getIdx = -1;
	static std::atomic<uint64_t> count;

	uint64_t claim(Disruptor3 &dis, uint64_t getIdx) {

		uint64_t ringIdx = (dis._ringbuffer_size - 1) & getIdx;

		do {

			if (dis._pos + 1 + dis._ringbuffer_size - 1 > getIdx) {
				break;
			}
			else {
				std::this_thread::yield();
			}

		} while (1);

		return ringIdx;
	}

	int commit(Disruptor3 &dis, uint64_t idx) {

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

	int push(Disruptor3 &dis, uint64_t getIdx, int data) {

		uint64_t ringIdx;

		_getIdx = getIdx;

		

		ringIdx = claim(dis, _getIdx);
		dis._ringbuffer[ringIdx] = data;
		commit(dis, _getIdx);

		return 0;
	}

};

struct Consumer3 {

	uint64_t _getIdx = -1;

	uint64_t size;
	uint64_t _count;


	uint64_t waitfor(Disruptor3 &dis, uint64_t getIdx) {


		do {

			if (dis._cursor + 1 > getIdx ) {
				break;
			}
			else {
				std::this_thread::yield();
			}

		} while (1);

		return 0;
	}

	int commit(Disruptor3 &dis, uint64_t idx) {

		//단점 : 가장 마지막에 가져가려는 녀석이 수행완료 되어야 나머지 애들도 commit 할 수 있다.
		do {

			if (dis._pos + 1 == idx) {
				break;
			}
			else {
				std::this_thread::yield();

			}

		} while (1);

		dis._pos.fetch_add(1);

		return 0;
	}

	int pop(Disruptor3 &dis, uint64_t getIdx) {

		int data;

		uint64_t ringIdx;


		_getIdx = getIdx;
		waitfor(dis, _getIdx);

		ringIdx = (dis._ringbuffer_size - 1) & getIdx;

		//여기서 0을 출력할 수 있다?
		data = dis._ringbuffer[ringIdx];

		//0인 곳을 접근한다?
		dis._ringbuffer[ringIdx] = 0;

		//개개인의 스레드의 값이므로 보장됨
		_count += data;

		commit(dis, _getIdx);



		return data;
	}
};


static int bundleSet = 1000;

static std::atomic<bool> latch(false);


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

			//그래도 pop할 때 blocking되서 , 같은 ringIdx가 2번 실행되어야하는데...
			con.pop(dis, getIdx);

			//checkTransaction[ringIdx] += con.pop(dis, getIdx);
			//printf("                      consume thread_id : %d %d\n", thread_id, checkTransaction[ringIdx]);
		}
		else {
			break;
		}
	} while (1);
		
}



static void runProducer(Disruptor3 &dis, Producer3 &pro, int thread_id) {

	while (!latch);

	//_sleep(10);

	//생산할거다.
	//동시에 진입할 수 있다. 더 생산할 수 있다. 
	do {

		//일로 들어오는 순간 내가 가져가야할 index가 결정된다.
		uint64_t getIdx = dis._next.fetch_add(1) + 1;
		
		if (getIdx < (dis._ringbuffer_size) * bundleSet) {
			pro.push(dis, getIdx, 1);
			//printf("produce thread_id : %d\n", thread_id);
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

	printf("start test8\n");

	//init


	//promise : buffer of disruptor is full by producer

	clock_t start = clock();

	for (int i = 0; i < con_count; i++) {
		con_thread[i] = std::thread(runConsumer, std::ref(distruptor), std::ref(consumer[i]), i);
	}

	for (int i = 0; i < pro_count; i++) {
		pro_thread[i] = std::thread(runProducer, std::ref(distruptor), std::ref(producer[i]), i);
	}

	for (int i = 0; i < con_count; i++) {
		consumer[i]._count = 0;
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

	uint64_t countSum = 0;
	for (int i = 0; i < con_count; i++) {
		countSum += consumer[i]._count;
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
