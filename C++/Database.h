#ifndef DATABASE_H
#define DATABASE_H
#include "FileProcessor.h"
#include "GenStack.h"
#include "DBTransaction.h"
class Database{
    public:
        //constructor/destructor
        Database();
        ~Database();

        void RunDatabase();
    private:
        //member variables
        FileProcessor *fp;
        BST<Faculty>* masterFaculty;
        BST<Student>* masterStudent;
        GenStack<DBTransaction*>* rollbackStack;
        int rollbackCount;

        //helper functions
        void incrementRollbackCounter();
        void printMenu();
        int getUserInput(int min, int max);
        int getUserInput();
        double getUserDouble();
        void addFaculty(int id);
        void recursivelyDeleteFacultyAdvisees(TreeNode<Faculty>* curr);
        void emptyAdviseeList(TreeNode<Faculty>* curr);

        //functions representing the 14 options
        void printStudents();
        void printFaculty();
        void printIndividualStudent();
        void printIndividualFaculty();
        void printStudentAdvisor();
        void printFacultyAdvisees();
        void addStudent();
        void deleteStudent();
        void addFaculty();
        void deleteFaculty();
        void changeAdvisor();
        void removeAdvisee();
        void rollback();
        void outputToFile();
};
#endif