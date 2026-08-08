//
// Created by wang.he on 2026/8/7.
//

#include "test_frame_work.h"

#include <minialgo/Iterator.h>

#include <list>
#include <vector>

void testDistanceVector() {
    std::vector<int> values{10, 20, 30, 40, 50};

    const auto result = minialgo::distance(values.begin(), values.end());

    ASSERT_EQ(result, 5);
}

void testDistanceList() {
    std::list<int> values{10, 20, 30, 40, 50};

    const auto result = minialgo::distance(values.begin(), values.end());

    ASSERT_EQ(result, 5);
}

void testDistancePointer() {
    int values[]{10, 20, 30, 40};

    const auto result = minialgo::distance(values, values + 4);

    ASSERT_EQ(result, 4);
}

void testAdvanceVector() {
    std::vector<int> values{10, 20, 30, 40, 50};

    auto iterator = values.begin();

    minialgo::advance(iterator, 3);

    ASSERT_EQ(*iterator, 40);
}

void testAdvanceListForward() {
    std::list<int> values{10, 20, 30, 40};

    auto iterator = values.begin();

    minialgo::advance(iterator, 2);

    ASSERT_EQ(*iterator, 30);
}

void testAdvanceListBackward() {
    std::list<int> values{10, 20, 30, 40};

    auto iterator = values.end();

    minialgo::advance(iterator, -2);

    ASSERT_EQ(*iterator, 30);
}

void testAdvancePointer() {
    int values[]{10, 20, 30, 40};

    int* iterator = values;

    minialgo::advance(iterator, 2);

    ASSERT_EQ(*iterator, 30);
}

int main() {
    testDistanceVector();
    testDistanceList();
    testDistancePointer();
    testAdvanceVector();
    testAdvanceListForward();
    testAdvanceListBackward();
    testAdvancePointer();

    std::cout << "Iterator tests passed\n";
    return 0;
}
