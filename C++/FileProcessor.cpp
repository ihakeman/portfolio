#include "FileProcessor.h"

//constructor
FileProcessor::FileProcessor(){
  currentLine = "";//initialize the currentLine to an empty string
}

//destructor
FileProcessor::~FileProcessor(){
  //nothing dynamically allocated, nothing to delete
}

//reads from input file, makes a BST, creates and adds the students read from the file, then returns the BST pointer
BST<Student>* FileProcessor::processStudentFile(){
  inputFS.open("studentTable");//try to open the inputfile
  if(!inputFS.is_open()){//check to ensure the file has opened, give an error if not
      cout << "No student database found on file." << endl;
      BST<Student> *masterStudent = new BST<Student>(); //make an empty BST to return
      return masterStudent;
  }
  else{//file is open
    DoublyLinkedList<string>* attributes;//make a linked list pointer for the strings (lines) read from the file
    BST<Student> *masterStudent = new BST<Student>();//make a new BST of student objects
    //loop until an error occurs or there is no more input to read (both are fail conditions)
    while(!inputFS.fail()) {//while an error in reading hasn't occurred,
      getline(inputFS, currentLine);//scan in a line to the current line string from the input file
      if(currentLine == ""){//if a line is empty, stop reading the file
        break;
      }
      attributes = parseLine(currentLine);//get the line broken into a linked list containing attributes for the student object
      try{//try to make the student (if not formatted properly in the file it will throw an exception)
        int id = stoi(attributes->removeFront());//get id as a string and convert it to integer
        string name = attributes->removeFront();//get name as a string
        string major = attributes->removeFront();//get major as a string
        string level = attributes->removeFront();//get level as a string
        double GPA = stod(attributes ->removeFront());//get GPA as a string and convert to double
        int advisor = stoi(attributes->removeFront());//get advisor id as a string and convert to int
        Student temp = Student(id, name, major, level, GPA, advisor);//make the student object with all of the above information
        masterStudent->insert(temp);//put the student into the BST
        delete attributes;//delete the now empty linked list that was dynamically allocated by parseline
      }
      catch(exception &e){//if there was an error reading any of the students
        delete masterStudent;//delete the BST containing the students
        cout << "Invalid student information found in studentTable, reading in aborted." << endl;//give error message
        BST<Student> *empty = new BST<Student>();//make a new empty BST to return
        inputFS.close();//close the file stream
        return empty;//return the empty BST, breaking the loop of reading
      }
    }
    if(!inputFS.eof()){//if an error occurs before reaching the end of the input file, display an error message
      cout << "Input failure before reaching the end of the file." << endl;
    }
    inputFS.close();//close the file stream
    return masterStudent;//return the list of students
  }
}

//reads from input file, makes a BST, creates and adds the faculty read from the file, then returns the BST pointer
BST<Faculty>* FileProcessor::processFacultyFile(){
  inputFS.open("facultyTable");//try to open the inputfile
  if(!inputFS.is_open()){//check to ensure the file has opened, give an error if not
      cout << "No faculty database found on file." << endl;
      BST<Faculty> *masterFaculty = new BST<Faculty>(); //make an empty BST to return
      return masterFaculty;
  }
  else{
    DoublyLinkedList<string>* attributes;//make a linked list pointer for strings of faculty attributes made in parseline
    BST<Faculty> *masterFaculty = new BST<Faculty>();//instantiate a BST to put the faculty on
    //loop until and error occurs or there is no more input to read (both are fail conditions)
    while(!inputFS.fail()) {//while an error in reading hasn't occurred,
      getline(inputFS, currentLine);//scan in a line to the current line string from the input file
      if(currentLine == ""){//if an empty line is reached, stop reading from the file
        break;
      }
      attributes = parseLine(currentLine);//break up the string of faculty information into attributes stored as a linked list
      try{//try in case formatted wrong and incompatible types
        int id = stoi(attributes->removeFront());//get string id from linked list and convert to int
        string name = attributes->removeFront();
        string level = attributes->removeFront();
        string department = attributes->removeFront();
        Faculty temp = Faculty(id, name, level, department);//instantiate the faculty object with the information
        int loop = stoi(attributes->removeFront());//get the number of advisees that the faculty has
        for(int i = 0; i < loop; ++i){//loop for the number of advisees
          int tempI = stoi(attributes->removeFront());//convert to integer the string containing the id from the linked list
          temp.addAdvisee(tempI);//add the advisee to their linked list of integers
        }
        masterFaculty->insert(temp);//insert the faculty to the BST
        delete attributes;//delete the linked list of strings dynamically allocated in the parseline function
      }
      catch(exception &e){//if an error occurs in the above parsing
        delete masterFaculty;//delete the BST with the faculty since it was dynamically allocated
        cout << "Invalid faculty information found in facultyTable, reading in aborted." << endl;//print error message
        BST<Faculty> *empty = new BST<Faculty>();//make a new empty BST to return
        inputFS.close();//close the file stream
        return empty;//return the empty BST aborting any more reading
      }
    }
    if(!inputFS.eof()){//if an error occurs before reaching the end of the input file, display an error message
      cout << "Input failure before reaching the end of the file." << endl;
    }
    inputFS.close();//close the file stream
    return masterFaculty;//return the BST full of faculty
  }
}

//takes a string as an argument and returns a linked list with the string broken down into different substrings
DoublyLinkedList<string>* FileProcessor::parseLine(string line){
  DoublyLinkedList<string> *attributes = new DoublyLinkedList<string>();//make the new linked list to return
  string currAttribute = "";//assign the temporary string to empty
  for(int i = 0; i < line.length(); ++i){//loop through each character in the line string
    if(line[i] == '`' && line[i+1] == '$' && line[i+2] == '`'){//if the current and next two characters are `$`
      i += 2;//increment the loop variable to skip the next two characters
      attributes->insertBack(currAttribute);//add the string with the current attribute to the linked list
      currAttribute = "";//reset the temporary string
    }
    else{//if not `$`, add the current character to the temporary string
      currAttribute = currAttribute + "" + line[i];
    }
  }
  return attributes;//return the linked list now full of strings
}

//takes output file name and pointer to linked list of string to output as input, writes the strings to output file
void FileProcessor::outputToFile(string outputFile, DoublyLinkedList<string> *outputList){
  outputFS.open(outputFile);//try to open the inputfile
  if(!outputFS.is_open()){//check to ensure the file has opened, give an error if not
    if(outputFile == "facultyTable")//if printing faculty and couldn't open
      cout << "Could not open file to save faculty database." << endl;
    else if(outputFile == "studentTable"){//if printing students and couldn't open
      cout << "Could not open file to save student database." << endl;
    }
  }

  else{//file is open
    while(!outputList->isEmpty()) {//while the list to print isn't empty
      outputFS << outputList->removeFront() << endl;//print out the string and newline to output file
    }
  }
  outputFS.close();//close the output stream
}
