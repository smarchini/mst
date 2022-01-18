#pragma once

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
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

template <size_t d>
inline void dary_heap() {
  std::vector<int> a(500);
  std::vector<int> b(500);
  std::generate(a.begin(), a.end(), std::rand);
  std::generate(b.begin(), b.end(), std::rand);

  DHeap<d, int, std::less<int>> heap;
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

template <int N>
void for_dary_heaps() {
  dary_heap<N>();
  for_dary_heaps<N - 1>();
}

template <>
void for_dary_heaps<1>() {}

TEST(DHeap, from_50_to_2) { for_dary_heaps<50>(); }
