#include <gtest/gtest.h>

#include "deheap/functions.hpp"

#include <algorithm>
#include <random>
#include <vector>

using namespace deheap;

namespace {
const int g_sample_data[] = {28, 57, 30, 25, 36, 34, 36, 27, 65, 39, 45,
                             38, 37, 45, 59, 50, 5,  15, 20, 12, 8,  13,
                             14, 10, 80, 30, 32, 31, 15, 16, 18, 17};
template <typename RandomIt>
void check_invariant(RandomIt first, RandomIt last) {
  if (first == last) return;
  auto min = *std::min_element(first, last);
  auto max = *std::max_element(first, last);
  auto sz = std::distance(first, last);
  EXPECT_EQ(*first, min);
  if (sz > 2) {
    EXPECT_EQ(std::max(*(first + 1), *(first + 2)), max);
  } else if (sz > 1) {
    EXPECT_EQ(*(first + 1), max);
  }
}
}  // namespace

TEST(Functions, push_deheap) {
  std::vector<int> v{1};
  push_deheap(begin(v), end(v));

  v.push_back(-1);
  push_deheap(begin(v), end(v));
  EXPECT_EQ(v, std::vector<int>({-1, 1}));

  v.push_back(3);
  push_deheap(begin(v), end(v));
  EXPECT_EQ(v, std::vector<int>({-1, 1, 3}));

  v.push_back(-4);
  push_deheap(begin(v), end(v));
  EXPECT_EQ(v, std::vector<int>({-4, 1, 3, -1}));

  v.push_back(4);
  push_deheap(begin(v), end(v));
  EXPECT_EQ(v, std::vector<int>({-4, 4, 3, -1, 1}));
}

TEST(Functions, pop_min) {
  std::vector<int> v{std::begin(g_sample_data), std::end(g_sample_data)};
  for (auto last = v.begin() + 1; last <= v.end(); ++last)
    push_deheap(v.begin(), last);
  while (!v.empty()) {
    int min = v.front();
    pop_min(v.begin(), v.end());
    EXPECT_EQ(min, v.back());
    v.pop_back();
    check_invariant(v.begin(), v.end());
  }
}

TEST(Functions, pop_max) {
  std::vector<int> v{std::begin(g_sample_data), std::end(g_sample_data)};
  for (auto last = v.begin() + 1; last <= v.end(); ++last)
    push_deheap(v.begin(), last);
  while (!v.empty()) {
    int max = *std::max_element(v.begin(), v.end());
    pop_max(v.begin(), v.end());
    EXPECT_EQ(max, v.back());
    v.pop_back();
    check_invariant(v.begin(), v.end());
  }
}

TEST(Functions, make_deheap_step) {
  std::vector<int> v{std::begin(g_sample_data), std::end(g_sample_data)};
  for (auto last = v.begin() + 1; last <= v.end(); ++last) {
    push_deheap(v.begin(), last);
    check_invariant(v.begin(), last);
  }
}

TEST(Functions, make_deheap) {
  std::vector<int> v{std::begin(g_sample_data), std::end(g_sample_data)};
  make_deheap(v.begin(), v.end());
  check_invariant(v.begin(), v.end());
}

TEST(Functions, make_deheap_big) {
  const int test_size = 100000;
  std::vector<int> v;
  v.reserve(test_size);
  std::uniform_int_distribution<> dis{0, 1 << 18};
  std::mt19937 gen;
  std::generate_n(std::back_inserter(v), test_size, [&]() { return dis(gen); });
  make_deheap(v.begin(), v.end());

  while (!v.empty()) {
    int min = v.front();
    if (gen() % 2) {
      pop_min(v.begin(), v.end());
      EXPECT_EQ(min, v.back());
    } else {
      int max = *std::max_element(v.begin(), std::min(v.begin() + 3, v.end()));
      pop_max(v.begin(), v.end());
      EXPECT_EQ(max, v.back());
    }
    v.pop_back();
    check_invariant(v.begin(), v.end());
  }
}
