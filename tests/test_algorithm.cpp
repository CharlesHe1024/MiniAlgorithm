//
// Created by wang.he on 2026/8/7.
//

#include "test_frame_work.h"

#include <minialgo/Algorithm.h>

#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <vector>

void testFindInVector() {
    std::vector<int> values{10, 20, 30, 40};

    const auto result = minialgo::find(values.begin(), values.end(), 30);

    ASSERT_TRUE(result != values.end());
    ASSERT_EQ(*result, 30);
}

void testFindMissingValue() {
    std::vector<int> values{10, 20, 30};

    const auto result = minialgo::find(values.begin(), values.end(), 100);

    ASSERT_TRUE(result == values.end());
}

#include <list>

void testFindInList() {
    std::list<std::string> values{"apple", "banana", "orange"};

    const auto result = minialgo::find(values.begin(), values.end(), std::string{"banana"});

    ASSERT_TRUE(result != values.end());
    ASSERT_EQ(*result, std::string{"banana"});
}

void testFindInArray() {
    int values[]{10, 20, 30, 40};

    const auto result = minialgo::find(std::begin(values), std::end(values), 20);

    ASSERT_TRUE(result != std::end(values));
    ASSERT_EQ(*result, 20);
}

void testFindWithPointers() {
    int values[]{10, 20, 30};

    int* first = values;
    int* last = values + 3;

    int* result = minialgo::find(first, last, 30);

    ASSERT_TRUE(result != last);
    ASSERT_EQ(*result, 30);
}

void testCountInVector() {
    std::vector<int> values{1, 2, 1, 3, 1};

    const auto result = minialgo::count(values.begin(), values.end(), 1);

    ASSERT_EQ(result, 3);
}

void testCountMissingValue() {
    std::vector<int> values{1, 2, 3};

    ASSERT_EQ(minialgo::count(values.begin(), values.end(), 100), 0);
}

void testCountEmptyRange() {
    std::vector<int> values;

    ASSERT_EQ(minialgo::count(values.begin(), values.end(), 1), 0);
}

void testCountInArray() {
    int values[]{1, 2, 1, 1, 3};

    ASSERT_EQ(minialgo::count(std::begin(values), std::end(values), 1), 3);
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

    [[nodiscard]] bool isAdult() {
        return age_ >= 18;
    }

  private:
    std::string name_;
    int age_;
};

void testCountPerson() {
    std::vector<Person> people{Person{"Alice", 18}, Person{"Bob", 20}, Person{"Alice", 18}};

    const Person target{"Alice", 18};

    ASSERT_EQ(minialgo::count(people.begin(), people.end(), target), 2);
}

void testForEachModifiesElements() {
    std::vector<int> values{1, 2, 3};

    minialgo::for_each(values.begin(), values.end(), [](int& value) { value *= 2; });

    ASSERT_EQ(values[0], 2);
    ASSERT_EQ(values[1], 4);
    ASSERT_EQ(values[2], 6);
}

void testForEachAccumulatesValues() {
    std::vector<int> values{1, 2, 3, 4};

    int sum = 0;

    minialgo::for_each(values.begin(), values.end(), [&sum](int value) { sum += value; });

    ASSERT_EQ(sum, 10);
}

struct MultiplyBy {
    int factor;

    void operator()(int& value) const {
        value *= factor;
    }
};

void testForEachWithFunctionObject() {
    std::vector<int> values{1, 2, 3};

    minialgo::for_each(values.begin(), values.end(), MultiplyBy{3});

    ASSERT_EQ(values[0], 3);
    ASSERT_EQ(values[1], 6);
    ASSERT_EQ(values[2], 9);
}

void testCopyToExistingRange() {
    std::vector<int> source{1, 2, 3};
    std::vector<int> destination(3);

    const auto result = minialgo::copy(source.begin(), source.end(), destination.begin());

    ASSERT_EQ(destination[0], 1);
    ASSERT_EQ(destination[1], 2);
    ASSERT_EQ(destination[2], 3);

    ASSERT_TRUE(result == destination.end());
}

void testCopyWithBackInserter() {
    std::vector<int> source{1, 2, 3};
    std::vector<int> destination;

    minialgo::copy(source.begin(), source.end(), std::back_inserter(destination));

    ASSERT_EQ(destination.size(), std::size_t{3});
    ASSERT_EQ(destination[0], 1);
    ASSERT_EQ(destination[1], 2);
    ASSERT_EQ(destination[2], 3);
}

