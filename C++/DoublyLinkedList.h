#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "List.h"
#include "ListNode.h"

//template class so it can be a linked list of any data type
template <typename T>
class DoublyLinkedList : List<T>{//implements from the list ADT, meaning it requires all functions in the list virtual class
    private:
        size_t listSize;//number of elements in the list

    public:
        ListNode<T> *front;//pointer to front of list now public so it can be iterated through
        ListNode<T> *back;//pointer to back of the list
        //constructor/destructor
        DoublyLinkedList();
        ~DoublyLinkedList();

        //functions from the list ADT
        virtual void insertFront(T data);
        virtual void insertBack(T data);
        virtual T removeFront();
        virtual T removeBack();
        virtual T getFront();
        virtual T remove(T key);
        virtual bool contains(T value);
        virtual bool isEmpty();
        virtual unsigned int getSize();

        //auxiliary functions
        int find(T value);
        T getBack();
        void printList(bool printLink);

        //overloaded insertion operators for printing, found in .cpp file since otherwise they become overdefined
        friend ostream& operator<<(ostream& os, DoublyLinkedList<int> list);
        friend ostream& operator<<(ostream& os, DoublyLinkedList<int>* list);
};
//constructor
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(){
    listSize = 0;//initialize size to 0
    front = nullptr;//set pointers to null since there are no nodes
    back = nullptr;
}

//destructor
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(){
    //cout << "Deleting linked List " << endl;
    while(front != nullptr){//loop while front is not null to ensure all nodes are deleted
        ListNode<T> *temp = front;//make a temporary pointer to the front node so pointers can be nulled without losing reference
        if(front == back){//if the front points to the same node as the back, we have one node left
            front = nullptr;//set the front and back pointers to null since there will be no more nodes in the list
            back = nullptr;
        }
        else{//if more than one node remains we will delete the front one
            front = front->next;//set the front equal to the next node
            temp->next = nullptr;//set the next pointer from the old front to null
            front->prev = nullptr;//set the new front's previous to null
        }
        delete temp;//delete the node
    }
}

//returns nothing but makes a new node at the front of the list with the data passed in
template <typename T>
void DoublyLinkedList<T>::insertFront(T data){
    ListNode<T> *node = new ListNode<T>(data);//make a new node with the data passed
    if(listSize == 0){//if currently an empty list, set the back pointer to the new node
        back = node;
    }
    else{//otherwise the list isn't empty
        front->prev = node;//set the front previous to the new node
        node->next = front;//set the new node's next pointer to the old front
    }
    front = node;//set the front to the new node
    listSize++;//increment the listSize;
}

//returns nothing but makes a new node at the back of the list with the data passed in
template <typename T>
void DoublyLinkedList<T>::insertBack(T data){
    ListNode<T> *node = new ListNode<T>(data);//make the new node
    if(listSize == 0){// if list is empty
        front = node;//set the front pointer to the new node
    }
    else{//otherwise it is not an empty list
        back->next = node;//set the old back's next node to the new node
        node->prev = back;//set the new nodes previous pointer to the back
    }
    back = node;//set the back pointer to the new node
    listSize++;//increment the listSize
}

//returns the data in the first node, and deletes the first node
template <typename T>
T DoublyLinkedList<T>::removeFront(){
    ListNode<T> *tp = front;//make a pointer to the front node so we can change other pointers without losing reference
    if(isEmpty()){//check if empty
        throw runtime_error("Linked list is empty");//throw an error since there is nothing to remove
    }
    if(front->next == nullptr){//check if size = 1;
        back = nullptr;//if so, set the back pointer to null (since we will have no nodes after this)
    }
    else{//size>1
        front->next->prev = nullptr;//set the node after front's previous pointer to null since it becomes the new front
    }
    front = front->next;//update the front pointer to the node after front
    tp->next = nullptr;//set the next pointer to null for the node you are removing
    T tempData = tp->data;//access the data in the node you are deleting
    listSize--;//decrement the list size
    delete tp;//delete the node
    return tempData;//return the data
}
//returns the data in the last node and deletes the back node
template <typename T>
T DoublyLinkedList<T>::removeBack(){
    ListNode<T> *tp = back;//make a pointer to the back node so we can change other pointers without losing reference
    if(isEmpty()){//check if empty
        throw runtime_error("Linked list is empty");//throw an error since there is nothing to remove
    }
    if(back->prev == nullptr){//check if one node in list
        front = nullptr;//if so, after deleting the back node there will be no nodes left, so set front to null
    }
    else{//otherwise there is more than one node
        back->prev->next = nullptr;//set the next pointer node before the back node to null since it will become the back node
    }
    back = back->prev;//set the back node to the one before it
    tp->prev = nullptr;//set the previous pointer of the old back node to null since it will be deleted
    T temp = tp->data;//access the data in the node to be delete (old back node)
    listSize--;//decrement the listSize
    delete tp;//delete the old back node
    return temp;//return the data
}
//returns the value at the front of the list (used for peek in a stack application)
template <typename T>
T DoublyLinkedList<T>::getFront(){
    return front->data;
}

