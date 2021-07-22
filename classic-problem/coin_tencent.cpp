//#include <bits/stdc++.h>
#include "common_function.h"
#include <vector>
#include <iostream>

using namespace std;

/*
refer to: https://www.nowcoder.com/discuss/241618?type=post&order=time&pos=&page=1
题目描述：
投掷n枚硬币，已知至少有p枚正面，q枚反面，请问这n枚硬币正面向上硬币数量的期望是多少
输入描述：
输入一行n,p,q（n为硬币枚数，p为至少正面次数，q为至少反面次数）
输出期望：输出取膜
示例输入：
2 1 0
示例输出：
333333337
说明：
期望为1/3x1+1/3x1+1/3x2=4/3，又因为333333337x3%1000000007=4，所以答案是333333337。
取模思路：把分子a加上1e9+7的整数倍直到能被分母b整除为止，然后返回整除时的商
 */
long Cnk(int n, int k) {
    if (n < k) return 0;
    if (k == 0) return 1;
    long num = Cnk(n-1, k-1) + Cnk(n-1, k);
    return num;
}

void CnkDp1(vector<vector<long> >& dp, int n, int k) {
    if (n < k) {
        dp[n][k] = 0;
        return;
    }
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
        }
    }
    return;
}

void CnkDp2(vector<vector<long> >& dp, int n, int k) {
    if (n < k) {
        dp[n % 2][k] = 0;
        return;
    }
    dp[0][0] = 1;
    dp[1][0] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[0][i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            dp[i % 2][j] = dp[(i - 1) % 2][j - 1] + dp[(i - 1) % 2][j];
        }
    }
    return;
}

void TestCnk1() {
    int N = 26;
    vector<long> cnk(N + 1);

    {
        TimerClock tc(true);
        for (int n = 0; n <= N; ++n) {
            vector<vector<long> > dp1(n + 1, vector<long>(n + 1));
            for (int i = 0; i <= n; ++i) {
                CnkDp1(dp1, n, i);
                cnk[i] = dp1[n][i];
            }
        }
    }

    {
        TimerClock tc(true);
        for (int n = 0; n <= N; ++n) {
            vector<vector<long> > dp2(2, vector<long>(n + 1));
            for (int i = 0; i <= n; ++i) {
                CnkDp2(dp2, n, i);
                cnk[i] = dp2[n % 2][i];
            }
        }
    }

    {
        TimerClock tc(true);
        for (int n = 0; n <= N; ++n) {
            for (int i = 0; i <= n; ++i) {
                long val = Cnk(n, i);
                cnk[i] = val;
            }
        }
    }
}

void TestCnk2() {
    int N = 26;
    for (int n = 0; n <= N; ++n) {
        vector<long> cnk1(n + 1);
        vector<long> cnk2(n + 1);
        vector<long> cnk3(n + 1);

        vector<vector<long> > dp1(n + 1, vector<long>(n + 1));
        for (int i = 0; i <= n; ++i) {
            CnkDp1(dp1, n, i);
            cnk1[i] = dp1[n][i];
        }

        vector<vector<long> > dp2(2, vector<long>(n + 1));
        for (int i = 0; i <= n; ++i) {
            CnkDp2(dp2, n, i);
            cnk2[i] = dp2[n % 2][i];
        }

        for (int i = 0; i <= n; ++i) {
            long val = Cnk(n, i);
            cnk3[i] = val;
        }

        cout << n << ": ";
        if (cnk1 == cnk2) cout << "cnk1 == cnk2";
        if (cnk1 == cnk3) cout << " cnk1 == cnk3" << endl;
    }
}

int getOne(int num) {
    int ret = 0;
    int tmp;
    while (num) {
        ret++;
        tmp = num - 1;
        num = num & tmp;
    }
    return ret;
}

long long fast_mod(long long a, long long b){
    int M = 1000000007;
    int step = 0;
    while((step * M + a) % b != 0)
        step += 1;
    return (step * M + a) / b;
}

long long fraction_mod(long long a, long long b, int mod) {
    int n = mod - 2;
    long long ans = 1;
    while (n) {
        if (n & 1) ans = (ans * b) % mod;
        b = (b * b) % mod;
        n >>= 1;
    }
//    long long inv_b = (ans + mod) % mod;
    long long inv_b = ans % mod;

    return (a * inv_b) % mod;
}

int main() {
  int n, p, q;
  cin >> n >> p >> q;
  int pp = n - q;  // 正面的上界
//  long long sum = 0;
//  int count = 0;
//
//  // 每个组合都是等概率的
//  // 2^n种组合数，i每种取值就代表1种组合；0代表全为反面；2^n-1代表全为正面
//  for (int i = 0; i < pow(2, n); i++) {
//	int ones = getOne(i);  // 模拟正面的个数
//	if (ones >= p && ones <= pp) {
//	  count++;      // 合法组合数
//	  sum += ones;  // 正面向上的个数
//	}
//  }
//
//  cout << fast_mod(sum, count);

    long denominator = 0;
    long numerator = 0;
    vector<vector<long> > dp(2, vector<long>(n + 1));
    for (int i = p; i <= pp; ++i) {
        CnkDp2(dp, n, i);
        long cnk = dp[n % 2][i];
        denominator += cnk;
        numerator += i * cnk;
    }
    cout << denominator << " " << numerator << endl;

//    long long res = fraction_mod(4, 3, 1000000007);
    long long res = fraction_mod(numerator, denominator, 1000000007);
    cout << res << endl;
    res = fast_mod(numerator, denominator);
    cout << res << endl;

//    TestCnk1();
//    TestCnk2();

    return 0;
}