void testCopyFromListToVector() {
    std::list<int> source{10, 20, 30};
    std::vector<int> destination;
    minialgo::copy(source.begin(), source.end(), std::back_inserter(destination));
    ASSERT_EQ(destination.size(), std::size_t{3});
    ASSERT_EQ(destination[0], 10);
    ASSERT_EQ(destination[1], 20);
    ASSERT_EQ(destination[2], 30);
}

void testFillVector() {
    std::vector<int> values{1, 2, 3, 4};
    minialgo::fill(values.begin(), values.end(), 10);
    ASSERT_EQ(values[0], 10);
    ASSERT_EQ(values[1], 10);
    ASSERT_EQ(values[2], 10);
    ASSERT_EQ(values[3], 10);
}

void testFillPartialRange() {
    std::vector<int> values{1, 2, 3, 4};

    minialgo::fill(values.begin() + 1, values.begin() + 3, 9);

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 9);
    ASSERT_EQ(values[2], 9);
    ASSERT_EQ(values[3], 4);
}

void testFillEmptyRange() {
    std::vector<int> values{1, 2, 3};

    minialgo::fill(values.begin(), values.begin(), 100);

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);
}

void testFillArray() {
    int values[] = {1, 2, 3};
    minialgo::fill(std::begin(values), std::end(values), 7);
    ASSERT_EQ(values[0], 7);
    ASSERT_EQ(values[1], 7);
    ASSERT_EQ(values[2], 7);
}

void testFillString() {
    std::vector<std::string> values{"a", "b", "c"};

    minialgo::fill(values.begin(), values.end(), std::string{"same"});

    ASSERT_EQ(values[0], std::string{"same"});
    ASSERT_EQ(values[1], std::string{"same"});
    ASSERT_EQ(values[2], std::string{"same"});
}

void testTransformSquaresValues() {
    std::vector<int> values{1, 2, 3};
    std::vector<int> destination(3);
    const auto result = minialgo::transform(
        values.begin(), values.end(), destination.begin(), [](const auto& v) { return v * v; });
    ASSERT_EQ(destination[0], 1);
    ASSERT_EQ(destination[1], 4);
    ASSERT_EQ(destination[2], 9);

    ASSERT_TRUE(result == destination.end());
}

void testTransformWithBackInserter() {
    std::vector<int> source{1, 2, 3};
    std::vector<std::string> destination;

    minialgo::transform(source.begin(),
                        source.end(),
                        std::back_inserter(destination),
                        [](int value) { return std::to_string(value); });

    ASSERT_EQ(destination.size(), std::size_t{3});
    ASSERT_EQ(destination[0], std::string{"1"});
    ASSERT_EQ(destination[1], std::string{"2"});
    ASSERT_EQ(destination[2], std::string{"3"});
}

void testTransformInPlace() {
    std::vector<int> values{1, 2, 3};

    minialgo::transform(
        values.begin(), values.end(), values.begin(), [](int value) { return value * 10; });

    ASSERT_EQ(values[0], 10);
    ASSERT_EQ(values[1], 20);
    ASSERT_EQ(values[2], 30);
}

void testTransformPersonToName() {
    std::vector<Person> people{Person{"Alice", 18}, Person{"Bob", 20}};

    std::vector<std::string> names;

    minialgo::transform(people.begin(),
                        people.end(),
                        std::back_inserter(names),
                        [](const Person& person) { return person.name(); });

    ASSERT_EQ(names[0], std::string{"Alice"});
    ASSERT_EQ(names[1], std::string{"Bob"});
}

// 普通函数
bool isEven(int value) {
    return value % 2 == 0;
}

// Function Object
struct GreaterThan {
    int threshold;

    bool operator()(int value) const {
        return value > threshold;
    }
};

void testFindIfWithLambda() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto it =
        minialgo::findIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(it != values.end());
    ASSERT_EQ(*it, 8);
}

void testFindIfWithFunctionObject() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto it = minialgo::findIf(values.begin(), values.end(), GreaterThan{7});

    ASSERT_TRUE(it != values.end());
    ASSERT_EQ(*it, 8);
}

void testFindIfWithFunction() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto it = minialgo::findIf(values.begin(), values.end(), isEven);

    ASSERT_TRUE(it != values.end());
    ASSERT_EQ(*it, 8);
}

