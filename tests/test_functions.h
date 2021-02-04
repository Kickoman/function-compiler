#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include "gtest/gtest.h"
#include "kfunction.h"
#include <cmath>

TEST(TestFunctions, sin_)
{
    Function<double> f;
    f = "sin(x)";
    for (double i = -10; i < 10; i += 0.3)
        ASSERT_FLOAT_EQ(f.run(i), sin(i));
}

TEST(TestFunctions, cos_)
{
    Function<double> f;
    f = "cos(x)";
    for (double i = -10; i < 10; i += 0.1)
        ASSERT_FLOAT_EQ(f.run(i), cos(i));
}

TEST(TestFunctions, many_functions)
{
    Function<double> f;
    f = "sin(x)*cos(x)";
    for (double i = -10; i < 10; i += 0.1)
        ASSERT_FLOAT_EQ(f.run(i), sin(i) * cos(i));
}

TEST(TestFunctions, nested_functions)
{
    Function<double> f;
    f = "sin(cos(x))";
    for (double i = -10; i < 10; i += 0.1)
        ASSERT_FLOAT_EQ(f.run(i), sin(cos(i)));
    f = "cos(sin(cos(x)))";
    for (double i = -10; i < 10; i += 0.1)
        ASSERT_FLOAT_EQ(f.run(i), cos(sin(cos(i))));
}

TEST(TestFunctions, integer_result)
{
    Function<int> f;
    f = "sin(x)";
    for (double i = -10; i < 10; i += 0.1)
        ASSERT_FLOAT_EQ(f.run(i), static_cast<int>(sin(static_cast<int>(i))));
}

#endif // TEST_FUNCTIONS_H