#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief Node structure for the Binary Search Tree.
 * @tparam KeyType Type of the key.
 * @tparam ValueType Type of the value.
 */
template <typename KeyType, typename ValueType>
struct Node {
    KeyType key;
    ValueType value;
    Node* left;
    Node* right;

    Node(const KeyType& k, const ValueType& v)
        : key(k), value(v), left(nullptr), right(nullptr) {}
};

/**
 * @brief Binary Search Tree class.
 * @tparam KeyType Type of the key.
 * @tparam ValueType Type of the value.
 */
template <typename KeyType, typename ValueType>
class BinarySearchTree {
private:
    Node<KeyType, ValueType>* root;

    // insertion, retrieval, deletion, and traversal functions
    Node<KeyType, ValueType>* insert(Node<KeyType, ValueType>* node, const KeyType& key, const ValueType& value);
    Node<KeyType, ValueType>* search(Node<KeyType, ValueType>* node, const KeyType& key) const;
    Node<KeyType, ValueType>* remove(Node<KeyType, ValueType>* node, const KeyType& key);
    void inorder_traversal(Node<KeyType, ValueType>* node, std::vector<std::string>& log) const;
    // frees memory after program ends
    void destroy_tree(Node<KeyType, ValueType>* node);

public:
    /**
     * @brief Constructor for Binary Search Tree.
     */
    BinarySearchTree() : root(nullptr) {}
    /**
     * @brief Destructor for Binary Search Tree.
     * Calls the destroy_tree function.
     */
    ~BinarySearchTree();

    /**
     * @brief Inserts a key-value pair into the Binary Search Tree.
     * @param key Key to be inserted.
     * @param value Value associated with the key.
     */
    void insert(const KeyType& key, const ValueType& value);

    /**
     * @brief Retrieves the value associated with a key from the Binary Search Tree.
     * @param key Key to be searched for.
     * @param result Output parameter to store the retrieved value.
     * @return 0 if successful, -1 if the key is not found.
     */
    int get(const KeyType& key, ValueType& result) const;

     /**
     * @brief Removes a key-value pair from the Binary Search Tree.
     * @param key Key to be removed.
     * @return 0 if successful, -1 if the key is not found.
     */
    int del(const KeyType& key);

    /**
     * @brief Updates the value associated with a key in the Binary Search Tree.
     * @param key Key to be updated.
     * @param value New value to be associated with the key.
     * @return 0 if successful, -1 if the key is not found.
     */
    int update(const KeyType& key, const ValueType& value);

    /**
     * @brief Retrieves the log of key-value pairs from an in-order traversal of the Binary Search Tree.
     * @return Vector containing the log.
     */
    std::vector<std::string> get_log() const;
};

// deconstructor
template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::~BinarySearchTree() {
    destroy_tree(root);
}

// frees memory
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::destroy_tree(Node<KeyType, ValueType>* node) {
    if (node != nullptr) {
        destroy_tree(node->left);
        destroy_tree(node->right);
        delete node;
    }
}

// insert into bst
template <typename KeyType, typename ValueType>
Node<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::insert(Node<KeyType, ValueType>* node, const KeyType& key, const ValueType& value) {
    if (node == nullptr) return new Node<KeyType, ValueType>(key, value); // root
    
    if (key < node->key) node->left = insert(node->left, key, value); // less than, insert left
    else if (key > node->key) node->right = insert(node->right, key, value); // greater than, insert right
    else node->value = value; // dupe key
    
    return node;
}

// search in bst
template <typename KeyType, typename ValueType>
Node<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::search(Node<KeyType, ValueType>* node, const KeyType& key) const {
    if (node == nullptr || node->key == key) return node; // dupe or null
    
    if (key < node->key) return search(node->left, key); // less than, search left
    else return search(node->right, key); // else search right

}

// delete in bst
template <typename KeyType, typename ValueType>
Node<KeyType, ValueType>* BinarySearchTree<KeyType, ValueType>::remove(Node<KeyType, ValueType>* node, const KeyType& key) {
    if (node == nullptr) return node;
    
    if (key < node->key) node->left = remove(node->left, key); // search left
    else if (key > node->key) node->right = remove(node->right, key); // search right
    else {
        // child handling
        if (node->left == nullptr) {
            Node<KeyType, ValueType>* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node<KeyType, ValueType>* temp = node->left;
            delete node;
            return temp;
        }

        Node<KeyType, ValueType>* temp = node->right;
        while (temp->left != nullptr) 
            temp = temp->left;
        
        node->key = temp->key;
        node->value = temp->value;
        node->right = remove(node->right, temp->key);
    }

    return node;
}

// insert into bst from kv store
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    root = insert(root, key, value);
}

// get from bst from kv store
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::get(const KeyType& key, ValueType& result) const {
    Node<KeyType, ValueType>* node = search(root, key);
    if (node != nullptr) {
        result = node->value;
        return 0; 
    } else return -1;
}

// del in bst from kv_store
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::del(const KeyType& key) {
    Node<KeyType, ValueType>* node = remove(root, key);
    if (node != nullptr) return 0; 
    else return -1; 
    
}

// updates bst from kv_store
template <typename KeyType, typename ValueType>
int BinarySearchTree<KeyType, ValueType>::update(const KeyType& key, const ValueType& value) {
    Node<KeyType, ValueType>* node = search(root, key);
    if (node != nullptr) {
        node->value = value;
        return 0; 
    } else return -1; 
    
}

// gets log, which is represented by the inorder traversal of the bst
template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::inorder_traversal(Node<KeyType, ValueType>* node, std::vector<std::string>& log) const {
    if (node != nullptr) {
        inorder_traversal(node->left, log);
        std::ostringstream oss;
        oss << "Key: " << node->key << ", Value: " << node->value;
        log.push_back(oss.str());
        inorder_traversal(node->right, log);
    }
}

// log getter implmentation
template <typename KeyType, typename ValueType>
std::vector<std::string> BinarySearchTree<KeyType, ValueType>::get_log() const {
    std::vector<std::string> log;
    inorder_traversal(root, log);
    return log;
}

#endif
