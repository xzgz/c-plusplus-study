#include <bits/stdc++.h>

using namespace std;

/*
 * 题目描述：
 * 有N个城市，现在给出这N个城市之间是否有路的连接矩阵，给定起始和目标城市，
 * 并且规定了一些特定城市的访问顺序，其他城市的访问顺序不做限制，并且每个
 * 城市的访问次数也不作限制，求能否从起始城市走到目标城市。
 */
bool dfs(int start, int end, vector<vector<int> >& road, vector<bool>& visited,
		 unordered_map<int, int>& order, int& cur_order) {
  for (int i = 0; i < road.size(); ++i) {
	if (!visited[i] && road[start][i] && order[i] <= cur_order) {
	  if (i == end) return true;
	  if (order[i] == cur_order) ++cur_order;
	  visited[i] = true;
	  if (dfs(i, end, road, visited, order, cur_order)) return true;
	  if (order[i] == cur_order) --cur_order;
	  visited[i] = false;
	}
  }

  return false;
}

bool bfs(int start, int end, vector<vector<int> >& road, vector<int>& visited_time,
		 unordered_map<int, int>& order, int& start_order) {
  if (start == end) return true;

  int city_cnt = road.size();
  queue<int> city_queue;
  queue<int> order_queue;
  city_queue.push(start);
  order_queue.push(start_order);
  int max_depth = -1;
  while (!city_queue.empty()) {
	int num = city_queue.size();
	for (int i = 0; i < num; ++i) {
	  int cur_city = city_queue.front();
	  int cur_order = order_queue.front();
	  city_queue.pop();
	  order_queue.pop();
	  for (int j = 0; j < city_cnt; ++j) {
		if (j != cur_city && road[cur_city][j] && order[j] <= cur_order && visited_time[j] <= city_cnt-3) {
		  if (j == end) {
			cout << "max depth: " << max_depth << endl;
			return true;
		  } else {
			city_queue.push(j);
			if (order[j] == cur_order) order_queue.push(cur_order+1);
			else order_queue.push(cur_order);
			visited_time[j]++;
			max_depth = max(max_depth, int(city_queue.size()));
		  }
		}
	  }
	}
  }
  cout << "max depth: " << max_depth << endl;

  return false;
}

int main() {
  int N = 4;
  vector<vector<int> > road(N, vector<int>(N, 0));
  road[0][1] = 1;
  road[1][0] = 1;
  road[0][2] = 1;
  road[2][0] = 1;
  road[0][3] = 1;
  road[3][0] = 1;
  unordered_map<int, int> order;
  order[2] = 1;
  order[1] = 2;
  order[3] = 3;
  vector<bool> visited(N, false);
  vector<int> visited_time(N, 0);
  int start = 0, end = 3;
  int cur_order = 1;
  visited[start] = true;
//  bool can_to_end = dfs(start, end, road, visited, order, cur_order);
  bool can_to_end = bfs(start, end, road, visited_time, order, cur_order);
  if (can_to_end) cout << "YES" << endl;
  else cout << "NO" << endl;

  return 0;
}