void testFindIfNotFound() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto it = minialgo::findIf(values.begin(), values.end(), [](int value) { return value > 100; });

    ASSERT_TRUE(it == values.end());
}

void testFindIfClassMemberFunctionPointer() {
    std::vector<Person> persons{{"test", 1}, {"test", 3}, {"test", 8}, {"test", 19}, {"test", 30}};
    auto it = minialgo::findIf(persons.begin(), persons.end(), &Person::isAdult);
    ASSERT_TRUE(it != persons.end());
    ASSERT_EQ(it->age(), 19);
    ASSERT_TRUE(((*it).*(&Person::isAdult))());
}

void testFindIfClassMemberFunctionPointerUsingProjection() {
    std::vector<Person> persons{{"test", 1}, {"test", 3}, {"test", 8}, {"test", 19}, {"test", 30}};

    auto it = minialgo::findIf(
        persons.begin(), persons.end(), [](int age) { return age >= 18; }, &Person::age);
    ASSERT_TRUE(it != persons.end());
    ASSERT_EQ(it->age(), 19);
}

void testCountIfWithLambda() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto result =
        minialgo::countIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_EQ(result, 2);
}

void testCountIfWithFunctionObject() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto result = minialgo::countIf(values.begin(), values.end(), GreaterThan{7});

    ASSERT_EQ(result, 2);
}

void testCountIfWithFunction() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto result = minialgo::countIf(values.begin(), values.end(), isEven);

    ASSERT_EQ(result, 2);
}

void testCountIfNotFound() {
    std::vector<int> values{1, 3, 7, 8, 10};

    auto result =
        minialgo::countIf(values.begin(), values.end(), [](int value) { return value > 100; });

    ASSERT_EQ(result, 0);
}

void testCountIfClassMemberFunctionPointer() {
    std::vector<Person> persons{{"test", 1}, {"test", 3}, {"test", 8}, {"test", 19}, {"test", 30}};
    auto result = minialgo::countIf(persons.begin(), persons.end(), &Person::isAdult);
    ASSERT_EQ(result, 2);
}

void testCountIfClassMemberFunctionPointerUsingProjection() {
    std::vector<Person> persons{{"test", 1}, {"test", 3}, {"test", 8}, {"test", 19}, {"test", 30}};

    auto result = minialgo::countIf(
        persons.begin(), persons.end(), [](int age) { return age >= 18; }, &Person::age);
    ASSERT_EQ(result, 2);
}

