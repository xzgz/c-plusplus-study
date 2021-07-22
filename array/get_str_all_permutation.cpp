#include <bits/stdc++.h>

using namespace std;

/*
 * detail: https://blog.csdn.net/github_36669230/article/details/58605959
 * 题目描述：输入一个字符串，按字典序打印出该字符串中字符的所有排列
 * 例如输入字符串abc，则打印出由字符a，b，c所能排列出来的所有字符串
 * abc,acb,bac,bca,cab和cba。结果请按字母顺序输出。注意输入一个字
 * 符串,长度不超过9(可能有字符重复),字符只包括大小写字母
 * 样例输入：
 * abc
 * BCA
 * 样例输出：
 * abc acb bac bca cab cba ABC ACB BAC BCA CAB CBA
 *
 * 解题思路：
 * 依次从字符串中取出一个字符作为最终排列的第一个字符，
 * 对剩余字符组成的字符串生成全排列，最终结果为取出的
 * 字符和剩余子串全排列的组合。全排列中去掉重复的方法：
 * 第一个字符只与后面非重复出现的字符交换。
*/
bool IsSwapstr(string str, int begin_index, int end_index) {
  for (int i = begin_index; i < end_index; ++i) {
    if (str[i] == str[end_index]) return false;
  }
  return true;
}

void PermutationStr(string str, int begin_index, int length, vector<string> *result) {
  if (begin_index == length) {
    result->push_back(str);
  } else {
    for (int p_index = begin_index; p_index < length; ++p_index) {
      if (IsSwapstr(str, begin_index, p_index)) {
        swap(str[begin_index], str[p_index]);
        PermutationStr(str, begin_index + 1, length, result);
        swap(str[begin_index], str[p_index]);
      }
    }
  }
}

void Permutation(string str, vector<string> *result) {
  if (str.empty()) return;

  PermutationStr(str, 0, str.size(), result);
  sort(result->begin(), result->end());
}

int main() {
  char str[] = "uaa";
//  char *str = "a";  // will appear segmentation fault in run time

  string sstr = string(str);
  vector<string> result;
  Permutation(sstr, &result);
  cout << "count: " << result.size() << endl;
  for (vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
    cout << *it << endl;
  }

  const char *a = "qqq";
  int *b;
  cout << static_cast<const void *>(a) << endl;
  cout << (char *)(a) << endl;
  cout << b;

  return 0;
}
