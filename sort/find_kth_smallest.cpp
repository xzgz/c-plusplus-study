#include "common_function.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <iostream>

using namespace std;

pair<int, int> Partition(vector<int>& arr, int L, int R, int pivot) {
    int less = L - 1;
    int more = R + 1;
    int cur = L;
    while (cur < more) {
        if (arr[cur] < pivot) {
            swap(arr[++less], arr[cur++]);
        } else if (arr[cur] > pivot) {
            swap(arr[cur], arr[--more]);
        } else {
            ++cur;
        }
    }
    return make_pair<int, int>(less + 1, more - 1);
}

int FindKthSmallest(vector<int>& arr, int L, int R, int index) {
    if (L == R) return arr[L];

    unsigned int seed = time(nullptr);
    srand(seed);
    int pivot_index = L + rand() % (R - L + 1);
    int pivot = arr[pivot_index];
    pair<int, int> range = Partition(arr, L, R, pivot);
    if (range.first <= index && index <= range.second) {
        return arr[index];
    } else if (index < range.first) {
        return FindKthSmallest(arr, L, range.first - 1, index);
    } else {
        return FindKthSmallest(arr, range.second + 1, R, index);
    }
}

void TestFindKthSmallest() {
    vector<int> array = GenerateRandom1DIntegerArray<int>(-20, 50, 30);
    vector<int> arr1 = array;
    vector<int> arr2 = array;
    int k = 8;
    sort(arr1.begin(), arr1.end());
    int kth_num = FindKthSmallest(arr2, 0, arr2.size() - 1, k);
    cout << "the " << k << "th smallest number in array is " << arr1[k] << " by sort" << endl;
    cout << "the " << k << "th smallest number in array is " << kth_num << " by FindKthSmallest" << endl;

    vector<int> res_find;
    vector<int> res_sort;
    for (int i = 0; i < 50; ++i) {
        array = GenerateRandom1DIntegerArray<int>(-20, 50, 30);
        arr1 = array;
        arr2 = array;
        sort(arr1.begin(), arr1.end());
        kth_num = FindKthSmallest(arr2, 0, arr2.size() - 1, k);
        res_sort.push_back(arr1[k]);
        res_find.push_back(kth_num);
    }
    Print1DVector(res_sort);
    Print1DVector(res_find);
}

int main() {
    TestFindKthSmallest();

    return 0;
}
