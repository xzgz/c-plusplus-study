#include <bits/stdc++.h>

using namespace std;

/*
 * 题目描述：
 * 输入一个字符串(不会为空)，再输入一个字符集(不会为空，也不会出现重复字符)。要求输出包含了字符集所有字符的第一个最小
 * 子串，如果没有符合条件的子串，则输出#。
 * 示例输入：
 * ABAKJSDYUIWNQJNDSAHDBALSDH
 * ABD
 * 示例输出：
 * DBA
 */

void FindSubsetFromStr(const string& str, const string& sub_str) {
  set<char> sub_set;
  for (int i = 0; i < sub_str.size(); ++i) {
    sub_set.insert(sub_str[i]);
  }
  for (int i = 0; i <= str.size()-sub_str.size(); ++i) {
    if (sub_set.count(str[i])) {
      set<char> temp(sub_set);
      for (int j = i; j < i+sub_str.size(); ++j) {
        if (temp.count(str[j])) temp.erase(str[j]);
      }
      if (temp.empty()) {
        for (int j = i; j < i+sub_str.size(); ++j) {
          cout << str[j];
        }
        return;
      }
    }
  }
  cout << "#";
}

int main() {
  string str, sub_str;
  cin >> str;
  cin >> sub_str;
  FindSubsetFromStr(str, sub_str);

  return 0;
}
