#include <bits/stdc++.h>

using namespace std;

// refer to https://www.cnblogs.com/ryan-mask/p/10102850.html

struct Point {
  int x;
  int y;
};

int IslandConut(vector<string>& mat) {
  int rows = mat.size();
  int cols = rows > 0 ? mat[0].size() : 0;
  if (rows == 0 || cols == 0) return 0;
  queue<Point> island;
  vector<int> dx = { 0, 0, -1, 1 };
  vector<int> dy = { -1, 1, 0, 0 };
  int island_count = 0;
  Point p;

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (mat[i][j] == '1') {
		p.x = j, p.y = i;
		island.push(p);
		mat[i][j] = '0';
		while (!island.empty()) {
		  p = island.front();
		  island.pop();
		  for (int k = 0; k < 4; ++k) {
			int x = p.x + dx[k];
			int y = p.y + dy[k];
			if (x < 0 || x >= cols || y < 0 || y >= rows) continue;
			if (mat[y][x] == '1') {
			  Point temp;
			  temp.x = x, temp.y = y;
			  island.push(temp);
			  mat[y][x] = '0';
			}
		  }
		}
		++island_count;
	  }
    }
  }

  return island_count;
}

int main() {
  int m;
  cin >> m;
  vector<string> mat(m);
  for (int i = 0; i < m; ++i) {
    string s;
    cin >> s;
    mat[i] = s;
  }
  int count = IslandConut(mat);
  cout << count;

  return 0;
}
