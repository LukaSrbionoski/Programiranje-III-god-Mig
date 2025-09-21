#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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
    insertionSort(arr);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    bool sorted = isSorted(arr);
    cout << "Insertion Sort Time: " << duration.count() << " milliseconds" << endl;
    cout << "Sorted correctly: " << (sorted ? "Yes" : "No") << endl;
    
    return 0;
}