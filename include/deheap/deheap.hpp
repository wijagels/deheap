#pragma once

#include <utility>
#include <vector>

namespace deheap {

template <typename T, typename Container = std::vector<T>>
class deheap_queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  deheap_queue() = default;
  deheap_queue(const Container &cont);
  deheap_queue(Container &&cont);

  void push(const value_type &value);
  void push(value_type &&value);
  template <class... Args>
  void emplace(Args &&...args);

  const_reference min() const;
  const_reference max() const;

  bool empty() const;
  size_type size() const;

  void pop_min();
  void pop_max();

  void swap(deheap_queue &other) noexcept(noexcept(std::swap(c, other.c)));

 protected:
  Container c;
};

}  // namespace deheap

#include "deheap.ipp"
