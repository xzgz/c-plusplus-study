#include <bits/stdc++.h>

using namespace std;

/*
题目：refer to: https://www.nowcoder.com/discuss/242989?type=all&order=time&pos=&page=1
代码：refer to: https://www.nowcoder.com/discuss/241487?type=post&order=time&pos=&page=1
产品经理小梅喜欢和他的男朋友小白一块玩扑克游戏。每一局，小梅抽取N张扑克牌，
自左向右依次排列在桌面上；小白也抽取M（8>=N>=M>=1）张扑克牌，自左向右依次
排列在桌面上。小梅需要进行N个回合，使用手中的扑克牌，组成一个新的扑克牌的
序列每个回合，小梅有d、l、r三种策略
选择d时，小梅将最左边的扑克牌丢弃
选择l时，小梅将最左边的扑克牌取出，放到新的扑克牌序列的最左边
选择r时，小梅将最左边的扑克牌取出，放到的扑克牌序列的最右边
N个回合完成，新的扑克牌序列与小白的扑克牌完全样（只考虑数字，不考虑花色），则小梅胜出
小梅向程序员小岛提了一个需求，希望了解获胜的全部方法。简化起见扑克牌仅包合1-9。
输入描述：
首先，输入数字S，作为局数（1<=10）每一局，分别输入两行字符串，分别代表小梅的
抽取的扑克牌（从左向右排列）和小白抽取到的扑克牌（从左向右排列）
输出描述：
对于每一局，在开始和结束，分别输出{和}输出获胜的方法，回合策略的结尾输出一个
空格。若存在多个获胜方法，请按字典序的升序输出。
示例输入：
3
123
3
123
321
45
67
实例输出：
{
d d l
d d r
}
{
l l l
r l l
}
{
}
 */
void DFS(vector<char>& res_one, vector<string>& res, string op_s,
		 const string& s, string& new_s, int N) {
  if (new_s == s && op_s.empty() && res_one.size() == N) {
    string ans;
    for (int i = 0; i < res_one.size(); ++i) ans += res_one[i];
    res.push_back(ans);
    return;
  }

  while (!op_s.empty()) {
    char tmp = op_s[0];
    op_s = op_s.substr(1);

    res_one.push_back('d');
    DFS(res_one, res, op_s, s, new_s, N);
    res_one.pop_back();

    res_one.push_back('l');
    new_s = tmp + new_s;
	DFS(res_one, res, op_s, s, new_s, N);
	new_s = new_s.substr(1);
	res_one.pop_back();

	res_one.push_back('r');
	new_s = new_s + tmp;
	DFS(res_one, res, op_s, s, new_s, N);
	new_s = new_s.substr(0, new_s.size()-1);
	res_one.pop_back();
  }

  return;
}

int main() {
  int T;
  cin >> T;
  string op_s;
  string s;
  string new_s;

  while (T--)
  {
	cin >> op_s;
	cin >> s;
	vector<char> res_one;
	vector<string> res;

	DFS(res_one, res, op_s, s, new_s, op_s.size());
	sort(res.begin(), res.end());

	cout << "{" << endl;
	for (int i = 0; i < res.size(); ++i) {
	  for (int j = 0; j < op_s.size(); ++j)
	    cout << res[i][j] << " ";
	  cout << "\n";
	}
	cout << "}" << endl;
  }

  return 0;
}
