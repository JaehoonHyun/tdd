#ifndef MY_DISRUPTOR_LV3_H_

#include <atomic>


#define CACHE_LINE_SIZE  64


static int *checkTransaction;

//static std::atomic<uint64_t> gCount;
static uint64_t gCount;

struct Disruptor3 {

	//for producer
	std::atomic<uint64_t> _next alignas(CACHE_LINE_SIZE);   //reserved
	std::atomic<uint64_t> _next_commit alignas(CACHE_LINE_SIZE); //commit 

	//for consumer
	std::atomic<uint64_t> _seq alignas(CACHE_LINE_SIZE); //reserved
	std::atomic<uint64_t> _seq_commit alignas(CACHE_LINE_SIZE); //commit

	int *_ringbuffer;
	int _ringbuffer_size;

	Disruptor3(int ring_buffer_size) :
		_next(-1),
		_next_commit(-1),
		_seq(-1),
		_seq_commit(-1),
		_ringbuffer(new int[ring_buffer_size]),
		_ringbuffer_size(ring_buffer_size){}

	
};


struct Producer3 {


	int Push(Disruptor3 &dis, uint64_t getIdx, int data);
	
	Producer3():_getIdx(-1){}

private:
	uint64_t _getIdx;

private:
    uint64_t claim(Disruptor3 &dis, uint64_t getIdx);
	int commit(Disruptor3 &dis, uint64_t idx);

};

struct Consumer3 {

	int Pop(Disruptor3 &dis, uint64_t getIdx);
	uint64_t getCount() { return _count;}

	Consumer3():
	_getIdx(-1),
	_count(0){}
	

private:
	uint64_t _getIdx;
	uint64_t _count;

private:
	uint64_t waitfor(Disruptor3 &dis, uint64_t getIdx);
	int commit(Disruptor3 &dis, uint64_t idx);
};


#endif