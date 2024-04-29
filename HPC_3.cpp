#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Function to perform parallel reduction for minimum value
template <typename T>
T parallelMin(const vector<T> &arr)
{
    T result = arr[0];
#pragma omp parallel for reduction(min : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = min(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for maximum value
template <typename T>
T parallelMax(const vector<T> &arr)
{
    T result = arr[0];
#pragma omp parallel for reduction(max : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = max(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for sum
template <typename T>
T parallelSum(const vector<T> &arr)
{
    T result = arr[0];
#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result += arr[i];
    }
    return result;
}

// Function to perform parallel reduction for average
template <typename T>
double parallelAverage(const vector<T> &arr)
{
    T sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main()
{
    const int size = 10;
    vector<int> arr(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 1000;
        cout << arr[i] << " ";
    }
    cout << endl;
    // Compute min, max, sum, and average using parallel reduction
    
    int maxVal = parallelMax(arr);
    int sum = parallelSum(arr);
    double average = parallelAverage(arr);

    auto start = high_resolution_clock::now();
    int minVal = parallelMin(arr);
    auto stop = high_resolution_clock::now();
    auto par_duration_min = duration_cast<milliseconds>(stop - start);

    // Output results
    cout << "Parallel Bubble Sort Time: " << par_duration_min.count() << " milliseconds" << endl;
    cout << "Minimum value: " << minVal << endl;
    cout << "Maximum value: " << maxVal << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}