#include "Database.h"

//constructor
Database::Database(){
    fp = new FileProcessor();//make file processor
    masterStudent = fp->processStudentFile();//get bst for students from file processor
    masterFaculty = fp->processFacultyFile();//get bst for faculty from file processor
    if(!masterStudent->isEmpty() && masterFaculty->isEmpty()){//if there are students but no faculty
        delete masterStudent;//impossible due to referential integrity, so delete the database and start over
        masterStudent = new BST<Student>();
    }
    else if(masterStudent->isEmpty() && !masterFaculty->isEmpty()){//if faculty but no students
        emptyAdviseeList(masterFaculty->root);//ensure all of the advisee lists are empty
    }
    rollbackStack = new GenStack<DBTransaction*>();//make a new stack for rollback
    rollbackCount = 0;//make the rollback count 0
}
//destructor
Database::~Database(){
    recursivelyDeleteFacultyAdvisees(masterFaculty->root);//delete the linked lists that the faculty have since dynamically allocated
    delete masterFaculty;//delete the faculty bst
    delete masterStudent;//delete the student bst
    delete fp;//delete the fileprocessor
    while(!rollbackStack->isEmpty()){//delete everything on the rollback stack
        DBTransaction *rb = rollbackStack->pop();//access any transactions still on the stack
        if(!rb->isStudent && !rb->isUpdate){//if it wasn't a student or update (it was faculty)
            delete rb->faculty->advisees;//delete the list of advisees that was dynamically allocated
        }
        delete rb;
    }
    delete rollbackStack;//then delete the rollback stack
}
//starts the database loop and runs until the user decides to quit
void Database::RunDatabase(){
    int menuChoice = 0;
    while(menuChoice != 14){//loop until the user selects exit
        printMenu();//print out the menu options
        menuChoice = getUserInput(1, 14);//prompt the user for their selection
        switch(menuChoice){//call the method corresponding to the selection number
            case 1:{
                printStudents();
                break;
            }
            case 2:{
                printFaculty();
                break;
            }
            case 3:{
                printIndividualStudent();
                break;
            }
            case 4:{
                printIndividualFaculty();
                break;
            }
            case 5:{
                printStudentAdvisor();
                break;
            }
            case 6:{
                printFacultyAdvisees();
                break;
            }
            case 7:{
                addStudent();
                break;
            }
            case 8:{
                deleteStudent();
                break;
            }
            case 9:{
                addFaculty();
                break;
            }
            case 10:{
                deleteFaculty();
                break;
            }
            case 11:{
                changeAdvisor();
                break;
            }
            case 12:{
                removeAdvisee();
                break;
            }
            case 13:{
                rollback();
                break;
            }
            case 14:{
                outputToFile();
                break;
            }
            default:{
                break;
            }
        }
    }
}
//just prints out the main menu options to the user
void Database::printMenu(){
    cout << endl << "Type in the number of the option below that you would like:" << endl;
    cout << "1.  Print all students and their information (sorted by ascending id #)" << endl;
    cout << "2.  Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << "3.  Find and display student information given the students id" << endl;
    cout << "4.  Find and display faculty information given the faculty id" << endl;
    cout << "5.  Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "6.  Given a faculty id, print ALL the names and info of his/her advisees" << endl;
    cout << "7.  Add a new student" << endl;
    cout << "8.  Delete a student given the id" << endl;
    cout << "9.  Add a new faculty member" << endl;
    cout << "10. Delete a faculty member given the id" << endl;
    cout << "11. Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "12. Remove an advisee from a faculty member given the ids" << endl;
    cout << "13. Rollback (" << rollbackCount << " available)" << endl;
    cout << "14. Exit" << endl;
    cout << "Selection: " << flush;
}

//takes a maximum and minimum integer the user can enter, and loops until they enter something in the range, returning their input as an int
int Database::getUserInput(int min, int max){
    int temp = -99999999;
    while(temp < min || temp > max){//loop while they didn't enter something in the bounds
        temp = getUserInput();//same method but without bounds, just gets any integer
        if(temp < min || temp > max)
            cout << "Invalid selection. Try again: " << flush;
    }
    return temp;//return the value that they entered
}

//gets an integer from the user and returns it
int Database::getUserInput(){
    string s = "";//initialize the temporary parsing string to empty
    int i = -99999999;
    while(i == -99999999){//loop while the user didn't put in something that can be converted to integer
        getline(cin, s);//get the users direct input
        try{
            i = stoi(s);//try to convert to an integer
        }
        catch (exception &error){//if failed, print error message prompting them again
            cout << "Invalid selection. Try again: " << flush;
        }
    }
    return i;//return the integer they submitted
}