void testAllOfTrue() {
    std::vector<int> values{2, 4, 6};

    ASSERT_TRUE(
        minialgo::allOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testAllOfFalse() {
    std::vector<int> values{2, 4, 5, 6};

    ASSERT_FALSE(
        minialgo::allOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testAllOfEmptyRange() {
    std::vector<int> values;

    ASSERT_TRUE(minialgo::allOf(values.begin(), values.end(), [](int value) { return value > 0; }));
}

void testAllOfWithProjection() {
    std::vector<Person> people{{"Alice", 20}, {"Bob", 25}, {"Charlie", 18}};

    ASSERT_TRUE(minialgo::allOf(
        people.begin(), people.end(), [](int age) { return age >= 18; }, &Person::age));
}

void testAnyOfTrue() {
    std::vector<int> values{1, 3, 4, 7};

    ASSERT_TRUE(
        minialgo::anyOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testAnyOfFalse() {
    std::vector<int> values{1, 3, 5, 7};

    ASSERT_TRUE(
        !minialgo::anyOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testAnyOfEmpty() {
    std::vector<int> values;

    ASSERT_TRUE(
        !minialgo::anyOf(values.begin(), values.end(), [](int value) { return value > 0; }));
}

void testAnyOfWithProjection() {
    std::vector<Person> people{{"Alice", 17}, {"Bob", 20}, {"Charlie", 15}};

    ASSERT_TRUE(minialgo::anyOf(
        people.begin(), people.end(), [](int age) { return age >= 18; }, &Person::age));
}

void testNoneOfTrue() {
    std::vector<int> values{1, 3, 5, 7};

    ASSERT_TRUE(
        minialgo::noneOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testNoneOfFalse() {
    std::vector<int> values{1, 3, 4, 7};

    ASSERT_TRUE(
        !minialgo::noneOf(values.begin(), values.end(), [](int value) { return value % 2 == 0; }));
}

void testNoneOfEmpty() {
    std::vector<int> values;

    ASSERT_TRUE(
        minialgo::noneOf(values.begin(), values.end(), [](int value) { return value > 0; }));
}

void testNoneOfWithProjection() {
    std::vector<Person> people{{"Alice", 17}, {"Bob", 16}, {"Charlie", 15}};

    ASSERT_TRUE(minialgo::noneOf(
        people.begin(), people.end(), [](int age) { return age >= 18; }, &Person::age));
}

void testCopyBackwardBasic() {
    std::vector<int> source{1, 2, 3};

    std::vector<int> destination(5, 0);

    auto result = minialgo::copyBackward(source.begin(), source.end(), destination.end());

    ASSERT_EQ(destination[0], 0);
    ASSERT_EQ(destination[1], 0);
    ASSERT_EQ(destination[2], 1);
    ASSERT_EQ(destination[3], 2);
    ASSERT_EQ(destination[4], 3);

    ASSERT_TRUE(result == destination.begin() + 2);
}

void testCopyBackwardOverlappingToRight() {
    std::vector<int> values{1, 2, 3, 4, 5};

    minialgo::copyBackward(values.begin(), values.begin() + 3, values.end());

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 1);
    ASSERT_EQ(values[3], 2);
    ASSERT_EQ(values[4], 3);
}

void testCopyBackwardList() {
    std::list<int> source{10, 20, 30};

    std::list<int> destination{0, 0, 0};

    auto result = minialgo::copyBackward(source.begin(), source.end(), destination.end());

    ASSERT_TRUE(result == destination.begin());

    auto it = destination.begin();

    ASSERT_EQ(*it, 10);
    ++it;

    ASSERT_EQ(*it, 20);
    ++it;

    ASSERT_EQ(*it, 30);
}

void testLowerBoundFindsFirstDuplicate() {
    std::vector<int> values{1, 3, 3, 3, 5};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 3);

    ASSERT_TRUE(it == values.begin() + 1);
    ASSERT_EQ(*it, 3);
}

void testLowerBoundInsertInMiddle() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 4);

    ASSERT_TRUE(it == values.begin() + 2);
    ASSERT_EQ(*it, 5);
}

void testLowerBoundBeforeAll() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 0);

    ASSERT_TRUE(it == values.begin());
}

void testLowerBoundAfterAll() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 10);

    ASSERT_TRUE(it == values.end());
}

void testLowerBoundList() {
    std::list<int> values{1, 3, 5, 7, 9};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 6);

    ASSERT_TRUE(it != values.end());
    ASSERT_EQ(*it, 7);
}

void testLowerBoundWithProjection() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people{{"Alice", 16}, {"Bob", 18}, {"Charlie", 18}, {"David", 25}};

    auto it = minialgo::lowerBound(people.begin(), people.end(), 18, std::less<>{}, &Person::age);

    ASSERT_TRUE(it != people.end());
    ASSERT_EQ(it->name, std::string{"Bob"});
    ASSERT_EQ(it->age, 18);
}

void testLowerBoundDescending() {
    std::vector<int> values{9, 7, 5, 3, 1};

    auto it = minialgo::lowerBound(values.begin(), values.end(), 6, std::greater<>{});

    ASSERT_TRUE(it == values.begin() + 2);
    ASSERT_EQ(*it, 5);
}

void testLowerBoundEmpty() {
    std::vector<int> values;

    auto it = minialgo::lowerBound(values.begin(), values.end(), 10);

    ASSERT_TRUE(it == values.end());
}

void testBinarySearchFound() {
    std::vector<int> values{1, 3, 5, 7, 9};

    ASSERT_TRUE(minialgo::binarySearch(values.begin(), values.end(), 5));
}

void testBinarySearchNotFound() {
    std::vector<int> values{1, 3, 5, 7, 9};

    ASSERT_TRUE(!minialgo::binarySearch(values.begin(), values.end(), 6));
}

void testBinarySearchDuplicate() {
    std::vector<int> values{1, 3, 3, 3, 5};

    ASSERT_TRUE(minialgo::binarySearch(values.begin(), values.end(), 3));
}

void testBinarySearchWithProjection() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people{{"Alice", 16}, {"Bob", 18}, {"Charlie", 20}};

    ASSERT_TRUE(
        minialgo::binarySearch(people.begin(), people.end(), 18, std::less<>{}, &Person::age));
}

void testBinarySearchDescending() {
    std::vector<int> values{9, 7, 5, 3, 1};

    ASSERT_TRUE(minialgo::binarySearch(values.begin(), values.end(), 5, std::greater<>{}));
}

