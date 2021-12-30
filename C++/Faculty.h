#ifndef FACULTY_H
#define FACULTY_H
#include "Person.h"
#include "DoublyLinkedList.h"
class Faculty : public Person{//extending person class for some member variables
    public:
    //constructors/destructors
    Faculty();
    Faculty(int id, string n, string l, string d);
    ~Faculty();

    //additional member variables
    string department;
    DoublyLinkedList<int>* advisees;//list of advisees

    //helper functions
    string toString();
    bool addAdvisee(int adv);
    bool removeAdvisee(int adv);

    //overloaded operators for printing
    friend ostream& operator<<(ostream& os, Faculty f);
    friend ostream& operator<<(ostream& os, Faculty* f);
};
#endif