//gets a double from the user input and returns it
double Database::getUserDouble(){
    string s = "";//initalize parsing string to empty
    double d = -99999999;//initalize the double to a value
    while(d == -99999999){//loop while there wasn't a value put in that is convertable to double
        getline(cin, s);//get the user input
        try{
            d = stod(s);//try converting to double
        }
        catch (exception &error){//if failed print out an error message
            cout << "Invalid selection. Try again: " << flush;
        }
    }
    return d;//when eventually a valid double is input, return it
}

//prints out the student BST
void Database::printStudents(){
    if(masterStudent->isEmpty()){//print out a message if the BST is empty
        cout << "No students found in the database." << endl;
    }
    masterStudent->print();//print out the BST to the user (sorted by ID)
}

//prints out the faculty BST
void Database::printFaculty(){
    if(masterFaculty->isEmpty()){//print out a message if faculty BST is empty
        cout << "No faculty found in the database." << endl;
    }
    masterFaculty->print();//print out the faculty in order by ID
}

//prints out the information of a student once ID is prompted for
void Database::printIndividualStudent(){
    cout << "Enter the student id for the student whose information you would like displayed: " << flush;
    int tempInt = getUserInput();//get the ID from the user
    try{
        cout << masterStudent->search(tempInt) << endl;//search the BST for that ID and print it
    }
    catch(exception &e){//if the search failed (didn't find it), print that the student wasn't found
        cout << "Student with ID " << tempInt << " not found in the database." << endl;
    }
}

//prints out the information of a faculty once ID is prompted for
void Database::printIndividualFaculty(){
    cout << "Enter the faculty id for the faculty whose information you would like displayed: " << flush;
    int tempInt = getUserInput();//get the faculty ID to print out
    try{
        cout << masterFaculty->search(tempInt) << endl;//try to search the BST and print the information for that faculty
    }
    catch(exception &e){//if failed let the user know that the faculty wasn't found in the database
        cout << "Faculty with ID " << tempInt << " not found in the database." << endl;
    }
}

//prompts for the student ID to then search for their advisor to print out the information of
void Database::printStudentAdvisor(){
    cout << "Enter the student id for the student whose advisor's information you would like displayed: " << flush;
    int temp = getUserInput();//get the student ID from the user
    if(masterStudent->contains(temp)){//if the student is found in the database
        if(masterFaculty->contains(masterStudent->search(temp).advisor)){//and if the faculty advisor is found in the database
            cout << masterFaculty->search(masterStudent->search(temp).advisor) << endl;//search for the student to access the advisor to use the advisor ID to search and print the faculty
        }
        else{//if faculty wasn't found, print error message (this would indicate referential integrity violation)
            cout << "Faculty not found for student ID " << temp << "." << flush;
        }
    }
    else{//if the student wasn't found tell the user that the student with the ID wasn't found.
        cout << "Student with ID " << temp << " not found in the database." << endl;
    }
}

//prompts for faculty ID of whose students to print out and then prints them
void Database::printFacultyAdvisees(){
    cout << "Enter the faculty id for the faculty whose students information you would like displayed: " << flush;
    int temp = getUserInput();//get faculty ID from user
    if(!masterFaculty->contains(temp)){//if faculty isn't found, print error
        cout << "Faculty with ID " << temp << " not found in the database." << endl;
    }
    else{//otherwise, access the faculty
        Faculty tempFac = masterFaculty->search(temp);
        ListNode<int> *curr = tempFac.advisees->front;//get pointer to the front of the linked list
        if(curr == nullptr){//if the linked list is empty, then output a message indicating that there are no advisees.
            cout << "Faculty " << temp << " does not have any advisees." << endl;
        }
        while(curr != nullptr){//otherwise loop through and print out each student from the advisee list
            cout << masterStudent->search(curr->data) << endl;
            curr = curr->next;
        }
    }
}

