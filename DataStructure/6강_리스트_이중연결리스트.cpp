#include <iostream>
using namespace std;

class Node2 {
private:
	Node2* prev;
	Node2* next;
	int data;
public:
	Node2(int val = 0) :data(val),prev(NULL),next(NULL){}
	Node2* getPrev() { return prev; }
	Node2* getNext() { return next; }
	void setPrev(Node2* p) { prev = p; }
	void setNext(Node2* n) { next = n; }
	void display() { cout << "[" << data << "]"; }
	bool hasData(int val) { return data == val; }

	void insertNext(Node2* n) {
		if (n != NULL) {
			n->prev = this;
			n->next = next;
			if (next != NULL) {
				next->prev = n;
			}
			next = n;
		}
	}
	Node2* remove() {
		if (prev != NULL) prev->next = next;
		if (next != NULL)next->prev = prev;
		return this;
	}
};


class DbLinkedList {
private:
	Node2 org;//Çìµå³ëµå
public:
	DbLinkedList() :org(0) {}
	~DbLinkedList() { while (!isEmpty())delete remove(0); }

	Node2* getHead() { return org.getNext(); }
	bool isEmpty() { return getHead() == NULL; }
	Node2* getEntry(int pos) {
		Node2* n = &org;
		for (int i = -1; i < pos; i++, n = n->getNext()) {
			if (n == NULL)break;
		}
		return n;
	}
	void insert(int pos, Node2* n) {
		Node2* prev = getEntry(pos - 1);
		if (prev != NULL) {
			prev->insertNext(n);
		}
	}
	Node2* remove(int pos) {
		Node2* n = getEntry(pos);
		return n->remove();
	}
	Node2* find(int val) {
		for (Node2* p = getHead(); p != NULL; p = p->getNext()) {
			if (p->hasData(val)) return p;
		}
		return NULL;
	}
	void replace(int pos, Node2* n) {
		Node2* prev = getEntry(pos - 1);
		if (prev != NULL) {
			delete prev->getNext()->remove();
			prev->insertNext(n);
		}
	}
	int size() {
		int count = 0;
		for (Node2* p = getHead(); p != NULL; p = p->getNext()) {
			p->display();
		}
		cout << endl;
	}
	void clear() { while (!isEmpty())delete remove(0); }
};
int main() {




}