
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

bool isSorted(const vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int SIZE = 100000;
    vector<int> arr(SIZE);
    srand(time(0));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000000 + 1;
    }

    vector<int> original = arr;
    
    auto start = high_resolution_clock::now();
    selectionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    bool sorted = isSorted(arr);
    cout << "Selection Sort Time: " << duration.count() << " milliseconds" << endl;
    cout << "Sorted correctly: " << (sorted ? "Yes" : "No") << endl;
    
    return 0;

}