//prompts for information for a student and then adds it to database
void Database::addStudent(){
    cout << "Enter the id of the student you wish to add: " << flush;
    int id = getUserInput();//get student ID from user
    if(masterStudent->contains(id)){//if that ID was already in the BST, abort so that no two students can share an ID
        cout << "A student with that ID already exists. Operation aborted." << endl;
        return;
    }
    //prompt for the rest of the student's information
    cout << "Enter the name of the student you wish to add: " << flush;
    string name;
    getline(cin, name);
    cout << "Enter the major of the student you wish to add: " << flush;
    string major;
    getline(cin, major);
    cout << "Enter the level of the student you wish to add: " << flush;
    string level;
    getline(cin, level);
    cout << "Enter the GPA of the student you wish to add: " << flush;
    double GPA = getUserDouble();
    cout << "Enter the id of the faculty advisor of the student you wish to add: " << flush;
    int advisor = getUserInput();
    //if their advisor they selected isn't found in the BST, give them options but loop until it is in the BST
    while(!masterFaculty->contains(advisor)){
        cout << "The advisor was not found in the database. Would you like to: " << endl;
        cout << "1. Add the advisor to the database." << endl;
        cout << "2. Change the student's advisor to a different faculty." << endl;
        cout << "3. Abort adding the student." << endl;
        cout << "Input the number indicating the option above you would like: " << flush;
        int temp = getUserInput(1, 3);//force them to choose from 1 to 3
        if(temp == 1){
            addFaculty(advisor);//add the faculty with the id (technically first, then the student afterwards)
        }
        else if(temp == 2){
            cout << "Enter the different id of the faculty advisor of the student you wish to add: " << flush;
            advisor = getUserInput();//prompt for a different advisor ID
        }
        else{
            return;//abort adding the student by exiting the method
        }
    }
    Student temp(id, name, level, major, GPA, advisor);//make the student
    masterStudent->insert(temp);//add it to the BST
    masterFaculty->search(advisor).addAdvisee(id);//add the student as an advisee to their faculty advisor's list
    DBTransaction *roll = new DBTransaction(true, temp);//make a record of the database change by passing in student and that it was an insertion
    rollbackStack->push(roll);//push the transaction on to the stack
    incrementRollbackCounter();//increment the number of available rollbacks
    cout << "Student successfully added to the database." << endl;//let the user know it was successful
}

//prompts for the ID of a student and then removes them from the database
void Database::deleteStudent(){
    cout << "Enter the id of the student you would like removed from the database: " << flush;
    int temp = getUserInput();//get the student ID to delete
    if(masterStudent->contains(temp)){//if the student is found
        masterFaculty->search(masterStudent->search(temp).advisor).removeAdvisee(temp);//remove them from their advisor's advisee list
        DBTransaction *roll = new DBTransaction(false, masterStudent->search(temp));//make a record of the deletion and pass in the student
        rollbackStack->push(roll);//add the record to the stack
        incrementRollbackCounter();//increment the number of available rollbacks
        masterStudent->deleteNode(temp);//remove the student from the BST
        cout << "Student " << temp << " sucessfully removed." << endl;
    }
    else{//if the student wasn't found, tell the user that it wasn't there to begin with
        cout << "Student with ID " << temp << " not found." << endl;
    }
}

//Prompts for the ID of the faculty, and if it is new, calls the other method that adds the faculty with the ID passed in
void Database::addFaculty(){
    cout << "Enter the id of the faculty that you wish to add: " << flush;
    int temp = getUserInput();//get the ID from the user
    if(masterFaculty->contains(temp)){//if it is already used, let the user know and abort
        cout << "A faculty with that ID already exists. Operation aborted." << endl;
        return;
    }
    addFaculty(temp);//otherwise add the faculty with the ID
}

//takes the faculty ID as an argument, prompts for remaining information, and then adds faculty to BST
void Database::addFaculty(int id){
    cout << "Enter the name of the faculty you wish to add: " << flush;
    string name;
    getline(cin, name);
    cout << "Enter the level of the faculty you wish to add: " << flush;
    string level;
    getline(cin, level);
    cout << "Enter the department of the faculty you wish to add: " << flush;
    string dept;
    getline(cin, dept);
    Faculty fac(id, name, level, dept);//make the faculty object
    cout << "Advisees will be added to the Faculty when the faculty is specified as the advisor of a student, or when explicity changed later." << endl;
    //adding students now as advisees, unless adding the students as we go, would lose referential integrity, so it isn't an option
    //adding students as the ID is given would become confusing if done a bunch, so the option isn't given
    masterFaculty->insert(fac);//put the faculty on the BST
    DBTransaction *roll = new DBTransaction(true, fac);//make a record of the BST change by passing in the faculty
    rollbackStack->push(roll);//add the record to the rollback options
    incrementRollbackCounter();//update the number of available rollbacks
    cout << "Faculty added successfully to the database." << endl;
}

