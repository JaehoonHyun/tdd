#pragma once

struct Node3 {

	struct Node3 *_next, *_prev;
	void *_data;

	Node3() :_next(this), _prev(this), _data(0) {}
};

struct List3 {

	int count;
	Node3 head;
	Node3 *iter;

	List3() :count(0) {}

	void add(void *data) {

		Node3 *newbie = new Node3;
		newbie->_data = data;

		Node3 *prev, *next;
		prev = &head;
		next = head._next;

		_add(prev, newbie, next);
		count++;
	}

	void _add(Node3 *prev, Node3 *newbie, Node3 *next) {

		prev->_next = newbie;
		next->_prev = newbie;

		newbie->_prev = prev;
		newbie->_next = next;

	}

	Node3 *iterator() {
		iter = head._next;
		return iter;
	}

	bool hasNext() {
		return iter == &head ? false : true;
	}

	Node3* next() {
		iter = iter->_next;
		return iter;
	}

	Node3 *remove(Node3 *old) {

		Node3 *prev, *next;

		prev = old->_prev;
		next = old->_next;

		prev->_next = next;
		next->_prev = prev;

		old->_next = old;
		old->_prev = old;

		count--;

		return old;
	}
};