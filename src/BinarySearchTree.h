// Created by Valeria Pineda on 20/10/2020
// Class that saves root of binary search tree, as well as
// other methods used in this non-linear data structure.

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include <iostream>
#include <vector>
#include <string>
#include "TreeNode.h"

using namespace std;

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // does the actual recursive insertion
    TreeNode<T>* insert_node_recursive(TreeNode<T>* node, T value, bool (*compare)(T& a, T& b));

    // does the actual node deleting
    TreeNode<T>* delete_node(TreeNode<T>* node, int key);

    // does the actual printing
    void print_preorder(TreeNode<T>* node);
    
    // do the actual stair-like printing
    void pretty_print_stairs(TreeNode<T>* node, bool left, string padding, int level, int (*get)(T& a));

    // gets the actual top n nodes of the tree
    void tree_top(int n, int& curr, TreeNode<T>* node, vector<T>& list);

public:
    // sets root as null
    BinarySearchTree();
    ~BinarySearchTree();

    TreeNode<T>* get_root();

    // finds the node in O(log n) time (if tree is balanced)
    TreeNode<T>* find_node(T target);

    // insert node using iteration
    bool insert_node(T value);
    
    // insert node using recursion
    void insert_node_recursive(T value, bool (*compare)(T& a, T& b));

    // returns successor node (to the right and then all to the left)
    TreeNode<T>* successor(TreeNode<T>* node);
    
    // searches for node with value and deletes it
    void delete_node(T value);
    
    // print root node before child nodes
    void print_preorder();

    // prints in stair-like structure
    void pretty_print_stairs(int (*get)(T& a));

    // gets n values that have highest values
    void tree_top(int n, vector<T>& list);

};

#include "BinarySearchTree.cpp"

#endif
