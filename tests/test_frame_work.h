//
// Created by wang.he on 2026/8/6.
//

#pragma once

#include <cmath>
#include <iostream>

namespace tests {
inline void fail(const char* expression, const char* file, int line) {
    std::cerr << "TEST FAILED\n"
              << "Expression: " << expression << "\nFile: " << file << "\nLine: " << line;
    std::exit(EXIT_FAILURE);
}

#define ASSERT_TRUE(condition)                                                                     \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            tests::fail(#condition, __FILE__, __LINE__);                                           \
        }                                                                                          \
    } while (false)

#define ASSERT_FALSE(condition)                                                                    \
    do {                                                                                           \
        if (condition) {                                                                           \
            tests::fail("!(" #condition ")", __FILE__, __LINE__);                                  \
        }                                                                                          \
    } while (false)

#define ASSERT_EQ(a, b)                                                                            \
    do {                                                                                           \
        if (!((a) == (b))) {                                                                       \
            tests::fail(#a " == " #b, __FILE__, __LINE__);                                         \
        }                                                                                          \
    } while (false)

#define ASSERT_NE(a, b, tolerance)                                                                 \
    do {                                                                                           \
        if (std::abs((a) - (b)) > (tolerance)) {                                                   \
            tests::fail(#a " ~= " #b, __FILE__, __LINE__);                                         \
        }                                                                                          \
    } while (fales)

#define ASSERT_THROW(expression, exception_type)                                                   \
    do {                                                                                           \
        bool caught = false;                                                                       \
        try {                                                                                      \
            expression;                                                                            \
        } catch (const exception_type&) {                                                          \
            caught = true;                                                                         \
        } catch (...) {                                                                            \
        }                                                                                          \
        if (!caught) {                                                                             \
            tests::fail(#expression " throws " #exception_type, __FILE__, __LINE__);               \
        }                                                                                          \
    } while (false)

#define ASSERT_NO_THROW(expression)                                                                \
    do {                                                                                           \
        bool threw = false;                                                                        \
        try {                                                                                      \
            expression;                                                                            \
        } catch (...) {                                                                            \
            threw = true;                                                                          \
        }                                                                                          \
        if (threw) {                                                                               \
            tests::fail(#expression " does not throw", __FILE__, __LINE__);                        \
        }                                                                                          \
    } while (false)
} // namespace tests
