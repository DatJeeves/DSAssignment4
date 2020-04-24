#ifndef QUEUE_H
#define QUEUE_H
#include "list.h"

// The Queue is a FIFO style list and this implementation
// is based on my generic LinkedList data type.
// The standard Queue functions are implemented in this version
// In many implementations of Queue there is a maxSize that the 
// user wishes the Queue to be.

using namespace std;

//QUEUE CLASS

template<typename T>
class Queue {
public:

	//constructors & destructors
	Queue();
	Queue(int max);
	~Queue();

	//Functions to augment the queue
	void Enqueue(T element);
	T Dequeue();
	T Peek();
	int Size();
	bool isEmpty();
	bool isFull();

private:
	int size;
	int maxSize;
	List<T> myQueue;
};


//Queue Constructor and Destructor

template <typename T>
Queue<T>::Queue() {
	maxSize = 100; // allow for a large queue by default
	size = 0;
}

template <typename T>
Queue<T>::Queue(int max) {
	maxSize = max;
	size = 0;
}

template <typename T>
Queue<T>::~Queue() {

}

template <typename T>
void Queue<T>::Enqueue(T element) {
	if (myQueue.GetListSize() < maxSize) {
		myQueue.AddToTail(element);
	}
}

template <typename T>
T Queue<T>::Dequeue() {
	if (!myQueue.isEmpty()) {
		return myQueue.popHead();
	}
}

template <typename T>
T Queue<T>::Peek() {
	if (!myQueue.isEmpty()) {
		return myQueue.GetHead();
	}
}

template <typename T>
int Queue<T>::Size() {
	return myQueue.GetListSize();
}


//Checks whether the Queue is empty via the size variable
template <typename T>
bool Queue<T>::isEmpty() {
	return myQueue.isEmpty();
}


#endif
