#pragma once

#include <algorithms.hpp>

TEST(minimum_spanning_tree, prim) {
  AdjList graph;
  graph.reserve(5);
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
