//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <minialgo/Iterator.h>

#include <concepts>
#include <functional>
#include <iterator>
#include <ranges>
#include <utility>

namespace minialgo {
template <std::input_iterator Iterator,
          std::sentinel_for<Iterator> Sentinel,
          typename T,
          typename Projection = std::identity>
    requires requires(Iterator iterator, const T& value, Projection projection) {
        { std::invoke(projection, *iterator) == value } -> std::convertible_to<bool>;
    }
Iterator find(Iterator first, Sentinel last, const T& value, Projection projection = {}) {
    while (first != last) {
        if (std::invoke(projection, *first) == value) {
            return first;
        }
        ++first;
    }
    return first;
}

template <std::ranges::input_range Range, typename T, typename Projection = std::identity>
    requires requires(Range&& range, const T& value, Projection projection) {
        {
            std::invoke(projection, *std::ranges::begin(range)) == value
        } -> std::convertible_to<bool>;
    }
std::ranges::borrowed_iterator_t<Range>
find(Range&& range, const T& value, Projection projection = {}) {
    auto result =
        minialgo::find(std::ranges::begin(range), std::ranges::end(range), value, projection);
    if constexpr (std::ranges::borrowed_range<Range>) {
        return result;
    } else {
        return std::ranges::dangling{};
    }
}

template <std::input_iterator Iterator,
          std::sentinel_for<Iterator> Sentinel,
          typename Predicate,
          typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
Iterator findIf(Iterator first, Sentinel last, Predicate predicate, Projection projection = {}) {
    while (first != last) {
        if (std::invoke(predicate, std::invoke(projection, *first))) {
            return first;
        }

        ++first;
    }

    return first;
}

template <std::ranges::input_range Range, typename Predicate, typename Projection = std::identity>
    requires requires(Range&& range, Predicate predicate, Projection projection) {
        {
            std::invoke(predicate, std::invoke(projection, *std::ranges::begin(range)))
        } -> std::convertible_to<bool>;
    }
std::ranges::borrowed_iterator_t<Range>
findIf(Range&& range, Predicate predicate, Projection projection = {}) {
    auto result =
        minialgo::findIf(std::ranges::begin(range), std::ranges::end(range), predicate, projection);

    if constexpr (std::ranges::borrowed_range<Range>) {
        return result;
    } else {
        return std::ranges::dangling{};
    }
}

template <std::input_iterator Iterator, typename T, typename Projection = std::identity>
    requires requires(Iterator iterator, const T& value, Projection projection) {
        { std::invoke(projection, *iterator) == value } -> std::convertible_to<bool>;
    }
auto count(Iterator first, Iterator last, const T& value, Projection projection = {}) {
    auto result = std::iter_difference_t<Iterator>{0};
    for (; first != last; ++first) {
        if (std::invoke(projection, *first) == value) {
            ++result;
        }
    }
    return result;
}

template <std::ranges::input_range Range, typename T, typename Projection = std::identity>
    requires requires(Range&& range, const T& value, Projection projection) {
        {
            std::invoke(projection, *std::ranges::begin(range)) == value
        } -> std::convertible_to<bool>;
    }
auto count(Range&& range, const T& value, Projection projection = {}) {
    return minialgo::count(std::ranges::begin(range), std::ranges::end(range), value, projection);
}

template <std::input_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
auto countIf(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    auto result = std::iter_difference_t<Iterator>{0};
    for (; first != last; ++first) {
        if (std::invoke(predicate, std::invoke(projection, *first))) {
            ++result;
        }
    }
    return result;
}

template <std::input_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
bool allOf(Iterator first, Iterator last, Predicate predicate, Projection project = {}) {
    for (; first != last; ++first) {
        if (!std::invoke(predicate, std::invoke(project, *first))) {
            return false;
        }
    }
    return true;
}

template <std::input_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
bool anyOf(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    for (; first != last; ++first) {
        if (std::invoke(predicate, std::invoke(projection, *first))) {
            return true;
        }
    }
    return false;
}

template <std::input_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
bool noneOf(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    return !minialgo::anyOf(first, last, std::move(predicate), std::move(projection));
}

template <std::input_iterator Iterator, typename Function>
    requires std::indirectly_unary_invocable<Function, Iterator>
Function forEach(Iterator first, Iterator last, Function function) {
    for (; first != last; ++first) {
        std::invoke(function, *first);
    }
    return function;
}

template <std::forward_iterator Iterator, typename T>
    requires std::indirectly_writable<Iterator, const T&>
void fill(Iterator first, Iterator last, const T& value) {
    for (; first != last; ++first) {
        *first = value;
    }
}

template <std::input_iterator InputIterator,
          typename OutputIterator,
          typename Operation,
          typename Projection = std::identity>
    requires std::indirectly_unary_invocable<Operation,
                                             std::projected<InputIterator, Projection>> &&
             std::indirectly_writable<
                 OutputIterator,
                 std::indirect_result_t<Operation, std::projected<InputIterator, Projection>>>
OutputIterator transform(InputIterator first,
                         InputIterator last,
                         OutputIterator destination,
                         Operation operation,
                         Projection projection = {}) {
    for (; first != last; ++first, ++destination) {
        *destination = std::invoke(operation, std::invoke(projection, *first));
    }
    return destination;
}

template <std::input_iterator InputIterator1,
          std::input_iterator InputIterator2,
          typename OutputIterator,
          typename BinaryOperation>
    requires requires(InputIterator1 input1,
                      InputIterator2 input2,
                      OutputIterator output,
                      BinaryOperation operation) {
        *output = std::invoke(operation, *input1, *input2);
    }
OutputIterator transform(InputIterator1 first1,
                         InputIterator1 last1,
                         InputIterator2 first2,
                         OutputIterator destination,
                         BinaryOperation operation) {
    for (; first1 != last1; ++first1, ++first2, ++destination) {
        *destination = std::invoke(operation, *first1, *first2);
    }
    return destination;
}

template <std::input_iterator InputIterator, typename OutputIterator>
    requires std::indirectly_copyable<InputIterator, OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator destinationFirst) {
    for (; first != last; ++first, ++destinationFirst) {
        *destinationFirst = *first;
    }
    return destinationFirst;
}

