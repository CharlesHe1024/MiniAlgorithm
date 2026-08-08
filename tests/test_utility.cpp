//
// Created by wang.he on 2026/8/6.
//

#include "test_frame_work.h"
#include <iostream>
#include <memory>
#include <minialgo/Utility.h>
#include <string>

void testMaxInt() {
    ASSERT_EQ(minialgo::max(3, 5), 5);
    ASSERT_EQ(minialgo::max(5, 3), 5);
    ASSERT_EQ(minialgo::max(-3, -5), -3);
}

void testMaxDouble() {
    ASSERT_EQ(minialgo::max(3.14, 2.71), 3.14);
    ASSERT_EQ(minialgo::max(-1.5, -2.0), -1.5);
}

void testMaxString() {
    std::string a = "apple";
    std::string b = "banana";

    ASSERT_EQ(minialgo::max(a, b), b);
}

void testMaxEqual() {
    ASSERT_EQ(minialgo::max(5, 5), 5);
}

class Person {
  public:
    Person(std::string name, int age) : name_(std::move(name)), age_(age) {}

    const std::string& name() const noexcept {
        return name_;
    }

    int age() const noexcept {
        return age_;
    }

    bool operator>(const Person& other) const {
        return age_ > other.age_;
    }

    bool operator<(const Person& other) const {
        return age_ < other.age_;
    }

    bool operator==(const Person& other) const {
        return name_ == other.name_ && age_ == other.age_;
    }

  private:
    std::string name_;
    int age_;
};

void testMaxCustomType() {
    Person alice("Alice", 18);
    Person bob("Bob", 20);

    ASSERT_EQ(minialgo::max(alice, bob), bob);
}

void testMaxReturnReference() {
    int a = 3;
    int b = 5;

    const int& r = minialgo::max(a, b);

    ASSERT_TRUE(&r == &b);
}

void testMaxReturnReferenceWhenFirstIsGreater() {
    int a = 8;
    int b = 5;

    const int& r = minialgo::max(a, b);

    ASSERT_TRUE(&r == &a);
}

void testMaxReturnsFirstWhenEqual() {
    int a = 5;
    int b = 5;

    const int& result = minialgo::max(a, b);

    ASSERT_TRUE(&result == &a);
}

void testMinInt() {
    ASSERT_EQ(minialgo::min(3, 5), 3);
    ASSERT_EQ(minialgo::min(5, 3), 3);
    ASSERT_EQ(minialgo::min(-3, -5), -5);
}

void testMinDouble() {
    ASSERT_EQ(minialgo::min(3.14, 2.71), 2.71);
    ASSERT_EQ(minialgo::min(-1.5, -2.0), -2.0);
}

void testMinString() {
    std::string a = "apple";
    std::string b = "banana";

    ASSERT_EQ(minialgo::min(a, b), a);
}

void testMinCustomType() {
    Person alice("Alice", 18);
    Person bob("Bob", 20);

    ASSERT_EQ(minialgo::min(alice, bob), alice);
}

void testMinReturnsOriginalObject() {
    int a = 3;
    int b = 5;

    const int& result = minialgo::min(a, b);

    ASSERT_TRUE(&result == &a);
}

void testMinReturnsFirstWhenEqual() {
    int a = 5;
    int b = 5;

    const int& result = minialgo::min(a, b);

    ASSERT_TRUE(&result == &a);
}

void testMaxPersonByAge() {
    Person alice{"Alice", 18};
    Person bob{"Bob", 20};

    const Person& result = minialgo::max(alice, bob, [](const Person& left, const Person& right) {
        return left.age() < right.age();
    });

    ASSERT_TRUE(&result == &bob);
}

void testMaxPersonByName() {
    Person alice{"Alice", 30};
    Person bob{"Bob", 20};

    const Person& result = minialgo::max(alice, bob, [](const Person& left, const Person& right) {
        return left.name() < right.name();
    });

    ASSERT_TRUE(&result == &bob);
}

void testClampValueInsideRange() {
    int value = 5;
    int low = 0;
    int high = 10;

    const int& result = minialgo::clamp(value, low, high);

    ASSERT_TRUE(&result == &value);
}

void testClampValueBelowRange() {
    int value = -3;
    int low = 0;
    int high = 10;

    const int& result = minialgo::clamp(value, low, high);

    ASSERT_TRUE(&result == &low);
}

void testClampValueAboveRange() {
    int value = 20;
    int low = 0;
    int high = 10;

    const int& result = minialgo::clamp(value, low, high);

    ASSERT_TRUE(&result == &high);
}

void testClampAtLowerBoundary() {
    int value = 0;
    int low = 0;
    int high = 10;

    const int& result = minialgo::clamp(value, low, high);

    ASSERT_TRUE(&result == &value);
}

void testClampAtUpperBoundary() {
    int value = 10;
    int low = 0;
    int high = 10;

    const int& result = minialgo::clamp(value, low, high);

    ASSERT_TRUE(&result == &value);
}

void testClampPersonByAge() {
    Person young{"Young", 18};
    Person middle{"Middle", 30};
    Person old{"Old", 60};

    Person value{"Charles", 70};

    const Person& result =
        minialgo::clamp(value, young, old, [](const Person& left, const Person& right) {
            return left.age() < right.age();
        });

    ASSERT_TRUE(&result == &old);
}

void testClampInvalidRangeThrows() {
    ASSERT_THROW(minialgo::clamp(5, 10, 0), std::invalid_argument);
}

void testSwapInt() {
    int a = 3;
    int b = 5;

    minialgo::swap(a, b);

    ASSERT_EQ(a, 5);
    ASSERT_EQ(b, 3);
}

void testSwapString() {
    std::string a = "apple";
    std::string b = "banana";

    minialgo::swap(a, b);

    ASSERT_EQ(a, std::string{"banana"});
    ASSERT_EQ(b, std::string{"apple"});
}

void testSwapUniquePtr() {
    auto first = std::make_unique<int>(10);
    auto second = std::make_unique<int>(20);

    minialgo::swap(first, second);

    ASSERT_EQ(*first, 20);
    ASSERT_EQ(*second, 10);
}

void testSwapSameObject() {
    std::string value = "hello";

    minialgo::swap(value, value);

    ASSERT_EQ(value, std::string{"hello"});
}

int main() {
    testMaxInt();
    testMaxDouble();
    testMaxString();
    testMaxEqual();
    testMaxCustomType();
    testMaxReturnReference();
    testMaxReturnReferenceWhenFirstIsGreater();
    testMaxReturnsFirstWhenEqual();
    testMinInt();
    testMinDouble();
    testMinString();
    testMinCustomType();
    testMinReturnsOriginalObject();
    testMinReturnsFirstWhenEqual();
    testMaxPersonByAge();
    testMaxPersonByName();
    testClampValueInsideRange();
    testClampValueBelowRange();
    testClampValueAboveRange();
    testClampAtLowerBoundary();
    testClampAtUpperBoundary();
    testClampPersonByAge();
    testClampInvalidRangeThrows();
    testSwapInt();
    testSwapString();
    testSwapUniquePtr();
    testSwapSameObject();

    std::cout << "Utility tests passed\n";
    return 0;
}
