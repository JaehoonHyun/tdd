#pragma once

struct TSNode {

	void *data;
	struct TSNode *less, *equal, *greater;
	char key;

	TSNode() :data(0), less(0), equal(0), greater(0), key(0) {}

};

struct TSTree
{
	TSNode root;

	void insert(const char *str, void *data) {

		const char *ptr;
		ptr = str;
		TSNode *iter;

		
		iter = &root;
		while (true) {
			
			

			if (iter->key == 0) {
				iter->key = *ptr;
				
				iter->equal = new TSNode;
				ptr++;

				if (*ptr == '\0') {
					if(iter->data == 0)
						iter->data = data;
					return;
				}
				iter = iter->equal;
			}
			else if (iter->key == *ptr) {
				ptr++;
				if (*ptr == '\0') {
					if (iter->data == 0)
						iter->data = data;
					return;
				}
				iter = iter->equal;
			}
			else if (iter->key > *ptr) {
				iter->less = new TSNode;
				iter = iter->less;
			}
			else if (iter->key < *ptr) {
				iter->greater = new TSNode;
				iter = iter->greater;
			}


			
		}
	}


	TSNode *_search(const char *str) {

		const char *ptr;
		TSNode *iter;
		ptr = str;

		iter = &root;
		while (true) {

			if (iter == 0) {
				return 0;
			}

			if (iter->key == *ptr) {
				ptr++;

				if (*ptr == '\0') {
					if (iter->data != 0)
						return iter;
					else
						return 0;
				}
				iter = iter->equal;
			}
			else if (iter->key > *ptr) {
				iter = iter->less;
			}
			else if (iter->key < *ptr) {
				iter = iter->greater;
			}



		}
	}

	void* search(const char *str) {

		TSNode *node;
		if ((node = _search(str)) != 0) {
			return node->data;
		}

		return 0;
	}
};