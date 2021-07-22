#include "common_function.h"
#include <vector>
#include <iostream>

using namespace std;

/*
 * array中都是正数且无重复值，返回组成aim的方法数，每一个数可以使用任意次。
 */

int CoinsWay(vector<int>& array, int index, int rest) {
    if (index == array.size()) return rest == 0 ? 1 : 0;
    int ways = 0;
    for (int zhang = 0; zhang * array[index] <= rest; ++zhang) {
        ways += CoinsWay(array, index + 1, rest - zhang * array[index]);
    }
    return ways;
}

int CoinsWay(vector<int>& array, int aim) {
    if (array.empty() || aim < 0) return 0;
    return CoinsWay(array, 0, aim);
}

int CoinsWayDp1(vector<int>& array, int index, int rest, vector<vector<int> >& dp) {
    if (dp[index][rest] != -1) return dp[index][rest];
    if (index == array.size()) {
        dp[index][rest] = rest == 0 ? 1 : 0;
        return dp[index][rest];
    }
    int ways = 0;
    for (int zhang = 0; zhang * array[index] <= rest; ++zhang) {
        ways += CoinsWayDp1(array, index + 1, rest - zhang * array[index], dp);
    }
    dp[index][rest] = ways;
    return dp[index][rest];
}

int CoinsWayDp1(vector<int>& array, int aim) {
    if (array.empty() || aim < 0) return 0;
    int n = array.size();
    vector<vector<int> > dp(n + 1, vector<int>(aim + 1, -1));
    return CoinsWayDp1(array, 0, aim, dp);
}

int CoinsWayDp2(vector<int>& array, int aim) {
    if (array.empty() || aim < 0) return 0;
    int n = array.size();
    vector<vector<int> > dp(n + 1, vector<int>(aim + 1, 0));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; --index) {
        for (int rest = 0; rest <= aim; ++rest) {
            int ways = 0;
            for (int zhang = 0; zhang * array[index] <= rest; ++zhang) {
                ways += dp[index + 1][rest - zhang * array[index]];
                dp[index][rest] = ways;
            }
        }
    }
    return dp[0][aim];
}

int CoinsWayDp3(vector<int>& array, int aim) {
    if (array.empty() || aim < 0) return 0;
    int n = array.size();
    vector<vector<int> > dp(n + 1, vector<int>(aim + 1, 0));
    dp[n][0] = 1;
    for (int index = n - 1; index >= 0; --index) {
        for (int rest = 0; rest <= aim; ++rest) {
            dp[index][rest] = dp[index + 1][rest];
            if (rest - array[index] >= 0) {
                dp[index][rest] += dp[index][rest - array[index]];
            }
        }
    }
    return dp[0][aim];
}

int main() {
    vector<int> array = GenerateRandom1DIntegerArray<int>(1, 100, 15);
    cout << "array:" << endl;
    Print1DVector(array);
    int aim = 400;
    int method_count;

    {
        TimerClock tc(true);
        method_count = CoinsWay(array, aim);
    }
    cout << "CoinsWay method_count: " << method_count << endl;

    {
        TimerClock tc(true);
        method_count = CoinsWayDp1(array, aim);
    }
    cout << "CoinsWayDp1 method_count: " << method_count << endl;

    {
        TimerClock tc(true);
        method_count = CoinsWayDp2(array, aim);
    }
    cout << "CoinsWayDp2 method_count: " << method_count << endl;

    {
        TimerClock tc(true);
        method_count = CoinsWayDp3(array, aim);
    }
    cout << "CoinsWayDp3 method_count: " << method_count << endl;

    return 0;
}
