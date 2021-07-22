#include <bits/stdc++.h>

using namespace std;

/*
题目描述：
在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个
整数，判断数组中是否含有该整数。
 */
bool Find(int target, const vector<vector<int> >& array) {
  int rows = array.size();
  int cols = rows ? array[0].size() : 0;
  int r = 0, c = cols - 1;
  while (r <= rows - 1 && c >= 0) {
	if (target == array[r][c]) return true;
	else if (target > array[r][c]) ++r;
	else --c;
  }

  return false;
}

int main() {
  vector<vector<int> > array = { { 1, 2, 8, 9 }, { 2, 4, 9, 12 }, { 4, 7, 10, 13 }, { 6, 8, 11, 15 } };
  int target = 7;
  bool flag = Find(target, array);
  cout << flag << endl;

  return 0;
}
