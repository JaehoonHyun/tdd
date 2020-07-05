#if 0

#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <atomic>
#include <thread>


/*
patch

todo:
 -. 

next :
-. fileTransaction
-. distruptor 추상화
-. IPC on shared memory

features :
-. producer / consumer thread가 많아질수록 퍼포먼스는 떨어진다.
-. consumer의 batch기능을 딴돈의 절반만 가져가 정책을 이용해서 구현

*/

#define CACHE_LINE_SIZE  64


static int *checkTransaction;
static std::atomic<uint64_t> gCount;

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
	uint64_t _count;

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

		//개개인의 스레드의 값이므로 보장됨
		_count += data;

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
			data = dis._ringbuffer[ringIdx];

			//set
			_count += data;


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


static int bundleSet = 1000;

static std::atomic<bool> latch(false);


static void runConsumer(Disruptor4 &dis, Consumer4 &con, int thread_id) {

	while (!latch);

	// std::this_thread::sleep_for(std::chrono::milliseconds(10));
	



	//동시에 소비할 수 있다. -> 해결하려면 내가 가져갈 인덱스를 얻은 후 진행해야함
	//소비를 못할 경우 블러킹 걸림
	do {

		//일로 들어오는 순간 내가 가져가야할 index가 결정된다.

		//생산된에서 소비할 걸 빼면 내가 예약할 수 있는 인덱스들을 얻을 수 있다.

		//생산된게 0개 이면, 1개만   예약해라
		//생산된게 1개 이면, 1개만   예약해라
		//생산된게 2개 이면, 1개만   예약해라
		//생산된게 3개 이면, 1개만   예약해라
		//생산된게 4개 이면, 2개만   예약해라
		//생산된게 5개 이면, 2개만   예약해라
		//생산된게 n개 이면, n/2개만 예약해라.
		uint64_t startIdx;
		uint64_t endIdx;

		int between;

		//음수가능
		between = (dis._cursor + 1) - (dis._seq + 1);
			
		if (between < 2) {
			startIdx = dis._seq.fetch_add(1) + 1;
			endIdx = startIdx;
		}
		else {
			startIdx = dis._seq.fetch_add(between / 2) + 1;
			endIdx = startIdx + between / 2 - 1;
		}

		if (startIdx < (dis._ringbuffer_size) * bundleSet) {

			uint64_t batch_count = con.multiPop(dis, startIdx, endIdx, checkTransaction);
			//printf("                      consume thread_id : %d [ %d ... %d ]\n", thread_id, startIdx, endIdx);
		}
		else {
			break;
		}
	} while (1);

}



static void runProducer(Disruptor4 &dis, Producer4 &pro, int thread_id) {

	while (!latch);

	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	//생산할거다.
	//동시에 진입할 수 있다. 더 생산할 수 있다. 
	do {

		//일로 들어오는 순간 내가 가져가야할 index가 결정된다.
		uint64_t getIdx = dis._next.fetch_add(1) + 1;

		if (getIdx < (dis._ringbuffer_size) * bundleSet) {
			pro.push(dis, getIdx, 1);
			//printf("produce thread_id : %d [%d] \n", thread_id, dis._cursor);
		}
		else {
			break;
		}
	} while (1);

}



int test9(int pro_count, int con_count, int queue_size) {


	Consumer4 *consumer = new Consumer4[con_count];
	Producer4 *producer = new Producer4[pro_count];

	std::thread *con_thread = new std::thread[con_count];
	std::thread *pro_thread = new std::thread[pro_count];

	Disruptor4 distruptor(queue_size);

	checkTransaction = new int[queue_size];

	latch = false;
	gCount = 0;

	for (int i = 0; i < queue_size; i++) {
		checkTransaction[i] = 0;
	}

	printf("start test9\n");

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
	//for (int i = 0; i < distruptor._ringbuffer_size; i++) {

	//	if (checkTransaction[i] != bundleSet) {
	//		isSuccess = 0;

	//		break;
	//	}
	//}

	//if (!isSuccess) {
	//	for (int i = 0; i < distruptor._ringbuffer_size; i++) {
	//		printf("%d ", checkTransaction[i]);
	//	}
	//	printf("\n");
	//}

	/*if (gCount != (queue_size)* bundleSet) {
		isSuccess = 0;
	}*/

	uint64_t countSum = 0;
	for (int i = 0; i < con_count; i++) {
		countSum += consumer[i]._count;
	}

	if (countSum != queue_size * bundleSet) {
		isSuccess = 0;
	}

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

#endif