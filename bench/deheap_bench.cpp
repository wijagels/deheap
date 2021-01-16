#include "deheap/functions.hpp"
#include <benchmark/benchmark.h>
#include <random>

static void make_deheap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    deheap::make_deheap(v.begin(), v.end());
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(make_deheap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();

static void push_deheap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    for (auto it = v.begin() + 1; it <= v.end(); ++it)
      deheap::push_deheap(v.begin(), it);
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(push_deheap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();

static void make_heap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    std::make_heap(v.begin(), v.end());
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(make_heap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();

static void push_heap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    for (auto it = v.begin() + 1; it <= v.end(); ++it)
      std::push_heap(v.begin(), it);
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(push_heap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();

static void sort_deheap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    deheap::make_deheap(v.begin(), v.end());
    deheap::sort_deheap_ascending(v.begin(), v.end());
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(sort_deheap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();

static void sort_heap(benchmark::State &state) {
  std::vector<int> v;
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), state.range(0), std::ref(gen));
  for (auto _ : state) {
    state.PauseTiming();
    std::shuffle(v.begin(), v.end(), gen);
    state.ResumeTiming();
    std::make_heap(v.begin(), v.end());
    std::sort_heap(v.begin(), v.end());
  }

  state.SetComplexityN(v.size());
}
BENCHMARK(sort_heap)->DenseRange(1 << 10, 1 << 14, 1024)->Complexity();
