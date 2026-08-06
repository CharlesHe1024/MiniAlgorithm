//
// Created by wang.he on 2026/8/7.
//

#include "test_frame_work.h"

#include <minialgo/Algorithm.h>

#include <vector>
#include <iterator>

void testFindInVector() {
    std::vector<int> values{
        10, 20, 30, 40
    };

    const auto result =
            minialgo::find(
                values.begin(),
                values.end(),
                30
            );

    ASSERT_TRUE(result != values.end());
    ASSERT_EQ(*result, 30);
}

void testFindMissingValue() {
    std::vector<int> values{
        10, 20, 30
    };

    const auto result =
            minialgo::find(
                values.begin(),
                values.end(),
                100
            );

    ASSERT_TRUE(result == values.end());
}

#include <list>

void testFindInList() {
    std::list<std::string> values{
        "apple",
        "banana",
        "orange"
    };

    const auto result =
            minialgo::find(
                values.begin(),
                values.end(),
                std::string{"banana"}
            );

    ASSERT_TRUE(result != values.end());
    ASSERT_EQ(*result, std::string{"banana"});
}

void testFindInArray() {
    int values[]{10, 20, 30, 40};

    const auto result =
            minialgo::find(
                std::begin(values),
                std::end(values),
                20
            );

    ASSERT_TRUE(result != std::end(values));
    ASSERT_EQ(*result, 20);
}

void testFindWithPointers() {
    int values[]{10, 20, 30};

    int *first = values;
    int *last = values + 3;

    int *result =
            minialgo::find(
                first,
                last,
                30
            );

    ASSERT_TRUE(result != last);
    ASSERT_EQ(*result, 30);
}

void testCountInVector() {
    std::vector<int> values{
        1, 2, 1, 3, 1
    };

    const auto result =
            minialgo::count(
                values.begin(),
                values.end(),
                1
            );

    ASSERT_EQ(result, 3);
}

void testCountMissingValue() {
    std::vector<int> values{
        1, 2, 3
    };

    ASSERT_EQ(
        minialgo::count(
            values.begin(),
            values.end(),
            100
        ),
        0
    );
}

void testCountEmptyRange() {
    std::vector<int> values;

    ASSERT_EQ(
        minialgo::count(
            values.begin(),
            values.end(),
            1
        ),
        0
    );
}

void testCountInArray() {
    int values[]{1, 2, 1, 1, 3};

    ASSERT_EQ(
        minialgo::count(
            std::begin(values),
            std::end(values),
            1
        ),
        3
    );
}

class Person {
public:
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {
    }

    const std::string &name() const noexcept { return name_; }

    int age() const noexcept { return age_; }

    bool operator>(const Person &other) const {
        return age_ > other.age_;
    }

    bool operator<(const Person &other) const {
        return age_ < other.age_;
    }

    bool operator==(const Person &other) const {
        return name_ == other.name_
               && age_ == other.age_;
    }

private:
    std::string name_;
    int age_;
};

void testCountPerson() {
    std::vector<Person> people{
        Person{"Alice", 18},
        Person{"Bob", 20},
        Person{"Alice", 18}
    };

    const Person target{"Alice", 18};

    ASSERT_EQ(
        minialgo::count(
            people.begin(),
            people.end(),
            target
        ),
        2
    );
}

int main() {
    testFindInVector();
    testFindMissingValue();
    testFindInList();
    testFindInArray();
    testFindWithPointers();
    testCountInVector();
    testCountMissingValue();
    testCountEmptyRange();
    testCountInArray();
    testCountPerson();

    std::cout << "Algorithm tests passed\n";
    return 0;
}
