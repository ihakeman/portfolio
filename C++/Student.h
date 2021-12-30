#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
class Student : public Person{//extends from person class for member variables
    public:
        //constructors/destructor
        Student();
        Student(int ID, string n, string l, string m, double G, int adv);
        ~Student();
        
        //member variables
        string major;
        double GPA;
        int advisor;
        
        //helper functions
        string toString();

        //overloaded operators for printing
        friend ostream& operator<<(ostream& os, Student student);
        friend ostream& operator<<(ostream& os, Student* student);
};
#endif