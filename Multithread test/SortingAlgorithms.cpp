#include "SortingAlgorithms.h"
#include <thread>
#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>


void swap(int* a, int* b);

SortingStrategy::~SortingStrategy() {};

void SequentialQuickSort::sort(std::vector<int>& list)
{
    quickSort(list, 0, list.size() - 1);
}

void SequentialQuickSort::quickSort(std::vector<int>& list, int low, int high)
{

    int i = low;
    int j = high;
    int pivot = list[(i + j) / 2];

    while (i <= j)
    {
        while (list[i] < pivot)
            i++;
        while (list[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(&list[i], &list[j]);
            i++;
            j--;
        }
    }
    if (j > low)
        quickSort(list, low, j);
    if (i < high)
        quickSort(list, i, high);

}


void SequentialMergeSort::sort(std::vector<int>& list)
{
    mergeSort(list, 0, list.size() - 1);
}


void MergeSort::mergeSort(std::vector<int>& list, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(list, left, middle);
        mergeSort(list, middle + 1, right);

        merge(list, left, middle, right);
    }
}

void MergeSort::merge(std::vector<int>& list, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    std::vector<int>Left;
    Left.reserve(n1);
    std::vector<int>Right;
    Right.reserve(n2);

    for (int i = 0; i < n1; i++)
        Left.push_back(list[left + i]);
    for (int j = 0; j < n2; j++)
        Right.push_back(list[middle + 1 + j]);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (Left[i] <= Right[j])
        {
            list[k] = Left[i];
            i++;
        }
        else
        {
            list[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        list[k] = Left[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        list[k] = Right[j];
        j++;
        k++;
    }
}

void InsertionSort::sort(std::vector<int>& list) {
    int i, j;
    int key;
    for (i = 1; i < list.size(); i++)
    {
        key = list[i];
        j = i - 1;

        while (j >= 0 && list[j] > key)
        {
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;
    }
}

void SelectionSort::sort(std::vector<int>& list)
{
    int min_idx;

    for (int i = 0; i < list.size() - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < list.size(); j++)
            if (list[j] < list[min_idx])
                min_idx = j;

        swap(&list[min_idx], &list[i]);
    }
}

void CocktailSort::sort(std::vector<int>& list)
{
    bool swapped = true;
    int start = 0;
    int end = list.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (list[i] > list[i + 1]) {
                swap(&list[i], &list[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i) {
            if (list[i] > list[i + 1]) {
                swap(&list[i], &list[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}

void MultithreadMergeSort::sort(std::vector<int>& list)
{
    //number of threads used
    unsigned int n = 4;
    std::vector<std::thread> threads;

    //creating threads for use
    for (int i = 0; i < n; i++)
        threads.push_back(std::thread(&MultithreadMergeSort::findParts, this, i, std::ref(list)));

    for (int i = 0; i < n; i++)
        threads[i].join();

    merge(list, 0, (list.size() / 2 - 1) / 2, list.size() / 2 - 1);
    merge(list, list.size() / 2, list.size() / 2 + (list.size() - 1 - list.size() / 2) / 2, list.size() - 1);
    merge(list, 0, (list.size() - 1) / 2, list.size() - 1);
}

void MultithreadMergeSort::findParts(int part, std::vector<int>& list)
{
    // calculating low and high 
    int low = part * (list.size() / 4);
    int high = (part + 1) * (list.size() / 4) - 1;

    mergeSort(list, low, high);
  
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void MultithreadQuickSort::sort(std::vector<int>& list)
{
    quickSort(list, 0, list.size() - 1);
}

void MultithreadQuickSort::quickSort(std::vector<int>& list, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = list[(i + j) / 2];

    //partition
    while (i <= j)
    {
        while (list[i] < pivot)
            i++;
        while (list[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(&list[i], &list[j]);
            i++;
            j--;
        }
    }
    if (j > low) {
        std::thread lThread(&MultithreadQuickSort::quickSort, this, std::ref(list), low, j);
        lThread.join();
    }
       

    if (i < high) {
        std::thread rThread(&MultithreadQuickSort::quickSort, this, std::ref(list), i, high);
        rThread.join();
    }
        

   
}
