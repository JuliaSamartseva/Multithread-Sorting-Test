#include "SortingAlgorithms.h"

void swap(int* a, int* b);

SortingStrategy::~SortingStrategy() {};

void QuickSort::sort(std::vector<int>& list)
{
    quickSort(list, 0, list.size() - 1);
}

void QuickSort::quickSort(std::vector<int>& list, int low, int high)
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


void MergeSort::sort(std::vector<int>& list)
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
    std::vector<int>Right;

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

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