//returns the value at the back of the list (could be used for peek in a stack application)
template <typename T>
T DoublyLinkedList<T>::getBack(){
    return back->data;
}

//deletes the list node containing a certain data and returns that data
template <typename T>
T DoublyLinkedList<T>::remove(T key){//key is value we are looking for to remove
    //we could leverage find here but for example we aren't
    ListNode<T> *current = front;//make a pointer to the front node to start our search
    while(current->data != key){//keep going until we find the node with the right data
        current = current->next;//since we didn't find it, check the subsequent node

        if(current == nullptr){//if we get to where current is null, it wasn't found so give an error since there is nothing to return
            throw runtime_error("key not found");
        }
    }
    //if we get here, we found it so now remove it
    if(current == front){//could call the remove front method
        front = current->next;//make the front point to the one after the current since it will become the front
        if(front != nullptr)
            front->prev = nullptr;//the new front has nothing before it, so null the previous pointer
    }
    else if (current == back){//if the last node
        back = current->prev;//the new back is the one before the current back
        back->next = nullptr;//the new back's next is null since it is now back
    }
    else{
        //the list node to be removed is somewhere between front and back
        current->prev->next = current->next;//the node before should point to the one after the one we remove as its next
        current->next->prev = current->prev;//the node after should point to the one before the one we remove as its previous
    }
    current->next = nullptr;//the current node (one with the key) should not point to anything anymore since it is being removed
    current->prev = nullptr;
    T temp = current->data;//get the data
    listSize--;//decrement the list size
    delete current;//delete the node
    return temp;//return the data
}

//returns true if the node is found in the list
template <typename T>
bool DoublyLinkedList<T>::contains(T value){//returns true if the node is found
    ListNode<T> *current = front;//make a temporary pointer to the front to start the search
    while(current != nullptr){//while we haven't reached the end keep looping
        if(current->data == value){//if the current node we are looking at has the value
            return true;//return true
        }
        else{//otherwise look at the next node
            current = current->next;
        }
    }
    return false;//return false since it wasn't found
}

//returns the index of the node, checks to see if the value is in the linked list (unused for stack application)
template <typename T>
int DoublyLinkedList<T>::find(T value){//returns an index of the node (even though it doesn't have direct access to it like in an array)
    int index = -1;//set the initial index to -1 since we don't know if it exists yet
    ListNode<T> *current = front;//make a temporary pointer to the front to start the search
    while(current != nullptr){//while we haven't reached the end keep looping
        ++index;//increment the index
        if(current->data == value){//if the current node we are looking at has the value
            break;//exit the loop
        }
        else{//otherwise look at the next node
            current = current->next;
        }
    }
    if(current == nullptr){
        //did not find the value since it doesn't exist in the linked list
        index = -1;//reset the index to -1 (an invalid index)
    }
    return index;//return the index
}

//returns the number of elements in the list
template <typename T>
unsigned int DoublyLinkedList<T>::getSize(){
    return listSize;
}

//returns whether the list has elements in it or not
template <typename T>
bool DoublyLinkedList<T>::isEmpty(){
    return listSize == 0;
}

//prints out the contents of the list visually (with or without pointers depending on bool input)
template <typename T>
void DoublyLinkedList<T>::printList(bool printLink)
{
    ListNode<T> *curr = front;//make a temporary pointer to start at the front
    while(curr != 0){//while we haven't gotten to a null pointer (end of list)
       if(curr == front){//print the front if it is the front
         cout << "{FRONT}: ";
       }
       else if(curr == back){//or print rear if it is the rear
         cout << "{REAR}: ";
       }
       if(printLink)//if we want to see the actual pointers, print them and the data contained
        cout << "[ PREV: "<< curr->prev << " || " << curr->data << " || NEXT: "<< curr->next << " ] ";
      else//otherwise just print the data in the spot
        cout << "[ " << curr->data << " ] ";

       curr = curr->next;//update the node we are looking at to the next one
       if(curr != 0){
         cout << " ==> ";//print an arrow if we haven't reached the end of the list
       }
    }
    cout << endl;
}

#endif