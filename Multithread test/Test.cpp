#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "SortingAlgorithms.h"
#include <iostream>
#include <chrono>
#include <execution>
namespace utf = boost::unit_test;


std::vector<int> generateArray(int size) {
    std::vector<int> result;
    result.reserve(size);
    for (int i = 0; i < size; i++)
        result.push_back(rand() % 100);
    return result;
}

BOOST_AUTO_TEST_SUITE(mergesort, *utf::disabled())

BOOST_AUTO_TEST_CASE(check_multithread_merge)
{
    std::vector<int> x = {1, 5, 2, 4, 2, 3, 5, 7};
    SortingContext y;
    y.setStrategy(new MultithreadMergeSort());
    y.sortNumbers(x);
    std::vector<int> z = { 1, 2, 2, 3, 4, 5, 5, 7 };
    BOOST_CHECK(x == z);
}

BOOST_AUTO_TEST_CASE(check_same_results_mergesort)
{
    std::cout << "===================================================================\n";
    std::cout << "From this test case we can see that the 4 threads merge sort duration is\non average 2 times faster than sequential one on my computer";
    std::cout << "\nAt the end of each test for the array size I check whether the arrays are the same (in sorted order)";
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

        std::cout << "Speedup: ";
        
        if (duration != 0) {
            double speedup = (double)duration2 / (double)duration;
            std::cout << speedup;
        }
        else std::cout << "0";

        array_size *= 4;

        BOOST_CHECK(x == y);
    }
    
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(check_multithread_quicksort)
{
    std::vector<int> x = { 1, 5, 2, 4, 2, 3, 5, 7 };
    SortingContext y;
    y.setStrategy(new MultithreadQuickSort());
    y.sortNumbers(x);
    std::vector<int> z = { 1, 2, 2, 3, 4, 5, 5, 7 };
    BOOST_CHECK(x == z);
}

BOOST_AUTO_TEST_CASE(check_same_results_quicksort)
{
    std::cout << "===================================================================\n";
    std::cout << "From this test case we can see that the 4 threads merge sort duration is\non average 2 times faster than sequential one on my computer";
    std::cout << "\nAt the end of each test for the array size I check whether the arrays are the same (in sorted order)";
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

        std::cout << "Speedup: ";

        if (duration != 0) {
            double speedup = (double)duration2 / (double)duration;
            std::cout << speedup;
        }
        else std::cout << "0";

        array_size *= 4;

        BOOST_CHECK(x == y);
    }

}


BOOST_AUTO_TEST_CASE(library_check)
{
    std::cout << "\n\n===================================================================\n";
    std::cout << "STD C++17 Library check of std::execution\n" << "Most STL operations now have a version with a parallel execution";

    int array_size = 32;
    for (int i = 0; i < 8; i++) {
        std::vector<int> x = generateArray(array_size);
        std::vector<int> y = x;
        std::vector<int> z = x;

        std::cout << "\n--------------------------------" << "Array size: " << array_size << std::endl;

        auto t1_thread = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par, y.begin(), y.end());
        auto t2_thread = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2_thread - t1_thread).count();
        std::cout << "Parallel sort duration: " << duration << std::endl;

        t1_thread = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::par_unseq, z.begin(), z.end());
        t2_thread = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2_thread - t1_thread).count();
        std::cout << "Parallel and vectorized sort duration: " << duration << std::endl;

        auto t1_sequential = std::chrono::high_resolution_clock::now();
        std::sort(std::execution::seq, x.begin(), x.end());
        auto t2_sequential = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(t2_sequential - t1_sequential).count();
        std::cout << "Sequential sort duration: " << duration2 << std::endl;

        array_size *= 4;

        std::cout << "Speedup: ";
        if (duration != 0) {
            double speedup = (double)duration2 / (double)duration;
            std::cout << speedup;
        }
        else std::cout << "0";

        BOOST_CHECK(x == y && y == z);
    }
}

