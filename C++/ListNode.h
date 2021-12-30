#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
using namespace std;

//template class so it can handle any data type
template <typename T>
class ListNode{
    public:
        ListNode();
        ListNode(T d);
        ~ListNode();
        ListNode *next;//pointer to next node in a linked list
        ListNode *prev;//pointer to previous node in a linked list
        T data;//actual data being stored
};

template <typename T>
ListNode<T>::ListNode(){}//empty default constructor since it has no data passed in, it is essentially useless

//overloaded constructor with data passed in
template <typename T>
ListNode<T>::ListNode(T d){
    data = d;//assign passed in data to the node's data
    next = NULL;//set pointers to null
    prev = nullptr;
}

//destructor
template <typename T>
ListNode<T>::~ListNode(){
    next = nullptr;//set pointers to null
    prev = nullptr;//nothing to delete since nothing was dynamically allocated
}

#endif