//prompts for ID from the user and then removes that faculty
void Database::deleteFaculty(){
    cout << "Enter the id of the faculty that you wish to remove from the database: " << flush;
    int temp = getUserInput();//get the faculty ID to remove
    if(!masterFaculty->contains(temp)){//if the faculty isn't in the databse, let the user know
        cout << "Faculty with id " << temp << " not found in the database." << endl;
    }
    else{//otherwise, get access to a copy of the faculty
        Faculty fac = masterFaculty->search(temp);
        if(!fac.advisees->isEmpty()){//if the advisee list isn't empty, let the user know they can't remove the faculty as it would break referential integrity
            cout << "List of advisees is not empty, so faculty member cannot be removed yet." << endl;
        }
        else{//if here the faculty is ripe for removal
            DBTransaction *roll = new DBTransaction(false, masterFaculty->search(temp));//make a record of the transaction by passing in the faculty
            rollbackStack->push(roll);//store that record on the stack
            incrementRollbackCounter();//update the available rollbacks
            delete masterFaculty->search(temp).advisees;//delete the dynamically allocated advisee list
            masterFaculty->deleteNode(temp);//remove the faculty from the BST
            cout << "Faculty with id " << temp << " removed successfully." << endl;
        }
    }
}

//prompts the user for the student ID and new faculty advisor's ID so the change can be made
void Database::changeAdvisor(){
    cout << "Enter the id of the student whose advisor you would like to change: " << flush;
    int studID = getUserInput();//get student ID
    if(masterStudent->contains(studID)){//if student is in the DB
        cout << "Enter the id of the faculty who will become the new advisor: " << flush;
        int newFac = getUserInput();//get new faculty advisor
        if(masterFaculty->contains(newFac)){//if the faculty is also in the DB
            if(masterStudent->search(studID).advisor == newFac){
                return;//if the advisor they are changing to is the same as the old one, quit
            }
            DBTransaction *roll = new DBTransaction(masterStudent->search(studID).advisor, studID, newFac);//make a new transaction for rollback
            rollbackStack->push(roll);//put the transaction on the stack
            incrementRollbackCounter();//increment the available rollbacks
            masterFaculty->search(masterStudent->search(studID).advisor).removeAdvisee(studID);//remove the student as advisee from the old advisor
            Student tempStud = masterStudent->search(studID);//get access to the student
            masterStudent->deleteNode(studID);//remove the student from the BST (since you can't directly access the one on there to change it)
            Student newStud = Student(tempStud.ID, tempStud.name, tempStud.level, tempStud.major, tempStud.GPA, newFac);//make a new student with old info but new advisor
            masterStudent->insert(newStud);//put the new old student back on the BST
            masterFaculty->search(newFac).addAdvisee(studID);//add the student to the advisee list of the new faculty
            cout << "Advisor change made successfully." << endl;
        }
        else{//if faculty wasn't found, let the user know and abort
            cout << "Faculty " << newFac << " not found in the database." << endl;
        }
    }
    else{//if the student wasn't found, let the user know and abort
        cout << "Student " << studID << " not found in the database." << endl;
    }
}

//prompts the user for the faculty whose ID will be removed, then the student to be removed, then the new faculty where it should go to
void Database::removeAdvisee(){
    cout << "Enter the id of the faculty whose advisee you want removed: " << flush;
    int fac = getUserInput();//get the faculty ID for the one to be removed from
    if(masterFaculty->contains(fac)){//if that faculty is found
        cout << "Enter the id of the advisee that you would like removed: " << flush;
        int stud = getUserInput();//get the student to be removed from advisee list
        if(masterFaculty->search(fac).advisees->contains(stud)){//if the student was on the advisee list
            cout << "Since each student must have a faculty advisor," << endl;
            cout << "Enter the id of the faculty you would like the new advisor to be: " << flush;
            int newFac = getUserInput();//prompt the user for the new advisor to the student, since it must have one for referential integrity reasons
            if(!masterFaculty->contains(newFac)){//if the new faculty isn't found, abort the operation
                cout << "Faculty " << newFac << " not found. Operation aborted." << endl;
            }
            else{//at this point, both faculty and student are in the database, and the change can happen
                if(newFac == fac){//if the new advisor and old advisor are the same, quit and skip any changes
                    return;
                }
                masterFaculty->search(fac).removeAdvisee(stud);//remove the student from the old advisors list
                Student tempStud = masterStudent->search(stud);//get access to the student
                masterStudent->deleteNode(stud);//remove from the BST (since it can't be accessed to change a member variable when on the BST)
                Student newStud = Student(tempStud.ID, tempStud.name, tempStud.level, tempStud.major, tempStud.GPA, newFac);//make a new student with the old information and new advisor
                masterStudent->insert(newStud);//add the student back to the BST
                masterFaculty->search(newFac).addAdvisee(stud);//add the student to the new advisors list
                DBTransaction *roll = new DBTransaction(fac, stud, newFac);//create a new transaction for rollback
                rollbackStack->push(roll);//push the transaction onto the stack
                incrementRollbackCounter();//increment the rollback counter
                cout << "Advisee removal made successfully." << endl;
            }
        }
        else{//if the student isn't found, let the user know and abort
            cout << "Student " << stud << " was not an advisee of faculty " << fac << "." << endl;
        }
    }
    else{//if the faculty wasn't found, let the user know and abort
        cout << "Faculty " << fac << " not found in the database." << endl;
    }
}

