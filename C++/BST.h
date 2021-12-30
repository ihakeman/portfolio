#ifndef BST_H
#define BST_H
#include "TreeNode.h"
#include "DoublyLinkedList.h"

template <typename T>
class BST{
    private:
        //member variable
        DoublyLinkedList<string> *output;//linked list of objects in BST as strings (only updated upon preOrderPrint)
    public:
        //constructor/destructor
        BST();
        ~BST();

        //member variables
        TreeNode<T> *root;//pointer to root node

        //core functions
        void insert(T obj);
        bool contains(int key);
        T search(int key);
        bool deleteNode(int key);
        bool isEmpty();
        void destroyRecursively(TreeNode<T> *node);

        //auxiliary functions
        T getMin();
        T getMax();
        
        //helper functions
        TreeNode<T>* getSuccessor(TreeNode<T> *d);//this simplifies deleteNode a bit
        void recPrint(TreeNode<T> *node);//inorder
        void recPrintPreOrder(TreeNode<T> *node);
        DoublyLinkedList<string>* preOrderPrint();
        void print();//inorder
};

//defualt constructor
template <typename T>
BST<T>::BST(){
    root = nullptr;//set root to null
    output = new DoublyLinkedList<string>();//instantiate a new linked list for the output
}

//destructor
template <typename T>
BST<T>::~BST(){
    delete output; // delete the dynamically allocated output doublylinked list of strings
    //delete every node recursively starting with root
    destroyRecursively(root);
}
//takes a pointer to a tree node, and destroys the children of the node, then the node itself
template <typename T>
void BST<T>::destroyRecursively(TreeNode<T> *node){
    if(node != nullptr){//keep going until a null leaf is reached
        destroyRecursively(node->left);//destroy left child
        destroyRecursively(node->right);//destroy right child
        delete node;//delete the current node
    }
}
//prints the tree inorder to the user
template <typename T>
void BST<T>::print(){
    recPrint(root);//call recprint with the root node so the whole thing is printed
}
//takes a pointer to a tree node and recursively prints left child then node then right child
template <typename T>
void BST<T>::recPrint(TreeNode<T> *node){
    if(node == nullptr)//if a null leaf is reached, stop recursive calls
        return;

    recPrint(node->left);//print the left child
    cout << node->object << endl;//print the data in the current node
    recPrint(node->right);//print the right child
}

//returns a doublyLinkedList of strings with the nodes data in preorder (node before its children) so that when adding in the nodes later, root comes first and BST efficiency is maintained
template <typename T>
DoublyLinkedList<string>* BST<T>::preOrderPrint(){
    delete output;//delete the output linked list if it exists already, so we start fresh
    output = new DoublyLinkedList<string>();//make a new linked list to store the objects in as strings
    recPrintPreOrder(root);//call the recursive preorder print method to print out all the nodes starting with the root
    return output;//return the linked list pointer
}

//recursively adds strings to the output doublylinked list for each node, with parent then left child then right child
template <typename T>
void BST<T>::recPrintPreOrder(TreeNode<T> *node){
    if(node == nullptr)//if a null leaf is reached, return
        return;
    output->insertBack(node->object.toString());//insert the node to the doublylinked list as a string
    recPrintPreOrder(node->left);//recursive print left child
    recPrintPreOrder(node->right);//recursive print right child
}
//returns the smallest object in the tree
template <typename T>
T BST<T>::getMin(){
    TreeNode<T> *current = root;//start at the root node
    if(root == nullptr){//if root is null, throw an error since no minimum exists
        throw runtime_error("No minimum value due to empty BST.");
    }
    while(current->left != nullptr){//otherwise go to left child until it is null
        current = current->left;
    }
    return current->object;//return the object in the leftmost descendent
}
//returns the largest object in the tree
template <typename T>
T BST<T>::getMax(){
    TreeNode<T> *current = root;//start at the root
    if(root == nullptr){//if root is null throw an error, since no maximum exists
        throw runtime_error("No maximum value due to empty BST.");
    }
    while(current->right != nullptr){//go to right child until it is null
        current = current->right;
    }
    return current->object;//return the object at the right most descendent
}
//takes an object to be inserted into the bst and inserts it 
template <typename T>
void BST<T>::insert(T obj){
    TreeNode<T> *node = new TreeNode<T>(obj);//make a new node with the object passed in 
    if(root == nullptr){
        //we have an empty tree
        root = node;//make the root the new node since tree was empty
    }
    else{
        //its not an empty tree
        TreeNode<T> *current = root;
        TreeNode<T> *parent = nullptr;
        while(true){
            parent = current;
            if(node->object < current->object){//go left if new object is less than the one currently compared to
                current = current->left;
                if(current == nullptr){
                    //we found our insertion point
                    parent->left = node;
                    break;
                }
            }
            else{
                //we go right
                current = current->right;
                if(current == nullptr){
                    //we found our insertion point
                    parent->right = node;
                    break;
                }
            }
        }

    }
}

