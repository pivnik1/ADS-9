// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <vector>
#include  <chrono>
#include  <iomanip>
#include "tree.h"

std::vector<char> generateAlphabet(int n) {
  std::vector<char> mass_alphabet;
  for (int i = 0; i < n; ++i) {
    mass_alphabet.push_back('A' + i);
  }
  return mass_alphabet;
}

template<typename Func>
double measureTime(Func func) {
  auto start_time = std::chrono::high_resolution_clock::now();
  func();
  auto end_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end_time - start_time;
  return duration.count();
}

void printResults(const std::vector<int>& sizes,
  const std::vector<double>& timesAll,
  const std::vector<double>& times1,
  const std::vector<double>& times2) {
  std::cout << "n\tgetAllPerms\tgetPerm1\tgetPerm2\n";
  for (size_t i = 0; i < sizes.size(); ++i) {
    std::cout << sizes[i] << "\t"
      << std::fixed << std::setprecision(4) << timesAll[i] << "\t\t"
      << std::fixed << std::setprecision(4) << times1[i] << "\t\t"
      << std::fixed << std::setprecision(4) << times2[i] << "\n";
  }
}

int main() {
  std::vector<int> test_sizes = { 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<double> timesAll, times1, times2;
  for (int n : test_sizes) {
    std::vector<char> mass_alphabet = generateAlphabet(n);
    PMTree tree(mass_alphabet);
    int total_perms = 1;
    for (int i = 1; i <= n; ++i) {
      total_perms *= i;
    }
    unsigned int seed = static_cast<unsigned int>(time(0));
    int random_perm = rand_r(&seed) % total_perms + 1;
    double time_all = measureTime([&]() {
      auto perms = tree.getAllPerms();
      });
    timesAll.push_back(time_all);
    std::cout << "getAllPerms: " << std::fixed
      << std::setprecision(4) << time_all << " ms\n";
    double time1 = measureTime([&]() {
      auto perm = getPerm1(tree, random_perm);
      });
    times1.push_back(time1);
    std::cout << "getPerm1: " << std::fixed
      << std::setprecision(4) << time1 << " ms\n";
    double time2 = measureTime([&]() {
      auto perm = getPerm2(tree, random_perm);
      });
    times2.push_back(time2);
    std::cout << "getPerm2: " << std::fixed
      << std::setprecision(4) << time2 << " ms\n";
  }
  printResults(test_sizes, timesAll, times1, times2);
  return 0;
}
