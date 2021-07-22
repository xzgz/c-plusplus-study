#include <bits/stdc++.h>

using namespace std;

/*
refer to: https://blog.csdn.net/yangquanhui1991/article/details/51981308
题目描述：
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14
15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
 */
vector<int> printMatrix(vector<vector<int> > matrix) {
  vector<int> result;
  int rows = matrix.size();
  int cols = rows ? matrix[0].size() : 0;
  if (rows == 0 || cols == 0) return result;
  int start = 0;
  while (rows > 2 * start && cols > start * 2) {
    int end_x = cols - 1 - start;
    int end_y = rows - 1 - start;

    for (int i = start; i <= end_x; ++i) result.push_back(matrix[start][i]);

    if (end_y > start) {
      for (int i = start+1; i <= end_y; ++i) result.push_back(matrix[i][end_x]);

	  if (end_x > start) {
		for (int i = end_x-1; i >= start; --i) result.push_back(matrix[end_y][i]);

		if (end_y > start+1) {
		  for (int i = end_y-1; i >= start+1; --i) result.push_back(matrix[i][start]);
		}
	  }
	}

    ++start;
  }

  return result;
}

int main() {
  vector<vector<int> > matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
  vector<int> res = printMatrix(matrix);
  for (int num : res) cout << num << " ";

  return 0;
}
