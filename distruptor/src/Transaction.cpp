
#include <atomic>
#include <thread>

struct {

	int age;
	int time;

} MyData;

static std::atomic<int> lock(0);

static void produce1() {

	while (1) {

		MyData.age++;
		MyData.time++;

		lock.store(1, std::memory_order_release);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

}

static void consume1() {

	while (1) {

		int ready = lock.load(std::memory_order_acquire);
	
		if (ready == 1) {
			printf("opening\n");
			lock.store(0, std::memory_order_release);
		}
	}

}

static void scenario1() {

	std::thread t2(consume1);
	std::thread t1(produce1);

	t2.join();
	t1.join();
}


void test3() {

	scenario1();
	//scenario2();
	//scenario3();
	//scenario4();

}