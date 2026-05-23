/*
Assignment 5 (DAA)
Write a program for analysis of quick sort by using deterministic and randomized variant.
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>

using namespace std;

// int partitionDeterministic(vector<int>& arr, int low, int high)
// {
//     int pivot = arr[low];   // pivot = first element
//     int i = low + 1;
//     int j = high;

//     while (true)
//     {
//         while (i <= high && arr[i] <= pivot)
//         {
//             i++;
//         }
//         while (j >= low && arr[j] > pivot)
//         {
//             j--;
//         }

//         if (i < j)
//         {
//             swap(arr[i], arr[j]);
//         }
//         else
//         {
//             break;
//         }
//     }

//     swap(arr[low], arr[j]);

//     cout << "Step " << step << " (Random Pivot = " << pivot << "): ";
//     printArray(arr);

//     return j;
// }


//------------------------------------------------------------------------------
// Partition (Deterministic) : pivot - last element
//------------------------------------------------------------------------------
int partitionDeterministic(vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j)
    {
        if (arr[j] <= pivot)
        {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

//------------------------------------------------------------------------------
// Quick Sort (Deterministic)
//------------------------------------------------------------------------------
void quickSortDeterministic(vector<int>& arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivotIndex = partitionDeterministic(arr, low, high);
    quickSortDeterministic(arr, low, pivotIndex - 1);
    quickSortDeterministic(arr, pivotIndex + 1, high);
}

//------------------------------------------------------------------------------
// Partition (Randomized)
//------------------------------------------------------------------------------
int partitionRandomized(vector<int>& arr, int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);
    return partitionDeterministic(arr, low, high);
}

//------------------------------------------------------------------------------
// Quick Sort (Randomized)
//------------------------------------------------------------------------------
void quickSortRandomized(vector<int>& arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivotIndex = partitionRandomized(arr, low, high);
    quickSortRandomized(arr, low, pivotIndex - 1);
    quickSortRandomized(arr, pivotIndex + 1, high);
}

//------------------------------------------------------------------------------
// Print Utility
//------------------------------------------------------------------------------
void printArray(const vector<int>& arr)
{
    for (int num : arr)
        cout << num << ' ';
    cout << '\n';
}

//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
int main()
{
    srand(time(0)); 

    int choice = 0;
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: "<<endl;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    while (choice != 3)
    {
        cout << "\nPress \n1. Deterministic Quick Sort (Pivot = First Element)"
             << "\n2. Randomized Quick Sort (Random Pivot)"
             << "\n3. End \nEnter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
            case 1:
            {
                vector<int> temp = arr;
                int step = 0;
                cout << "Original Array: ";
                printArray(temp);
                quickSortDeterministic(temp, 0, n - 1);
                cout << "Sorted Array (Deterministic): ";
                printArray(temp);
                break;
            }

            case 2:
            {
                vector<int> temp = arr;
                int step = 0;
                cout << "Original Array: ";
                printArray(temp);
                quickSortRandomized(temp, 0, n - 1);
                cout << "Sorted Array (Randomized): ";
                printArray(temp);
                break;
            }

            case 3:
                cout << "End :)" << endl;
                break;

            default:
                cout << "Invalid Input" << endl;
                break;
        }
    }

    return 0;
}

