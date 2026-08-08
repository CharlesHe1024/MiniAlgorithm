//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <iterator>
#include <stdexcept>
#include <type_traits>

#include "IteratorTraits.h"

namespace minialgo {
namespace detail {
template <typename InputIterator>
auto distanceImpl(InputIterator first, InputIterator last, std::input_iterator_tag) {
    using DifferenceType = typename IteratorTraits<InputIterator>::difference_type;

    DifferenceType result{0};

    while (first != last) {
        ++first;
        ++result;
    }

    return result;
}

template <typename RandomAccessIterator>
auto distanceImpl(RandomAccessIterator first,
                  RandomAccessIterator last,
                  std::random_access_iterator_tag) {
    return last - first;
}
} // namespace detail

template <typename Iterator> auto distance(Iterator first, Iterator last) {
    using Category = typename IteratorTraits<Iterator>::iterator_category;

    return detail::distanceImpl(first, last, Category{});
}

template <typename Iterator, typename Distance> void advance(Iterator& iterator, Distance n) {
    using Category = typename IteratorTraits<Iterator>::iterator_category;

    if constexpr (std::is_base_of_v<std::random_access_iterator_tag, Category>) {
        iterator += n;
    } else if constexpr (std::is_base_of_v<std::bidirectional_iterator_tag, Category>) {
        if (n >= 0) {
            while (n > 0) {
                ++iterator;
                --n;
            }
        } else {
            while (n < 0) {
                --iterator;
                ++n;
            }
        }
    } else {
        if (n < 0) {
            throw std::invalid_argument("advance: input iterator cannot move backward");
        }
        while (n > 0) {
            ++iterator;
            --n;
        }
    }
}
} // namespace minialgo
