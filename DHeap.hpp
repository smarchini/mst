#pragma once

#include <array>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

template <size_t d>
static constexpr std::array<size_t, d + 1> i_and_children(size_t i) {
  std::array<size_t, d + 1> result{};
  result[0] = i;
  for (size_t k = 0; k < d; k++) result[k + 1] = i * d + k + 1;
  return result;
}

template <size_t D, typename T, typename Comparator>
class DHeap {
 private:
  std::vector<T> data;

 public:
  using value_type = typename decltype(data)::value_type;
  using size_type = typename decltype(data)::size_type;
  using reference = typename decltype(data)::reference;
  using const_reference = typename decltype(data)::const_reference;
  using iterator = typename decltype(data)::iterator;

  DHeap() : data() {}

  template <typename It>
  explicit DHeap(It begin, It end) : data(begin, end) {
    static_assert(std::is_same<value_type, T>::value, "Type mismatch");
    for (size_t i = data.size() / 2; i > 0; --i) downheapfy(i);
  }

  DHeap(const std::initializer_list<T> &lst)
      : DHeap(std::begin(lst), std::end(lst)) {}

  DHeap(std::initializer_list<T> &&lst) : data(std::move(lst)) {
    static_assert(std::is_same<value_type, T>::value, "Type mismatch");
    for (size_t i = data.size() / 2; i > 0; --i) downheapfy(i);
  }

  iterator begin() { return data.begin(); }

  iterator end() { return data.end(); }

  void reserve(size_t size) { data.reserve(size); }

  size_type size() const noexcept { return data.size(); }

  bool empty() const noexcept { return data.empty(); }

  const_reference top() const noexcept { return data[0]; }

  void pop() {
    swap(0, data.size() - 1);
    data.pop_back();
    downheapfy(0);
  }

  constexpr void push(std::convertible_to<value_type> auto &&value) {
    data.push_back(std::forward<decltype(value)>(value));
    upheapfy(data.size() - 1);
  }

  void merge(DHeap<D, T, Comparator> &&oth) {
    const size_t n = data.size() - 1;
    data.insert(std::end(data), std::begin(oth.data), std::end(oth.data));
    for (size_t i = n; i != -1ULL; --i) downheapfy(i);
  }

 private:
  void swap(size_t i, size_t j) {
    auto x = data[i];
    data[i] = data[j];
    data[j] = x;
  }

  size_t upgoal(std::initializer_list<size_t> list) {
    auto curr = std::begin(list), last = std::end(list), best = curr;
    for (++curr; curr != last && *curr < data.size(); ++curr)
      if (Comparator()(data[*best], data[*curr])) best = curr;
    return *best;
  }

  size_t downgoal(const std::array<size_t, D + 1> &list) {
    auto curr = std::begin(list), last = std::end(list), best = curr;
    for (++curr; curr != last && *curr < data.size(); ++curr)
      if (Comparator()(data[*curr], data[*best])) best = curr;
    return *best;
  }

  void upheapfy(size_t i) {
    if (i == 0) return;
    auto x = upgoal({i, (i - 1) / D});
    if (x == i) return;
    swap(i, x);
    upheapfy(x);
  }

  void downheapfy(size_t i) {
    if (i >= data.size() / 2) return;
    auto x = downgoal(i_and_children<D>(i));
    if (x == i) return;
    swap(i, x);
    downheapfy(x);
  }
};
