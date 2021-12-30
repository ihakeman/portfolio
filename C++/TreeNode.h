#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

using namespace std;
template <typename T>
class TreeNode{
    public:
        //constructors//destructors
        TreeNode();
        TreeNode(T obj);
        ~TreeNode();
        //member variables
        T object;
        TreeNode* left;
        TreeNode* right;
};
template <typename T>
TreeNode<T>::TreeNode(){
    left = nullptr;//assign left and right children to null
    right = nullptr;
}
template <typename T>
TreeNode<T>::TreeNode(T obj){
    left = nullptr;//assign left and right children to null
    right = nullptr;
    object = obj;//assign the object passed in to the object stored in the node
}
template <typename T>
TreeNode<T>::~TreeNode(){
    left = nullptr;//set the left and right pointers to null since it should not have references to other nodes when being deleted
    right = nullptr;
}
#endif