#include <stdio.h>
#include <time.h>

#include <atomic>
#include <thread>

#include "inc/MyDisruptorLv3.h"

/*
patch
int->uint64_t
producer have a _getIdx

features :
-. sub thread가 많아질수록 퍼포먼스는 떨어진다. 
   이유는 프로세서의 리소스는 한정되어있으므로, 스레드가 많아질수록 경합을 하게 되고, 생산하는 녀석보다 소비하는 녀석이 많으면, 쓸데없는 프로세서 리소스 낭비함.

*/

//not consuming that index, wait until consuming.
uint64_t Producer3::claim(Disruptor3 &dis, uint64_t getIdx) {
	uint64_t ringIdx = (dis._ringbuffer_size - 1) & getIdx;
	do {
		
		//when getIdx: 64, dis._seq_commit: 0, then 64 > 64 is false 
		//when getIdx: 64, dis._seq_commit: 1, then 65 > 64 is true
		if (dis._seq_commit + 1 + dis._ringbuffer_size - 1 > getIdx) {
			break;
		}
		else {
			std::this_thread::yield();
		}

	} while (1);

	return ringIdx;
}

//if next commit is it's me, I can commit 
int Producer3::commit(Disruptor3 &dis, uint64_t idx) {

	do {
		//when idx: 64, dis._next_commit: 0, then  64 == 1 is false
		//when idx: 64, dis._next_commit: 1, then  64 == 2 is false
		//when idx: 64, dis._next_commit: 63, then 64 == 64 is true
		if (idx == dis._next_commit + 1) {
			break;
		}
		else {
			std::this_thread::yield();

		}

	} while (1);

	dis._next_commit.fetch_add(1);

	return 0;
}

int Producer3::Push(Disruptor3 &dis, uint64_t getIdx, int data) {

	uint64_t ringIdx;

	_getIdx = getIdx;

	
	//reserved -> updated -> commited
	ringIdx = claim(dis, _getIdx);
	dis._ringbuffer[ringIdx] = data;
	commit(dis, _getIdx);

	return 0;
}

uint64_t Consumer3::waitfor(Disruptor3 &dis, uint64_t getIdx) {
		
	do {

	//when _next_commit == -1, getIdx == 0, then -1 + 1 > 0 false
	//when _next_commit == 0, getIdx == 0, then 0 + 1 > 0 true
	//when _next_commit == 1, getIdx == 0, then 1 + 1 > 0 true
		if (dis._next_commit + 1 > getIdx ) {
			break;
		}
		else {
			std::this_thread::yield();
		}

	} while (1);

	return 0;
}


int Consumer3::commit(Disruptor3 &dis, uint64_t idx) {

	//단점 : 가장 마지막에 가져가려는 녀석이 수행완료 되어야 나머지 애들도 commit 할 수 있다.
	//when _seq_commit == -1, idx == 0, then -1 + 1 == 0 true
	//when _seq_commit ==  0, idx == 0, then  0 + 1 == 1 false  
	do {

		if (dis._seq_commit + 1 == idx) {
			break;
		}
		else {
			std::this_thread::yield();

		}

	} while (1);

	dis._seq_commit.fetch_add(1);

	return 0;
}

int Consumer3::Pop(Disruptor3 &dis, uint64_t getIdx) {

	int data;
	uint64_t ringIdx;

	//waitfor -> pop -> commit
	_getIdx = getIdx;
	waitfor(dis, _getIdx);
	ringIdx = (dis._ringbuffer_size - 1) & getIdx;
	data = dis._ringbuffer[ringIdx];
	dis._ringbuffer[ringIdx] = 0;
	_count += data;
	commit(dis, _getIdx);

	return data;
}