#pragma once
struct MyNode2 {
	struct MyNode2 *_prev;
	struct MyNode2 *_next;

	void *data;

	MyNode2() :_prev(this), _next(this), data(0) {}


};

struct MyList2 {
	
	MyNode2 head;
	MyNode2 *iter;

	int count;

	MyList2() :count(0) {}

	void add(void *data) {

		MyNode2 *newbie;
		newbie = new MyNode2;
		newbie->data = data;

		MyNode2 *prev, *next;

		prev = &head;
		next = head._next;

		_add(prev, newbie, next);
	}

	void _add(MyNode2 *prev, MyNode2 *newbie, MyNode2 *next) {

		prev->_next = next;
		next->_prev = prev;

		newbie->_next = next;
		newbie->_prev = prev;
	}

	bool hasNext() {
		return iter != &head ? true : false;
	}

	MyNode2 *iterator() {
		iter = head._next;
		return iter;
	}

	MyNode2 *next() {
		iter = iter->_next;
		return iter;
	}

	MyNode2 *remove(MyNode2 *old) {

		MyNode2 *prev, *next;

		prev = old->_prev;
		next = old->_next;

		prev->_next = next;
		next->_prev = prev;

		old->_next = old;
		old->_prev = old;

		//
		iter = prev;

		return old;

	}



};