//if called it will reverse whatever operations were just done (inserts or deletes to either BST)
void Database::rollback(){
    if(rollbackCount > 0){//if there is a rollback available to do
        DBTransaction *rb = rollbackStack->pop();//pop the rollback off the stack
        if(rb->isUpdate){//check if the operation was an insertion
            masterFaculty->search(rb->oldFacultyID).addAdvisee(rb->studentID);//add the student back to the old advisor
            masterFaculty->search(rb->newFacultyID).removeAdvisee(rb->studentID);//remove the student from the new advisor
            Student temp = masterStudent->search(rb->studentID);//get access to a copy of the student
            masterStudent->deleteNode(rb->studentID);//remove the student from the BST
            Student newStud = Student(temp.ID, temp.name, temp.level, temp.major, temp.GPA, rb->oldFacultyID);//make a copy of the new student but with the old advisor as advisor id
            masterStudent->insert(newStud);//put the student back in the BST
        }
        else if(rb->isInsertion){//if the operation done was an insertion
            if(rb->isStudent){//and if it was a student that was inserted (now we delete the student)
                masterFaculty->search(masterStudent->search(rb->student->ID).advisor).removeAdvisee(rb->student->ID);//remove the student from the advisors list
                masterStudent->deleteNode(rb->student->ID);//and then remove the student from the BST
            }
            else{//otherwise it was a faculty insertion, so now we delete the faculty
                delete masterFaculty->search(rb->faculty->ID).advisees;//delete the dynamically allocated faculty list
                masterFaculty->deleteNode(rb->faculty->ID);//and then remove the faculty from the BST
            }
        }
        else{//the operation done before was a deletion so now we reinsert what was removed
            if(rb->isStudent){//if the operation was done on a student, we now insert the student
                masterStudent->insert(*rb->student);//add the student to the BST
                masterFaculty->search(rb->student->advisor).addAdvisee(rb->student->ID);//add the student to their advisors list
            }
            else{//the operation done was deleting a faculty so now we insert the faculty
                masterFaculty->insert(*rb->faculty);
            }
        }
        delete rb;//the record is no longer needed, so the dynamically allocated record can be removed
        --rollbackCount;//decrement the amount of rollbacks available
        cout << "Successful rollback. " << rollbackCount << " more are available." << endl;//indicate that it was successful
    }
    else{//if there were no available rollbacks, let the user know
        cout << "No rollbacks available." << endl;
    }
}

//prints out the BST's to a file, with one person on each line
void Database::outputToFile(){
    fp->outputToFile("facultyTable", masterFaculty->preOrderPrint());//print the faculty to facultyTable
    fp->outputToFile("studentTable", masterStudent->preOrderPrint());//print the student to studentTable
}

//increments the rollback counter if the value was less than 5, does nothing otherwise
void Database::incrementRollbackCounter(){
    if(rollbackCount < 5){
        ++rollbackCount;
    }
}

//recursively deletes the advisor's dynamically allocated linked list of advisees given a treenode
void Database::recursivelyDeleteFacultyAdvisees(TreeNode<Faculty>* curr){
    if(curr == nullptr){//if a null leaf is reached, stop recursive calls
        return;
    }
    recursivelyDeleteFacultyAdvisees(curr->left);//delete the left childs
    recursivelyDeleteFacultyAdvisees(curr->right);//delete the right childs
    delete curr->object.advisees;//delete the current node's advisee list
}
//takes a pointer to a tree node and ensures all faculty advisee lists are empty for case when student file isn't found
void Database::emptyAdviseeList(TreeNode<Faculty>* curr){
    if(curr == nullptr){
        return;
    }
    emptyAdviseeList(curr->left);
    emptyAdviseeList(curr->right);
    while(!curr->object.advisees->isEmpty()){//empty out the advisee list
        curr->object.advisees->removeFront();
    }
}