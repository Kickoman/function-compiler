#ifndef TST_OPERATIONS_H
#define TST_OPERATIONS_H

#include "gtest/gtest.h"
#include "kfunction.h"

TEST(TestOperations, add_float)
{
    Function<double> f;

    f = "1+2+3+4+5";
    ASSERT_FLOAT_EQ(f.run(0), 15);

    f = "1+2+3+4+x";
    ASSERT_FLOAT_EQ(f.run(1), 11);
    ASSERT_FLOAT_EQ(f.run(2), 12);
    ASSERT_FLOAT_EQ(f.run(-5), 5);

    for (int i = -20; i < 100; ++i)
        ASSERT_FLOAT_EQ(f.run(i), 1+2+3+4+static_cast<double>(i));

    f = "1+2+3+4+x-x";
    ASSERT_FLOAT_EQ(f.run(INT_MAX), 10);
    ASSERT_FLOAT_EQ(f.run(0), 10);
}

TEST(TestOperations, add_integer)
{//1612790705
    Function<int> f;
    f = "1+2+3+4+5";
    ASSERT_EQ(f.run(0), 15);

    f = "1+2+3+4+x";
    ASSERT_EQ(f.run(1), 11);
    ASSERT_EQ(f.run(2), 12);
    ASSERT_EQ(f.run(-5), 5);

    for (int i = -1; i < 100; ++i)
        ASSERT_EQ(f.run(i), 1+2+3+4+i);

    f = "1+2+3+4+x-x";
    ASSERT_EQ(f.run(INT_MAX), 10);
    ASSERT_EQ(f.run(0), 10);
}

TEST(TestOperations, unary_operators)
{
    Function<double> f;
    f = "-x";
    for (int i = -10; i < 10; ++i)
        ASSERT_FLOAT_EQ(f.run(i), static_cast<double>(-i));

    f = "5+(-x)";
    for (int i = -10; i < 10; ++i)
        ASSERT_FLOAT_EQ(f.run(i), 5 + static_cast<double>(-i));
}

TEST(TestOperations, braces)
{
    Function<double> f;
    f = "(x-100)^3/100";

    ASSERT_FLOAT_EQ(f.run(1), -9702.99);
    for (int i = -5; i < 100; ++i)
        ASSERT_FLOAT_EQ(f.run(i), pow(static_cast<double>(i)-100, 3)/100);
}

#endif // TST_OPERATIONS_H
