#pragma once

#include "deheap/functions.hpp"

namespace deheap {

template <typename T, typename Container>
deheap_queue<T, Container>::deheap_queue(const Container &cont) : c{cont} {
  make_deheap(std::begin(c), std::end(c));
}

template <typename T, typename Container>
deheap_queue<T, Container>::deheap_queue(Container &&cont)
    : c{std::move(cont)} {
  make_deheap(std::begin(c), std::end(c));
}

template <typename T, typename Container>
void deheap_queue<T, Container>::push(const value_type &value) {
  c.push_back(value);
  push_deheap(std::begin(c), std::end(c));
}

template <typename T, typename Container>
void deheap_queue<T, Container>::push(value_type &&value) {
  c.push_back(std::move(value));
  push_deheap(std::begin(c), std::end(c));
}

template <typename T, typename Container>
template <typename... Args>
void deheap_queue<T, Container>::emplace(Args &&...args) {
  c.emplace_back(std::forward<Args>(args)...);
  push_deheap(std::begin(c), std::end(c));
}

template <typename T, typename Container>
typename deheap_queue<T, Container>::const_reference
deheap_queue<T, Container>::min() const {
  return c.front();
}

template <typename T, typename Container>
typename deheap_queue<T, Container>::const_reference
deheap_queue<T, Container>::max() const {
  return *get_max(std::begin(c), std::end(c));
}

template <typename T, typename Container>
bool deheap_queue<T, Container>::empty() const {
  return c.empty();
}

template <typename T, typename Container>
typename deheap_queue<T, Container>::size_type
deheap_queue<T, Container>::size() const {
  return c.size();
}

template <typename T, typename Container>
void deheap_queue<T, Container>::pop_min() {
  deheap::pop_min(std::begin(c), std::end(c));
  c.pop_back();
}

template <typename T, typename Container>
void deheap_queue<T, Container>::pop_max() {
  deheap::pop_max(std::begin(c), std::end(c));
  c.pop_back();
}

template <typename T, typename Container>
void deheap_queue<T, Container>::swap(deheap_queue &other) noexcept(
    noexcept(std::swap(c, other.c))) {
  std::swap(c, other.c);
}

}  // namespace deheap
