#pragma once

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
#include <FibonacciHeap.hpp>
#include <algorithm>
#include <vector>

template <typename HEAP>
inline void heap(size_t n) {
  std::vector<int> a(n);
  std::vector<int> b(n);
  std::generate(a.begin(), a.end(), std::rand);
  std::generate(b.begin(), b.end(), std::rand);

  HEAP heap;
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

TEST(BinaryHeap, heapsort) { heap<BinaryHeap<int, std::less<int>>>(100); }

template <int N>
void for_dary_heaps(size_t n) {
  heap<DHeap<N, int, std::less<int>>>(n);
  for_dary_heaps<N - 1>(n);
}

template <>
void for_dary_heaps<1>(size_t n) {}

TEST(DHeap, from_50_to_2) { for_dary_heaps<50>(100); }

TEST(FibonacciHeap, heapsort) { heap<FibonacciHeap<int, std::less<int>>>(100); }

TEST(FibonacciHeap, traversal) {
  std::vector<int> a = { 4, 9, 1, 5, 7, 2, 3, 8, 6, 0};
  FibonacciHeap<int, std::less<int>> heap;
  for (auto e : a) heap.push(e);
  for(auto e: heap) std::cout << e << "\n";
}
