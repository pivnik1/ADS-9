// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <vector>
#include  "tree.h"

std::vector<std::vector<char>> PMTree::getAllPerms() {
  std::vector<std::vector<char>> peres;
  std::vector<char> current;
  collectPerms(root_node, current, peres);
  return peres;
}

std::vector<char> getPerm1(PMTree& PMtree, int erin) {
  std::vector<std::vector<char>> allPerms = PMtree.getAllPerms();
  if (erin > 0 && erin <= allPerms.size()) {
    return allPerms[erin - 1];
  }
  return {};
}

std::vector<char> getPerm2(PMTree& PMtree, int erin) {
  int totalPerms = 1;
  int elementsCount = PMtree.root_node->child_node.size();
  for (int i = 1; i <= elementsCount; ++i) {
    totalPerms *= i;
  }
  if (erin < 1 || erin > totalPerms) {
    return {};
  }
  std::vector<int> factorials;
  int fact = 1;
  for (int i = 1; i <= elementsCount; ++i) {
    fact *= i;
    factorials.push_back(fact);
  }
  std::vector<char> result;
  PMNode* current_node = PMtree.root_node;
  erin--;
  while (true) {
    if (current_node->child_node.empty()) {
      break;
    }
    int numChild = current_node->child_node.size();
    int fact = (numChild == 1) ? 1 : factorials[numChild - 2];
    int index = erin / fact;
    if (index >= numChild) {
      return {};
    }
    result.push_back(current_node->child_node[index]->symbol);
    erin %= fact;
    current_node = current_node->child_node[index];
  }
  return result;
}
