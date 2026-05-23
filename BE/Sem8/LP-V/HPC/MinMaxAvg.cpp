/*Implement Min, Max, Sum and Average operations using Parallel Reduction 
Measure the performance of sequential and parallel algorithms.*/

#include <iostream>
#include <vector>
#include <omp.h>
#include <algorithm>

using namespace std;

long long arr_min(const vector<long long>& arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(min:minimum)
    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    }

    double end = omp_get_wtime();
    cout << "Minimum : " << minimum << endl;
    cout << "Time : " << end - start << endl;
    return minimum;
}

long long arr_min_seq(const vector<long long>& arr)
{
    long long minimum = arr[0];
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        minimum = min(minimum, arr[i]);
    }

    double end = omp_get_wtime();
    cout << "Minimum : " << minimum << endl;
    cout << "Time : " << end - start << endl;
    return minimum;
}

long long arr_max(const vector<long long>& arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(max:maximum)
    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    }

    double end = omp_get_wtime();
    cout << "Maximum : " << maximum << endl;
    cout << "Time : " << end - start << endl;
    return maximum;
}

long long arr_max_seq(const vector<long long>& arr)
{
    long long maximum = arr[0];
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        maximum = max(maximum, arr[i]);
    }

    double end = omp_get_wtime();
    cout << "Maximum : " << maximum << endl;
    cout << "Time : " << end - start << endl;
    return maximum;
}

long long arr_sum(const vector<long long>& arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    double end = omp_get_wtime();
    cout << "Sum : " << sum << endl;
    cout << "Time : " << end - start << endl;
    return sum;
}

long long arr_sum_seq(const vector<long long>& arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    double end = omp_get_wtime();
    cout << "Sum : " << sum << endl;
    cout << "Time : " << end - start << endl;
    return sum;
}

double arr_avg(const vector<long long>& arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

#pragma omp parallel for reduction(+:sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    double avg = (double)sum / arr.size();

    double end = omp_get_wtime();
    cout << "Average : " << avg << endl;
    cout << "Time : " << end - start << endl;
    return avg;
}

double arr_avg_seq(const vector<long long>& arr)
{
    long long sum = 0;
    double start = omp_get_wtime();

    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }

    double avg = (double)sum / arr.size();

    double end = omp_get_wtime();
    cout << "Average : " << avg << endl;
    cout << "Time : " << end - start << endl;
    return avg;
}

int main()
{
    long long N = 90000000;

    vector<long long> arr(N);

    for (long long i = 0; i < N; i++)
    {
        arr[i] = rand() % 1000;
    }

    cout << "\nMinimum (Parallel Execution)" << endl;
    arr_min(arr);
    cout << "\nMinimum (Sequential Execution)" << endl;
    arr_min_seq(arr);

    cout << "\nMaximum (Parallel Execution)" << endl;
    arr_max(arr);
    cout << "\nMax (Sequential Execution)" << endl;
    arr_max_seq(arr);

    cout << "\nSum (Parallel Execution)" << endl;
    arr_sum(arr);
    cout << "\nSum (Sequential Execution)" << endl;
    arr_sum_seq(arr);

    cout << "\nAvg (Parallel Execution)" << endl;
    arr_avg(arr);
    cout << "\nAvg (Sequential Execution)" << endl;
    arr_avg_seq(arr);

    return 0;
}