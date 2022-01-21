#include <benchmark/benchmark.h>

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
#include <FibonacciHeap.hpp>
#include <algorithms.hpp>

constexpr size_t nodes[] = {100, 500, 1000};
constexpr double degrees[] = {0.1, 0.5, 1.0};
constexpr int weights[] = {100};

static void args(benchmark::internal::Benchmark* b) {
  for (size_t n = 0; n < std::size(nodes); n++)
    for (size_t d = 0; d < std::size(degrees); d++)
      for (size_t w = 0; w < std::size(weights); w++)
        b->Args({(int64_t)n, (int64_t)d, (int64_t)w});
}

static AdjList* graph(benchmark::State& state, bool directed = false) {
  static AdjList result;
  const int64_t n = state.range(0);
  const int64_t d = state.range(1);
  const int64_t w = state.range(2);
  result = random_graph(nodes[n], degrees[d], weights[w], directed);
  return &result;
}

// D-ary Heaps

template <typename T, typename Comparator>
using D3Heap = DHeap<3, T, Comparator>;

template <typename T, typename Comparator>
using D4Heap = DHeap<4, T, Comparator>;

template <typename T, typename Comparator>
using D5Heap = DHeap<5, T, Comparator>;

// Kruskal

static void BM_Kruskal(benchmark::State& state) {
  // Kruskal's algorithm does not need bidirectional links
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal(*g));
}
BENCHMARK(BM_Kruskal)->Apply(args);

// Prim

static void BM_Prim2Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<BinaryHeap>(*g, 0));
}
BENCHMARK(BM_Prim2Heap)->Apply(args);

static void BM_PrimFHeap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<FibonacciHeap>(*g, 0));
}
BENCHMARK(BM_PrimFHeap)->Apply(args);

static void BM_PrimD3Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D3Heap>(*g, 0));
}
BENCHMARK(BM_PrimD3Heap)->Apply(args);

static void BM_PrimD4Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D4Heap>(*g, 0));
}
BENCHMARK(BM_PrimD4Heap)->Apply(args);

static void BM_PrimD5Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D5Heap>(*g, 0));
}
BENCHMARK(BM_PrimD5Heap)->Apply(args);

// Edmonds

static void BM_Edmonds2Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<BinaryHeap>(*g, 0));
}
BENCHMARK(BM_Edmonds2Heap)->Apply(args);

static void BM_EdmondsFHeap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<FibonacciHeap>(*g, 0));
}
BENCHMARK(BM_EdmondsFHeap)->Apply(args);

static void BM_EdmondsD3Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D3Heap>(*g, 0));
}
BENCHMARK(BM_EdmondsD3Heap)->Apply(args);

static void BM_EdmondsD4Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D4Heap>(*g, 0));
}
BENCHMARK(BM_EdmondsD4Heap)->Apply(args);

static void BM_EdmondsD5Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D5Heap>(*g, 0));
}
BENCHMARK(BM_EdmondsD5Heap)->Apply(args);

BENCHMARK_MAIN();
