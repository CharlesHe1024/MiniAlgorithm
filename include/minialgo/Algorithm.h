//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <iterator>

namespace minialgo {
    template<typename InputIterator, typename T>
    InputIterator find(
        InputIterator first,
        InputIterator last,
        const T &value
    ) {
        while (first != last) {
            if (*first == value) {
                return first;
            }
            ++first;
        }
        return last;
    }

    template<typename InputIterator, typename T>
    auto count(
        InputIterator first,
        InputIterator last,
        const T &value
    ) {
        using DifferenceType =
                typename std::iterator_traits<InputIterator>
                ::difference_type;

        DifferenceType result{0};
        for (; first != last; ++first) {
            if (*first == value) {
                ++result;
            }
        }
        return result;
    }
}
