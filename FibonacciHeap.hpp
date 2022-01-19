#pragma once

template <typename T, typename Comparator>
class FibonacciHeap {
 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;

 private:
  struct Node {
    T value;
    Node *prev = this, *next = this;
    Node *child = nullptr, *parent = nullptr;
    int degree = 0;
    bool marked = false;

    Node(T value) : value(value) {}
  };

  Node* heap = nullptr;

 public:
  FibonacciHeap() {}

  ~FibonacciHeap() {
    // TODO
  }

  // iterator begin() { }

  // iterator end() { }

  // void reserve(size_t size) { }

  // size_type size() const noexcept { }

  bool empty() const noexcept { return heap == nullptr; }

  const_reference top() const noexcept { return heap->value; }

  void pop() {
    for (Node* it = heap->child; it; it = it->next) {
      it->marked = false;
      it->parent = nullptr;
    }
    if (heap->next == heap) {
      heap = heap->child;
    } else {
      heap->next->prev = heap->prev;
      heap->prev->next = heap->next;
      Node *child = heap->child;
      heap = heap->next;
      merge(child);
    }
    if(!heap) return;
  }

  constexpr void push(std::convertible_to<value_type> auto&& value) {
    merge(FibonacciHeap(new Node(value)));
  }

  void merge(FibonacciHeap<T, Comparator>&& oth) {
    if (!heap) heap = oth.heap;
    if (!oth.heap) return;
    if (heap->value > oth.heap->value) std::swap(heap, oth.heap);
    Node* following = heap->next;
    Node* preceding = oth.heap->prev;
    heap->next = oth.heap;
    oth.heap->prev = heap;
    following->prev = preceding;
    preceding->next = following;
  }

 private:
  FibonacciHeap(Node* heap) : heap(heap) {}
};
