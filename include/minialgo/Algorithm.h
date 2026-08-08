//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <minialgo/Iterator.h>

#include <iterator>
#include <functional>
#include <concepts>


namespace minialgo {
    template<std::input_iterator Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T &value) {
        while (first != last) {
            if (*first == value) {
                return first;
            }
            ++first;
        }
        return last;
    }

    template<
        std::input_iterator Iterator,
        typename Predicate,
        typename Projection = std::identity>
        requires requires(
    Iterator iterator,
    Predicate predicate,
    Projection projection
)
        {
            {
                std::invoke(
                    predicate,
                    std::invoke(projection, *iterator)
                )
            } -> std::convertible_to<bool>;
        }
    Iterator findIf(
        Iterator first,
        Iterator last,
        Predicate predicate,
        Projection projection = {}
    ) {
        while (first != last) {
            if (
                std::invoke(predicate,
                            std::invoke(projection, *first)
                )
            ) {
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

    template<
        std::input_iterator Iterator,
        typename Predicate,
        typename Projection = std::identity>
        requires requires(
    Iterator iterator,
    Predicate predicate,
    Projection projection
)
        {
            {
                std::invoke(
                    predicate,
                    std::invoke(projection, *iterator)
                )
            } -> std::convertible_to<bool>;
        }
    auto countIf(
        Iterator first,
        Iterator last,
        Predicate predicate,
        Projection projection = {}
    ) {
        using DifferenceType = typename std::iterator_traits<Iterator>::difference_type;
        DifferenceType result{0};
        for (; first != last; ++first) {
            if (
                std::invoke(
                    predicate,
                    std::invoke(projection, *first)
                )
            ) {
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

    template<
        std::input_iterator InputIterator,
        typename OutputIterator
    >
        requires std::indirectly_copyable<
            InputIterator,
            OutputIterator
        >
    OutputIterator copy(
        InputIterator first,
        InputIterator last,
        OutputIterator destinationFirst
    ) {
        for (; first != last; ++first, ++destinationFirst) {
            *destinationFirst = *first;
        }
        return destinationFirst;
    }

    template<
        std::bidirectional_iterator InputIterator,
        std::bidirectional_iterator OutputIterator
    >
        requires std::indirectly_copyable<
            InputIterator,
            OutputIterator
        >
    OutputIterator copyBackward(
        InputIterator first,
        InputIterator last,
        OutputIterator destinationLast
    ) {
        while (first != last) {
            --last;
            --destinationLast;
            *destinationLast = *last;
        }
        return destinationLast;
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

    template<
        std::input_iterator Iterator,
        typename Predicate,
        typename Project = std::identity>
        requires requires(
    Iterator iterator,
    Predicate predicate,
    Project project)
        {
            std::invoke(project, *iterator);
            {
                std::invoke(
                    predicate,
                    std::invoke(project, *iterator)
                )
            } -> std::convertible_to<bool>;
        }
    bool allOf(
        Iterator first,
        Iterator last,
        Predicate predicate,
        Project project = {}
    ) {
        for (; first != last; ++first) {
            if (
                !std::invoke(
                    predicate,
                    std::invoke(project, *first)
                )
            ) {
                return false;
            }
        }
        return true;
    }

    template<
        std::input_iterator Iterator,
        typename Predicate,
        typename Projection = std::identity>
        requires requires(
    Iterator iterator,
    Predicate predicate,
    Projection projection
)
        {
            {
                std::invoke(
                    predicate,
                    std::invoke(projection, *iterator)
                )
            } -> std::convertible_to<bool>;
        }
    bool anyOf(
        Iterator first,
        Iterator last,
        Predicate predicate,
        Projection projection = {}
    ) {
        for (; first != last; ++first) {
            if (
                std::invoke(
                    predicate,
                    std::invoke(projection, *first)
                )
            ) {
                return true;
            }
        }
        return false;
    }

    template<
        std::input_iterator Iterator,
        typename Predicate,
        typename Projection = std::identity>
        requires requires(
    Iterator iterator,
    Predicate predicate,
    Projection projection
)
        {
            {
                std::invoke(
                    predicate,
                    std::invoke(projection, *iterator)
                )
            } -> std::convertible_to<bool>;
        }
    bool noneOf(
        Iterator first,
        Iterator last,
        Predicate predicate,
        Projection projection = {}
    ) {
        return !anyOf(
            first,
            last,
            std::move(predicate),
            std::move(projection)
        );
    }

    template<
        std::forward_iterator Iterator,
        typename T,
        typename Compare = std::less<>,
        typename Projection = std::identity>
        requires requires(
    Iterator iterator,
    const T &value,
    Compare compare,
    Projection projection)
        {
            {
                std::invoke(
                    compare,
                    std::invoke(projection, *iterator),
                    value
                )
            } -> std::convertible_to<bool>;
        }
    Iterator lowerBound(
        Iterator first,
        Iterator last,
        const T &value,
        Compare compare = {},
        Projection projection = {}
    ) {
        auto count = minialgo::distance(first, last);

        while (count > 0) {
            auto step = count / 2;
            Iterator middle = first;
            minialgo::advance(middle, step);

            if (
                std::invoke(
                    compare,
                    std::invoke(projection, *middle),
                    value
                )
            ) {
                first = middle;
                ++first;
                count -= step + 1;
            } else {
                count = step;
            }
        }
        return first;
    }
} // namespace minialgo
