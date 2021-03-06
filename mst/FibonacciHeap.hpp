#pragma once
#include <iostream>

template <typename T, typename Comparator>
class FibonacciHeap {
 private:
  struct Node {
    T value;
    Node *prev = this, *next = this;
    Node *child = nullptr, *parent = nullptr;
    int degree = 0;

    Node(T value) : value(value) {}

    void addChild(Node* node) {
      degree++;
      node->prev = node;
      node->next = node;
      node->parent = this;
      child = merge(parent->child, node);
    }
  };

 public:
  class NodeIterator {
   private:
    Node *head, *node;

   public:
    NodeIterator(Node* node) : head(node), node(node) {}

    T& operator*() { return node->value; }

    bool operator==(const NodeIterator& oth) const { return node == oth.node; }

    NodeIterator& operator++() {
      if (node->next == head) {
        node = node->parent;
        head = node;
      } else if (node->child) {
        node = node->child;
      } else {
        node = node->next;
      }
      return *this;
    }
  };

 public:
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;
  using iterator = NodeIterator;

 private:
  Node* heap = nullptr;

 public:
  FibonacciHeap() {}
  ~FibonacciHeap() { deleteTraversal(heap); }

  template <typename It>
  explicit FibonacciHeap(It begin, It end) {
    static_assert(std::is_same<value_type, T>::value, "Type mismatch");
    for (auto it = begin; it != end; ++it) push(*it);
  }

  FibonacciHeap(const std::initializer_list<T> &lst)
      : FibonacciHeap(std::begin(lst), std::end(lst)) {}

  FibonacciHeap(std::initializer_list<T> &&lst)
      : FibonacciHeap(std::begin(lst), std::end(lst)) {}


  FibonacciHeap(FibonacciHeap &) = delete;
  FibonacciHeap& operator=(FibonacciHeap &) = delete;
  FibonacciHeap(FibonacciHeap&& oth) { std::swap(this->heap, oth.heap); }
  FibonacciHeap& operator=(FibonacciHeap&& oth) {
    std::swap(this->heap, oth.heap);
    return *this;
  }

  iterator begin() { return NodeIterator(heap); }
  iterator end() { return nullptr; }

  bool empty() const noexcept { return heap == nullptr; }

  const_reference top() const noexcept { return heap->value; }

  void pop() {
    //  Melding: move the children into the forest
    if (Node* it = heap->child) {
      do {
        it->parent = nullptr;
        it = it->next;
      } while (it != heap->child);
    }
    if (heap->next == heap) {
      heap = heap->child;
    } else {
      heap->next->prev = heap->prev;
      heap->prev->next = heap->next;
      heap = merge(heap->next, heap->child);
    }

    if (!heap) return;

    // Consolidation: all the trees must have different rank
    Node* curr = heap;
    std::vector<Node*> tree(heap->degree + 1, nullptr);
    while (true) {
      if (!tree[curr->degree]) {
        tree[curr->degree] = curr;
        continue;
      }
      if (tree[curr->degree] == heap) break;
      Node* oth = tree[curr->degree];
      tree[curr->degree] = nullptr;
      oth->next->prev = oth->prev;
      oth->prev->next = oth->next;
      if (curr->next == curr) {
        oth->next = oth;
        oth->prev = oth;
      } else {
        curr->prev->next = oth;
        curr->next->prev = oth;
        oth->next = curr->next;
        oth->prev = curr->prev;
      }
      if (Comparator()(curr->value, oth->value)) {
        curr->addChild(oth);
        curr = curr->next;
      } else {
        oth->addChild(curr);
        curr = oth;
      }
    }

    // Fix the head pointer: must be the minimum value
    Node* begin = heap;
    for (Node* it = heap->next; it != begin; it = it->next)
      if (Comparator()(it->value, heap->value)) heap = it;
  }

  constexpr void push(std::convertible_to<value_type> auto&& value) {
    heap = merge(heap, new Node(value));
  }

  void merge(FibonacciHeap<T, Comparator>&& oth) {
    heap = merge(heap, oth.heap);
    oth.heap = nullptr;
  }

 private:
  FibonacciHeap(Node* heap) : heap(heap) {}

  static Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (Comparator()(b->value, a->value)) std::swap(a, b);
    Node* following = a->next;
    Node* preceding = b->prev;
    a->next = b;
    b->prev = a;
    following->prev = preceding;
    preceding->next = following;
    return a;
  }

  void deleteTraversal(Node* node) {
    if (!node) return;
    Node* curr = node;
    do {
      Node* tmp = curr;
      curr = curr->next;
      deleteTraversal(tmp->child);
      delete tmp;
    } while (curr != node);
  }
};
