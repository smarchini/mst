#include <benchmark/benchmark.h>

#include <BinaryHeap.hpp>
#include <DHeap.hpp>
#include <FibonacciHeap.hpp>
#include <algorithms.hpp>

#ifdef DENSITYBENCH
constexpr size_t nodes[] = {500};
constexpr double degrees[] = {0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.0};
constexpr int weights[] = {1000}; // INT_MAX if we do not use Kruskal's counting sort
#elif SIZEBENCH
constexpr size_t nodes[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
constexpr double degrees[] = {1.00};
constexpr int weights[] = {1000}; // INT_MAX if we do not use Kruskal's counting sort
#else
constexpr size_t nodes[] = {};
constexpr double degrees[] = {};
constexpr int weights[] = {};
#endif

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
using D8Heap = DHeap<8, T, Comparator>;

template <typename T, typename Comparator>
using D16Heap = DHeap<16, T, Comparator>;

template <typename T, typename Comparator>
using D64Heap = DHeap<64, T, Comparator>;


// Kruskal (it does not need explicit bidirectional links)

static void BM_Kruskal(benchmark::State& state) {
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

static void BM_KruskalD8Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal<D8Heap>(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_KruskalD8Heap)->Apply(args);

static void BM_KruskalD16Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal<D16Heap>(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_KruskalD16Heap)->Apply(args);

static void BM_KruskalD64Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal<D64Heap>(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_KruskalD64Heap)->Apply(args);

static void BM_KruskalFHeap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(kruskal<FibonacciHeap>(*g));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_KruskalFHeap)->Apply(args);


// Prim

static void BM_Prim2Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<BinaryHeap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_Prim2Heap)->Apply(args);

static void BM_PrimD8Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D8Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_PrimD8Heap)->Apply(args);

static void BM_PrimD16Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D16Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_PrimD16Heap)->Apply(args);

static void BM_PrimD64Heap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<D64Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_PrimD64Heap)->Apply(args);

static void BM_PrimFHeap(benchmark::State& state) {
  AdjList* g = graph(state);
  for (auto _ : state) benchmark::DoNotOptimize(prim<FibonacciHeap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_PrimFHeap)->Apply(args);


// Edmonds

static void BM_Edmonds2Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<BinaryHeap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_Edmonds2Heap)->Apply(args);

static void BM_EdmondsD8Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D8Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_EdmondsD8Heap)->Apply(args);

static void BM_EdmondsD16Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D16Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_EdmondsD16Heap)->Apply(args);

static void BM_EdmondsD64Heap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<D64Heap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_EdmondsD64Heap)->Apply(args);

static void BM_EdmondsFHeap(benchmark::State& state) {
  AdjList* g = graph(state, true);
  for (auto _ : state) benchmark::DoNotOptimize(edmonds<FibonacciHeap>(*g, 0));
  state.counters["edges"] = g->elements();
}
BENCHMARK(BM_EdmondsFHeap)->Apply(args);

BENCHMARK_MAIN();
