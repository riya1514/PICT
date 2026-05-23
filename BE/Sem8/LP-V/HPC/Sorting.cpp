/* Write a program to implement Parallel Bubble Sort and Merge sort using OpenMP. Use 
existing algorithms and measure the performance of sequential and parallel algorithms.*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>

using namespace std;

void printArray(const vector<int> &arr)
{
    for (int i = 0; i < 10; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void BubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// -------------------- PARALLEL BUBBLE SORT (ODD-EVEN) --------------------
void parallelBubbleSort(vector<int> &arr)
{
    int n = arr.size();

    #pragma omp parallel
    for (int i = 0; i < n; i++)
    {
        // Even phase
        #pragma omp for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        // Odd phase
        #pragma omp for
        for (int j = 1; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void merge(vector<int> &arr, int start, int mid, int end)
{
    vector<int> temp(end - start + 1);

    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= end)
        temp[k++] = arr[j++];

    for (int i = 0; i < temp.size(); i++)
        arr[start + i] = temp[i];
}

void MergeSort(vector<int> &arr, int start, int end)
{
    if (start >= end)
        return;

    int mid = (start + end) / 2;

    MergeSort(arr, start, mid);
    MergeSort(arr, mid + 1, end);

    merge(arr, start, mid, end);
}

void MergeSortParallel(vector<int> &arr, int start, int end)
{
    if (start >= end)
        return;

    if(end-start < 5000)
    {
        MergeSort(arr,start,end);
        return;
    }

    int mid = (start + end) / 2;

#pragma omp task shared(arr)
    MergeSortParallel(arr, start, mid);

#pragma omp task shared(arr)
    MergeSortParallel(arr, mid + 1, end);

#pragma omp taskwait
    merge(arr, start, mid, end);
}

int main()
{
    int N = 90000; // Increase for better performance comparison
    vector<int> arr(N);

    // Generate random array
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 100000;

    vector<int> arr1 = arr;
    vector<int> arr2 = arr;
    vector<int> arr3 = arr;
    vector<int> arr4 = arr;

    cout << "Array before Sorting : ";
    printArray(arr);

    double start = omp_get_wtime();
    BubbleSort(arr1);
    double end = omp_get_wtime();
    double seq_bubble = end - start;

    start = omp_get_wtime();
    parallelBubbleSort(arr2);
    end = omp_get_wtime();
    double par_bubble = end - start;

    cout << "\n--- Bubble Sort ---\n";
    cout << "Array After Bubble Sort : ";
    printArray(arr1);
    cout << "Sequential Time: " << seq_bubble << " sec\n";
    cout << "Parallel Time:   " << par_bubble << " sec\n";
    cout << "Speedup:         " << seq_bubble / par_bubble << "\n";

    start = omp_get_wtime();
    MergeSort(arr3, 0, N - 1);
    end = omp_get_wtime();
    double seq_merge = end - start;

    start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        MergeSortParallel(arr4, 0, N - 1);
    }

    end = omp_get_wtime();
    double par_merge = end - start;

    cout << "\n--- Merge Sort ---\n";
    cout << "Array After Bubble Sort : ";
    printArray(arr2);
    cout << "Sequential Time: " << seq_merge << " sec\n";
    cout << "Parallel Time:   " << par_merge << " sec\n";
    cout << "Speedup:         " << seq_merge / par_merge << "\n";

    return 0;
}