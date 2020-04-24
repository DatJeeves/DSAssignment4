#ifndef LIST_H
#define LIST_H
#include "node.h"
#include <exception>

using namespace std;

/* A double linked list to store Generic nodes*/
template<typename T>
class List {
public:
	//pointers for the doubly linked list
	Node<T>* head; // Head of the list
	Node<T>* tail; // End of the list

	List();
	T GetHead();
	T GetTail();
	void AddToTail(T data);
	void AddToHead(T data);
	bool isEmpty();
	T popHead();
	T popTail();
	bool search(T data);
	int GetListSize();

	~List();

private:
	//var for size of linked list
	int size;
};

template <typename T>
List<T>::List() {
	// Create an empty list
	head = NULL;
	tail = NULL;
	size = 0;
}

//Checks whether the List is empty via the size variable
template <typename T>
bool List<T>::isEmpty() {
	if (size == 0)
		return true;
	else
		return false;
}

template<typename T>
T List<T>::GetHead()
{
	return head->data;
}

template<typename T>
T List<T>::GetTail()
{
	return tail->data;
}


/*Inserts a value at the head of the list.
NOTE this means:
If the list is empty, then the inserted node becomes the
head AND tail node.

If the list isn't empty, then we have to update
the head node as well as it's next value. Then we have to
update the previous head node's prev value. Note that we
don't have to set the previous head node's prev pointer
to NULL because as being the previous head node, it's prev
pointer already pointed to NULL.

Lastly, we finish the function off the function by
incrementing it's size.
*/
template<typename T>
void List<T>::AddToHead(T data)
{
	Node<T>* n = new Node<T>();

	if (isEmpty()) {
		head = n;
		tail = head;
		n->data = data;
		head->prevNode = NULL;
		head->nextNode = NULL;
	}
	else {
		n->prevNode = NULL;
		n->nextNode = head;
		head->prevNode = n;
		n->data = data;
		head = n;
	}
	++size;

}

template<typename T>
void List<T>::AddToTail(T data)
{
	Node<T>* n = new Node<T>();

	if (isEmpty()) {
		// Tail and head will do the same thing
		head = n;
		tail = head;
		n->data = data;
		head->prevNode = NULL;
		head->nextNode = NULL;
	}
	else {
		n->prevNode = tail;
		n->nextNode = NULL;
		tail->nextNode = n;
		n->data = data;
		tail = n;
	}
	++size;

}

template <typename T>
T List<T>::popHead() {

	T answer;

	if (isEmpty()) {
		//should throw error here?
		//return answer; //in place of an exception
		throw "ERROR: Trying to pop from an empty stack";
	}
	answer = head->data;
	head = head->nextNode;
	--size;
	return answer;
}

template <typename T>
T List<T>::popTail() {

	T answer;

	if (isEmpty()) {
		throw "ERROR: Trying to pop from an empty stack";
	}
	answer = tail->data;
	tail = tail->prevNode;
	--size;
	return answer;
}

template <typename T>
int List<T>::GetListSize() {
	return size;
}

template <typename T>
bool List<T>::search(T data) {
	Node<T>* tempNode = head;

	while (tempNode != NULL) {
		if (tempNode->data == data) {
			return true;
		}
		else {
			tempNode = tempNode->nextNode;
		}
	}
	return false;
}

template <typename T>
List<T>::~List() {
	Node<T> tempNode;

	while (!isEmpty()) {
		tempNode = popHead();
	}
}
#endif
