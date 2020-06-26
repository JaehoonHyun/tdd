#ifndef LIST_H_
#define LIST_H_


/*
����� �� 
-. Node�� �ڱ��ڽ����� �ʱ�ȭ��Ų��.
-. iter(), hasNext(), next() �Լ��� ����
-. add �Լ��� _add�Լ��� ���� �����ϸ� �� ����
-. remove�� �Ҵ���� �޸𸮸� �������� ���� ���� ������ �����ؾ���
-. STACK : prev -> &head,     next -> head.next (��� <-> newbie <-> ���.next)
-. QUEUE : prev -> head.prev, next-> &head (head.prev�� �׻� ������, ���� <-> newbie <-> ���)
*/
struct Node {
	void *data;
	struct Node * prev;
	struct Node * next;

	Node()
		:prev(this)
		, next(this)
	{}
};

struct List {

	struct Node head;
	struct Node *_iter;
	unsigned int _size;

	List() : _size(0)
	{

	}

	void add(void *data) {

		struct Node *newbie;
		struct Node *_prev;
		struct Node *_next;

		newbie = new struct Node;

		newbie->data = data;

		//STACK
		//_prev = &head;
		//_next = head.next;
		//_add(_prev, newbie, _next);

		//QUEUE
		_prev = head.prev;
		_next = &head;
		_add(_prev, newbie, _next);


		_size++;
	}

	void setIdx(int i, void *data) {
		Node *node = get(i);
		node->data = data;
		
	}

	static void _add(struct Node *prev, struct Node *newbie, struct Node *next) {

		prev->next = newbie;
		next->prev = newbie;

		newbie->next = next;
		newbie->prev = prev;


	}

	struct Node * remove(struct Node *old) {

		struct Node *prev;
		struct Node *next;

		prev = old->prev;
		next = old->next;

		prev->next = next;
		next->prev = prev;

		old->prev = old;
		old->next = old;

		_size--;

		_iter = prev;

		return old;
	}
	


	struct Node * iterator() {
		_iter = head.next;
		return _iter;
	}

	bool hasNext() {

		return _iter != &head ? true : false;
	}

	struct Node *next() {
		_iter = _iter->next;
		return _iter;
	}

	Node *get(int idx) {

		Node *iter;
		iter = iterator();
		int i = 0;

		while (hasNext()) {

			if (i == idx) {
				return iter;
			}
			else {
				iter = next();
				i++;
			}
		}

		return 0;
	}
};

#endif