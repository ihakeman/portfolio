#ifndef DBTRANSACTION_H
#define DBTRANSACTION_H
#include "Student.h"
#include "Faculty.h"
#include "DoublyLinkedList.h"
class DBTransaction{
    public:
        //constructors/destructor
        DBTransaction();
        DBTransaction(bool insert, Student stud);
        DBTransaction(bool insert, Faculty fac);
        DBTransaction(int oldFac, int studID, int newFac);
        ~DBTransaction();

        //member variables
        bool isInsertion;
        bool isStudent;
        bool isUpdate;
        Student *student;
        Faculty *faculty;
        int oldFacultyID;
        int studentID;
        int newFacultyID;
        
        //overloaded comparison operators for when stored in linked list (not used, but compiler needs)
        friend bool operator==(DBTransaction db1, DBTransaction db2);
        friend bool operator!=(DBTransaction db1, DBTransaction db2);
};
#endif