#pragma once

#include <algorithm>
#include <random>
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

std::vector<edge> kruskal(const AdjList& graph) {
  std::vector<edge> result;
  result.reserve(graph.size() - 1);
  DisjointSet set(graph.size());

  std::vector<edge> edges;
  edges.reserve(graph.elements());
  for (size_t u = 0; u < graph.size(); u++)
    for (auto [v, w] : graph.adjacents(u)) edges.push_back({u, v, w});
  std::sort(edges.begin(), edges.end(), weightless());

  for (auto [u, v, w] : edges) {
    if (set.find(u) != set.find(v)) {
      result.push_back({u, v, w});
      set.unite(u, v);
    }
  }

  return result;
}

template <template <typename, typename> class PriorityQueue>
int edmonds(const AdjList& graph, size_t source) {
  DisjointSet set(graph.size());
  std::vector<PriorityQueue<edgeto, weightless>> inedges(graph.size());
  for (size_t u = 0; u < graph.size(); u++)
    for (auto [v, w] : graph.adjacents(u))
      inedges[v].push(std::make_tuple(u, w));
  int score = 0;
  std::vector<size_t> visited(graph.size(), -1ULL);
  visited[source] = source;
  for (size_t s = 0; s < graph.size(); s++) {
    std::vector<size_t> path;
    for (size_t v = s; visited[v] == -1ULL;) {
      path.push_back(v);
      visited[v] = s;
      if (inedges[v].empty()) return infty;
      auto [u, w] = inedges[v].top();
      inedges[v].pop();
      score += w;
      for (auto& [_, x] : inedges[v]) x -= w;
      if (visited[set.find(u)] == s) {
        while (true) {
          size_t x = path.back();
          path.pop_back();
          if (!set.unite(u, x)) break;
          inedges[set.find(u)].merge(std::move(inedges[x]));
        }
        visited[set.find(u)] = -1ULL;
      }
      v = set.find(u);
    }
  }
  return score;
}

inline AdjList random_graph(size_t n, double d, int w, bool directed = false) {
  const size_t m = directed ? n * (n - 1) * d : n * (n - 1) * d / 2.0;
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> node(0, n - 1);
  std::uniform_int_distribution<int> weight(1, w);

  AdjList result(n);
  for (size_t k = 0; k < m;) {
    size_t u = node(rng), v = node(rng);
    auto cmp = [v](const auto x) { return std::get<0>(x) == v; };
    auto adj = result.adjacents(u);
    if (std::find_if(std::begin(adj), std::end(adj), cmp) == std::end(adj)) {
      if (directed)
        result.insert(u, v, weight(rng));
      else
        result.insertBidirectional(u, v, weight(rng));
      k++;
    }
  }
  return result;
}
