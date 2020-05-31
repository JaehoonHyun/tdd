
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern void test_list();
extern void test_hash();
extern void test_heap();

extern int cert_run();
extern int cert_run2();

#include "ternary.h"


int genRandom() {
	return rand();
}


int genRandom(int mod) {
	return rand() % mod;
}

int main() {
	
	srand(time(NULL));

	TSTree tree;
	tree.insert("CATS", new int(1));
	tree.insert("UP", new int(1));
	tree.insert("CAT", new int(1));
	tree.insert("BUG", new int(1));

	int *a;
	a = (int *)tree.search("BUG");

	a = (int *)tree.search("BUS");
	a = (int *)tree.search("B");

	a = (int *)tree.search("CATS");
	a = (int *)tree.search("CAT");
	a = (int *)tree.search("UP");




	clock_t start, end;

	start = clock();

	test_list();
	//test_hash();
	//test_heap();

	//cert_run();
	//cert_run2();

	end = clock();

	printf("performance time : %.2lf ms\n", (double)end - start);
		
	return 0;
 }