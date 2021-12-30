#include <fstream>//needed for input and output streams in methods
#include <iostream>
#include "DoublyLinkedList.h"
#include "BST.h"
#include "Student.h"
#include "Faculty.h"
using namespace std;
class FileProcessor{
  public:
    //constructor/destructor
    FileProcessor();
    ~FileProcessor();

    //core functions
    BST<Faculty>* processFacultyFile();
    BST<Student>* processStudentFile();
    DoublyLinkedList<string>* parseLine(string line);
    void outputToFile(string outputFile, DoublyLinkedList<string> *outputList);
  private:
    string currentLine;//the current line of the inputfile that has been read
    ifstream inputFS;//input and output file streams are member variables so all methods can access
    ofstream outputFS;
};
