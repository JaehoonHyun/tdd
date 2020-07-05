
#include <atomic>
#include <thread>

static int y;
static int x;
static int r1;
static int r2;

static void produce1() {

	y = 1;
	std::atomic_thread_fence(std::memory_order_release);
	x = 1;
	std::atomic_thread_fence(std::memory_order_release);

}

static void consume1() {
	
	std::atomic_thread_fence(std::memory_order_acquire);
	r1 = x;
	std::atomic_thread_fence(std::memory_order_acquire);
	r2 = y;

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

		
		if (r1 == 1 && r2 == 1)
			break;

		printf("r1 == %d r2 == %d\n", r1, r2);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	} while (1);

	printf("r1 == %d r2 == %d\n", r1, r2);
}

void test4() {

	scenario4();

}