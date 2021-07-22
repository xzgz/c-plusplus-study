#include "common_function.h"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>

using namespace std;

/*
 * 给定一个正整数数组array，array无序，把array想象成一个直方图，这个直方图如果装水，能装下几格水？
 */
int Water1(const vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len <= 2) return 0;

    int water = 0;
    for (int i = 1; i <= arr_len - 2; ++i) {
        int left_max = numeric_limits<int>::min();
        for (int j = 0; j < i; ++j) {
            left_max = max(left_max, array[j]);
        }
        int right_max = numeric_limits<int>::min();
        for (int j = i + 1; j < arr_len; ++j) {
            right_max = max(right_max, array[j]);
        }
        water += max(min(left_max, right_max) - array[i], 0);
    }
    return water;
}

int Water2(const vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len <= 2) return 0;

    vector<int> left_max(arr_len);
    vector<int> right_max(arr_len);
    left_max[0] = array[0];
    for (int i = 1; i < arr_len; ++i) {
        left_max[i] = max(array[i], left_max[i - 1]);
    }
    right_max[arr_len - 1] = array[arr_len - 1];
    for (int i = arr_len - 2; i >= 0; --i) {
        right_max[i] = max(array[i], right_max[i + 1]);
    }

    int water = 0;
    for (int i = 1; i <= arr_len - 2; ++i) {
        water += max(min(left_max[i - 1], right_max[i + 1]) - array[i], 0);
    }
    return water;
}

int Water3(const vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len <= 2) return 0;

    vector<int> right_max(arr_len);
    right_max[arr_len - 1] = array[arr_len - 1];
    for (int i = arr_len - 2; i >= 0; --i) {
        right_max[i] = max(array[i], right_max[i + 1]);
    }

    int water = 0;
    int left_max = array[0];
    for (int i = 1; i <= arr_len - 2; ++i) {
        water += max(min(left_max, right_max[i + 1]) - array[i], 0);
        left_max = max(left_max, array[i]);
    }
    return water;
}

int Water4(const vector<int>& array) {
    size_t arr_len = array.size();
    if (arr_len <= 2) return 0;

    int L = 1;
    int R = arr_len - 2;
    int left_max = array[0];
    int right_max = array[arr_len - 1];
    int water = 0;
    while (L <= R) {
        if (left_max <= right_max) {
            water += max(left_max - array[L], 0);
            left_max = max(left_max, array[L++]);
        } else {
            water += max(right_max - array[R], 0);
            right_max = max(right_max, array[R--]);
        }
    }
    return water;
}

void TestWater() {
    int cycle = 10000;
    int length = 1000;
    vector<int> res1(cycle);
    vector<int> res2(cycle);
    vector<int> res3(cycle);
    vector<int> res4(cycle);
    vector<int> array = GenerateRandom1DIntegerArray<int>(1, 500, length);

    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            int water4 = Water4(array);
            res4[i] = water4;
        }
    }
    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            int water2 = Water2(array);
            res2[i] = water2;
        }
    }
    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            int water1 = Water1(array);
            res1[i] = water1;
        }
    }
    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            int water3 = Water3(array);
            res3[i] = water3;

        }
    }

    for (int i = 0; i < cycle; ++i) {
        array = GenerateRandom1DIntegerArray<int>(1, 500, length);
        int water1 = Water1(array);
        int water2 = Water2(array);
        int water3 = Water3(array);
        int water4 = Water4(array);
        res1[i] = water1;
        res2[i] = water2;
        res3[i] = water3;
        res4[i] = water4;
    }
//    Print1DVector<int>(res1);
//    Print1DVector<int>(res2);
//    Print1DVector<int>(res3);
//    Print1DVector<int>(res4);
    if (res1 == res2 && res1 == res3 && res1 == res4) {
        cout << "res1 == res2 && res1 == res3 && res1 == res4" << endl;
    }
}

int main() {
    TestWater();

    return 0;
}
