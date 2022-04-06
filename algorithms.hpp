#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>

#include "AdjList.hpp"
#include "DisjointSet.hpp"

static void make_complete(AdjList& g, int w, bool digraph) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> weight(1, w);
  if (digraph) {
    for (size_t u = 0; u < g.size(); u++)
      for (size_t v = 0; v < g.size(); v++) g.insert(u, v, weight(rng));
  } else {
    for (size_t u = 0; u < g.size() - 1; u++)
      for (size_t v = u + 1; v < g.size(); v++)
        g.insertBidirectional(u, v, weight(rng));
  }
}

static void set_edges(AdjList& g, size_t m, int w, bool add, bool digraph) {
  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> node(0, g.size() - 1);
  std::uniform_int_distribution<int> weight(1, w);

  for (size_t k = 0; k < m;) {
    size_t u = node(rng), v = node(rng);
    if (u == v) continue;
    auto adj = g.adjacents(u);
    auto it = std::find_if(std::begin(adj), std::end(adj), [v, w](auto x) {
      return std::get<0>(x) == v && std::get<1>(x) <= w;
    });
    if (add && it == std::end(adj)) {
      if (digraph) {
        g.insert(u, v, weight(rng));
        k += 1;
      } else {
        g.insertBidirectional(u, v, weight(rng));
        k += 2;
      }
    } else if (!add && it != std::end(adj)) {
      if (digraph) {
        g.remove(u, v);
        k += 1;
      } else {
        g.removeBidirectional(u, v);
        k += 2;
      }
    }
  }
}

inline AdjList random_graph(size_t n, double d, int w, bool digraph = false) {
  AdjList result(n);
  const size_t m = digraph ? n * n : n * (n - 1);

  if (d <= 0.5) {
    set_edges(result, m * d, w, true, digraph);
  } else {
    make_complete(result, w, digraph);
    set_edges(result, m * (1 - d), w, false, digraph);
  }

  for (size_t v = 1; v < n; v++) {
    if (digraph) {
      result.insert(0, v, w + 1);
    } else {
      result.insertBidirectional(0, v, w + 1);
    }
  }

  return result;
}

inline std::vector<edge> kruskal(const AdjList& graph) {
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
inline std::vector<edge> kruskal(const AdjList& graph) {
  std::vector<edge> result;
  result.reserve(graph.size() - 1);
  DisjointSet set(graph.size());

  std::vector<edge> edges;
  edges.reserve(graph.elements());
  for (size_t u = 0; u < graph.size(); u++)
    for (auto [v, w] : graph.adjacents(u)) edges.push_back({u, v, w});
  PriorityQueue<edge, weightless> queue(edges.begin(), edges.end());

  while (result.size() != graph.size() - 1) {
    auto [u, v, w] = queue.top();
    queue.pop();
    if (set.find(u) != set.find(v)) {
      result.push_back({u, v, w});
      set.unite(u, v);
    }
  }

  return result;
}

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
        PriorityQueue<edgeto, weightless> heap;
        while (true) {
          size_t x = path.back();
          path.pop_back();
          heap.merge(std::move(inedges[x]));
          if (!set.unite(u, x)) break;
        }
        inedges[set.find(u)] = std::move(heap);
        visited[set.find(u)] = -1ULL;
      }
      v = set.find(u);
    }
  }
  return score;
}

inline std::vector<edge> countsort(std::vector<edge>& input) {
  int min = std::numeric_limits<int>::max();
  int max = std::numeric_limits<int>::min();
  for (auto [u, v, w] : input) {
    if (w > max) max = w;
    if (w < min) min = w;
  }

  std::vector<int> counter(max - min + 1);
  for (auto [u, v, w] : input) counter[w - min]++;
  for (size_t i = 1; i < counter.size(); i++) counter[i] += counter[i - 1];

  std::vector<edge> result(input.size());
  for (int i = input.size() - 1; i >= 0; i--) {
    auto [u, v, w] = input[i];
    result[counter[w - min] - 1] = {u, v, w};
    counter[w - min]--;
  }

  return result;
}

inline std::vector<edge> kruskal_int(const AdjList& graph) {
  std::vector<edge> result;
  result.reserve(graph.size() - 1);
  DisjointSet set(graph.size());

  std::vector<edge> edges;
  edges.reserve(graph.elements());
  for (size_t u = 0; u < graph.size(); u++)
    for (auto [v, w] : graph.adjacents(u))
      edges.push_back({u, v, w});

  edges = countsort(edges);

  for (auto [u, v, w] : edges) {
    if (set.find(u) != set.find(v)) {
      result.push_back({u, v, w});
      set.unite(u, v);
    }
  }

  return result;
}
