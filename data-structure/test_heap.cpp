

#include <stdio.h>
#include "heap.h"
int genRandom();

static long greater(long *a, long *b) {
	
	int *_a = (int *)a;
	int *_b = (int *)b;

	if (*_a > *_b) {
		return 1;
	}
	else {
		return 0;
	}

}

void test_heap() {


	const int size = 10001;
	MyHeap<int *> heap(size, greater);

	for (int i = 1; i < 15; i++) {
		heap.add(new int(i));
	}

	heap.heapify();

	int *iter;
	iter = heap.iterator();

	while (heap.hasNext()) {

		printf("%d\n", *iter);

		iter = heap.next();
	}

	int tcCase = 1;
	int fCount = 2;

	for (int tc = 0; tc < tcCase; tc++) {

		for (int j = 0; j < fCount; j++) {

			int *a[10];
			printf("fCount : %d\n", j);

			for (int i = 0; i < 10; i++) {
				a[i] = heap.pop();
				printf("pop : %d\n", *a[i]);
			}

			for (int i = 0; i < 10; i++) {
				heap.add(a[i]);
			}

			heap.heapify();

		}
	}

	printf("reInit\n");

	heap._length = 0;
	for (int i = 1; i < 15; i++) {
		heap.add(new int(i));
	}
	iter = heap.iterator();

	while (heap.hasNext()) {

		printf("%d\n", *iter);

		iter = heap.next();
	}

	return;
}