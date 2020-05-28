#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "SortingAlgorithms.h"
#include <iostream>
#include <chrono>
#include <execution>


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
    std::cout << "From this test case we can see that the 4 threads merge sort duration is\non average 2 times faster than sequential one";
    int array_size = 32;
    for (int i = 0; i < 8; i++) {
        
        std::vector<int> x = generateArray(array_size);
        std::vector<int> y = x;
        SortingContext context;

        std::cout << "\n--------------------------------" << "Array size: " << array_size << std::endl;

        context.setStrategy(new MultithreadMergeSort());
        auto t1_thread = std::chrono::high_resolution_clock::now();
        context.sortNumbers(x);
        auto t2_thread = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2_thread - t1_thread).count();
        std::cout << "Merge sort multithread duration: " << duration << std::endl;

        context.setStrategy(new SequentialMergeSort());
        auto t1_sequential = std::chrono::high_resolution_clock::now();
        context.sortNumbers(y);
        auto t2_sequential = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2_sequential - t1_sequential).count();
        std::cout << "Merge sort sequential duration: " << duration2 << std::endl;

        array_size *= 4;

        BOOST_CHECK(x == y);
    }
    
}

