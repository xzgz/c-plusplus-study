#include <bits/stdc++.h>

using namespace std;

/*
detail: https://blog.csdn.net/github_36669230/article/details/58605959
题目：字符的所有组合
输入三个字符a、b、c，组合有：a, b, c , ab, ac, bc, abc。
*/

/*
思路1：假设输入n个字符，则这n个字符能构成长度为1的组合、长度为2的组合、……、长度为n的组合。
在求n个字符组成长度为m的组合的时候，与字符串全排列的求解思想类似，我们可以把这n个字符分为两个部分：
第一个字符和剩余的其他所有的n-1个字符。这个时候可以分为两种情况：
如果组合里包含第一个字符，则从所有剩余n-1个字符里选取m-1个字符；
如果组合里不包含第一个字符，则下一步在剩余的n-1个字符选取m个字符。
*/
void CombinationCore(const string::iterator it, const string::iterator end,
                     int number, vector<string> *result) {
  static string select_chars;

  if (number == 0) {
    result->push_back(select_chars);
    return;
  }
  if (it == end) return;
  // n-1个字符串中，选取number-1个字符
  select_chars.push_back(*it);
  CombinationCore(it+1, end, number-1, result);
  // n-1个字符串中，选取number个字符
  select_chars.pop_back();
  CombinationCore(it+1, end, number, result);
}

void Combination(string str, vector<string> *result) {
  if (str.empty()) return;
  for (int i = 1; i <= str.size(); i++)
    CombinationCore(str.begin(), str.end(), i, result);
  sort(result->begin(), result->end());
  vector<string>::iterator new_end = unique(result->begin(), result->end());
  result->erase(new_end, result->end());
}

void CombinationCoreRP(const string::iterator it, const string::iterator end,
                       int number, vector<string> *result) {
  static string select_chars;

  if (number == 0) {
    result->push_back(select_chars);
    return;
  }
  if (it == end) return;
  select_chars.push_back(*it);
  CombinationCoreRP(it+1, end, number-1, result);
  select_chars.pop_back();
  CombinationCoreRP(it+1, end, number, result);
}

void CombinationRP(string str, vector<string> *result) {
  if (str.empty()) return;

  for (int i = 1; i <= str.size(); ++i) {
    CombinationCoreRP(str.begin(), str.end(), i, result);
  }
  sort(result->begin(), result->end());
  vector<string>::iterator new_end;
  new_end = unique(result->begin(), result->end());
  result->erase(new_end, result->end());
}

/*
思路2：假设一共有n个字符，则可能的组合结果共有2^n-1种。以输入3个字符a、b、c为例：
3个字符，可以用3个位来表示，从右到左的每一位分别用来代表a、b、c，
该位为1表示取该元素，该位为0表示不取该元素。例如如组合a表示为001，组合b表示为010，
组合ac表示为101，组合abc表示为111，而000是没有意义的，所以总共的结果就是2^n-1种。
因此，我们可以从值1开始循环到2^n-1，输出每个值所代表的组合即可。
*/
void Combination2(const string& str, vector<string> *result) {
  if (str.empty()) return;

  int i, j, temp;
  int length = str.size();
  int n = 1 << length;              // n为2^n-1(111)
  for (i = 1; i < n; i++) {         // 依次输出值1到2^n-1所代表值的组合
    string res;
    for (j = 0; j < length; j++) {  // 判断第j位是否为1
      temp = i;
      if (temp & (1 << j)) res.push_back(str[j]);
    }
    result->push_back(res);
  }
  sort(result->begin(), result->end());
  vector<string>::iterator new_end = unique(result->begin(), result->end());
  result->erase(new_end, result->end());
}

void Combination2RP(const string& str, vector<string> *result) {
  if (str.empty()) return;

  int length = str.size();
  int n = 1 << length;
  for (int i = 1; i < n; ++i) {
    string res;
    for (int j = 0; j < length; ++j) {
      if (i & (1 << j)) res.push_back(str[j]);
    }
    result->push_back(res);
  }
  sort(result->begin(), result->end());
  vector<string>::iterator new_end = unique(result->begin(), result->end());
  result->erase(new_end, result->end());
}

int main() {
  string str = "baa";
//  Combination(str);
//  cout << "******************\n";
  vector<string> result;
//  Combination(str, &result);
  CombinationRP(str, &result);
//  Combination2(str, &result);
//  Combination2RP(str, &result);
  for (string s : result) cout << s << endl;

  return 0;
}
