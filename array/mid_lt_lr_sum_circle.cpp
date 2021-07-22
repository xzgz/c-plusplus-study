#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  vector<vector<int> > arrs(t);
  vector<bool> res(t, false);
  for(int i = 0; i < t; ++i) {
    int n;
    cin >> n;
    vector<int> arr(n);
    int num;
    for(int j = 0; j < n; ++j) {
      cin >> num;
      arr[j] = num;
    }
    arrs[i] = arr;
  }

  for(int i = 0; i < arrs.size(); ++i) {
    sort(arrs[i].begin(), arrs[i].end());

    int n = arrs[i].size();
    swap(arrs[i][n-1], arrs[i][n-2]);
    if(arrs[i][n-2] < arrs[i][n-3] + arrs[i][n-1]) res[i] = true;
  }

  for(int i = 0; i < res.size(); ++i) {
    if(res[i]) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}
