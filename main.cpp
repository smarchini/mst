#include <benchmark/benchmark.h>

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
#include <FibonacciHeap.hpp>
#include <algorithms.hpp>

constexpr size_t nodes[] = {1000, 1000000};
constexpr double degrees[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
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
using D10Heap = DHeap<10, T, Comparator>;

template <typename T, typename Comparator>
using D100Heap = DHeap<100, T, Comparator>;

// Kruskal

static void BM_Kruskal(benchmark::State& state) {
  // Kruskal's algorithm does not need bidirectional links
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_Kruskal)->Apply(args);

static void BM_KruskalCounting(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal_int(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_KruskalCounting)->Apply(args);

static void BM_Kruskal2Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal<BinaryHeap>(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_Kruskal2Heap)->Apply(args);

// static void BM_KruskalD10Heap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(kruskal<D10Heap>(*g));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_KruskalD10Heap)->Apply(args);

// static void BM_KruskalD100Heap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(kruskal<D100Heap>(*g));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_KruskalD100Heap)->Apply(args);

// // Prim

// static void BM_Prim2Heap(benchmark::State& state) {
//   AdjList* g = graph(state);
//   for (auto _ : state) benchmark::DoNotOptimize(prim<BinaryHeap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_Prim2Heap)->Apply(args);

// static void BM_PrimFHeap(benchmark::State& state) {
//   AdjList* g = graph(state);
//   for (auto _ : state) benchmark::DoNotOptimize(prim<FibonacciHeap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_PrimFHeap)->Apply(args);

// static void BM_PrimD10Heap(benchmark::State& state) {
//   AdjList* g = graph(state);
//   for (auto _ : state) benchmark::DoNotOptimize(prim<D10Heap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_PrimD10Heap)->Apply(args);

// static void BM_PrimD100Heap(benchmark::State& state) {
//   AdjList* g = graph(state);
//   for (auto _ : state) benchmark::DoNotOptimize(prim<D100Heap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_PrimD100Heap)->Apply(args);

// // Edmonds

// static void BM_Edmonds2Heap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(edmonds<BinaryHeap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_Edmonds2Heap)->Apply(args);

// static void BM_EdmondsFHeap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(edmonds<FibonacciHeap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_EdmondsFHeap)->Apply(args);

// static void BM_EdmondsD10Heap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(edmonds<D10Heap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_EdmondsD10Heap)->Apply(args);

// static void BM_EdmondsD100Heap(benchmark::State& state) {
//   AdjList* g = graph(state, true);
//   for (auto _ : state) benchmark::DoNotOptimize(edmonds<D100Heap>(*g, 0));
//   state.counters["edges"] = g->elements();
// }
// BENCHMARK(BM_EdmondsD100Heap)->Apply(args);

BENCHMARK_MAIN();