void testUpperBoundBasic() {
    std::vector<int> values{1, 3, 3, 3, 5, 7};

    auto it = minialgo::upperBound(values.begin(), values.end(), 3);

    ASSERT_TRUE(it == values.begin() + 4);
    ASSERT_EQ(*it, 5);
}

void testUpperBoundMissingValue() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::upperBound(values.begin(), values.end(), 4);

    ASSERT_TRUE(it == values.begin() + 2);
    ASSERT_EQ(*it, 5);
}

void testUpperBoundBeforeAll() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::upperBound(values.begin(), values.end(), 0);

    ASSERT_TRUE(it == values.begin());
}

void testUpperBoundAfterAll() {
    std::vector<int> values{1, 3, 5, 7};

    auto it = minialgo::upperBound(values.begin(), values.end(), 10);

    ASSERT_TRUE(it == values.end());
}

void testUpperBoundWithProjection() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people{{"Alice", 16}, {"Bob", 18}, {"Charlie", 18}, {"David", 25}};

    auto it = minialgo::upperBound(people.begin(), people.end(), 18, std::less<>{}, &Person::age);

    ASSERT_TRUE(it != people.end());
    ASSERT_EQ(it->name, std::string{"David"});
    ASSERT_EQ(it->age, 25);
}

void testUpperBoundDescending() {
    std::vector<int> values{9, 7, 5, 5, 3, 1};

    auto it = minialgo::upperBound(values.begin(), values.end(), 5, std::greater<>{});

    ASSERT_TRUE(it == values.begin() + 4);
    ASSERT_EQ(*it, 3);
}

void testEqualRange() {
    std::vector<int> values{1, 3, 3, 3, 5, 7};

    auto [first, last] = minialgo::equalRange(values.begin(), values.end(), 3);

    ASSERT_TRUE(first == values.begin() + 1);

    ASSERT_TRUE(last == values.begin() + 4);

    ASSERT_EQ(minialgo::distance(first, last), 3);
}

void testEqualRangeNotFound() {
    std::vector<int> values{1, 3, 5, 7};

    auto [first, last] = minialgo::equalRange(values.begin(), values.end(), 4);

    ASSERT_TRUE(first == last);
    ASSERT_TRUE(first == values.begin() + 2);
}

void testBinaryTransformInt() {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{10, 20, 30};
    std::vector<int> result(3);

    auto out = minialgo::transform(a.begin(), a.end(), b.begin(), result.begin(), std::plus<>{});

    ASSERT_EQ(result[0], 11);
    ASSERT_EQ(result[1], 22);
    ASSERT_EQ(result[2], 33);

    ASSERT_TRUE(out == result.end());
}

void testBinaryTransformDifferentTypes() {
    std::vector<int> a{1, 2, 3};
    std::vector<double> b{0.5, 1.5, 2.5};
    std::vector<double> result(3);

    minialgo::transform(a.begin(), a.end(), b.begin(), result.begin(), std::plus<>{});

    ASSERT_EQ(result[0], 1.5);
    ASSERT_EQ(result[1], 3.5);
    ASSERT_EQ(result[2], 5.5);
}

void testBinaryTransformCustomOperation() {
    std::vector<int> a{2, 3, 4};
    std::vector<int> b{10, 20, 30};
    std::vector<int> result(3);

    minialgo::transform(
        a.begin(), a.end(), b.begin(), result.begin(), [](int x, int y) { return x * y; });

    ASSERT_EQ(result[0], 20);
    ASSERT_EQ(result[1], 60);
    ASSERT_EQ(result[2], 120);
}

void testBinaryTransformDifferentOutputType() {
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{2, 4, 6};
    std::vector<double> result(3);

    minialgo::transform(a.begin(), a.end(), b.begin(), result.begin(), [](int x, int y) {
        return static_cast<double>(x) / y;
    });

    ASSERT_EQ(result[0], 0.5);
    ASSERT_EQ(result[1], 0.5);
    ASSERT_EQ(result[2], 0.5);
}

