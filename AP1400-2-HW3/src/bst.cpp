#include "bst.h"
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>


BST::BST() : root(nullptr) {}

BST::BST(std::initializer_list<int> list) : root(nullptr) {
  for (auto val : list) {
    this->add_node(val);
  }
}

BST::BST(Node* root) : root(root) {}

// copy constructor
BST::Node* copy_node(BST::Node* node) {
  if (node == nullptr) return nullptr;
  BST::Node* new_node = new BST::Node(*node);
  new_node->left = copy_node(node->left);
  new_node->right = copy_node(node->right);
  return new_node;
}

BST::BST(const BST& other) {
  this->root = copy_node(other.root);
}

// move constructor
BST::BST(BST&& other) : root(other.root) {
  other.root = nullptr;
}

// copy assignment operator
BST& BST::operator=(const BST& other) {
  if (this == &other) {
    return *this;
  }
  this->root = copy_node(other.root);
  return *this;
}

BST& BST::operator=(BST&& other) {
  if (this == &other) {
    return *this;
  }
  delete this->root;
  this->root = other.root;
  other.root = nullptr;
  return *this;
}

BST::~BST() {
  std::vector<Node*> nodes;
  bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
  for (auto& node : nodes)
    delete node;
}

BST::Node*& BST::get_root () {
  return this->root;
}

void BST::bfs(std::function<void(Node*& node)> func) {
  if (!this->root) return;

  std::queue<Node*> q;
  q.push(this->root);
  while (!q.empty()) {
    Node* curr = q.front(); q.pop();
    func(curr);
    if (curr->left) q.push(curr->left);
    if (curr->right) q.push(curr->right);
  }
}

size_t BST::length() const {
  if (!this->root) return 0;

  int length = 0;
  std::queue<Node*> q;
  q.push(this->root);
  while (!q.empty()) {
    Node* curr = q.front(); q.pop();
    ++length;
    if (curr->left) q.push(curr->left);
    if (curr->right) q.push(curr->right);
  }
  return length;
}

bool BST::add_node(int value) {
  if (!this->root) {
    this->root = new Node(value, nullptr, nullptr);
    return true;
  }
  Node* curr = root;
  while (true) {
    if (curr->value == value) {
      return false;
    }
    else if (curr->value > value) {
      if (curr->left) curr = curr->left;
      else {
        curr->left = new Node(value, nullptr, nullptr);
        return true;
      }
    }
    else {
      if (curr->right) curr = curr->right;
      else {
        curr->right = new Node(value, nullptr, nullptr);
        return true;
      }
    }
  }
}

BST::Node** BST::find_node(int value) {
  if (!this->root) return nullptr;
  Node** curr_ptr = &root;
  while (*curr_ptr) {
    Node* curr = *curr_ptr;
    if (curr->value == value) {
      return curr_ptr;
    }
    else if (curr->value > value) {
      curr_ptr = &(curr->left);
    }
    else {
      curr_ptr = &(curr->right);
    }
  }
  return nullptr;
}

BST::Node** BST::find_parrent(int value) {
  if (!this->root) return nullptr;
  Node** curr_ptr = &root, **prev_ptr;
  while (curr_ptr) {
    Node* curr = *curr_ptr;
    if (curr->value == value) {
      return prev_ptr;
    }
    else if (curr->value > value) {
      prev_ptr = curr_ptr;
      curr_ptr = &(curr->left);
    }
    else {
      prev_ptr = curr_ptr;
      curr_ptr = &(curr->right);
    }
  }
  return nullptr;
}

// according to the unit_test, successor means the largest child in left subtree
BST::Node** BST::find_successor(int value) {
  if (!this->root) return nullptr;
  Node** curr_ptr = find_node(value);
  Node* curr = *curr_ptr;
  if (!(*curr_ptr)->left) return nullptr;

  Node** child_ptr = &(curr->left);
  Node* child = *child_ptr;
  while (child->right) {
    child_ptr = &(child->right);
    child = *child_ptr;
  }
  return child_ptr;
}

