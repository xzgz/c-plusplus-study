#include <bits/stdc++.h>

using namespace std;

/*
 * 现在有一个矩阵，元素由'.'和'X'构成。'.'踩2次就碎了，'X'踩一次就碎了。
 * 现给定起始(可以是'X')和终止位置，求能否从起始位置到达终止位置，并且终
 * 止位置恰好被踩碎。
 * 输入描述：
 * 第一行，测试组数。对于每一组测试用例，第一行，2个数n,m，表示矩阵的行数
 * 和列数。接下来n行是矩阵，再接下来2行分别是起点坐标和终点坐标(坐标从1开始)。
 * 示例输入：
2
4 6
X...XX
...XX.
.X..X.
......
1 6
2 2
9 47
....X.X.X.X...X..X.....X..X..X..X....X.X...X..X
XX..X...X.........X...X...X..X.XX......X...X...
..XX...X.......X.....X.....X.XX..X.....X..XX...
.X...XX....X...X.......X.X...X......X.X.X......
X......X..X.XXX....X...X.X.XX..X.......X....X.X
....XX.X...X.XXX.X..XX.XXX...XXX..XX.X.X.XX..XX
.........X...X.XXXX...XX.XX....XX..X...X....X..
.............X....XXXX....X.X...XX.XX.X.X..X...
.X......X.....X......X......X.X.X..X.......XXX.
2 34
7 30
 * 示例输出：
YES
NO
 */

bool IsCoordValid(const int px, const int py, const int bx, const int by) {
  if (0 <= px && px < bx && 0 <= py && py < by) return true;
  else return false;
}

bool IsRoad(const int px, const int py, const vector<vector<char> >& mat,
			const vector<vector<bool> >& is_used) {
  int by = mat.size();
  int bx = by ? mat[0].size() : 0;
  if (0 <= px && px < bx && 0 <= py && py < by
	  && mat[py][px] == '.' && !is_used[py][px]) return true;
  else return false;
}

bool IsTherePassagewayBFS(const vector<vector<char> >& mat, const int n, const int m,
						  const pair<int, int>& start, const pair<int, int>& end) {
  int end_sur_pt_cnt = 0;
  int dx[4] = { 0, 0, -1, 1 };
  int dy[4] = { -1, 1, 0, 0 };
  if (!(IsCoordValid(end.second, end.first, m, n) &&
		IsCoordValid(start.second, start.first, m, n))) return false;
  if (mat[end.first][end.second] == '.') {
	for (int i = 0; i < 4; ++i) {
	  if (IsCoordValid(end.second+dx[i], end.first+dy[i], m, n)
		  && mat[end.first+dy[i]][end.second+dx[i]] == '.') end_sur_pt_cnt += 1;
	}
  } else end_sur_pt_cnt = 2;
  if (end_sur_pt_cnt < 2) return false;
  if (start == end) return true;

  bool is_used[n][m] = { false };
  queue<pair<int, int> > roads;
  roads.push(start);
  pair<int, int> front;
  pair<int, int> point;
  int max_depth = -1;
  while (!roads.empty()) {
    int node_count = roads.size();
    for (int i = 0; i < node_count; ++i) {
      front = roads.front();
      roads.pop();
      for (int j = 0; j < 4; ++j) {
		point = make_pair(front.first + dy[j], front.second + dx[j]);
		if (IsCoordValid(point.second, point.first, m, n) &&
			!is_used[point.first][point.second] && mat[point.first][point.second] == '.') {
		  if (point == end) {
		    cout << endl << "max depth: " << max_depth << endl;
		    return true;
		  }
		  roads.push(point);
		  is_used[point.first][point.second] = true;
		  max_depth = max(max_depth, int(roads.size()));
		}
	  }
    }
  }
  cout << "max depth: " << max_depth << endl;

  return false;
}

bool IsTherePassagewayDFS(vector<vector<char> >& mat, const int n, const int m,
						  const pair<int, int>& start, const pair<int, int>& end) {
  int end_sur_pt_cnt = 0;
  int dx[4] = { 0, 0, -1, 1 };
  int dy[4] = { -1, 1, 0, 0 };
  if (!(IsCoordValid(end.second, end.first, m, n) &&
		IsCoordValid(start.second, start.first, m, n))) return false;
  if (mat[end.first][end.second] == '.') {
    for (int i = 0; i < 4; ++i) {
      if (IsCoordValid(end.second+dx[i], end.first+dy[i], m, n)
		  && mat[end.first+dy[i]][end.second+dx[i]] == '.') end_sur_pt_cnt +=1;
	}
  } else end_sur_pt_cnt = 2;
  if (end_sur_pt_cnt < 2) return false;
  if (start == end) return true;

  vector<vector<bool> > is_used(n, vector<bool>(m, false));
  stack<pair<int, int> > roads;
  mat[start.first][start.second] = '.';
  pair<int, int> cur = start;
  pair<int, int> top;
  int dir = 1;
  int max_depth = -1;
  while (IsRoad(cur.second, cur.first, mat, is_used) || !roads.empty()) {
	while (IsRoad(cur.second, cur.first, mat, is_used)) {
	  if (cur == end) {
		cout << endl << "max depth: " << max_depth << endl;
		return true;
	  }
	  roads.push(cur);
	  is_used[cur.first][cur.second] = true;
	  cur = make_pair(cur.first+dy[0], cur.second+dx[0]);
	  dir = 1;
	  max_depth = max(max_depth, int(roads.size()));
	}
	if (dir == 1) top = roads.top();
	cur = make_pair(top.first+dy[dir], top.second+dx[dir]);
	++dir;
	if (dir == 4) { dir = 1; roads.pop(); }
  }
  cout << "max depth: " << max_depth << endl;

  return false;
}

int main() {
  int t, n, m;
  pair<int, int> start, end;
  cin >> t;
  vector<string> result(t);
  for (int i = 0; i < t; ++i) {
    cin >> n;
    cin >> m;
    vector<vector<char> > mat(n, vector<char>(m, 0));
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < m; ++k) {
        char c;
        cin >> c;
        mat[j][k] = c;
      }
    }
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    start.first = y1 - 1;
    start.second = x1 - 1;
    end.first = y2 - 1;
    end.second = x2 - 1;

	bool is_there_passageway = IsTherePassagewayBFS(mat, n, m, start, end);
//	bool is_there_passageway = IsTherePassagewayDFS(mat, n, m, start, end);
    if (is_there_passageway) result[i] = "YES";
    else result[i] = "NO";
  }
  for (int i = 0; i < t; ++i) {
    cout << result[i] << endl;
  }

  return 0;
}
