#include "common_function.h"
#include <iostream>

using namespace std;

int minDistance(string word1, string word2) {
  int m = word1.size(), n = word2.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  for (int i = 0; i <= m; ++i) dp[i][0] = i;
  for (int i = 0; i <= n; ++i) dp[0][i] = i;
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
      }
    }
  }
  return dp[m][n];
}

int main() {
  string str1 = "as正确的";
  string str2 = "ab正的";
  const char *str3 = "收aa到bb";
  int dis = minDistance(str1, str2);
  cout << dis << endl;
  cout << str1 << endl;
  cout << str2 << endl;
  cout << str3 << endl;

  return 0;
}
