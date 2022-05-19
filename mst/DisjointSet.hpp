#pragma once

#include <numeric>
#include <vector>

class DisjointSet {
 private:
  std::vector<size_t> parent, rank;

 public:
  DisjointSet(size_t size) : parent(size), rank(size) {
    std::iota(std::begin(parent), std::end(parent), 0);
  }

  size_t find(size_t elt) {
    if (parent[elt] == elt) return elt;
    parent[elt] = find(parent[elt]);
    return parent[elt];
  }

  bool unite(size_t a, size_t b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (rank[a] < rank[b]) std::swap(a, b);
    if (rank[a] == rank[b]) rank[a]++;
    rank[a] += rank[b];
    parent[b] = a;
    return true;
  }

  size_t count() const {
    size_t count = 0;
    for (size_t i = 0; i < parent.size(); i++)
      if (parent[i] == i) count++;
    return count;
  }
};
