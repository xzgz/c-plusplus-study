#include <bits/stdc++.h>

using namespace std;

/*
 * 题目描述：
 * 某种冰激淋中有n种配料，每种配料在店铺中有wi份，如果用完了就要去商店中购买。商店里
 * 每种配料售价为vi元。小Q现在有店铺中的这些配料，还有一些钱，小Q用这些配料和钱能够做
 * 出多少份冰激淋？
 * 输入描述：
 * 输入第一行包含2个数字n,m(1<=n<=100,1<=m<=10^12)，分别代表冰激淋配料的种类数量和小
 * Q的钱数，之后的一行包含n个数字wi(0<=wi<=10^12)，代表每份原料的储配数量，之后的一
 * 行包含n个数字vi(1<=vi<=100)，代表每份配料的售价。
 * 输出描述：
 * 输出一个数字，代表小Q最多可以制作的冰激淋数量。
 * 示例输入：
 * 3 10
 * 2 5 3
 * 2 1 3
 * 示例输出：
 * 4
 *
 * 解题思路1：
 * 首先找到数组w的最小值min_w和最大值max_w。然后计算制作的冰激淋的数量为max_w时需要的
 * 钱数sum_m，若sum_m<=m，则计算一份冰激淋所需配料的价格总和sum_v，显然制作的冰激淋的
 * 数量最多为 c = max_w + (m - sum_m) / sum_v。否则，初始化c=min_w，然后让c累加，直至
 * 需要的钱数sum_m>m，得到制作冰激淋的数量最多为c-1。
 *
 * 解题思路2：
 * 首先找到数组w的最小值min_w和最大值max_w。然后计算制作的冰激淋的数量为max_w时需要的
 * 钱数sum_m，若sum_m<=m，则计算一份冰激淋所需配料的价格总和sum_v，显然制作的冰激淋的
 * 数量最多为 c = max_w + (m - sum_m) / sum_v。否则，初始化 c = (min_w + max_w) / 2，
 * 采用二分法找到合适的c，使得 sum_m(c) > m, sum_m(c-1) <= m，得到制作冰激淋的数量最
 * 多为c-1。
 */

long IceCreamCount(const vector<long>& w, const vector<int>& v, long m) {
  long min_w = LONG_MAX;
  long max_w = -1;
  for (int i = 0; i < w.size(); ++i) {
    if (w[i] < min_w) min_w = w[i];
    if (w[i] > max_w) max_w = w[i];
  }

  long c = max_w;
  long sum_m = 0;
  for (int i = 0; i < w.size(); ++i) {
    sum_m += (c - w[i]) * v[i];
  }
  if (sum_m <= m) {
    int sum_v = 0;
    for (int i = 0; i < v.size(); ++i) {
      sum_v += v[i];
    }
    assert(sum_v);
    c += (m - sum_m) / sum_v;
    return c;
  } else {
    sum_m = 0;
    for (long i = min_w+1; i <= max_w; ++i) {
      for (int j = 0; j < w.size(); ++j) {
        if (w[j] - i < 0) sum_m += v[j];
        if (sum_m > m) return i-1;
      }
    }
  }

  return 0;
}

long Count2Money(const vector<long>& w, const vector<int>& v, long count) {
  long sum_m = 0;
  long lack_w;
  for (int i = 0; i < w.size(); ++i) {
    lack_w = count - w[i];
    if (lack_w > 0) sum_m += lack_w * v[i];
  }

  return sum_m;
}

long IceCreamCountV2(const vector<long>& w, const vector<int>& v, long m) {
  long min_w = LONG_MAX;
  long max_w = -1;
  for (int i = 0; i < w.size(); ++i) {
    if (w[i] < min_w) min_w = w[i];
    if (w[i] > max_w) max_w = w[i];
  }

  long c = max_w;
  long sum_m = Count2Money(w, v, c);
  if (sum_m <= m) {
    int sum_v = 0;
    for (int i = 0; i < v.size(); ++i) {
      sum_v += v[i];
    }
    assert(sum_v);
    c += (m - sum_m) / sum_v;
    return c;
  } else {
    assert(min_w < max_w);
    long min_c = min_w;
    long max_c = max_w;
    c = (min_c + max_c) / 2;
    while (min_c < max_c) {
      sum_m = Count2Money(w, v, c);
      if (sum_m <= m && c+1 == max_c) return c;
      if (sum_m < m) {  // money is sufficient
        min_c = c;
        c = (min_c + max_c) / 2;
      } else {          // money is insufficient
        if (sum_m == m) {
          return c;
        }
        else {
          // When count=c, money is insufficient, but when count=c-1, money is sufficient, the count should be c-1.
          if (Count2Money(w, v, c-1) <= m) return c-1;
        }
        max_c = c;
        c = (min_c + max_c) / 2;
      }
    }
  }

  return 0;
}

int main() {
  long n, m;
  cin >> n;
  cin >> m;
  vector<long> w(n);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    int wi;
    cin >> wi;
    w[i] = wi;
  }
  for (int i = 0; i < n; ++i) {
    int vi;
    cin >> vi;
    v[i] = vi;
  }

//  long count = IceCreamCount(w, v, m);
  long count = IceCreamCountV2(w, v, m);
  cout << count;

  return 0;
}
