#include "common_function.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * 在数组元素从小到大排列的sorted_array上，寻找是否存在值为number的元素。
 */
bool Exist(const vector<int>& sorted_array, const int number) {
    size_t arr_len = sorted_array.size();
    if (arr_len == 0) return false;

    int L = 0;
    int R = arr_len - 1;
    int mid;
    while (L < R) {
        mid = (L + R) >> 1;
        if (sorted_array[mid] == number) {
            return true;
        } else if (sorted_array[mid] > number) {
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    return sorted_array[L] == number;
}

/*
 * 在数组元素从小到大排列的sorted_array上，找满足<=value的最右位置。
 */
int MostRightIndex(const vector<int>& sorted_array, const int value) {
    int index = -1;
    size_t arr_len = sorted_array.size();
    if (arr_len == 0) return index;

    int L = 0;
    int R = arr_len - 1;
    int mid;
    while (L <= R) {
        mid = (L + R) >> 1;
        if (sorted_array[mid] <= value) {
            index = mid;
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    return index;
}

/*
 * 在数组元素从小到大排列的sorted_array上，找满足>=value的最左位置。
 */
int MostLeftIndex(const vector<int>& sorted_array, const int value) {
    int index = -1;
    size_t arr_len = sorted_array.size();
    if (arr_len == 0) return index;

    int L = 0;
    int R = arr_len - 1;
    int mid;
    while (L <= R) {
        mid = (L + R) >> 1;
        if (sorted_array[mid] >= value) {
            index = mid;
            R = mid - 1;
        } else {
            L = mid + 1;
        }
    }
    return index;
}

/*
 * 局部最小定义：array[0] < array[1]; array[N - 1] < array[N - 2]; array[i] < array[i - 1] && array[i] < array[i + 1]
 * 数组array无序，且任意两个相邻的元素都不相等，求局部最小的位置。
 */
int GetLessIndex(const vector<int>& array) {
    int index = -1;
    size_t arr_len = array.size();
    if (arr_len == 0) return index;
    if (arr_len == 1) return 0;
    if (array[0] < array[1]) return 0;
    if (array[arr_len - 1] < array[arr_len - 2]) return arr_len - 1;

    int left = 1;
    int right = arr_len - 2;
    while (left < right) {
        int mid = (left + right) >> 1;
        if (array[mid] > array[mid - 1]) {
            right = mid - 1;
        } else if (array[mid] > array[mid + 1]) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return left;
}

void TestExist() {
    TimerClock tc(true);
    int cycle = 100;
    int length = 1000;
    vector<bool> exist_label(length);
    vector<bool> exist_pred(length);
    for (int i = 0; i < cycle; ++i) {
        vector<int> array(length);
        vector<int> replace_indices = GenerateRandom1DIntegerArray<int>(1, length - 1, length);

        for (int j = 0; j < length; ++j) {
            if (j % 2 == 0) {
                vector<int> array1 = GenerateRandom1DIntegerArray<int>(0, replace_indices[j], replace_indices[j]);
                vector<int> array2 = GenerateRandom1DIntegerArray<int>(replace_indices[j], length, length - replace_indices[j]);
                for (int k = 0; k < replace_indices[j]; ++k) {
                    array[k] = array1[k];
                }
                for (int k = 0; k < length - replace_indices[j]; ++k) {
                    array[replace_indices[j] + k] = array2[k];
                }
                sort(array.begin(), array.end());
                array[replace_indices[j]] = replace_indices[j];
                bool is_exist = Exist(array, replace_indices[j]);
                exist_label[j] = true;
                exist_pred[j] = is_exist;
            } else {
                vector<int> array1 = GenerateRandom1DIntegerArray<int>(0, replace_indices[j] - 1, replace_indices[j]);
                vector<int> array2 = GenerateRandom1DIntegerArray<int>(replace_indices[j] + 1, length, length - replace_indices[j]);
                for (int k = 0; k < replace_indices[j]; ++k) {
                    array[k] = array1[k];
                }
                for (int k = 0; k < length - replace_indices[j]; ++k) {
                    array[replace_indices[j] + k] = array2[k];
                }
                sort(array.begin(), array.end());
                bool is_exist = Exist(array, replace_indices[j]);
                exist_label[j] = false;
                exist_pred[j] = is_exist;
            }
        }
        if (exist_label == exist_pred) cout << i << ": exist_label == exist_pred" << endl;
    }
}

int main() {
    TestExist();

    return 0;
}
