#include <bits/stdc++.h>

using namespace std;

/*
refer to: https://www.nowcoder.com/discuss/242989?type=all&order=time&pos=&page=1
题目描述：
扔n个般子，第i个骰子有可能投掷出Xi种等概率的不同的结果，数字
从1到Xi。所有般子的结果的最大值将作为最终结果。求最终结果的期望。
输入描述：
第一行一个整数n，表示有n个骰子。（1<=n<=50）
第二行n个整数，表示每个骰子的结果数xi。（2<=Xi<=50）
输出描述：
输出最终结果的期望，保留两位小数
示例输入：
2
2 2
示例输出：
1.75
解题思路：p(x=xi) = p(x<=xi) - p(x<=xi-1)
 */
int main() {
  int n;
  cin >> n;
  vector<int> X(n);
  for (int i = 0; i < n; ++i) cin >> X[i];

  sort(X.begin(), X.end());
  int max_x = X[X.size()-1];
  vector<float> p(max_x+1, 0);
  int begin = 0;
  for (int max = 1; max <= max_x; ++max) {
    while (X[begin] < max) ++begin;
    float p_max = 1.0;
    for (int i = begin; i < n; ++i)
      p_max *= max / (float)X[i];
    float sum = 0;
    for (float pi : p) sum += pi;
    p[max] = p_max - sum;
  }
  float EX = 0;
  for (int xi = 1; xi <= max_x; ++xi)
    EX += xi * p[xi];
  cout << fixed << setprecision(2) << EX;

  return 0;
}
