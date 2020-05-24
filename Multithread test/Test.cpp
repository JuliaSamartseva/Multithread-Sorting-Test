#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "SortingAlgorithms.h"


BOOST_AUTO_TEST_CASE(force_division_by_zero)
{
    std::vector<int> x = {1, 5, 2, 4, 2, 3, 5, 7};
    SortingContext y;
    y.setStrategy(new MultithreadMergeSort());
    y.sortNumbers(x);
    std::vector<int> z = { 1, 2, 2, 3, 4, 5, 5, 7 };
    BOOST_CHECK(x == z);
}