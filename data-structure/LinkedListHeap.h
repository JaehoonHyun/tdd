#pragma once

#include "list.h"

struct MyLinkedListHeap {

#define _length _array._size

	List _array;

	MyLinkedListHeap() {
		
		_array.add(0);
	}

	void add(MyPost *data) {
		_array.add(data);

	}

	void heapify() {

		for (int i = _length / 2 + 1; i >= 1; i--) {
			downHeapify(i);
		}
	}

	void downHeapify(int i) {
		int s = i;

		while (s < _length) {

			int lChildIdx = 2 * s;
			int rChildIdx = 2 * s + 1;

			int maxIdx = s;



			unsigned long long maxValue = ((MyPost *)_array.get(s)->data)->_priority.value;

			if (lChildIdx < _length) {
				unsigned long long lChildValue = ((MyPost *)_array.get(lChildIdx)->data)->_priority.value;

				if (maxValue < lChildValue) {
					maxValue = lChildValue;
					maxIdx = lChildIdx;
				}
			}

			if (rChildIdx < _length) {
				unsigned long long rChildValue = ((MyPost *)_array.get(rChildIdx)->data)->_priority.value;

				if (maxValue < rChildValue) {
					maxValue = rChildValue;
					maxIdx = rChildIdx;
				}
			}

			if (s != maxIdx) {

				//swap
				void *temp;

				temp = _array.get(s)->data;
				_array.get(s)->data = _array.get(maxIdx)->data;
				_array.get(maxIdx)->data = temp;

				s = maxIdx;
			}
			else {
				break;
			}

		}

	}

	MyPost *pop() {

		MyPost *temp;

		if (_length == 1) {
			return 0;
		}

		temp = (MyPost *)_array.get(1)->data;
		_array.get(1)->data = _array.get(_length-1)->data;

		_length--;

		downHeapify(1);

		return temp;
	}

	void sort() {

		int tempLength;
		tempLength = _length;

		for (int i = tempLength; i >= 1; i--) {

			_array.get(i)->data = pop();
		}

		_length = tempLength;
	}

	int _iterIdx;

	bool hasNext() {
		return _iterIdx < _length ? true : false;

	}

	MyPost *iterator() {
		_iterIdx = 1;
		return (MyPost *)_array.get(_iterIdx)->data;
	}

	MyPost *next() {
		_iterIdx++;
		Node *node;
		node = _array.get(_iterIdx);

		if (node == 0) {
			return 0;
		}
		else {
			return (MyPost *)node->data;
		}

	}

};