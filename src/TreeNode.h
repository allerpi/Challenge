// Created by Valeria Pineda on 20/10/2020
// Class that defines a node of a binary search tree.

#ifndef TreeNode_h
#define TreeNode_h

#include <stdlib.h>

template <typename T>
class TreeNode {
private:
    T value;
    TreeNode<T>* right;
    TreeNode<T>* left;

public:
    // sets all values as null
    TreeNode();
    // sets left and right as null
    TreeNode(T val);
    TreeNode(T val, TreeNode<T>* left, TreeNode<T>* right);
    ~TreeNode();
    
    // setters
    void set_value(T new_value);
    void set_right(TreeNode<T>* new_right);
    void set_left(TreeNode<T>* new_left);

    // getters
    T get_value();
    TreeNode<T>* get_right();
    TreeNode<T>* get_left();
};

#include "TreeNode.cpp"

#endif