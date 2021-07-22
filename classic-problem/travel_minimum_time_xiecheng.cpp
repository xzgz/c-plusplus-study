#include <bits/stdc++.h>

using namespace std;

/*
refer to: https://www.nowcoder.com/discuss/245173?type=post&order=time&pos=&page=1
题目描述：
有n个城市，某个旅行者需要不重复的旅行一遍，求最短时间。
输入描述：
第一行2个数n,m分别表示城市个数和城市之间的路线个数。接下来是m行，
每行3个数a,b,t分别表示某条路线起始、终止城市编号（从0开始）以及该路线的时间。
输出描述：最短路径的时间。
示例输入：
4 6
0 1 1
0 2 2
0 3 3
1 2 2
1 3 3
2 3 1
示例输出：
7
 */
void helper(int idx, int nums, int& res, int cur, vector<vector<pair<int, int> > >& neigh,
			vector<bool>& flag) {
  if (idx == 0 && flag[idx] == true) {
	if (nums == flag.size())
	  res = min(res, cur);
	return;
  }
  for (int i = 0; i < neigh[idx].size(); i++) {
	if (flag[neigh[idx][i].first] == false) {
	  flag[neigh[idx][i].first] = true;
	  helper(neigh[idx][i].first, nums + 1, res, cur + neigh[idx][i].second, neigh, flag);
	  flag[neigh[idx][i].first] = false;
	}
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  if (n == 1) {
	cout << 0 << endl;
	return 0;
  }
  vector<vector<pair<int, int> > > neigh(n);
  while (m--) {
	int a, b, t;
	cin >> a >> b >> t;
	neigh[a].push_back(make_pair(b, t));
	neigh[b].push_back(make_pair(a, t));
  }
  vector<bool> flag(n, false);
  int res = INT_MAX;
  helper(0, 0, res, 0, neigh, flag);
  if (res == INT_MAX)
	cout << -1;
  else
	cout << res;

  return 0;
}
