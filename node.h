#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
public:
    Node(const std::string& key, const std::string& value);

    std::string get_key() const;

    std::string get_value() const;
    void set_value(const std::string& value);

    Node* get_left_child() const;
    void set_left_child(Node* left_child);

    Node* get_right_child() const;
    void set_right_child(Node* right_child);

    bool has_left_child() const;
    bool has_right_child() const;
    bool is_leaf() const;

private:
    std::string key;
    std::string value;
    Node* left;
    Node* right;
};

#endif 