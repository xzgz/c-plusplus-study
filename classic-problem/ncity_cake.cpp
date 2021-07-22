#include <bits/stdc++.h>

using namespace std;

/*
 * 有N个城市，各城市之间总共有M条路线，每条路线用时为ti，同时每个城市有Qi个蛋糕。
 * 现在有一个人从A城市出发前往B城市，问在用时最短的前提下，此人最多能获得多少蛋
 * 糕。假设A城市到B城市至少有一条路径。
 * 输入描述：第一行4个数，N，M，S，D，分别表示城市个数，路线总个数，出发城市编号，
 * 到达城市编号。第二行N个数，表示N个城市的蛋糕数量。接下来是M行个数，分别表示M
 * 条路线及其所需要的时间。
 *
 * 输入示例：
 * 4 5 1 4
 * 10 20 30 40
 * 1 2 2
 * 1 3 3
 * 2 3 2
 * 3 4 3
 * 2 4 4
 * 输出示例：
 * 6 80
 * 输出说明：
 * 行走路线为1->3->4
 */
struct Meta {
  int t;
  int q;
};

bool comp(Meta& a, Meta& b) {
  if (a.t < b.t) return true;
  else return false;
}

void FindRoads(int s, int d, int acc_t, int acc_q, vector<vector<pair<int, int> > >& neighbor,
			   vector<int>& Q, vector<bool>& flag, vector<Meta> *roads) {
  Meta temp;
  if (s == d) {
    temp.t = acc_t;
    temp.q = acc_q;
    roads->push_back(temp);
    return;
  }
  for (int i = 0; i < neighbor[s].size(); ++i) {
    if (flag[neighbor[s][i].first] == false) {
      flag[neighbor[s][i].first] = true;
      FindRoads(neighbor[s][i].first, d, acc_t+neighbor[s][i].second,
				acc_q+Q[neighbor[s][i].first], neighbor, Q, flag, roads);
      flag[neighbor[s][i].first] = false;
    }
  }
}

int main() {
  int N, M, S, D;
  cin >> N >> M >> S >> D;
  vector<int> Q(N);
  for (int i = 0; i < N; ++i) cin >> Q[i];
  vector<vector<pair<int, int> > > neighbor(N);
  while (M--) {
    int s, d, t;
    cin >> s >> d >> t;
    neighbor[s-1].push_back(make_pair(d-1, t));
    neighbor[d-1].push_back(make_pair(s-1, t));
  }
  vector<Meta> roads;
  vector<bool> flag(N, false);
  flag[S-1] = true;
  FindRoads(S-1, D-1, 0, Q[S-1], neighbor, Q, flag, &roads);
  sort(roads.begin(), roads.end(), comp);
  Meta first = roads[0];
  Meta res;
  res.q = -1;
  for (Meta v : roads) {
    if (v.t == first.t && v.q > res.q) {
      res.t = v.t;
      res.q = v.q;
    } else break;
  }
  cout << res.t << " " << res.q;

  return 0;
}
