#pragma once

#include <functional>
#include <iterator>
#include <type_traits>
#include <utility>

namespace deheap {

namespace detail {

template <typename RandomIt>
struct Children {
  RandomIt ch1, ch2;
};

template <typename RandomIt>
Children<RandomIt> get_children(RandomIt first, RandomIt pos) {
  auto ch1 = pos + std::distance(first, pos) + 1;
  auto ch2 = ch1 + 1;
  return {ch1, ch2};
}

template <typename RandomIt>
RandomIt get_parent(RandomIt first, RandomIt pos) {
  return first + ((std::distance(first, pos) - 1) / 2);
}

template <typename RandomIt>
RandomIt get_grandparent(RandomIt first, RandomIt pos) {
  return first + ((std::distance(first, pos) - 3) / 4);
}

template <typename RandomIt>
int get_level(RandomIt first, RandomIt pos) {
#ifdef __GNUC__
  return sizeof(size_t) * 8 - 1 -
         __builtin_clzll(size_t(std::distance(first, pos) + 1));
#else
  int level = 0;
  for (auto n = std::distance(first, pos) + 1; n > 1; n >>= 1, ++level)
    ;
  return level;
#endif
}

template <typename RandomIt, typename Compare>
void sift_down(RandomIt first, RandomIt last, RandomIt pos, Compare comp) {
  using std::swap;
  // Maintain C++11 compatibility and no <tuple>
  RandomIt ch1, ch2;
  RandomIt gc1, gc2, gc3, gc4;
  auto ch = get_children(first, pos);
  ch1 = ch.ch1;
  ch2 = ch.ch2;
  if (ch1 >= last) return;
  auto lc = get_children(first, ch1);
  gc1 = lc.ch1;
  gc2 = lc.ch2;
  auto rc = get_children(first, ch2);
  gc3 = rc.ch1;
  gc4 = rc.ch2;

  RandomIt smallest = pos;
  for (RandomIt candidate : {ch1, ch2, gc1, gc2, gc3, gc4}) {
    if (candidate >= last) break;
    if (comp(*candidate, *smallest)) smallest = candidate;
  }

  if (smallest != pos) {
    if (smallest == ch1 || smallest == ch2) {
      swap(*pos, *smallest);
    } else {  // Grandchild
      swap(*pos, *smallest);
      if ((smallest == gc1 || smallest == gc2) && comp(*ch1, *smallest))
        swap(*ch1, *smallest);
      else if (comp(*ch2, *smallest))
        swap(*ch2, *smallest);
      sift_down(first, last, smallest, comp);
    }
  }
}

template <typename RandomIt, typename Compare>
void sift_up(RandomIt first, RandomIt last, RandomIt pos, Compare comp) {
  using std::swap;
  if (get_parent(first, pos) <= first) return;
  auto grandparent = get_grandparent(first, pos);
  if (comp(*pos, *grandparent)) {
    swap(*pos, *grandparent);
    sift_up(first, last, grandparent, comp);
  }
}

template <typename RandomIt>
void sift_down(RandomIt first, RandomIt last, RandomIt pos) {
  using T = typename std::remove_reference<decltype(*pos)>::type;
  if (get_level(first, pos) % 2 == 0)
    sift_down(first, last, pos, std::less<T>{});
  else
    sift_down(first, last, pos, std::greater<T>{});
}

template <typename RandomIt>
void sift_up(RandomIt first, RandomIt last, RandomIt pos) {
  using std::swap;
  using T = typename std::remove_reference<decltype(*pos)>::type;
  auto parent = get_parent(first, pos);
  if (get_level(first, pos) % 2 == 0) {
    if (pos != first && *pos > *parent) {
      swap(*pos, *parent);
      sift_up(first, last, parent, std::greater<T>{});
    } else {
      sift_up(first, last, pos, std::less<T>{});
    }
  } else {
    if (pos != first && *pos < *parent) {
      swap(*pos, *parent);
      sift_up(first, last, parent, std::less<T>{});
    } else {
      sift_up(first, last, pos, std::greater<T>{});
    }
  }
}

}  // namespace detail

template <typename RandomIt>
void push_deheap(RandomIt first, RandomIt last) {
  detail::sift_up(first, last, last - 1);
}

template <typename RandomIt>
void pop_min(RandomIt first, RandomIt last) {
  using std::swap;
  swap(*first, *(last - 1));
  detail::sift_down(first, last - 1, first);
}

template <typename RandomIt>
void pop_max(RandomIt first, RandomIt last) {
  using std::swap;
  RandomIt largest = get_max(first, last);
  swap(*largest, *(last - 1));
  detail::sift_down(first, last - 1, largest);
}

template <typename RandomIt>
void make_deheap(RandomIt first, RandomIt last) {
  if (first == last) return;
  auto it = detail::get_parent(first, last - 1);
  while (it >= first) {
    detail::sift_down(first, last, it);
    --it;
  }
}

template <typename RandomIt>
RandomIt get_max(RandomIt first, RandomIt last) {
  RandomIt largest = first;
  for (RandomIt candidate : {first + 1, first + 2})
    if (candidate < last && (*candidate > *largest)) largest = candidate;
  return largest;
}

}  // namespace deheap