template <std::bidirectional_iterator InputIterator, std::bidirectional_iterator OutputIterator>
    requires std::indirectly_copyable<InputIterator, OutputIterator>
OutputIterator
copyBackward(InputIterator first, InputIterator last, OutputIterator destinationLast) {
    while (first != last) {
        --last;
        --destinationLast;
        *destinationLast = *last;
    }
    return destinationLast;
}

template <std::input_iterator InputIterator, typename OutputIterator>
    requires std::indirectly_movable<InputIterator, OutputIterator>
OutputIterator move(InputIterator first, InputIterator last, OutputIterator destination) {
    for (; first != last; ++first, ++destination) {
        *destination = std::ranges::iter_move(first);
    }
    return destination;
}

template <std::bidirectional_iterator InputIterator, std::bidirectional_iterator OutputIterator>
    requires std::indirectly_movable<InputIterator, OutputIterator>
OutputIterator
moveBackward(InputIterator first, InputIterator last, OutputIterator destinationLast) {
    while (first != last) {
        --last;
        --destinationLast;
        *destinationLast = std::ranges::iter_move(last);
    }
    return destinationLast;
}

template <std::input_iterator Iterator1, std::input_iterator Iterator2>
    requires std::indirectly_swappable<Iterator1, Iterator2>
void iterSwap(Iterator1 iterator1, Iterator2 iterator2) {
    std::ranges::iter_swap(iterator1, iterator2);
}

template <std::bidirectional_iterator Iterator>
    requires std::permutable<Iterator>
void reverse(Iterator first, Iterator last) {
    while (first != last) {
        --last;
        if (first == last) {
            break;
        }
        minialgo::iterSwap(first, last);
        ++first;
    }
}

template <std::bidirectional_iterator Iterator>
    requires std::permutable<Iterator>
Iterator rotate(Iterator first, Iterator middle, Iterator last) {
    if (first == middle) {
        return last;
    }
    if (middle == last) {
        return first;
    }

    auto rightSize = minialgo::distance(middle, last);
    minialgo::reverse(first, middle);
    minialgo::reverse(middle, last);
    minialgo::reverse(first, last);
    Iterator result = first;
    minialgo::advance(result, rightSize);
    return result;
}

template <std::bidirectional_iterator Iterator,
          typename Predicate,
          typename Projection = std::identity>
    requires std::permutable<Iterator> &&
             std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
Iterator partition(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    while (true) {
        while (first != last && std::invoke(predicate, std::invoke(projection, *first))) {
            ++first;
        }

        if (first == last) {
            return first;
        }

        do {
            --last;

            if (first == last) {
                return first;
            }
        } while (!std::invoke(predicate, std::invoke(projection, *last)));

        minialgo::iterSwap(first, last);
        ++first;
    }
}

template <std::forward_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
Iterator
partitionPoint(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    auto count = minialgo::distance(first, last);

    while (count > 0) {
        auto step = count / 2;

        Iterator middle = first;
        minialgo::advance(middle, step);

        if (std::invoke(predicate, std::invoke(projection, *middle))) {

            first = middle;
            ++first;
            count -= step + 1;

        } else {

            count = step;
        }
    }

    return first;
}

template <std::forward_iterator Iterator, typename Predicate, typename Projection = std::identity>
    requires std::permutable<Iterator> &&
             std::indirect_unary_predicate<Predicate, std::projected<Iterator, Projection>>
Iterator removeIf(Iterator first, Iterator last, Predicate predicate, Projection projection = {}) {
    first = minialgo::findIf(first, last, predicate, projection);

    if (first == last) {
        return first;
    }

    auto current = first;
    ++current;

    for (; current != last; ++current) {
        if (!std::invoke(predicate, std::invoke(projection, *current))) {

            *first = std::ranges::iter_move(current);
            ++first;
        }
    }

    return first;
}

