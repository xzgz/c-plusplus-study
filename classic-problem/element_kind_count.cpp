#include "common_function.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

/*
 * 给定一个从小到大排列的有序数组sorted_array，其中值可能为正、负、零，返回数组中每个数都平方之后，不同的结果有多少种。
 * 时间复杂度O(N)，额外空间复杂度O(N)。
 */
int Power2Diff1(const vector<int>& sorted_array) {
    size_t arr_len = sorted_array.size();
    if (arr_len == 0) return 0;

    unordered_set<int> set;
    for (int val : sorted_array) {
        set.insert(abs(val));
    }
    return set.size();
}

/*
 * 时间复杂度O(N)，额外空间复杂度O(1)。
 */
int Power2Diff2(const vector<int>& sorted_array) {
    size_t arr_len = sorted_array.size();
    if (arr_len == 0) return 0;

    int L = 0;
    int R = arr_len - 1;
    int count = 0;
    int left_abs = 0;
    int right_abs = 0;
    while (L <= R) {
        count++;
        left_abs = abs(sorted_array[L]);
        right_abs = abs(sorted_array[R]);
        if (left_abs < right_abs) {
            while (R >= 0 && abs(sorted_array[R]) == right_abs) R--;
        } else if (left_abs > right_abs) {
            while (L < arr_len && abs(sorted_array[L]) == left_abs) L++;
        } else {
            while (L < arr_len && abs(sorted_array[L]) == left_abs) L++;
            while (R >= 0 && abs(sorted_array[R]) == right_abs) R--;
//            while (L <= R && abs(sorted_array[L]) == left_abs) L++;
//            while (R >= L && abs(sorted_array[R]) == right_abs) R--;
        }
    }
    return count;
}

void TestPower2Diff() {
    int cycle = 3000;
    int length = 1000;
    vector<int> res1(cycle);
    vector<int> res2(cycle);

    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            vector<int> array = GenerateRandom1DIntegerArray<int>(-500, 500, length);
            sort(array.begin(), array.end());
            int count2 = Power2Diff2(array);
            res2[i] = count2;
        }
    }

    {
        TimerClock tc(true);
        for (int i = 0; i < cycle; ++i) {
            vector<int> array = GenerateRandom1DIntegerArray<int>(-500, 500, length);
            sort(array.begin(), array.end());
            int count1 = Power2Diff1(array);
            res1[i] = count1;
        }
    }

    for (int i = 0; i < cycle; ++i) {
        vector<int> array = GenerateRandom1DIntegerArray<int>(-500, 500, length);
        sort(array.begin(), array.end());
        int count1 = Power2Diff1(array);
        int count2 = Power2Diff2(array);
        res1[i] = count1;
        res2[i] = count2;
    }
    if (res1 == res2) {
        cout << "res1 == res2" << endl;
    }
}

int main() {
    TestPower2Diff();

    return 0;
}