bool BST::delete_node(int value) {
  if (!this->root) return false;
  Node** curr_ptr = find_node(value);
  if (!curr_ptr) return false;
  if (*curr_ptr == root) {
    Node** child_ptr = find_successor(value);
    Node* child = *child_ptr;
    Node** child_parent_ptr = find_parrent(child->value);
    Node* child_parent = *child_parent_ptr;
    if (child_parent->left == child) child_parent->left = nullptr;
    else child_parent->right = nullptr;
    child->left = root->left;
    child->right = root->right;
    root = child;
    return true;
  }
  Node** parent_ptr = find_parrent(value);
  Node* curr = *curr_ptr, *parent = *parent_ptr;
  bool is_left_child;
  if (parent->left == curr) is_left_child = true;
  else is_left_child = false;
  if (!curr->left) {  // has only right child
    if (is_left_child) parent->left = curr->right;
    else parent->right = curr->right;
    return true;
  }
  else if (!curr->right) {  // has only left child
    if (is_left_child) parent->left = curr->left;
    else parent->right = curr->left;
    return true;
  }
  else {  // has both children
    Node** child_ptr = find_successor(value);
    Node* child = *child_ptr;
    Node** child_parent_ptr = find_parrent(child->value);
    Node* child_parent = *child_parent_ptr;
    if (child_parent->left == child) child_parent->left = nullptr;
    else child_parent->right = nullptr;
    child->left = curr->left;
    child->right = curr->right;
    if (is_left_child) parent->left = child;
    else parent->right = child;
    return true;
  }
  return false;
}

BST& BST::operator++() {
  auto add_one = [](Node*& node) -> void {
    if (!node) return;
    ++node->value;
  };
  bfs(add_one);
  return *this;
}

BST BST::operator++(int) {
  auto copy(*this);
  ++(*this);
  return copy;
}

std::ostream& operator<<(std::ostream& os, BST& bst) {
  if (bst.get_root() == nullptr) return os;
  os << std::string("*", 80) << '\n';
  std::queue<BST::Node*> q;
  q.push(bst.get_root());

  while (!q.empty()) {
    BST::Node* curr = q.front(); q.pop();
    os << *curr;
    if (curr->left) q.push(curr->left);
    if (curr->right) q.push(curr->right);
  }
  os << "binary search tree size: " << bst.length() << "\n";
  os << std::string('*', 80) << '\n';
  return os;
}

BST::Node::Node(int value, Node* left, Node* right) :
  value(value), left(left), right(right) {}

BST::Node::Node() : value(0), left(nullptr), right(nullptr) {}

BST::Node::Node(const Node& node) : value(node.value), left(node.left), right(node.right) {}

std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
  os << &node << "   => value:" << std::setw(2) << node.value << "   left:";
  if (node.left) os << node.left << "   ";
  else os << "0                ";
  os << "right:";
  if (node.right) os << node.right << "   \n";
  else os << "0          \n";
  return os;
}

bool operator<(const BST::Node& node, int val) {
  return node.value < val;
}
bool operator<=(const BST::Node& node, int val) {
  return node.value <= val;
}
bool operator>(const BST::Node& node, int val) {
  return node.value > val;
}
bool operator>=(const BST::Node& node, int val) {
  return node.value >= val;
}
bool operator==(const BST::Node& node, int val) {
  return node.value == val;
}
bool operator<(int val, const BST::Node& node) {
  return val < node.value;
}
bool operator<=(int val, const BST::Node& node) {
  return val <= node.value;
}
bool operator>(int val, const BST::Node& node) {
  return val > node.value;
}
bool operator>=(int val, const BST::Node& node) {
  return val >= node.value;
}
bool operator==(int val, const BST::Node& node) {
  return val == node.value;
}