template <std::forward_iterator Iterator, typename T, typename Projection = std::identity>
    requires std::permutable<Iterator> &&
             requires(Iterator iterator, const T& value, Projection projection) {
                 { std::invoke(projection, *iterator) == value } -> std::convertible_to<bool>;
             }
Iterator remove(Iterator first, Iterator last, const T& value, Projection projection = {}) {
    return minialgo::removeIf(
        first, last, [&value](const auto& projected) { return projected == value; }, projection);
}

template <std::forward_iterator Iterator,
          typename BinaryPredicate = std::equal_to<>,
          typename Projection = std::identity>
    requires std::permutable<Iterator> &&
             std::indirect_binary_predicate<BinaryPredicate,
                                            std::projected<Iterator, Projection>,
                                            std::projected<Iterator, Projection>>
Iterator
unique(Iterator first, Iterator last, BinaryPredicate predicate = {}, Projection projection = {}) {
    if (first == last) {
        return last;
    }

    Iterator result = first;
    Iterator current = first;
    ++current;

    for (; current != last; ++current) {
        if (!std::invoke(
                predicate, std::invoke(projection, *result), std::invoke(projection, *current))) {

            ++result;

            if (result != current) {
                *result = std::ranges::iter_move(current);
            }
        }
    }

    ++result;
    return result;
}

template <std::forward_iterator Iterator,
          typename T,
          typename Compare = std::less<>,
          typename Projection = std::identity>
    requires std::
        indirect_strict_weak_order<Compare, std::projected<Iterator, Projection>, const T*>
    Iterator lowerBound(Iterator first,
                        Iterator last,
                        const T& value,
                        Compare compare = {},
                        Projection projection = {}) {
    auto count = minialgo::distance(first, last);

    while (count > 0) {
        auto step = count / 2;
        Iterator middle = first;
        minialgo::advance(middle, step);

        if (std::invoke(compare, std::invoke(projection, *middle), value)) {
            first = middle;
            ++first;
            count -= step + 1;
        } else {
            count = step;
        }
    }
    return first;
}

template <std::forward_iterator Iterator,
          typename T,
          typename Compare = std::less<>,
          typename Projection = std::identity>
    requires std::
        indirect_strict_weak_order<Compare, std::projected<Iterator, Projection>, const T*>
    Iterator upperBound(Iterator first,
                        Iterator last,
                        const T& value,
                        Compare compare = {},
                        Projection projection = {}) {
    auto count = minialgo::distance(first, last);
    while (count > 0) {
        auto step = count / 2;
        Iterator middle = first;
        minialgo::advance(middle, step);
        if (std::invoke(compare, value, std::invoke(projection, *middle))) {
            count = step;
        } else {
            first = middle;
            ++first;
            count -= step + 1;
        }
    }
    return first;
}

template <std::forward_iterator Iterator,
          typename T,
          typename Compare = std::less<>,
          typename Projection = std::identity>
    requires std::
        indirect_strict_weak_order<Compare, std::projected<Iterator, Projection>, const T*>
    bool binarySearch(Iterator first,
                      Iterator last,
                      const T& value,
                      Compare compare = {},
                      Projection projection = {}) {
    const auto it = minialgo::lowerBound(first, last, value, compare, projection);
    if (it == last) {
        return false;
    }
    auto&& projected = std::invoke(projection, *it);
    return !std::invoke(compare, projected, value) && !std::invoke(compare, value, projected);
}

template <std::forward_iterator Iterator,
          typename T,
          typename Compare = std::less<>,
          typename Projection = std::identity>
    requires std::
        indirect_strict_weak_order<Compare, std::projected<Iterator, Projection>, const T*>
    auto equalRange(Iterator first,
                    Iterator last,
                    const T& value,
                    Compare compare = {},
                    Projection projection = {}) {
    auto lower = minialgo::lowerBound(first, last, value, compare, projection);
    auto upper = minialgo::upperBound(lower, last, value, compare, projection);
    return std::pair(lower, upper);
}

template <std::random_access_iterator Iterator,
          typename Compare = std::less<>,
          typename Projection = std::identity>
    requires std::sortable<Iterator, Compare, Projection>
void sort(Iterator first, Iterator last, Compare compare = {}, Projection projection = {}) {
    if (last - first <= 1) {
        return;
    }
    auto pivot = std::invoke(projection, *(first + (last - first) / 2));
    Iterator left = first;
    Iterator right = last - 1;
    while (left <= right) {
        while (std::invoke(compare, std::invoke(projection, *left), pivot)) {
            ++left;
        }
        while (std::invoke(compare, pivot, std::invoke(projection, *right))) {
            --right;
        }
        if (left <= right) {
            minialgo::iterSwap(left, right);
            ++left;
            --right;
        }
    }
    if (first < right + 1) {
        minialgo::sort(first, right + 1, compare, projection);
    }
    if (left < last) {
        minialgo::sort(left, last, compare, projection);
    }
}
} // namespace minialgo
