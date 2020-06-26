#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <memory.h>
#include "list.h"

struct Bucket {

	
	List list;

	Bucket() {

	}

};

struct Hash {

	unsigned int _size;
	unsigned int _collision;

	struct Bucket *hash;

	Hash(unsigned int size) : _size(size) , _collision(0)
	{
		hash = new Bucket[size];
	}


	unsigned int hashing(char *str) {

		/*
		unsigned int val;
		unsigned int tmp;

		char *ptr;

		ptr = str;

		val = 0;
		while (*ptr != '\0') {


			val = (val << 4) + *ptr;

			if (tmp = val & 0xF0000000) {
				val = val ^ (tmp >> 24);
				val = val ^ tmp;

			}


			*ptr++;
		}

		printf("hashvalue : %d\n", val % _size);
		return val % _size;
		*/

		unsigned int val = 0;
		unsigned int poly = 0xEDB88320;
		char *ptr;

		ptr = str;

		while (*ptr != '\0') {
			poly = (poly << 1) | (poly >> (32 - 1));
			val = poly * val + *ptr;
			*ptr++;
		}

		printf("hashvalue : %d\n", val % _size);
		return val % _size;

	}


	//Create
	//str이 중복인지는 보장해주지 않는다. 해쉬값이 같으면 추가될 뿐
	//User가 중복이 아님을 처리해야함
	unsigned int add(unsigned int hashvalue, void *data) {

		
		if (hash[hashvalue].list._size > 1) {
			_collision++;
		}

		hash[hashvalue].list.add(data);

		return 0;
	}

	//collisionTest
	double testCollision() {
		return _collision / (double)_size;
	}

	//Read

	//Update





	//PRINT
	

};




#endif
