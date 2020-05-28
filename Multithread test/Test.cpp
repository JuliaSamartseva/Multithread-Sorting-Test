#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "SortingAlgorithms.h"

std::vector<int> generateArray(int size) {
    std::vector<int> result;
    result.reserve(size);
    for (int i = 0; i < size; i++)
        result.push_back(rand() % 100);
    return result;
}


BOOST_AUTO_TEST_CASE(check_sorting)
{
    std::vector<int> x = {1, 5, 2, 4, 2, 3, 5, 7};
    SortingContext y;
    y.setStrategy(new MultithreadMergeSort());
    y.sortNumbers(x);
    std::vector<int> z = { 1, 2, 2, 3, 4, 5, 5, 7 };
    BOOST_CHECK(x == z);
}

BOOST_AUTO_TEST_CASE(check_same_results)
{
    std::vector<int> x = generateArray(20480);
    std::vector<int> y = x;
    SortingContext context;
    context.setStrategy(new MultithreadMergeSort());
    context.sortNumbers(x);
    context.setStrategy(new SequentialMergeSort());
    context.sortNumbers(y);
    BOOST_CHECK(x == y);
}