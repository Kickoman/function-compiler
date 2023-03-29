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

TEST(FunctionTest, Test1) {
    Function<double> f("2*x+3");
    EXPECT_EQ(f(0), 3);
    EXPECT_EQ(f(1), 5);
    EXPECT_EQ(f(2), 7);
}

TEST(FunctionTest, Test2) {
    Function<double> f("sin(x)");
    EXPECT_NEAR(f(0), 0, 1e-6);
    EXPECT_NEAR(f(M_PI/2), 1, 1e-6);
    EXPECT_NEAR(f(M_PI), 0, 1e-6);
}

TEST(FunctionTest, Test3) {
    Function<double> f("x^2");
    EXPECT_EQ(f(-2), 4);
    EXPECT_EQ(f(-1), 1);
    EXPECT_EQ(f(0), 0);
    EXPECT_EQ(f(1), 1);
    EXPECT_EQ(f(2), 4);
}

TEST(FunctionTest, Test4) {
    Function<double> f("exp(x)");
    EXPECT_NEAR(f(0), 1, 1e-6);
    EXPECT_NEAR(f(1), exp(1), 1e-6);
    EXPECT_NEAR(f(2), exp(2), 1e-6);
}

TEST(FunctionTest, Test5) {
    Function<double> f("log10(x)");
    EXPECT_NEAR(f(1), 0, 1e-6);
    EXPECT_NEAR(f(10), 1, 1e-6);
    EXPECT_NEAR(f(100), 2, 1e-6);
}

TEST(FunctionTest, Test6) {
    Function<double> f("tan(x)");
    EXPECT_NEAR(f(0), 0, 1e-6);
    EXPECT_NEAR(f(M_PI/4), 1, 1e-6);
}

TEST(FunctionTest, Test7) {
    Function<double> f("sgn(x)");
    EXPECT_EQ(f(-10), -1);
    EXPECT_EQ(f(-1), -1);
    EXPECT_EQ(f(0), 0);
    EXPECT_EQ(f(1), 1);
    EXPECT_EQ(f(10), 1);
}

TEST(FunctionTest, Test8) {
    Function<double> f("floor(x)");
    EXPECT_EQ(f(-1.5), -2);
    EXPECT_EQ(f(-0.5), -1);
    EXPECT_EQ(f(0), 0);
    EXPECT_EQ(f(1.5), 1);
    EXPECT_EQ(f(2.5), 2);
}

#endif // TEST_FUNCTIONS_H