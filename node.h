#ifndef NODE_H
#define NODE_H
#include <cstddef>

template <typename T>
class Node
{
public:
    //stores the data and references to previous and next node
    T data;
    Node<T>* nextNode;
    Node<T>* prevNode;

    //constructors and destructors
    Node();
    Node(T storeData);
    ~Node();
};

//constructor
template <typename T>
Node<T>::Node() {
    // Do nothing
}

//data constructor
template <typename T>
Node<T>::Node(T storeData)
{
    // This store the data for the node
    data = storeData;
    nextNode = NULL; // set the next node to null
    prevNode = NULL; // set the prev node to nul
}

//destructor
template <typename T>
Node<T>::~Node()
{
    if (nextNode == NULL)
        delete nextNode;
    if (prevNode == NULL)
        delete prevNode;
}
#endif