void testTransformOverloads() {
    std::vector<int> values{1, 2, 3};

    std::vector<int> unaryResult(3);

    minialgo::transform(
        values.begin(), values.end(), unaryResult.begin(), [](int x) { return x * 2; });

    ASSERT_EQ(unaryResult[0], 2);
    ASSERT_EQ(unaryResult[1], 4);
    ASSERT_EQ(unaryResult[2], 6);

    std::vector<int> other{10, 20, 30};
    std::vector<int> binaryResult(3);

    minialgo::transform(
        values.begin(), values.end(), other.begin(), binaryResult.begin(), std::plus<>{});

    ASSERT_EQ(binaryResult[0], 11);
    ASSERT_EQ(binaryResult[1], 22);
    ASSERT_EQ(binaryResult[2], 33);
}

struct MoveTracker {
    std::string value;

    int copyAssignments = 0;
    int moveAssignments = 0;

    MoveTracker() = default;

    explicit MoveTracker(std::string value) : value(std::move(value)) {}

    MoveTracker(const MoveTracker&) = default;
    MoveTracker(MoveTracker&&) noexcept = default;

    MoveTracker& operator=(const MoveTracker& other) {
        value = other.value;
        ++copyAssignments;
        return *this;
    }

    MoveTracker& operator=(MoveTracker&& other) noexcept {
        value = std::move(other.value);
        ++moveAssignments;
        return *this;
    }
};

void testMove() {
    std::vector<MoveTracker> source;

    source.emplace_back("Alice");
    source.emplace_back("Bob");
    source.emplace_back("Charlie");

    std::vector<MoveTracker> destination(3);

    auto result = minialgo::move(source.begin(), source.end(), destination.begin());

    ASSERT_TRUE(result == destination.end());

    ASSERT_EQ(destination[0].value, std::string{"Alice"});
    ASSERT_EQ(destination[1].value, std::string{"Bob"});
    ASSERT_EQ(destination[2].value, std::string{"Charlie"});

    ASSERT_EQ(destination[0].moveAssignments, 1);
    ASSERT_EQ(destination[1].moveAssignments, 1);
    ASSERT_EQ(destination[2].moveAssignments, 1);

    ASSERT_EQ(destination[0].copyAssignments, 0);
    ASSERT_EQ(destination[1].copyAssignments, 0);
    ASSERT_EQ(destination[2].copyAssignments, 0);
}

void testCopyUsesCopyAssignment() {
    std::vector<MoveTracker> source;

    source.emplace_back("Alice");
    source.emplace_back("Bob");

    std::vector<MoveTracker> destination(2);

    minialgo::copy(source.begin(), source.end(), destination.begin());

    ASSERT_EQ(destination[0].copyAssignments, 1);
    ASSERT_EQ(destination[1].copyAssignments, 1);

    ASSERT_EQ(destination[0].moveAssignments, 0);
    ASSERT_EQ(destination[1].moveAssignments, 0);
}

void testMoveBackward() {
    std::vector<MoveTracker> source;

    source.emplace_back("Alice");
    source.emplace_back("Bob");
    source.emplace_back("Charlie");

    std::vector<MoveTracker> destination(5);

    auto result = minialgo::moveBackward(source.begin(), source.end(), destination.end());

    ASSERT_TRUE(result == destination.begin() + 2);

    ASSERT_EQ(destination[2].value, std::string{"Alice"});

    ASSERT_EQ(destination[3].value, std::string{"Bob"});

    ASSERT_EQ(destination[4].value, std::string{"Charlie"});

    ASSERT_EQ(destination[2].moveAssignments, 1);
    ASSERT_EQ(destination[3].moveAssignments, 1);
    ASSERT_EQ(destination[4].moveAssignments, 1);

    ASSERT_EQ(destination[2].copyAssignments, 0);
    ASSERT_EQ(destination[3].copyAssignments, 0);
    ASSERT_EQ(destination[4].copyAssignments, 0);
}

void testReverseEven() {
    std::vector<int> values{1, 2, 3, 4};

    minialgo::reverse(values.begin(), values.end());

    ASSERT_EQ(values[0], 4);
    ASSERT_EQ(values[1], 3);
    ASSERT_EQ(values[2], 2);
    ASSERT_EQ(values[3], 1);
}

void testReverseOdd() {
    std::vector<int> values{1, 2, 3, 4, 5};

    minialgo::reverse(values.begin(), values.end());

    ASSERT_EQ(values[0], 5);
    ASSERT_EQ(values[1], 4);
    ASSERT_EQ(values[2], 3);
    ASSERT_EQ(values[3], 2);
    ASSERT_EQ(values[4], 1);
}

void testReverseList() {
    std::list<int> values{1, 2, 3, 4};

    minialgo::reverse(values.begin(), values.end());

    auto it = values.begin();

    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it++, 3);
    ASSERT_EQ(*it++, 2);
    ASSERT_EQ(*it++, 1);
}

