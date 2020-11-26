// Created by Valeria Pineda on 20/10/2020
// Class that saves root of binary search tree, as well as
// other methods used in this non-linear data structure.

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class TreeNode {
private:
    T value;
    TreeNode<T>* right;
    TreeNode<T>* left;

public:
    // sets all values as null
    TreeNode() {
        value = NULL;
        right = NULL;
        left = NULL;
    };
    // sets left and right as null
    TreeNode(T val) {
        value = val;
        right = NULL;
        left = NULL;
    };
    TreeNode(T val, TreeNode<T>* left, TreeNode<T>* right) {
        value = val;
        this->right = right;
        this->left = left;
    };
    ~TreeNode() {};
    
    // setters
    void set_value(T new_value) { value = new_value; };
    void set_right(TreeNode<T>* new_right) { right = new_right; };
    void set_left(TreeNode<T>* new_left) { left = new_left; };

    // getters
    T get_value() { return value; };
    TreeNode<T>* get_right() { return right; };
    TreeNode<T>* get_left() { return left; };
};

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // does the actual recursive insertion
    TreeNode<T>* insert_node_recursive(TreeNode<T>* node, T value, bool (*compare)(T& a, T& b)) {
        // when there's no root node
        if(node == NULL) {
            return new TreeNode<T>(value);
        }
        T yeet = node->get_value();
        // goes to left subtree
        if((*compare)(yeet, value)) {
            node->set_left(insert_node_recursive(node->get_left(), value, compare));
        }
        // goes to right subtree
        else {
            node->set_right(insert_node_recursive(node->get_right(), value, compare));
        }
        // comes here when new node wasn't inserted
        return node;
    };

    // does the actual node deleting
    TreeNode<T>* delete_node(TreeNode<T>* node, int key) {
        // if node is not found
        if(node == NULL) {
            return node;
        }
        
        // goes to right subtree
        if(key > node->get_value()) {
            node->set_right(delete_node(node->get_right(), key));
        }
        // goes to left subtree
        else if(key < node->get_value()) {
            node->set_left(delete_node(node->get_left(), key));
        }
        // deletion time >:)
        else {
            // when there's only one or no child nodes
            if(node->get_left() == NULL) {
                TreeNode<T>* temp = node->get_right();
                delete node;
                // node to be set in place of deleted node
                return temp;
            }
            else if(node->get_right() == NULL) {
                TreeNode<T>* temp = node->get_left();
                delete node;
                // node to be set in place of deleted node
                return temp;
            }
            // node has two child nodes
            else {
                // get successor
                TreeNode<T>* temp = successor(node);

                // give node value of successor
                node->set_value(temp->get_value());

                // delete succesor node (so it's not circular)
                node->set_right(delete_node(node->get_right(), temp->get_value()));
            }
        }

        return node;
    };

    // does the actual printing
    void print_preorder(TreeNode<T>* node) {
        if(node != NULL) {
            cout << node->get_value() << " ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    };
    
    // do the actual stair-like printing
    void pretty_print_stairs(TreeNode<T>* node, bool left, string padding, int level) {
        // base step
        if(node != NULL) {
            // print out initial symbols depending on left/right
            cout << padding + (left ? "├──" : "└──") << node->get_value() << endl;
            
            // change padding of |
            padding += (level == 0 || !left ? "    " : "|   ");
            
            pretty_print_stairs(node->get_left(), true, padding, level+1);
            pretty_print_stairs(node->get_right(), false, padding, level+1);
        }
    };

    // does actual printing of n-amount of right-most nodes
    void tree_top(int n, int& curr, TreeNode<T>* node, vector<T>& list) {
        if(node != NULL && curr < n) {
            curr++;
            tree_top(n, curr, node->get_right(), list);
            list.push_back(node->get_value());
            tree_top(n, curr, node->get_left(), list);
        }
    };

public:
    // sets root as null
    BinarySearchTree() { root = NULL; };
    ~BinarySearchTree() {};

    // finds the node in O(log n) time (if tree is balanced)
    TreeNode<T>* find_node(T target) {
        TreeNode<T>* ptr = root;

        while(ptr != NULL) {
            // value was found on current node
            if(ptr->get_value() == target) {
                return ptr;
            }

            // go to right subtree if target is greater than ptr, otherwise the left
            ptr = target > ptr->get_value() ? ptr->get_right() : ptr->get_left();
        }

        // in case target value was not found
        return NULL;
    };

    // insert node using iteration
    bool insert_node(T value) {
        TreeNode<T>* ptr = root;
        TreeNode<T>* pre = NULL;

        // makes sure value isn't already in tree
        while(ptr != NULL) {
            if(ptr->get_value() == value) {
                return false;
            }
            pre = ptr;

            // go to right subtree if target is greater than ptr, otherwise the left
            ptr = value > ptr->get_value() ? ptr->get_right() : ptr->get_left();
        }

        TreeNode<T>* new_node = new TreeNode<T>(value);

        // in case there isn't anything before it
        if(pre == NULL) {
            root = new_node;
        }
        // if it's left node of predecessor
        else if(pre->get_value() > value) {
            pre->set_left(new_node);
        }
        // if it's right node of predecessor
        else{
            pre->set_right(new_node);
        }
        return true;
    };
    
    // insert node using recursion
    void insert_node_recursive(T value, bool (*compare)(T& a, T& b)) {
        root = insert_node_recursive(root, value, compare);
    };

    // returns successor node (to the right and then all to the left)
    TreeNode<T>* successor(TreeNode<T>* node) {
        // goes to right subtree
        TreeNode<T>* ptr = node->get_right();

        // goes to left subtree as long as node ptr has it
        while(ptr->get_left() != NULL) {
            ptr = ptr->get_left();
        }

        return ptr;
    };
    
    // searches for node with value and deletes it
    void delete_node(T value) {
        root = delete_node(root, value);
    };
    
    // print root node before child nodes
    void print_preorder() {
        print_preorder(root);
        cout << endl;
    };

    // prints in stair-like structure
    void pretty_print_stairs() {
        pretty_print_stairs(root, false, "", 0);
    };
    
    // returns 1 if nodes are siblings
    bool check_if_siblings(T one, T two) {
        // checks that values are different
        if(one != two) {
            TreeNode<T>* ptr = root;
            // checks if root has existing child nodes
            while(ptr->get_left() != NULL && ptr->get_right()){
                T lefty = ptr->get_left()->get_value();
                T righty = ptr->get_right()->get_value();
                
                // curent root has both nodes we're looking for
                if((lefty == one && righty == two) || (righty == one && lefty == two)) {
                    return true;
                }
                
                // goes to left subtree
                else if(ptr->get_value() > one) {
                    ptr = ptr->get_left();
                }

                // goes to right subtree
                else {
                    ptr = ptr->get_right();
                }
            }
        }

        return false;
    };

    // prints out the n amount of right-most nodes
    void tree_top(int n, vector<T>& list) {
        int i = 0;
        tree_top(n, i, root, list);
    };
};

#endif
