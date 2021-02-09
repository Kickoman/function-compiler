#ifndef TEST_CLASSES_H
#define TEST_CLASSES_H

#include "gtest/gtest.h"
#include "testfunction.h"
#include <string>
#include <vector>

TEST(TestSimplify, simplify_spaces)
{
    using TestCase = std::pair<std::string, std::string>;

    std::vector<TestCase> testCases;
    testCases.push_back({"x + 2 + 3 + 4", "x+2+3+4"});

    TestFunction f;

    for (const auto &test_case : testCases)
        ASSERT_EQ(f.call_simplify(test_case.first), test_case.second);
}

TEST(TestSimplify, simplify_zeros)
{
    using TestCase = std::pair<std::string, std::string>;

    std::vector<TestCase> testCases;
    testCases.push_back({"-x+2", "0-x+2"});
    testCases.push_back({"2+(-x-2)", "2+(0-x-2)"});
    testCases.push_back({"-x", "0-x"});
    testCases.push_back({"-1", "0-1"});
    testCases.push_back({"(x-100)^3/100", "(x-100)^3/100"});

    TestFunction f;

    for (const auto &test_case : testCases)
        ASSERT_EQ(f.call_simplify(test_case.first), test_case.second);
}

TEST(TestSimplify, simplify_functions)
{
    using TestCase = std::pair<std::string, std::string>;

    std::vector<TestCase> testCases;
    testCases.push_back({"x+sin(-x)", "x+sin#(0-x)"});
    testCases.push_back({"x+sin(x)", "x+sin#(x)"});
    testCases.push_back({"cos(x)", "cos#(x)"});

    TestFunction f;

    for (const auto &test_case : testCases)
        ASSERT_EQ(f.call_simplify(test_case.first), test_case.second);
}

//TEST(TestConvert, convert)
//{
//    using TestCase = std::pair<std::string, std::string>;

//    std::vector<TestCase> testCases;
//    testCases.push_back({"x+sin(-x)", "x+sin#(0-x)"});
//    testCases.push_back({"x+sin(x)", "x+sin#(x)"});
//    testCases.push_back({"cos(x)", "cos#(x)"});

//    TestFunction f;

//    for (const auto &test_case : testCases)
//        ASSERT_EQ(f.call_simplify(test_case.first), test_case.second);
//}

#endif // TEST_CLASSES_H
