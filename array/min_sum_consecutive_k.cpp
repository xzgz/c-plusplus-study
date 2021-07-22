#include <bits/stdc++.h>

using namespace std;

/*
 * 题目描述：
 * 一个整型数组，求数组中的一个位置(数组的位置从1开始)，使得从这个位置开始的连续k个数的和最小。
 * 输入描述：
 * 第一行2个数，分别是数组的长度n和k，第二行是该数组的n个数。
 * 示例输入：
 * 6 3
 * 2 3 5 1 1 6
 * 示例输出：
 * 3
 */

int main() {
  int n, k;
  cin >> n;
  cin >> k;
  vector<int> h(n);

  for (int i = 0; i < n; ++i) {
    int hi;
    cin >> hi;
    h[i] = hi;
  }

  int min_k_h;
  int sum = 0;
  int loc = 0;
  for (int j = 0; j < k; ++j) {
    sum += h[j];
  }
  min_k_h = sum;
  for (int i = 1; i < n-k+1; ++i) {
    sum = sum - h[i-1] + h[i-1+k];
    (sum < min_k_h) ? (min_k_h = sum, loc = i) : (0);
  }
  cout << loc+1;

  return 0;
}
