#include "common_function.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

/*
 * Nª ∫ÛŒ Ã‚
 */

bool IsValid(vector<int>& record, int i, int j) {
    for (int k = 0; k < i; ++k) {
        if (j == record[k] || abs(record[k] - j) == abs(k - i)) return false;
    }
    return true;
}

int Process1(int i, vector<int>& record, int n) {
    if (i == n) return 1;
    int res = 0;
    for (int j = 0; j < n; ++j) {
        if (IsValid(record, i, j)) {
            record[i] = j;
            res += Process1(i + 1, record, n);
        }
    }
    return res;
}

int Process2(int limit, int col_lim, int left_dia_lim, int right_dia_lim) {
    if (col_lim == limit) return 1;
    // all candidate queen locations are on the location of bit 1 in pos
    int pos = limit & (~(col_lim | left_dia_lim | right_dia_lim));
    int most_right_one = 0;
    int res = 0;
    while (pos != 0) {
        most_right_one = pos & (~pos + 1);
        pos = pos - most_right_one;
        res += Process2(limit,
                col_lim | most_right_one,
                (left_dia_lim | most_right_one) << 1,
                (right_dia_lim | most_right_one) >> 1);
    }
    return res;
}

int Process2(int n) {
    if (n < 1 || n > 32) return 0;
    // in the 13 queen problem, the right 13 bits of limit is 1, other bits is 0
    int limit = n == 32 ? -1 : (1 << n) - 1;
    return Process2(limit, 0, 0, 0);
}

int main() {
    int n = 14;
    vector<int> record(n, 0);
    int place_method;
    {
        TimerClock tc(true);
        place_method = Process1(0, record, n);
    }
    cout << "place_method: " << place_method << endl;

    {
        TimerClock tc(true);
        place_method = Process2(n);
    }
    cout << "place_method: " << place_method << endl;

    return 0;
}
