#pragma once

#include <algorithms.hpp>
#include <random>

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
  AdjList digraph;
  digraph.reserve(4);
  digraph.insert(0, 1, 20);
  digraph.insert(0, 2, 5);
  digraph.insert(0, 3, 4);
  digraph.insert(1, 2, 1);
  digraph.insert(2, 1, 2);
  digraph.insert(3, 2, 8);
  digraph.insert(2, 3, 3);

  auto msa = edmonds<BinaryHeap>(digraph, 0);
  EXPECT_EQ(msa, 10);
}

TEST(minimum_spanning_tree, all_the_same) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> weight(1, 100);

  AdjList graph;
  graph.reserve(100 * 100 * 2);
  for (size_t u = 0; u < 100; u++)
    for (size_t v = 0; v < 100; v++)
      graph.insertBidirectional(u, v, weight(rng));

  int prim_weight = 0, kruskal_weight = 0, edmonds_weight = 0;
  for (auto [u, v, w] : prim<BinaryHeap>(graph, 0)) prim_weight += w;
  for (auto [u, v, w] : kruskal(graph)) kruskal_weight += w;
  edmonds_weight = edmonds<BinaryHeap>(graph, 0);
  EXPECT_EQ(prim_weight, kruskal_weight);
  EXPECT_EQ(prim_weight, edmonds_weight);
  EXPECT_EQ(kruskal_weight, edmonds_weight);
}