void testRotateVector() {
    std::vector<int> values{1, 2, 3, 4, 5};

    auto result = minialgo::rotate(values.begin(), values.begin() + 2, values.end());

    ASSERT_EQ(values[0], 3);
    ASSERT_EQ(values[1], 4);
    ASSERT_EQ(values[2], 5);
    ASSERT_EQ(values[3], 1);
    ASSERT_EQ(values[4], 2);

    ASSERT_TRUE(result == values.begin() + 3);
}

void testRotateNoLeftPart() {
    std::vector<int> values{1, 2, 3};

    auto result = minialgo::rotate(values.begin(), values.begin(), values.end());

    ASSERT_TRUE(result == values.end());

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);
}

void testRotateNoRightPart() {
    std::vector<int> values{1, 2, 3};

    auto result = minialgo::rotate(values.begin(), values.end(), values.end());

    ASSERT_TRUE(result == values.begin());
}

void testRotateList() {
    std::list<int> values{1, 2, 3, 4, 5};

    auto middle = values.begin();
    std::advance(middle, 2);

    auto result = minialgo::rotate(values.begin(), middle, values.end());

    auto it = values.begin();

    ASSERT_EQ(*it++, 3);
    ASSERT_EQ(*it++, 4);
    ASSERT_EQ(*it++, 5);
    ASSERT_EQ(*it++, 1);
    ASSERT_EQ(*it++, 2);

    ASSERT_EQ(*result, 1);
}

void testPartition() {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    auto boundary =
        minialgo::partition(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(
        minialgo::allOf(values.begin(), boundary, [](int value) { return value % 2 == 0; }));

    ASSERT_TRUE(minialgo::noneOf(boundary, values.end(), [](int value) { return value % 2 == 0; }));
}

void testPartitionPoint() {
    std::vector<int> values{2, 4, 6, 1, 3, 5};

    auto it = minialgo::partitionPoint(
        values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(it == values.begin() + 3);
    ASSERT_EQ(*it, 1);
}

void testPartitionPointAllTrue() {
    std::vector<int> values{2, 4, 6};

    auto it = minialgo::partitionPoint(
        values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(it == values.end());
}

void testPartitionPointAllFalse() {
    std::vector<int> values{1, 3, 5};

    auto it = minialgo::partitionPoint(
        values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(it == values.begin());
}

void testRemoveIfBasic() {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    auto newEnd =
        minialgo::removeIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_EQ(minialgo::distance(values.begin(), newEnd), 3);

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 3);
    ASSERT_EQ(values[2], 5);
}

void testRemoveIfWithErase() {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    auto newEnd =
        minialgo::removeIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    values.erase(newEnd, values.end());

    ASSERT_EQ(values.size(), std::size_t{3});
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 3);
    ASSERT_EQ(values[2], 5);
}

void testRemove() {
    std::vector<int> values{1, 3, 2, 3, 4, 3, 5};

    auto newEnd = minialgo::remove(values.begin(), values.end(), 3);

    values.erase(newEnd, values.end());

    ASSERT_EQ(values.size(), std::size_t{4});
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 4);
    ASSERT_EQ(values[3], 5);
}

void testRemoveWithProjection() {
    struct Person {
        std::string name;
        int age;
    };

    std::vector<Person> people{{"Alice", 18}, {"Bob", 20}, {"Charlie", 18}, {"David", 25}};

    auto newEnd = minialgo::remove(people.begin(), people.end(), 18, &Person::age);

    people.erase(newEnd, people.end());

    ASSERT_EQ(people.size(), std::size_t{2});
    ASSERT_EQ(people[0].name, std::string{"Bob"});
    ASSERT_EQ(people[1].name, std::string{"David"});
}

void testRemoveIfMoveOnlyType() {
    std::vector<std::unique_ptr<int>> values;

    values.push_back(std::make_unique<int>(1));
    values.push_back(std::make_unique<int>(2));
    values.push_back(std::make_unique<int>(3));
    values.push_back(std::make_unique<int>(4));

    auto newEnd =
        minialgo::removeIf(values.begin(), values.end(), [](const std::unique_ptr<int>& value) {
            return *value % 2 == 0;
        });

    values.erase(newEnd, values.end());

    ASSERT_EQ(values.size(), std::size_t{2});

    ASSERT_EQ(*values[0], 1);
    ASSERT_EQ(*values[1], 3);
}

void testRemoveIfNothingRemoved() {
    std::vector<int> values{1, 3, 5};

    auto newEnd =
        minialgo::removeIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(newEnd == values.end());
}
void testRemoveIfEverythingRemoved() {
    std::vector<int> values{2, 4, 6};

    auto newEnd =
        minialgo::removeIf(values.begin(), values.end(), [](int value) { return value % 2 == 0; });

    ASSERT_TRUE(newEnd == values.begin());
}

void testUniqueBasic() {
    std::vector<int> values{1, 1, 2, 2, 2, 3, 3, 4};

    auto newEnd = minialgo::unique(values.begin(), values.end());

    ASSERT_EQ(minialgo::distance(values.begin(), newEnd), 4);

    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);
    ASSERT_EQ(values[3], 4);
}

