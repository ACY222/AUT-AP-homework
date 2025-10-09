#ifndef BST_H
#define BST_H

#include <functional>
#include <initializer_list>

class BST {
public:
  class Node;
  // default constructor
  BST();
  BST(std::initializer_list<int>);
  BST(Node* root);
  // copy constructor
  BST(const BST& other);
  // move constructor
  BST(BST&& other);
  // copy assignment operator
  BST& operator=(const BST& other);
  // move assignment operator
  BST& operator=(BST&& other);
  // destructor
  ~BST();

  Node*& get_root ();
  void bfs(std::function<void(Node*& node)> func);
  size_t length() const;
  bool add_node(int value);
  Node** find_node(int value);
  Node** find_parrent(int value);
  Node** find_successor(int value);
  bool delete_node(int value);
  // operator ++
  BST& operator++();    // ++bst
  BST operator++(int);  // bst++
  friend std::ostream& operator<<(std::ostream& os, BST& bst);

private:
  Node* root;
};

std::ostream& operator<<(std::ostream& os, BST& bst);

class BST::Node {
public:
  Node(int value, Node* left, Node* right);
  Node();
  Node(const Node& node);

  int value;
  Node* left;
  Node* right;
};

std::ostream& operator<<(std::ostream& os, const BST::Node& node);

bool operator<(const BST::Node& node, int val);
bool operator<=(const BST::Node& node, int val);
bool operator>(const BST::Node& node, int val);
bool operator>=(const BST::Node& node, int val);
bool operator==(const BST::Node& node, int val);
bool operator<(int val, const BST::Node& node);
bool operator<=(int val, const BST::Node& node);
bool operator>(int val, const BST::Node& node);
bool operator>=(int val, const BST::Node& node);
bool operator==(int val, const BST::Node& node);

#endif //BST_H