//returns true if an object is found in the tree with the same key
template <typename T>
bool BST<T>::contains(int key){
    if(root == nullptr){//if root is null, nothing is in the tree, so false
        return false;
    }
    else{
        //not an empty tree
        TreeNode<T> *current = root;//start at root and traverse
        while(current->object != key){//if not finding the object yet
            if(key < current->object){//if less than current object
                current = current->left;//go left
            }
            else{//otherwise go right
                current = current->right;
            }
            if(current == nullptr){//if null leaf is reached, not found so return false
                return false;
            }
        }
    }
    return true;//otherwise not a null leaf, so we found the object and can return true
}

//takes a integer key and returns the object if found
template <typename T>
T BST<T>::search(int key){
    if(root == nullptr){//if empty tree, throw error since object isn't found and can't return nullptr
        throw runtime_error("Not found in BST");
    }
    else{
        //not an empty tree
        TreeNode<T> *current = root;//start at root and traverse (same as contains algorithm)
        while(current->object != key){
            if(key < current->object){
                current = current->left;
            }
            else{
                current = current->right;
            }
            if(current == nullptr){//if null leaf is reached, throw error since not found and can't return nullptr
                throw runtime_error("Not found in BST");
            }
        }
        return current->object;//otherwise we found it and can return the object
    }
}

//returns a bool of if the tree is empty
template <typename T>
bool BST<T>::isEmpty(){
    return root == nullptr;
}

//takes an integer key and deletes the node with that key if it exists, returning a bool indicating if it was successful or not
template <typename T>
bool BST<T>::deleteNode(int key){
    if(isEmpty())//if empty tree, nothing to delete so return false
        return false;
    TreeNode<T> *parent = nullptr;//keep pointer to parent and current
    TreeNode<T> *current = root;//start at root node
    bool isLeftNode = true;
    while(current->object != key){//traverse the list looking for the key
        parent = current;//set parent to current
        if(key < current->object){//if key is less than current
            isLeftNode = true;
            current = current->left;//go left
        }
        else{//otherwise the node isn't a left node, and go right
            isLeftNode = false;
            current = current->right;
        }
        if(current == nullptr){
            return false;//if nullptr reached, not found in tree, so return false
        }
    }
    //at this point we have found the key/value, now lets proceed to delete this node
    //case: node to be deleted does not have children, AKA a leaf node
    if(current->left == nullptr && current->right == nullptr){
        if(current == root){//if the root and no children, make root null
            root = nullptr;
        }
        else if(isLeftNode){//or if is a left node, with no children, make parents pointer left to null
            parent->left = nullptr;
        }
        else{//or right node no children, make right pointer from parent null
            parent->right = nullptr;
        }
    }
    //case: node to be deleted has one child. Need to determine whether descendent is left or right
    else if(current->right == nullptr){
        //does not have a right child, must have left
        if(current == root){//if current is root, make the left child the root (since no right child)
            root = current->left;
        }
        else if(isLeftNode){//if the node to be deleted is a left node
            parent->left = current->left;//make parent's left child point to left child of deleting node
        }
        else{
            //node to be deleted is a right child
            parent->right = current->left;//point parent's right to the only child of the deleting node
        }
    }
    else if(current->left == nullptr){
        //does not have a left child, must have right
        if(current == root){//if node is root, make the only child the root
            root = current->right;
        }
        else if(isLeftNode){//if is a left child, then the parent's left pointer goes to the only child
            parent->left = current->right;
        }
        else{
            //node to be deleted is a right child
            parent->right = current->right;//the parent's right pointer goes to the only child
        }
    }
    else{
        //the node to be deleted has two children
        //we have to find the successor.
        TreeNode<T> *successor = getSuccessor(current); //current is the node to be deleted

        if(current == root)//make the successor the root, if the root is the one to be deleted
            root = successor;
        else if(isLeftNode){//otherwise move the successor to the point of the node to be deleted
            parent->left = successor;
        }
        else
            parent->right = successor;
        
        successor->left = current->left;//make the left pointer of the replacing node point to the child of the deleting node
    }
    delete current;//delete the current node
    return true;//return true since deletion was successful
}

//returns a pointer to the successor node of the node pointer passed in
template <typename T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T> *d){
    TreeNode<T> *sp = d;//successors parent
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;//get right child (successor must be greater than current)

    while(current != nullptr){//move down list as far left as possible until null leaf is reached
        sp = successor;
        successor = current;
        current = current->left;
    }
    if(successor != d->right){//if the successor isn't the node to be deleted's right child
        sp->left = successor->right;//part of deletion algorithm -- move the successor nodes right child to the its parent's left
        successor->right = d->right;//part of deletion algorithm -- the successor node moves to the point of the deletion node, so its right pointer goes to the deleting nodes right child
    }
    return successor;//return the successor nodes pointer
}

#endif