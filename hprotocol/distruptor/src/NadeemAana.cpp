

#include <thread>

static int y = 0;
static int x = 0;
static int r1;
static int r2;

static void produce1() {
	y = 0;
	r1 = 0;

	y = 1;
	r1 = x;

}

static void consume1() {
	x = 0;
	r2 = 0;

	x = 1;
	r2 = y;
}

static void scenario1() {

	do {



		std::thread t2(consume1);
		std::thread t1(produce1);

		t1.join();
		t2.join();

		if (r1 == 1 && r2 == 1)
			break;

		printf("r1 == %d r2 == %d\n", r1, r2);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	} while (1);

	printf("r1 == %d r2 == %d\n", r1, r2);
}

static void scenario2() {

	do {



		std::thread t2(consume1);
		std::thread t1(produce1);

		t1.join();
		t2.join();

		if (r1 == 1 && r2 == 0)
			break;

		printf("r1 == %d r2 == %d\n", r1, r2);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	} while (1);

	printf("r1 == %d r2 == %d\n", r1, r2);
}

static void scenario3() {

	do {

		

		std::thread t1(produce1);
		std::thread t2(consume1);

		t1.join();
		t2.join();

		if (r1 == 0 && r2 == 1)
			break;

		printf("r1 == %d r2 == %d\n", r1, r2);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

	} while (1);

	printf("r1 == %d r2 == %d\n", r1, r2);
}

static void scenario4() {

	do {


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

void test1() {

	//scenario1();
	//scenario2();
	//scenario3();
	scenario4();

}
