#include "kfunction.h"
#include "gtest/gtest.h"
#include <iostream>

TEST(TestTypes, double_)
{
    Function<double> f;
    f = "5*x";
    ASSERT_FLOAT_EQ(f.run(5), 25);
    ASSERT_FLOAT_EQ(f.run(0), 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}