#include "common_function.h"
#include <vector>
#include <cassert>
#include <iostream>
#include <numeric>

using namespace std;

/*
detail: https://juejin.im/post/5b40c99ee51d45190b615f33#heading-0
背包问题：有一个背包，它的容量为C(Capacity)。现在有n中不同的物品，编号为0…n-1，
其中每一件物品的重量为w(i)，价值为v(i)。问可以向这个背包中盛放哪些物品，
使得在不超过背包容量的基础上，物品的总价值最大。
*/

/*
思路：F(n,C)表示在考虑将前n个物品放进容量为C的背包，能取得的最大价值。
对于F(i,c)，有两种情况，将第i个物品加入和直接忽略第i个物品
F(i,C) = max{F(i-1, C), v(i) + F(i-1, C-w(i))}
*/

class Solution1 {
 private:
  vector<vector<int> > memo;
  int bestValue(const vector<int>& w, const vector<int>& v, int index, int c) {
    if (c <= 0 || index < 0) return 0;
    if (memo[index][c] != -1) return memo[index][c];

    int res = bestValue(w, v, index-1, c);
    if (c >= w[index]) res = max(res, v[index] + bestValue(w, v, index - 1, c - w[index]));
    memo[index][c] = res;

    return res;
  }

 public:
  int knapsack01(const vector<int>& w, const vector<int>& v, int c) {
    assert(w.size() == v.size() && c >= 0);
    int n = w.size();
    if (n == 0 || c == 0) return 0;

    memo = vector<vector<int> >(n, vector<int>(c + 1, -1));
    return bestValue(w, v, n - 1, c);
  }
};

class Solution2 {
 public:
  int knapsack01(const vector<int>& w, const vector<int>& v, int c) {
    assert(w.size() == v.size() && c >= 0);
    int n = w.size();
    if (n == 0 || c == 0) return 0;

    vector<vector<int> > memo(n, vector<int>(c+1, 0));
    for (int j = 0; j <= c; ++j) memo[0][j] = (j >= w[0] ? v[0] : 0);
    for (int i = 1; i < n; ++i)
      for (int j = 0; j <= c; ++j) {
      memo[i][j] = memo[i-1][j];
      if (j >= w[i]) memo[i][j] = max(memo[i][j], v[i] + memo[i - 1][j - w[i]]);
    }

    return memo[n - 1][c];
  }
};

class Solution3 {
 public:
  int knapsack01(const vector<int>& w, const vector<int>& v, int c) {
	assert(w.size() == v.size());
	int n = w.size();
	if (n == 0 || c == 0) return 0;

	vector<vector<int> > memo(2, vector<int>(c + 1, 0));
	for (int j = 0; j <= c; ++j) memo[0][j] = (j >= w[0] ? v[0] : 0);
	for (int i = 1; i < n; ++i)
	  for (int j = 0; j <= c; ++j) {
		memo[i % 2][j] = memo[(i - 1) % 2][j];
		if (j >= w[i]) memo[i % 2][j] = max(memo[i % 2][j], v[i] + memo[(i - 1) % 2][j - w[i]]);
	  }

	return memo[(n - 1) % 2][c];
  }
};

class Solution4 {
 public:
  int knapsack01(const vector<int>& w, const vector<int>& v, int c) {
	assert(w.size() == v.size() && c >= 0);
	int n = w.size();
	if (n == 0) return 0;

	vector<int> memo(c + 1, 0);
	for (int j = 0; j <= c; ++j) memo[j] = (j >= w[0] ? v[0] : 0);
	for (int i = 1; i < n; ++i)
	  for (int j = c; j >= w[i]; --j)
		memo[j] = max(memo[j], v[i] + memo[j - w[i]]);

	return memo[c];
  }
};

int Knapsack1(vector<int>& w, vector<int>& v, int index, int already_w, int bag) {
    if (already_w > bag) return -1;
    if (index == w.size()) return 0;
    int p1 = Knapsack1(w, v, index + 1, already_w, bag);
    int p2next = Knapsack1(w, v, index + 1, already_w + w[index], bag);
    int p2 = -1;
    if (p2next != -1) {
        p2 = p2next + v[index];
    }
    return max(p1, p2);
}

int Knapsack2(vector<int>& w, vector<int>& v, int index, int rest) {
    if (rest <= 0) return 0;
    if (index == w.size()) return 0;
    int p1 = Knapsack2(w, v, index + 1, rest);
    int p2 = numeric_limits<int>::min();
    if (rest >= w[index]) {
        p2 = v[index] + Knapsack2(w, v, index + 1, rest - w[index]);
    }
    return max(p1, p2);
}

int Knapsack2Dp(vector<int>& w, vector<int>& v, int bag) {
    int n = w.size();
    vector<vector<int> > dp(n + 1, vector<int>(bag + 1, 0));
    for (int index = n - 1; index >= 0; --index) {
        for (int rest = 0; rest <= bag; ++rest) {
            dp[index][rest] = dp[index + 1][rest];
            int p2 = numeric_limits<int>::min();
            if (rest >= w[index]) {
                p2 = v[index] + dp[index + 1][rest - w[index]];
            }
            dp[index][rest] = max(dp[index][rest], p2);
        }
    }
    return dp[0][bag];
}

int Knapsack2DpV2(vector<int>& w, vector<int>& v, int bag) {
    int n = w.size();
    vector<vector<int> > dp(2, vector<int>(bag + 1, 0));
    for (int index = n - 1; index >= 0; --index) {
        for (int rest = 0; rest <= bag; ++rest) {
            dp[index % 2][rest] = dp[(index + 1) % 2][rest];
            int p2 = numeric_limits<int>::min();
            if (rest >= w[index]) {
                p2 = v[index] + dp[(index + 1) % 2][rest - w[index]];
            }
            dp[index % 2][rest] = max(dp[index % 2][rest], p2);
        }
    }
    return dp[0][bag];
}

int main() {
  vector<int> w = GenerateRandom1DIntegerArray<int>(1, 30, 20);
  vector<int> v = GenerateRandom1DIntegerArray<int>(1, 10, 20);
  cout << "w:" << endl;
  Print1DVector(w);
  cout << "v:" << endl;
  Print1DVector(v);

  int c = 126;
  Solution1 so1;
  Solution2 so2;
  Solution3 so3;
  Solution4 so4;

  int max_value = so1.knapsack01(w, v, c);
  cout << "Solution1 max value: " << max_value << endl;

  max_value = so2.knapsack01(w, v, c);
  cout << "Solution2 max value: " << max_value << endl;

  max_value = so3.knapsack01(w, v, c);
  cout << "Solution3 max value: " << max_value << endl;

  max_value = so4.knapsack01(w, v, c);
  cout << "Solution4 max value: " << max_value << endl;

  max_value = Knapsack1(w, v, 0, 0, c);
  cout << "Knapsack1 max value: " << max_value << endl;

  max_value = Knapsack2(w, v, 0, c);
  cout << "Knapsack2 max value: " << max_value << endl;

  max_value = Knapsack2Dp(w, v, c);
  cout << "Knapsack2Dp max value: " << max_value << endl;

  max_value = Knapsack2DpV2(w, v, c);
  cout << "Knapsack2DpV2 max value: " << max_value << endl;

  return 0;
}
