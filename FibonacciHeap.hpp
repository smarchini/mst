#pragma once

template <typename T, typename Comparator>
class FibonacciHeap {
 private:
  struct Node {
    T value;
    Node *prev = this, *next = this;
    Node *child = nullptr, *parent = nullptr;
    int degree = 0;
    bool marked = false;

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
    Node *head, node;

   public:
    NodeIterator(Node* node) : head(node), node(node) {}
    // NodeIterator& operator++() {}
    // NodeIterator operator++(int) {}
    // bool operator==(const NodeIterator&) const {}
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
    //  Melding: move the children into the forest
    if (Node* it = heap->child) {
      do {
        it->marked = false;
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
      if (curr->value < oth->value) {
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
      if (it->value < heap->value) heap = it;
  }

  constexpr void push(std::convertible_to<value_type> auto&& value) {
    heap = merge(heap, new Node(value));
  }

  void merge(FibonacciHeap<T, Comparator>&& oth) {
    heap = merge(heap, oth.heap);
  }

 private:
  FibonacciHeap(Node* heap) : heap(heap) {}

  static Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->value > b->value) std::swap(a, b);
    Node* following = a->next;
    Node* preceding = b->prev;
    a->next = b;
    b->prev = a;
    following->prev = preceding;
    preceding->next = following;
    return a;
  }

  Node* _removeMinimum(Node* n) {
    _unMarkAndUnParentAll(n->child);
    if (n->next == n) {
      n = n->child;
    } else {
      n->next->prev = n->prev;
      n->prev->next = n->next;
      n = merge(n->next, n->child);
    }
    if (n == NULL) return n;
    Node* trees[64] = {NULL};

    while (true) {
      if (trees[n->degree] != NULL) {
        Node* t = trees[n->degree];
        if (t == n) break;
        trees[n->degree] = NULL;
        if (n->value < t->value) {
          t->prev->next = t->next;
          t->next->prev = t->prev;
          n->addChild(t);
        } else {
          t->prev->next = t->next;
          t->next->prev = t->prev;
          if (n->next == n) {
            t->next = t->prev = t;
            t->addChild(n);
            n = t;
          } else {
            n->prev->next = t;
            n->next->prev = t;
            t->next = n->next;
            t->prev = n->prev;
            t->addChild(n);
            n = t;
          }
        }
        continue;
      } else {
        trees[n->degree] = n;
      }
      n = n->next;
    }
    Node* min = n;
    Node* start = n;
    do {
      if (n->value < min->value) min = n;
      n = n->next;
    } while (n != start);
    return min;
  }

  void _unMarkAndUnParentAll(Node* n) {
    if (n == NULL) return;
    Node* c = n;
    do {
      c->marked = false;
      c->parent = NULL;
      c = c->next;
    } while (c != n);
  }
};
