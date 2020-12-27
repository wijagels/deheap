#pragma once

namespace deheap {

template <typename RandomIt>
void push_deheap(RandomIt first, RandomIt last);

template <typename RandomIt>
void pop_min(RandomIt first, RandomIt last);

template <typename RandomIt>
void pop_max(RandomIt first, RandomIt last);

template <typename RandomIt>
void make_deheap(RandomIt first, RandomIt last);

template <typename RandomIt>
RandomIt get_max(RandomIt first, RandomIt last);

}  // namespace deheap

#include "deheap/functions.ipp"
