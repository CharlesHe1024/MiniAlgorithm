//
// Created by wang.he on 2026/8/7.
//

#pragma once

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace minialgo {
    template<typename Iterator>
    struct IteratorTraits {
        using value_type = typename Iterator::value_type;
        using difference_type = typename Iterator::difference_type;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
        using iterator_category = typename Iterator::iterator_category;
    };

    template<typename T>
    struct IteratorTraits<T *> {
        using value_type = std::remove_cv_t<T>;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;
    };
}
