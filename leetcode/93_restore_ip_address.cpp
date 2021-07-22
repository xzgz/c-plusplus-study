#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
refer to: https://www.cnblogs.com/grandyang/p/4305572.html
给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

示例:

输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/restore-ip-addresses
 */

void helper(string s, int n, string out, vector<string> *res) {
  if (n == 4) {
    if (s.empty()) res->push_back(out);
  } else {
    for (int k = 1; k <= 3; ++k) {
      if (s.size() < k) break;
      int val = stoi(s.substr(0, k));
      if (val > 255 || k != to_string(val).size()) continue;
      helper(s.substr(k), n+1, out+s.substr(0, k)+(n == 3 ? "" : "."), res);
    }
  }
}

vector<string> restoreIpAddresses(string& s) {
  vector<string> res;
  if (s.size() > 12) return res;
  helper(s, 0, "", &res);
  return res;
}

int main() {
  string s = "25525511135";
  vector<string> res = restoreIpAddresses(s);
  for (string s : res) cout << s << endl;

  return 0;
}
