//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <iterator>

namespace minialgo {
    template<typename InputIterator, typename T>
    InputIterator find(InputIterator first, InputIterator last, const T &value) {
        while (first != last) {
            if (*first == value) {
                return first;
            }
            ++first;
        }
        return last;
    }

    template<typename InputIterator, typename T>
    auto count(InputIterator first, InputIterator last, const T &value) {
        using DifferenceType =
                typename std::iterator_traits<InputIterator>::difference_type;

        DifferenceType result{0};
        for (; first != last; ++first) {
            if (*first == value) {
                ++result;
            }
        }
        return result;
    }

    template<typename InputIterator, typename Function>
    Function for_each(InputIterator first, InputIterator last, Function function) {
        for (; first != last; ++first) {
            function(*first);
        }
        return function;
    }

    template<typename InputIterator, typename OutputIterator>
    OutputIterator copy(
        InputIterator first,
        InputIterator last,
        OutputIterator destination
    ) {
        for (; first != last; ++first, ++destination) {
            *destination = *first;
        }
        return destination;
    }

    template<typename ForwardIterator, typename T>
    void fill(
        ForwardIterator first,
        ForwardIterator last,
        const T &value
    ) {
        for (; first != last; ++first) {
            *first = value;
        }
    }

    template<typename InputIterator, typename OutputIterator, typename UnaryOperation>
    OutputIterator transform(
        InputIterator first,
        InputIterator last,
        OutputIterator destination,
        UnaryOperation operation
    ) {
        for (; first != last; ++first, ++destination) {
            *destination = operation(*first);
        }
        return destination;
    }
} // namespace minialgo
