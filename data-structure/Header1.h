#pragma once
struct TNode1 {

	TNode1 *_equal, *_high, *_low;

	char _key;
	void *_value;

	TNode1() :_equal(0), _high(0), _low(0), _key(0), _value(0) {}
};

struct TTree1 {

	TNode1 root;

	void insert(char *key, void *value) {

		TNode1 *iter;
		char *ptr;

		ptr = key;
		iter = &root;

		while (true) {

			if (iter->_key == 0) {

				//create
				iter->_key = *ptr;
				iter->_equal = new TNode1;
				iter->_high = new TNode1;
				iter->_low = new TNode1;

				//check end

				ptr++;

				if (*ptr == '\0') {
					iter->_value = value;
					break;
				}
				else {
					iter = iter->_equal;
				}
				
			}
			else if (*ptr < iter->_key) {
				iter = iter->_low;
			}
			else if (*ptr > iter->_key) {
				iter = iter->_high;
			}
			else if (*ptr == iter->_key) {
				
				ptr++;

				if (*ptr == '\0') {
					iter->_value = value;
					break;
				}
				else {
					iter = iter->_equal;
				}
			}

		}
	
	}
};