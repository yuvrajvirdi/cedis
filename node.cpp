#include "node.h"

Node::Node(const std::string& key, const std::string& value)
    : key(key), value(value), left(nullptr), right(nullptr) {}

std::string Node::get_key() const {
    return key;
}

std::string Node::get_value() const {
    return value;
}

void Node::set_value(const std::string& new_value) {
    value = new_value;
}

Node* Node::get_left_child() const {
    return left;
}

void Node::set_left_child(Node* leftChild) {
    left = leftChild;
}

Node* Node::get_right_child() const {
    return right;
}

void Node::set_right_child(Node* rightChild) {
    right = rightChild;
}

bool Node::has_left_child() const {
    return left != nullptr;
}

bool Node::has_right_child() const {
    return right != nullptr;
}

bool Node::is_leaf() const {
    return !has_left_child() && !has_right_child();
}

#include "node.h"

Node::Node(const std::string& key, const std::string& value)
    : key(key), value(value), left(nullptr), right(nullptr) {}

std::string Node::get_key() const {
    return key;
}

std::string Node::get_value() const {
    return value;
}

void Node::set_value(const std::string& new_value) {
    value = new_value;
}

Node* Node::get_left_child() const {
    return left;
}

void Node::set_left_child(Node* leftChild) {
    left = leftChild;
}

Node* Node::get_right_child() const {
    return right;
}

void Node::set_right_child(Node* rightChild) {
    right = rightChild;
}

bool Node::has_left_child() const {
    return left != nullptr;
}

bool Node::has_right_child() const {
    return right != nullptr;
}

bool Node::is_leaf() const {
    return !has_left_child() && !has_right_child();
}