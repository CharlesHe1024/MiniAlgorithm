//
// Created by wang.he on 2026/8/7.
//

#include <minialgo/IteratorTraits.h>

#include <iostream>
#include <type_traits>
#include <vector>
#include <list>

void testVectorIteratorTraits() {
    using Iterator = std::vector<int>::iterator;
    using Traits = minialgo::IteratorTraits<Iterator>;

    static_assert(
        std::is_same_v<
            Traits::value_type,
            int>
    );

    static_assert(
        std::is_same_v<
            Traits::iterator_category,
            std::random_access_iterator_tag
        >
    );
}

void testListIteratorTraits() {
    using Iterator = std::list<int>::iterator;
    using Traits = minialgo::IteratorTraits<Iterator>;

    static_assert(
        std::is_same_v<
            Traits::value_type,
            int>
    );

    static_assert(
        std::is_same_v<
            Traits::iterator_category,
            std::bidirectional_iterator_tag
        >
    );
}

void testPointerIteratorTraits() {
    using Traits =
            minialgo::IteratorTraits<int *>;

    static_assert(
        std::is_same_v<
            Traits::value_type,
            int>
    );

    static_assert(
        std::is_same_v<
            Traits::pointer,
            int *>
    );

    static_assert(
        std::is_same_v<
            Traits::reference,
            int &>
    );

    static_assert(
        std::is_same_v<
            Traits::iterator_category,
            std::random_access_iterator_tag
        >
    );
}

int main() {
    testVectorIteratorTraits();
    testListIteratorTraits();

    std::cout << "Iterator Traits tests passed\n";
    return 0;
}
