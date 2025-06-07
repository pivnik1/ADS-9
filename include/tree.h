// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <string>

class PMNode {
 public:
  char symbol;
  std::vector<PMNode*> child_node;
  explicit PMNode(char sym) : symbol(sym) {}
};

class PMTree {
 public:
  PMNode* root_node;
  explicit PMTree(const std::vector<char>& mass_elements) {
    root_node = buildTree(mass_elements);
  }
  ~PMTree() {
    deleteTree(root_node);
  }
  std::vector<std::vector<char>> getAllPerms();

 private:
  PMNode* buildTree(const std::vector<char>& remainingElements) {
    PMNode* node = new PMNode('\0');
    for (size_t i = 0; i < remainingElements.size(); ++i) {
      std::vector<char> newRemaining;
      for (size_t j = 0; j < remainingElements.size(); ++j) {
        if (j != i) {
          newRemaining.push_back(remainingElements[j]);
        }
      }
      PMNode* child = new PMNode(remainingElements[i]);
      if (!newRemaining.empty()) {
        PMNode* subtree = buildTree(newRemaining);
        child->child_node = subtree->child_node;
        delete subtree;
      }
      node->child_node.push_back(child);
    }
  return node;
}
  void deleteTree(PMNode* node) {
    if (node == 0) {
      return;
    }
    for (PMNode* child : node->child_node) {
      deleteTree(child);
    }
    delete node;
  }
  void collectPerms(PMNode* node, std::vector<char>& current,
    std::vector<std::vector<char>>& permutations) {
    if (node == nullptr) {
      return;
    }
    if (node->symbol != '\0') {
      current.push_back(node->symbol);
    }
    if (node->child_node.empty()) {
      permutations.push_back(current);
    } else {
      for (PMNode* child : node->child_node) {
        collectPerms(child, current, permutations);
      }
    }
    if (node->symbol != '\0') {
      current.pop_back();
    }
  }
};

  std::vector<char> getPerm1(PMTree&, int);
  std::vector<char> getPerm2(PMTree&, int);
#endif  // INCLUDE_TREE_H_
