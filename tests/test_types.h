#ifndef TEST_TYPES_H
#define TEST_TYPES_H

#include "gtest/gtest.h"
#include "kfunction.h"

TEST(TestTypes, double_)
{
    Function<double> f;
    f = "5*x";
    ASSERT_FLOAT_EQ(f.run(5), 25);
    ASSERT_FLOAT_EQ(f.run(0), 0);
    ASSERT_FLOAT_EQ(f.run((DBL_MAX - 1) / 5), DBL_MAX - 1);
}

TEST(TestTypes, int_)
{
    Function<int> f;
    f = "5*x";
    ASSERT_EQ(f.run(5), 25);
    ASSERT_EQ(f.run(10), 50);

    f = "20/x";
    ASSERT_EQ(f.run(3), 6);
}

#endif // TEST_TYPES_H