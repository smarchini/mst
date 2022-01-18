#pragma once

#include <algorithms.hpp>

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
  // Kruskal's algorithm does not need bidirectional edges
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
