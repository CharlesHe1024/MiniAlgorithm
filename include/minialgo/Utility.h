//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <stdexcept>
#include <utility>

namespace minialgo {

template<typename T>
const T& max(const T& a, const T& b)
{
  return a < b ? b : a;
}

template<typename T, typename Compare>
const T& max(
    const T& a,
    const T& b,
    Compare comp)
{
  return comp(a, b) ? b : a;
}

template<typename T>
const T& min(const T& a, const T& b)
{
  return b < a ? b : a;
}

template<typename T, typename Compare>
const T& min(
    const T& a,
    const T& b,
    Compare comp)
{
  return comp(b, a) ? b : a;
}

template<typename T>
const T& clamp(
    const T& value,
    const T& low,
    const T& high)
{
  if (high < low) {
    throw std::invalid_argument(
        "clamp: low is greater than high"
    );
  }

  if (value < low) {
    return low;
  }

  if (high < value) {
    return high;
  }

  return value;
}

template<typename T, typename Compare>
const T& clamp(
    const T& value,
    const T& low,
    const T& high,
    Compare comp)
{
  if (comp(high, low)) {
    throw std::invalid_argument(
        "clamp: low is greater than high"
    );
  }

  if (comp(value, low)) {
    return low;
  }

  if (comp(high, value)) {
    return high;
  }

  return value;
}

template<typename T>
void swap(T& a, T& b)
{
  if (&a == &b) {
    return;
  }

  T temporary = std::move(a);
  a = std::move(b);
  b = std::move(temporary);
}

} // namespace minialgo