# Database that holds Faculty and Students

## Directions for Compiling and Running
There is a Makefile accompanying the code that utilizes the g++ compiler which is what this code was written for and ran on. A docker container was also used for all testing and execution of this code. To use the Makefile, ensure that g++ is installed on your computer and navigate to the directory containing the Makefile. Run `make all` and then `./database.out`. Interaction with the database should be self explanatory.

## Notes

To see the the design specifications of the database, look at the Database_Specification pdf.

I wrote all of the classes by myself except for the data structures (List, ListNode, GenStack, BST, TreeNode). These classes were written in the Data Structures and Algorithms course and modified some as seen in [References](#references).

Notes about my database:

- Extra feature not in the specification: Rollback keeps track of updates (advisor changes) and will undo them when rollback is selected!

- When adding a student, if the faculty advisor id is not in the database, user is given option to add the faculty, choose a different one or abort. (if adding, the faculty addition is considered to be done before the student in the case of rollback, so immediately doing rollback would remove the student, and if done again would remove the faculty).
- When adding faculty, you don't get to assign students as advisees since this might cause errors to referential integrity, so changes to student advisors must be done through menu option 11 or 12. When students are added to the database and an advisor is given, they are added to the faculty's advisor list at that point.
- For advisee removal, must give a different faculty id for the student's advisor to become to preserve referential integrity.

## References
1. The textbook for overloading operators (<<, ==, !=)
2. Professor on help with getting the BST to work.
3. DoublyLinkedList class and ListNode class were modified by me from the one written in the course. BST and TreeNode from the course were modified by me to be template classes. Fileprocessor was created with help from the textbook. The GenStack class was unmodified from the one wrtten in the course.
4. https://docs.microsoft.com/en-us/cpp/standard-library/overloading-the-output-operator-for-your-own-classes?view=msvc-160 for overloading <<
5. https://www.cplusplus.com/reference/string/string/length/ to remember the string length function.
6. https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c for converting a double to a string (also used for integers).
7. Consulted some with fellow students although no code shared.
8. https://stackoverflow.com/questions/677632/different-methods-for-instantiating-an-object-in-c for instantiating objects on stack with overloaded constructors.
9. For help on getting rid of errors: https://www.cplusplus.com/forum/beginner/5734/ 