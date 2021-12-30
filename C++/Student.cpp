#include "Student.h"
//default constructor
Student::Student(){//give all member variables an "empty" default value. This never gets called
    ID = -1;
    name = "None";
    level = "None";
    major = "None";
    GPA = -1;
    advisor = -1;
}
//overloaded constructor with all member variables getting passed in and assigned
Student::Student(int id, string n, string l, string m, double G, int adv){
    ID = id;
    name = n;
    level = l;
    major = m;
    GPA = G;
    advisor = adv;
}
//destructor
Student::~Student(){
    //nothing dynamically allocated within class, so nothing to delete
}

//returns a string containing all of the member variables formatted so they can be printed to and read from a file later
string Student::toString(){
    return to_string(ID) + "`$`" + name + "`$`" + level + "`$`" + major + "`$`" + to_string(GPA) + "`$`" + to_string(advisor) + "`$`";
}

//overloaded insertion operators so student objects can be printed with all of their member variables formatted onto one line
ostream& operator<<(ostream& os, Student student){
    os << "ID: " << student.ID << "  Name: " << student.name << "  Level: " << student.level << "  Major: " << student.major << "  GPA: " << student.GPA << "  Advisor: " << student.advisor << flush;
    return os;
}
ostream& operator<<(ostream& os, Student* student){
    os << "ID: " << student->ID << "  Name: " << student->name << "  Level: " << student->level << "  Major: " << student->major << "  GPA: " << student->GPA << "  Advisor: " << student->advisor << flush;
    return os;
}