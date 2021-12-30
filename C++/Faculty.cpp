#include "Faculty.h"
//default constructor
Faculty::Faculty(){//set all values to a standard "empty" value (this never gets called)
    ID = -1;
    name = "None";
    level = "None";
    department = "None";
    advisees = new DoublyLinkedList<int>();//instantiate a new linked list to house advisees when they get added later    
}
//overloaded constructor with member variables passed in 
Faculty::Faculty(int id, string n, string l, string d){
    ID = id;
    name = n;
    level = l;
    department = d;
    advisees = new DoublyLinkedList<int>();
}
//destructor
Faculty::~Faculty(){
    //nothing to delete since the linked lists which are dynamically allocated are deleted automatically when the faculty falls out of scope
}

//returns a string with the faculty object's data formatted so it can be printed to a file and read back later
string Faculty::toString(){
    string temp = to_string(ID) + "`$`" + name + "`$`" + level + "`$`" + department + "`$`" + to_string(advisees->getSize()) + "`$`";
    ListNode<int> *curr = advisees->front;//get a pointer to the front of the list of advisees
    while(curr != nullptr){//loop through the advisees one at a time to add them to the string
        temp += to_string(curr->data) + "`$`";//convert current node's integer to a string and append it
        curr = curr->next;
    }
    return temp;
}

//takes an integer id of an advisee to be added to the list, returns true if successful operation
bool Faculty::addAdvisee(int adv){
    if(advisees->contains(adv)){//if already in the list, return false
        return false;
    }
    else{
        advisees->insertBack(adv);//otherwise insert it and return true
    }
    return true;
}

//takes an integer id of an advisee to be removed from the list, returns true if successful operation
bool Faculty::removeAdvisee(int adv){
    if(!advisees->contains(adv)){
        return false;//if not found in the list, return false
    }
    else{//otherwise remove it and return true
        advisees->remove(adv);
    }
    return true;
}

//overloaded print operators. Displays each of the fields of the faculty object on one line
ostream& operator<<(ostream& os, Faculty f){
    os << "ID: " << f.ID << "  Name: " << f.name << "  Level: " << f.level << "  Department: " << f.department << "  Advisees: " << f.advisees << flush;
    return os;
}
ostream& operator<<(ostream& os, Faculty* f){
    os << "ID: " << f->ID << "  Name: " << f->name << "  Level: " << f->level << "  Department: " << f->department << "  Advisees: " << f->advisees << flush;
    return os;
}