#include "common_function.h"
#include <iostream>

using namespace std;

/*
 * 从左往右尝试的模型
 * 规定1和A对应、2和B对应、3和C对应...那么一个字符串"111"就可以转化为："AAA"、"KA"和"AK"。
 * 给定一个只由数字字符组成的字符串str，返回有多少种转化结果。
 */

int Process(const string& str, int i) {
    if (i == str.length()) return 1;
    if (str[i] == '0') return 0;
    if (str[i] == '1') {
        int res = Process(str, i + 1);
        if (i + 1 < str.length()) {
            res += Process(str, i + 2);
        }
        return res;
    }
    if (str[i] == '2') {
        int res = Process(str, i + 1);
        if (i + 1 < str.length() && str[i + 1] >= '0' && str[i + 1] <= '6') {
            res += Process(str, i + 2);
        }
        return res;
    }
    // str[i] = '3' ~ '9'
    return Process(str, i + 1);
}

int ProcessDp(const string& str) {
    int N = str.length();
    vector<int> dp(N + 1);
    dp[N] = 1;
    for (int i = N - 1; i >= 0; --i) {
        if (str[i] == '0') {
            dp[i] = 0;
        } else if (str[i] == '1') {
            dp[i] = dp[i + 1];
            if (i + 1 < N) {
                dp[i] += dp[i + 2];
            }
        } else if (str[i] == '2') {
            dp[i] = dp[i + 1];
            if (i + 1 < N && str[i + 1] >= '0' && str[i + 1] <= '6') {
                dp[i] += dp[i + 2];
            }
        } else {
            dp[i] = dp[i + 1];
        }
    }
    return dp[0];
}

int main() {
    string str = "1235121";
//    string str = "11111";
    int kinds;
    kinds = Process(str, 0);
    cout << "Process transformation kinds: " << kinds << endl;
    kinds = ProcessDp(str);
    cout << "ProcessDp transformation kinds: " << kinds << endl;

    return 0;
}
