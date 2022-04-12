#pragma once

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
#include <FibonacciHeap.hpp>
#include <algorithms.hpp>
#include <random>

template <typename T, typename Comparator>
using D3Heap = DHeap<3, T, Comparator>;

template <typename T, typename Comparator>
using D4Heap = DHeap<4, T, Comparator>;

template <typename T, typename Comparator>
using D5Heap = DHeap<5, T, Comparator>;

TEST(minimum_spanning_tree, prim) {
  AdjList graph;
  graph.reserve(5 * 2);
  graph.insertBidirectional(0, 1, 3);
  graph.insertBidirectional(0, 2, 2);
  graph.insertBidirectional(1, 2, 1);
  graph.insertBidirectional(1, 3, 4);
  graph.insertBidirectional(2, 4, 1);
  graph.insertBidirectional(3, 4, 2);

  auto mst = prim<BinaryHeap>(graph, 0);

  int weight = 0;
  for (auto [u, v, w] : mst) weight += w;
  EXPECT_EQ(weight, 6);
}

TEST(minimum_spanning_tree, kruskal) {
  // Kruskal's algorithm does not need bidirectional links
  AdjList graph;
  graph.reserve(5);
  graph.insert(0, 1, 3);
  graph.insert(0, 2, 2);
  graph.insert(1, 2, 1);
  graph.insert(1, 3, 4);
  graph.insert(2, 4, 1);
  graph.insert(3, 4, 2);

  auto mst = kruskal(graph);

  int weight = 0;
  for (auto [u, v, w] : mst) weight += w;
  EXPECT_EQ(weight, 6);
}

TEST(minimum_spanning_arborescence, edmonds) {
  AdjList invdigraph;
  invdigraph.reserve(4);

  // digraph.insert(0, 1, 20);
  // digraph.insert(0, 2, 5);
  // digraph.insert(0, 3, 4);
  // digraph.insert(1, 2, 1);
  // digraph.insert(2, 1, 2);
  // digraph.insert(3, 2, 8);
  // digraph.insert(2, 3, 3);

  invdigraph.insert(1, 0, 20);
  invdigraph.insert(2, 0, 5);
  invdigraph.insert(3, 0, 4);
  invdigraph.insert(2, 1, 1);
  invdigraph.insert(1, 2, 2);
  invdigraph.insert(2, 3, 8);
  invdigraph.insert(3, 2, 3);

  auto msa = edmonds<BinaryHeap>(invdigraph, 0);
  EXPECT_EQ(msa, 10);
}

TEST(minimum_spanning_tree, all_the_same) {
  const size_t n = 100;
  auto graph = random_graph(n, 0.8, 100);
  // AdjList graph;
  // graph.insert(0, 4, 13);
  // graph.insert(0, 3, 57);
  // graph.insert(0, 1, 8);
  // graph.insert(0, 2, 69);
  // graph.insert(1, 4, 27);
  // graph.insert(1, 0, 8);
  // graph.insert(1, 2, 5);
  // graph.insert(1, 3, 20);
  // graph.insert(2, 4, 4);
  // graph.insert(2, 0, 69);
  // graph.insert(2, 1, 5);
  // graph.insert(2, 3, 65);
  // graph.insert(3, 0, 57);
  // graph.insert(3, 4, 43);
  // graph.insert(3, 2, 65);
  // graph.insert(3, 1, 20);
  // graph.insert(4, 1, 27);
  // graph.insert(4, 0, 13);
  // graph.insert(4, 3, 43);
  // graph.insert(4, 2, 4);

  int w_kruskal = 0;
  for (auto [u, v, w] : kruskal(graph)) w_kruskal += w;

  int w_kruskal_counting = 0;
  for (auto [u, v, w] : kruskal_int(graph)) w_kruskal_counting += w;

  int w_prim_2heap = 0;
  for (auto [u, v, w] : prim<BinaryHeap>(graph, 0)) w_prim_2heap += w;
  int w_prim_d3heap = 0;
  for (auto [u, v, w] : prim<D3Heap>(graph, 0)) w_prim_d3heap += w;
  int w_prim_d4heap = 0;
  for (auto [u, v, w] : prim<D4Heap>(graph, 0)) w_prim_d4heap += w;
  int w_prim_d5heap = 0;
  for (auto [u, v, w] : prim<D4Heap>(graph, 0)) w_prim_d5heap += w;
  int w_prim_fheap = 0;
  for (auto [u, v, w] : prim<FibonacciHeap>(graph, 0)) w_prim_fheap += w;

  int w_kruskal_2heap = 0;
  for (auto [u, v, w] : kruskal<BinaryHeap>(graph)) w_kruskal_2heap += w;
  int w_kruskal_d3heap = 0;
  for (auto [u, v, w] : kruskal<D3Heap>(graph)) w_kruskal_d3heap += w;
  int w_kruskal_d4heap = 0;
  for (auto [u, v, w] : kruskal<D4Heap>(graph)) w_kruskal_d4heap += w;
  int w_kruskal_d5heap = 0;
  for (auto [u, v, w] : kruskal<D4Heap>(graph)) w_kruskal_d5heap += w;

  int w_edmonds_2heap = edmonds<BinaryHeap>(graph, 0);
  int w_edmonds_d3heap = edmonds<D3Heap>(graph, 0);
  int w_edmonds_d4heap = edmonds<D4Heap>(graph, 0);
  int w_edmonds_d5heap = edmonds<D5Heap>(graph, 0);
  int w_edmonds_fheap = edmonds<FibonacciHeap>(graph, 0);

  EXPECT_EQ(w_kruskal, w_kruskal_counting);

  EXPECT_EQ(w_kruskal, w_prim_2heap);
  EXPECT_EQ(w_kruskal, w_prim_d3heap);
  EXPECT_EQ(w_kruskal, w_prim_d4heap);
  EXPECT_EQ(w_kruskal, w_prim_d5heap);
  EXPECT_EQ(w_kruskal, w_prim_fheap);

  EXPECT_EQ(w_kruskal, w_kruskal_2heap);
  EXPECT_EQ(w_kruskal, w_kruskal_d3heap);
  EXPECT_EQ(w_kruskal, w_kruskal_d4heap);
  EXPECT_EQ(w_kruskal, w_kruskal_d5heap);

  EXPECT_EQ(w_kruskal, w_edmonds_2heap);
  EXPECT_EQ(w_kruskal, w_edmonds_d3heap);
  EXPECT_EQ(w_kruskal, w_edmonds_d4heap);
  EXPECT_EQ(w_kruskal, w_edmonds_d5heap);
  EXPECT_EQ(w_kruskal, w_edmonds_fheap);
}
