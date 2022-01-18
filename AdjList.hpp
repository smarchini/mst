#pragma once

#include <functional>
#include <limits>
#include <tuple>
#include <vector>

constexpr int infty = std::numeric_limits<int>::max();
typedef std::tuple<size_t, size_t, int> edge;
typedef std::tuple<size_t, int> edgeto;

struct weightless {
  bool operator()(const edgeto &lhs, const edgeto &rhs) const {
    return std::get<1>(lhs) < std::get<1>(rhs);
  }

  bool operator()(const edge &lhs, const edge &rhs) const {
    return std::get<2>(lhs) < std::get<2>(rhs);
  }
};

class AdjList {
 private:
  std::vector<std::vector<edgeto>> data;

 public:
  using value_type = typename decltype(data)::value_type;
  using size_type = typename decltype(data)::size_type;
  using const_reference = typename decltype(data)::const_reference;
  using const_iterator = typename decltype(data)::const_iterator;

  AdjList() {}

  void reserve(size_t size) { data.reserve(size); }
  void resize(size_t size) { data.resize(size); }

  size_t size() const noexcept { return data.size(); }
  const_reference adjacents(size_t i) const noexcept { return data[i]; }

  void insert(size_t i, size_t j, int w) {
    size_t m = std::max(i, j);
    if (m >= data.size()) resize(m + 1);
    data[i].push_back({j, w});
  }

  void insertBidirectional(size_t i, size_t j, int w) {
    insert(i, j, w);
    insert(j, i, w);
  }
};
