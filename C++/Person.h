#ifndef PERSON_H
#define PERSON_H
using namespace std;
#include <iostream>

class Person{
    public:
        //member variables
        int ID;
        string name;
        string level;

        //overloaded comparison operators so 2 Person, or a person and an integer can be compared for BST
        friend bool operator==(Person& p1, Person& p2);
        friend bool operator!=(Person& p1, Person& p2);
        friend bool operator<(Person& p1, Person& p2);
        friend bool operator>(Person& p1, Person& p2);
        friend bool operator==(Person& p1, int p2);
        friend bool operator!=(Person& p1, int p2);
        friend bool operator<(Person& p1, int p2);
        friend bool operator>(Person& p1, int p2);
        friend bool operator==(int p1, Person& p2);
        friend bool operator!=(int p1, Person& p2);
        friend bool operator<(int p1, Person& p2);
        friend bool operator>(int p1, Person& p2);
};
#endif
