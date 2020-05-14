
#include <atomic>
#include <thread>

static std::atomic<int> y(0);
static std::atomic<int> x(0);
static int r1;
static int r2;

static void produce1() {
	y.store(1, std::memory_order_release); 
	x.store(1, std::memory_order_release); 


}

static void consume1() {

	r1 = x.load(std::memory_order_acquire); 
	r2 = y.load(std::memory_order_acquire); 

}


static void scenario4() {

	do {

		x = 0;
		y = 0;
		r1 = 0;
		r2 = 0;
		

		std::thread t1(produce1);
		std::thread t2(consume1);

		t1.join();
		t2.join();

		//스레드 시작 순서는 보장되어야 함.
		if (r1 == 1 && r2 == 1)
			break;

		printf("r1 == %d r2 == %d\n", r1, r2);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));


	} while (1);

	printf("r1 == %d r2 == %d\n", r1, r2);
}

void test2() {
	
	scenario4();

}