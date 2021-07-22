#include "common_function.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void SwapXor(int& a, int& b) {
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

void SelectSort(vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len == 0 || arr_len == 1) return;

    for (int i = 1; i < arr_len; ++i) {
        int min_index = i - 1;
        for (int j = i; j < arr_len; ++j) {
            min_index = array[j] < array[min_index] ? j : min_index;
        }
        Swap(array[min_index], array[i - 1]);
    }
}

void BubbleSort(vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len == 0 || arr_len == 1) return;

    for (int end = arr_len - 2; end >= 0; --end) {
        for (int i = 0; i <= end; ++i) {
            if (array[i] > array[i + 1]) {
                Swap(array[i], array[i + 1]);
            }
        }
    }
}

void InsertSort(vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len == 0 || arr_len == 1) return;

    for (int i = 1; i < arr_len; ++i) {
        for (int j = i; j >= 1; --j) {
            if (array[j] < array[j - 1]) {
                Swap(array[j], array[j - 1]);
            }
        }
    }
}

void TestSelectSort(bool is_print = true) {
    TimerClock tc(true);
    for (int i = 0; i < 100; ++i) {
        vector<int> array = GenerateRandom1DIntegerArray<int>(20, 1000, 2000);
        vector<int> arr_a = array;
        vector<int> arr_b = array;
        SelectSort(arr_a);
        sort(arr_b.begin(), arr_b.end());
        if (is_print) {
            if (arr_a == arr_b) {
                cout << i << ": " << array[0] << " " << array[1] << " arr_a == arr_b" << endl;
            }
        }
    }
//    vector<int> array = GenerateRandom1DIntegerArrayUseRandSideClose(23, 50, 25);
//    vector<int> array = GenerateRandom1DIntegerArray<int>(23, 50, 25);
//    vector<int> arr_a = array;
//    vector<int> arr_b = array;
//    cout << "array:" << endl;
//    Print1DVector<int>(array);
//    cout << "arr_a:" << endl;
//    Print1DVector<int>(arr_a);
//
//    SelectSort(arr_a);
//    cout << "arr_b:" << endl;
//    Print1DVector<int>(arr_b);
//    cout << endl;
//
//    cout << "arr_a:" << endl;
//    Print1DVector<int>(arr_a);
//
//    sort(arr_b.begin(), arr_b.end());
//    cout << "arr_b:" << endl;
//    Print1DVector<int>(arr_b);
//
//    if (arr_a == arr_b) cout << "arr_a == arr_b" << endl;
}

void TestBubbleSort(bool is_print = true) {
    TimerClock tc(true);
    for (int i = 0; i < 100; ++i) {
        vector<int> array = GenerateRandom1DIntegerArray<int>(20, 1000, 2000);
        vector<int> arr_a = array;
        vector<int> arr_b = array;
        BubbleSort(arr_a);
        sort(arr_b.begin(), arr_b.end());
        if (is_print) {
            if (arr_a == arr_b) {
                cout << i << ": " << array[0] << " " << array[1] << " arr_a == arr_b" << endl;
            }
        }
    }
}

void TestInsertSort(bool is_print = true) {
    TimerClock tc(true);
    for (int i = 0; i < 100; ++i) {
        vector<int> array = GenerateRandom1DIntegerArray<int>(20, 1000, 2000);
        vector<int> arr_a = array;
        vector<int> arr_b = array;
        InsertSort(arr_a);
        sort(arr_b.begin(), arr_b.end());
        if (is_print) {
            if (arr_a == arr_b) {
                cout << i << ": " << array[0] << " " << array[1] << " arr_a == arr_b" << endl;
            }
        }
    }
}

int main() {
    TestInsertSort(false);
    TestBubbleSort(false);
    TestSelectSort(false);
    int a = -4;
    int b = -9;
    SwapXor(a, b);
    cout << "a: " << a << "\tb: " << b << endl;

    return 0;
}
