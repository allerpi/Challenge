#include "TreeNode.h"

template <typename T>
TreeNode<T>::TreeNode() {
    value = NULL;
    right = NULL;
    left = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T val) {
    value = val;
    right = NULL;
    left = NULL;
}

template <typename T>
TreeNode<T>::TreeNode(T val, TreeNode<T>* left, TreeNode<T>* right) {
    value = val;
    this->right = right;
    this->left = left;
}

template <typename T>
TreeNode<T>::~TreeNode() {}

template <typename T>
void TreeNode<T>::set_value(T new_value) { value = new_value; }

template <typename T>
void TreeNode<T>::set_right(TreeNode* new_right) { right = new_right; }

template <typename T>
void TreeNode<T>::set_left(TreeNode* new_left) { left = new_left; }

template <typename T>
T TreeNode<T>::get_value() { return value; }

template <typename T>
TreeNode<T>* TreeNode<T>::get_right() { return right; }

template <typename T>
TreeNode<T>* TreeNode<T>::get_left() { return left; }