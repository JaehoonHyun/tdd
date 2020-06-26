
#include <stdio.h>
#include <string.h>

#include <stdlib.h>
#include <time.h>

#include "hash.h"

#define STRING_HASH_SIZE 16

int g_hash_uid = 0;

struct MyPeople {

	List order;

	void add(int uid) {
		int *data = new int;
		*data = uid;
		order.add(data);
	}

	void remove(int uid) {
		//find
		Node *iter;

		iter = order.iterator();
		while (order.hasNext()) {
			int *p_uid;
			p_uid = (int *)iter->data;

			if (*p_uid == uid) {
				break;
			}

			order.next();


		}

		//that remove
		iter = order.remove(iter);
		delete iter->data;
		delete iter;

	}
};

struct MyRoom {

	char _name[STRING_HASH_SIZE];
	int _uid;

	struct MyPeople people;

	MyRoom(char *name, int uid) {
		memcpy(_name, name, STRING_HASH_SIZE);
		_uid = uid;
	}

	void print() {

		Node *iter = people.order.iterator();

		while (people.order.hasNext()) {

			int *p_uid = (int *)iter->data;
			printf("[uid in room ] :%d\n", *p_uid);

			iter = people.order.next();
		}

	}
};

struct Board {

	unsigned int _size;
	Hash *_table;

	Board(unsigned int size) : _size(size)
	{
		_table = new Hash(size);
	}

	void add(MyRoom * new_room) {


		unsigned int hashvalue;
		hashvalue = _table->hashing(new_room->_name);
		List *rooms = &_table->hash[hashvalue].list;

		Node *already_room;
		already_room = rooms->iterator();
		int found = 0;
		while (rooms->hasNext()) {

			MyRoom *room_data = (MyRoom *)already_room->data;
			if (strcmp(room_data->_name, new_room->_name) == 0) {
				found = 1;
				break;
			}
			already_room = rooms->next();
		}

		if (found) {

			//already allocate room_data 
			MyRoom *room_data = (MyRoom *)already_room->data;
			room_data->people.add(new_room->_uid);

			printf("%s already_room FOUND\n", room_data->_name);

			//new_room do not use.

		}
		else {
			
			//new new_room
			new_room->people.add(new_room->_uid);

			_table->add(hashvalue, new_room);
		}
	}
};

void genRandomString(char *randomString) {

	for (size_t i = 0; i < STRING_HASH_SIZE - 1; i++) {
		randomString[i] = 'a' + rand() % 26;
	}

	randomString[STRING_HASH_SIZE - 1] = '\0';


}

void test_hash() {

	unsigned int size = 64 * 1024;
	Board board(size);

	MyRoom *myRoom;

	//myRoom = new MyRoom("abcd" , 2);
	//board.add(myRoom);

	//myRoom = new MyRoom("abcd", 3);
	//board.add(myRoom);
	//
	//myRoom = new MyRoom("quit", 6);
	//board.add(myRoom);

	//myRoom = new MyRoom("tear", 1);
	//board.add(myRoom);

	//test collision
	srand(time(NULL));

	char genString[STRING_HASH_SIZE];
	for (size_t i = 0; i < 10000000; i++) {
		genRandomString(genString);
		unsigned int uid = rand() % 1000;

		printf("%s : %d\n", genString, uid);
		board.add(new MyRoom(genString, uid));
	}


	//PRINT
	for (unsigned int i = 0; i < size; i++) {

		List *rooms = &board._table->hash[i].list;
		
		Node *already_room = rooms->iterator();
		while (rooms->hasNext()) {
			MyRoom *myRoom;
			myRoom = (MyRoom *)already_room->data;
			printf("[list element value ] : %s\n", myRoom->_name);

			myRoom->print();

			already_room = rooms->next();
		}
		
	}

	printf("collision : %lf\n", board._table->testCollision());

	//REMOVE
	


}


void print() {

	
}
