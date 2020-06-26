#pragma once

template<typename T>
struct MyHeap {
	int _length;

	T *_array;

	typedef long(*tGreater)(long *a, long *b);
	tGreater _greater;

	MyHeap(int size, tGreater greater) :_length(0), _array(new T[size]), _greater(greater) {

	}

	void add(T data) {
		_array[++_length] = data;
	}

	void heapify() {

		for (int i = _length / 2 + 1; i >= 1; i--) {
			downHeapify(i);
		}
	}

	void downHeapify(int i) {
		int s = i;

		while (s <= _length) {

			int lChildIdx = 2 * s;
			int rChildIdx = 2 * s + 1;

			int maxIdx = s;
			T maxValue = _array[s];

			if (lChildIdx <= _length) {
				
				if (_greater((long *)_array[lChildIdx], (long *)maxValue)) {
					maxValue = _array[lChildIdx];
					maxIdx = lChildIdx;
				}
			}

			if (rChildIdx <= _length) {

				if (_greater((long *)_array[rChildIdx], (long *)maxValue)) {
					maxValue = _array[rChildIdx];
					maxIdx = rChildIdx;
				}
			}

			if (s != maxIdx) {

				//swap
				T temp;
				temp = _array[s];//////////////////////////////
				_array[s] = _array[maxIdx];
				_array[maxIdx] = temp;

				s = maxIdx;
			}
			else {
				break;
			}

		}

	}

	T pop() {
		
		T temp;

		if (_length == 0) {
			return 0;
		}

		temp = _array[1];
		_array[1] = _array[_length];

		_length--;

		downHeapify(1);

		return temp;
	}

	void sort() {

		int tempLength;
		tempLength = _length;

		for (int i = tempLength; i >= 1; i--) {

			_array[i] = pop();
		}

		_length = tempLength;
	}

	int _iterIdx;

	bool hasNext() {
		return _iterIdx <= _length ? true : false;

	}

	T iterator() {
		_iterIdx = 1;
		return _array[_iterIdx];
	}

	T next() {
		_iterIdx++;
		return _array[_iterIdx];
	}

};