#include <bits/stdc++.h>

using namespace std;

/*
 * 输入两个正整数m、n，将m个字母A，n个字母B按照一定顺序排列，使得不会出现连续3个字符相同的情况。
 * 请输出任意一种排列。m、n会保证存在这样的排列。
 */
int main() {
  int m, n;
  int interval;
  bool a;
  cin >> m;
  cin >> n;

  if(m > n) {
    interval = m/n + 1;
    a = true;
  } else {
    interval = n/m + 1;
    a = false;
  }

  int mc = 0, nc = 0;
  for (int i = 0; i < m+n; ++i) {
    if (a) {
      if ((i + 1) % interval == 0) {
        if (nc < n) {
          cout << "B ";
          nc++;
        }
      } else {
        if (mc < m) {
          cout << "A ";
          mc++;
        }
      }
    } else {
      if ((i + 1) % interval == 0) {
        if (mc < m) {
          cout << "A ";
          mc++;
        }
      } else {
        if (nc < n) {
          cout << "B ";
          nc++;
        }
      }
    }
  }

  return 0;
}
