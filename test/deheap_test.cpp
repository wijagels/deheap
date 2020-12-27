#include <gtest/gtest.h>

#include "deheap/deheap.hpp"

using namespace deheap;

TEST(deheap_queue, constructors) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
  deheap_queue<int> dh1{v};
  deheap_queue<int> dh2{std::move(v)};
  EXPECT_EQ(dh1.min(), dh2.min());
  EXPECT_EQ(dh1.max(), dh2.max());

  dh1.swap(dh2);
  EXPECT_EQ(dh1.size(), 7);
  EXPECT_EQ(dh2.size(), 7);
  EXPECT_EQ(dh1.min(), dh2.min());
  EXPECT_EQ(dh1.max(), dh2.max());
}

TEST(deheap_queue, pop) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
  deheap_queue<int> dq{v};
  EXPECT_EQ(dq.min(), 1);
  EXPECT_EQ(dq.max(), 7);
  dq.pop_min();
  dq.pop_max();
  EXPECT_EQ(dq.min(), 2);
  EXPECT_EQ(dq.max(), 6);
  dq.pop_min();
  dq.pop_max();
  EXPECT_EQ(dq.min(), 3);
  EXPECT_EQ(dq.max(), 5);
  dq.pop_min();
  dq.pop_max();
  EXPECT_EQ(dq.min(), 4);
  EXPECT_EQ(dq.max(), 4);
  dq.pop_max();
  EXPECT_TRUE(dq.empty());
}

TEST(deheap_queue, push) {
  deheap_queue<int> dq{};
  EXPECT_TRUE(dq.empty());

  dq.push(4);
  EXPECT_EQ(dq.min(), 4);
  EXPECT_EQ(dq.max(), 4);

  dq.push(5);
  EXPECT_EQ(dq.min(), 4);
  EXPECT_EQ(dq.max(), 5);

  dq.push(2);
  EXPECT_EQ(dq.min(), 2);
  EXPECT_EQ(dq.max(), 5);

  dq.push(3);
  EXPECT_EQ(dq.min(), 2);
  EXPECT_EQ(dq.max(), 5);

  dq.emplace(6);
  EXPECT_EQ(dq.min(), 2);
  EXPECT_EQ(dq.max(), 6);
}