void testUniqueWithErase() {
    std::vector<int> values{1, 1, 2, 2, 3, 3};

    auto newEnd = minialgo::unique(values.begin(), values.end());

    values.erase(newEnd, values.end());

    ASSERT_EQ(values.size(), std::size_t{3});
    ASSERT_EQ(values[0], 1);
    ASSERT_EQ(values[1], 2);
    ASSERT_EQ(values[2], 3);
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
    testForEachModifiesElements();
    testForEachAccumulatesValues();
    testForEachWithFunctionObject();
    testCopyToExistingRange();
    testCopyWithBackInserter();
    testCopyWithBackInserter();
    testCopyFromListToVector();
    testFillVector();
    testFillPartialRange();
    testFillEmptyRange();
    testFillArray();
    testFillString();
    testTransformSquaresValues();
    testTransformWithBackInserter();
    testTransformInPlace();
    testTransformPersonToName();
    testFindIfWithLambda();
    testFindIfWithFunctionObject();
    testFindIfWithFunction();
    testFindIfNotFound();
    testFindIfClassMemberFunctionPointer();
    testFindIfClassMemberFunctionPointerUsingProjection();
    testCountIfWithLambda();
    testCountIfWithFunctionObject();
    testCountIfWithFunction();
    testCountIfNotFound();
    testCountIfClassMemberFunctionPointer();
    testCountIfClassMemberFunctionPointerUsingProjection();
    testAllOfTrue();
    testAllOfFalse();
    testAllOfEmptyRange();
    testAllOfWithProjection();
    testAnyOfTrue();
    testAnyOfFalse();
    testAnyOfEmpty();
    testAnyOfWithProjection();
    testNoneOfTrue();
    testNoneOfFalse();
    testNoneOfEmpty();
    testNoneOfWithProjection();
    testCopyBackwardBasic();
    testCopyBackwardOverlappingToRight();
    testCopyBackwardList();
    testLowerBoundFindsFirstDuplicate();
    testLowerBoundInsertInMiddle();
    testLowerBoundBeforeAll();
    testLowerBoundAfterAll();
    testLowerBoundList();
    testLowerBoundWithProjection();
    testLowerBoundDescending();
    testLowerBoundEmpty();
    testBinarySearchFound();
    testBinarySearchNotFound();
    testBinarySearchDuplicate();
    testBinarySearchWithProjection();
    testBinarySearchDescending();
    testUpperBoundBasic();
    testUpperBoundMissingValue();
    testUpperBoundBeforeAll();
    testUpperBoundAfterAll();
    testUpperBoundWithProjection();
    testUpperBoundDescending();
    testEqualRange();
    testEqualRangeNotFound();
    testBinaryTransformInt();
    testBinaryTransformDifferentTypes();
    testBinaryTransformCustomOperation();
    testBinaryTransformDifferentOutputType();
    testTransformOverloads();
    testMove();
    testCopyUsesCopyAssignment();
    testMoveBackward();
    testReverseEven();
    testReverseOdd();
    testReverseList();
    testRotateVector();
    testRotateNoLeftPart();
    testRotateNoRightPart();
    testRotateList();
    testPartition();
    testPartitionPoint();
    testRemove();
    testRemoveIfBasic();
    testRemoveIfMoveOnlyType();
    testRemoveIfNothingRemoved();
    testRemoveIfEverythingRemoved();
    testRemoveIfWithErase();
    testRemoveWithProjection();
    testUniqueBasic();
    testUniqueWithErase();

    std::cout << "Algorithm tests passed\n";
    return 0;
}
