#include "DoublyLinkedList.h"
//overloaded insertion operators to print the linked list
ostream& operator<<(ostream& os, DoublyLinkedList<int> list){
    ListNode<int> *curr = list.front;//access the front of the list
    while(curr!= nullptr){//loop while not reaching the end of the list
        os << curr->data << flush;//insert the data from the node to the output stream
        curr = curr->next;//go to the next node
        if(curr != nullptr){//if not the last node
            os << ", " << flush;//print out a comma and a space
        }
    }
    return os;//return the output stream
}
//same as above but with a pointer instead of an object passed in
ostream& operator<<(ostream& os, DoublyLinkedList<int>* list){
    ListNode<int> *curr = list->front;
    while(curr!= nullptr){
        os << curr->data << flush;
        curr = curr->next;
        if(curr != nullptr){
            os << ", " << flush;
        }
    }
    return os;
}