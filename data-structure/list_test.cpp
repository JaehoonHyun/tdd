
#include <stdio.h>
#include "list.h"



char g_name[] = "A";

struct MyPost {

	char name[16];
	struct List list;

	MyPost() {
		name[0] = g_name[0]++;
		name[1] = '\0';
	}
};


void test_list() {
	struct List list;


	for (int i = 0; i < 26; i++) {
		list.add(new MyPost);
	}

	struct Node *iter;

	//search
	iter = list.iterator();
	while (list.hasNext()) {
		MyPost *mydata;
		mydata = (MyPost *)iter->data;
		printf("%s\n", mydata->name);
		iter = list.next();
	}
	printf("=====================================\n");

	//find
	iter = list.iterator();
	while (list.hasNext()) {
		MyPost *mydata;
		mydata = (MyPost *)iter->data;

		if (mydata->name[0] == 'A') {
			break;
		}

		list.next();


	}

	//that remove
	iter = list.remove(iter);
	delete iter->data;
	delete iter;

	//search
	iter = list.iterator();
	while (list.hasNext()) {
		MyPost *mydata;
		mydata = (MyPost *)iter->data;
		printf("%s\n", mydata->name);
		iter = list.next();
	}
	printf("=====================================\n");


	//list element remove all
	
	iter = list.iterator();
	while (list.hasNext()) {
		iter = list.remove(iter);
		delete iter->data;
		delete iter;
	}
	

	//search
	iter = list.iterator();
	while (list.hasNext()) {
		MyPost *mydata;
		mydata = (MyPost *)iter->data;
		printf("%s\n", mydata->name);
		iter = list.next();
	}
	printf("=====================================\n");


}