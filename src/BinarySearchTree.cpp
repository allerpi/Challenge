#include "BinarySearchTree.h"

template <typename T>
BinarySearchTree<T>::BinarySearchTree() {
    root = NULL;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::get_root() { return root; }

template <typename T>
TreeNode<T>* BinarySearchTree<T>::find_node(T target) {
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
}

template <typename T>
bool BinarySearchTree<T>::insert_node(T value) {
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
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert_node_recursive(TreeNode<T>* node, T value, bool (*compare)(T& a, T& b)) {
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
}

template <typename T>
void BinarySearchTree<T>::insert_node_recursive(T value, bool (*compare)(T& a, T& b)) {
    root = insert_node_recursive(root, value, compare);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::successor(TreeNode<T>* node) {
    // goes to right subtree
    TreeNode<T>* ptr = node->get_right();

    // goes to left subtree as long as node ptr has it
    while(ptr->get_left() != NULL) {
        ptr = ptr->get_left();
    }

    return ptr;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::delete_node(TreeNode<T>* node, int key) {
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
}

template <typename T>
void BinarySearchTree<T>::delete_node(T value) {
    root = delete_node(root, value);
}

template <typename T>
void BinarySearchTree<T>::print_preorder(TreeNode<T>* node) {
    if(node != NULL) {
        cout << node->get_value() << " ";
        print_preorder(node->get_left());
        print_preorder(node->get_right());
    }
}

template <typename T>
void BinarySearchTree<T>::print_preorder() {
    print_preorder(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::pretty_print_stairs(TreeNode<T>* node, bool left, string padding, int level, int (*get)(T& a)) {
    // base step
    if(node != NULL) {
        T yeet = node->get_value();
        // print out initial symbols depending on left/right
        cout << padding + (left ? "├──" : "└──") << (*get)(yeet) << endl;
        
        // change padding of |
        padding += (level == 0 || !left ? "    " : "|   ");
        
        pretty_print_stairs(node->get_left(), true, padding, level+1, get);
        pretty_print_stairs(node->get_right(), false, padding, level+1, get);
    }
}

template <typename T>
void BinarySearchTree<T>::pretty_print_stairs(int (*get)(T& a)) {
    pretty_print_stairs(root, false, "", 0, get);
}

template <typename T>
void BinarySearchTree<T>::tree_top(int n, int& curr, TreeNode<T>* node, vector<T>& list) {
    if(node != NULL && curr < n) {
        curr++;
        tree_top(n, curr, node->get_right(), list);
        list.push_back(node->get_value());
        tree_top(n, curr, node->get_left(), list);
    }
}

template <typename T>
void BinarySearchTree<T>::tree_top(int n, vector<T>& list) {
    int i = 0;
    tree_top(n, i, root, list);
}