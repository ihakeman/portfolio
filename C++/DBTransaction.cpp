#include "DBTransaction.h"
//default constructor (not called)
DBTransaction::DBTransaction(){
    isInsertion = true;//initialize bools to true
    isStudent = true;
    isUpdate = false;//false since it can't be update and insertion
    faculty = nullptr;//initialize pointers to null since nothing is passed in
    student = nullptr;
    oldFacultyID = -1;//initalize ints to -1 since unused
    studentID = -1;
    newFacultyID = -1;
}
//overloaded constructor with passed in student, and if it was an insertion
DBTransaction::DBTransaction(bool insert, Student stud){
    isInsertion = insert;//is insertion is passed in as insert
    isStudent = true;//a student is passed in, so isStudent = true
    student = new Student(stud.ID, stud.name, stud.level, stud.major, stud.GPA, stud.advisor);//instantiate a new Student with attributes of one passed in
    faculty = nullptr;//no faculty to be stored, since the operation was with a student, so nullptr
    isUpdate = false;//not an update since student passed in
    oldFacultyID = -1;//initialize ints to -1 since unused
    studentID = -1;
    newFacultyID = -1;
}
//overloaded constructor with passed in faculty, and if it was an insertion
DBTransaction::DBTransaction(bool insert, Faculty fac){
    isInsertion = insert;//is insertion passed in as insert
    isStudent = false;//a faculty was passed in, not student, so false
    faculty = new Faculty(fac.ID, fac.name, fac.level, fac.department);//instantiate a new faculty with members of the one passed in
    ListNode<int> *curr = fac.advisees->front;//get a pointer to front of passed in faculties advisee list
    while(curr != nullptr){//loop while not reaching the end of the loop
        faculty->addAdvisee(curr->data);//add the advisee id to the new faculty's list
        curr = curr->next;
    }
    student = nullptr;//no student passed in, so nullptr
    isUpdate = false;//not an update, so false
    oldFacultyID = -1;//unused ints initialize to -1
    studentID = -1;
    newFacultyID = -1;
}

DBTransaction::DBTransaction(int oldFac, int studID, int newFac){
    isInsertion = false;//not an insertion
    isUpdate = true;//it is an update since 3 ints are passed in
    isStudent = false;//not a student
    oldFacultyID = oldFac;//initalize ints to those passed in
    studentID = studID;
    newFacultyID = newFac;
    student = nullptr;//no faculty or student stored since it is an update
    faculty = nullptr;
}

//destructor
DBTransaction::~DBTransaction(){
    delete student;//delete the dynamically allocated student
    delete faculty;//delete the dynamically allocated faculty
}

//equality operators overloaded to make compiler happy, not used in any of the methods called
bool operator==(DBTransaction db1, DBTransaction db2){
    return (db1.isInsertion == db2.isInsertion && db1.isStudent == db2.isStudent && db1.faculty == db2.faculty && db1.student == db2.student);
}

bool operator!=(DBTransaction db1, DBTransaction db2){
    return (db1.isInsertion != db2.isInsertion || db1.isStudent != db2.isStudent || db1.faculty != db2.faculty || db1.student != db2.student);
}