#pragma once

#include <BinaryHeap.hpp>
#include <algorithm>
#include <vector>

TEST(BinaryHeap, heapsort) {
  std::vector<int> a(500);
  std::vector<int> b(500);
  std::generate(a.begin(), a.end(), std::rand);
  std::generate(b.begin(), b.end(), std::rand);
  BinaryHeap<int, std::less<int>> heap;
  for (auto e : a) heap.push(e);
  for (auto e : b) heap.push(e);
  auto curr = heap.top();
  while (!heap.empty()) {
    auto next = heap.top();
    EXPECT_LE(curr, next);
    curr = next;
    heap.pop();
  }
}
