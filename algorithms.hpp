#pragma once

#include <tuple>
#include <vector>

#include "AdjList.hpp"
#include "BinaryHeap.hpp"
#include "DisjointSet.hpp"

template <template <typename, typename> class PriorityQueue>
std::vector<edge> prim(const AdjList& graph, size_t source) {
  std::vector<int> key(graph.size(), infty);
  std::vector<size_t> parent(graph.size(), -1ULL);
  std::vector<bool> visited(graph.size(), false);

  PriorityQueue<edgeto, weightless> queue;
  queue.push(std::make_tuple(source, infty));
  key[source] = 0;

  while (!queue.empty()) {
    size_t u = std::get<0>(queue.top());
    queue.pop();
    visited[u] = true;

    for (auto [v, w] : graph.adjacents(u)) {
      if (!visited[v] && key[v] > w) {
        key[v] = w;
        queue.push(std::make_tuple(v, w));
        parent[v] = u;
      }
    }
  }

  std::vector<edge> result;
  result.reserve(graph.size() - 1);
  for (size_t i = 1; i < graph.size(); i++)
    if (parent[i] != -1ULL) result.push_back({parent[i], i, key[i]});
  return result;
}

