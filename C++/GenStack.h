#ifndef GENSTACK_H
#define GENSTACK_H
#include "DoublyLinkedList.h"

//template class so the stack can hold any data type
template <typename T>
class GenStack{
public:
  GenStack();
  ~GenStack();
  void push(T c); //add to top
  T pop(); //remove from top
  T peek(); //return top without removing
  bool isEmpty();
  int size();
  void printStackList();

private:
  DoublyLinkedList<T> *stackList;//linked list that the stack is based on
  int count; //number of items currently in stack
};

//constructor
template <typename T>
GenStack<T>::GenStack(){
  stackList = new DoublyLinkedList<T>;//instantiate the underlying linked list
  count = 0;//no elements on the stack initially
}

template <typename T>
GenStack<T>::~GenStack(){
  delete stackList;//delete the dynamically allocated linked list
}

//returns whether the stack is empty or not as bool
template <typename T>
bool GenStack<T>::isEmpty(){
  return (count == 0);
}

//returns the number of items on the stack
template <typename T>
int GenStack<T>::size(){
  return count;
}

//pushes the data passed in to the top of the stack
template <typename T>
void GenStack<T>::push(T c){
  count++;//increment the number of items in the stack
  stackList->insertFront(c);//insert the data to the front of the underlying list (top)
}

//returns the data at the top of the stack and removes it from the stack/linked list
template <typename T>
T GenStack<T>::pop(){
  if(isEmpty()){//throw an error if there is nothing to remove
    throw runtime_error("Stack is empty");
  }
  --count;//decrement the count
  return stackList->removeFront();//remove the item at the front of the linked list (top of the stack) and return its data
}

//returns the data at the front of the stack without removing the element from the stack/linked list
template <typename T>
T GenStack<T>::peek(){
  if(isEmpty()){//throw an error if there is nothing to remove
    throw runtime_error("Stack is empty");
  }
  return stackList->getFront();//access the data at the top of the stack without removing it
}

//prints out the stack visually by printing out the underlying doublylinked list with front indicating the top of the stack
template <typename T>
void GenStack<T>::printStackList(){
  stackList->printList(false);//call the doublylinked list print method without showing pointers
}
#endif
