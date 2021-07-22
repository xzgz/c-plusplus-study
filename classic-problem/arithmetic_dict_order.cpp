#include <bits/stdc++.h>

using namespace std;

/*
 * 题目描述：
 * 一个算术表达式，只由加、减、乘、除四种运算符和整数构成，没有括号。
 * 现在可以无限次地交换相邻的2个数字，使表达式的值不变。请求出字典序
 * 最小的一个表达式并打印出来。
 * 输入描述：
 * 第一行是一个数字t，表示测试组数，接下来是2t行输入。每组第一行是数
 * 字n，表示算术表达式中数字的个数，运算符的个数为n-1，运算符和数字
 * 之间用一个空格隔开。1<=n<=1000，数字的绝对值小于等于1000，第二行
 * 是这个算术表达式。
 *
 * 示例输入：
9
8
3 + 2 + 1 + -4 * -5 + 6 + 1 + 2
8
3 / 2 + 1 + -4 * -5 + 6 + 1 + 2
8
3 - 2 + 1 + -4 * -5 + 6 + 1 + 2
8
3 + 2 / 1 + -4 * -5 + 6 + 1 + 2
8
3 + 2 - 1 + -4 * -5 + 6 + 1 + 2
8
3 + 2 - 1 - -4 * -5 + 6 + 1 + 2
8
3 + 2 - 1 - -4 - -5 * 6 + 1 + 2
8
3 + 2 - 1 - -4 + -5 * 6 + 1 + 2
11
3 * 2 - 7 - 1 - -4 + 8 / 2 / 1 * 4 - 2 - 1

 * 示例输出：
1 + 2 + 3 + -5 * -4 + 1 + 2 + 6

3 / 2 + 1 + -5 * -4 + 1 + 2 + 6

3 - 2 + 1 + -5 * -4 + 1 + 2 + 6

2 + 3 / 1 + -5 * -4 + 1 + 2 + 6

2 + 3 - 1 + -5 * -4 + 1 + 2 + 6

2 + 3 - 1 - -5 * -4 + 1 + 2 + 6

2 + 3 - -4 - 1 - -5 * 6 + 1 + 2

2 + 3 - -4 - 1 + -5 * 6 + 1 + 2

2 * 3 - -4 - 1 - 7 + 8 / 1 / 2 * 4 - 1 - 2

 */

struct NumSym {
  int val;
  bool is_num;
};

bool HaveHigherPriority(int op1, int op2) {
  bool higher = false;
  switch (op1) {
  case '+': case '-':
	higher = op2 == '*' || op2 == '/' ? true : false;
	break;
  }
  return higher;
}

int EvalExpression(const vector<int>& nums, const vector<char>& symbol) {
  int num_cnt = nums.size();
  stack<NumSym> num_op;
  stack<NumSym> op;
  NumSym temp;
  for (int i = 0; i < num_cnt-1; ++i) {
    temp.val = nums[i];
    temp.is_num = true;
	num_op.push(temp);
	temp.val = symbol[i];
	temp.is_num = false;
    if (op.empty()) {
      op.push(temp);
    } else if (HaveHigherPriority(op.top().val, symbol[i])) {
      op.push(temp);
    } else {
      while (true) {
        num_op.push(op.top());
        op.pop();
        if (op.empty()) { op.push(temp); break; }
        else if (HaveHigherPriority(op.top().val, symbol[i])) { op.push(temp); break; }
      }
    }
  }
  temp.val = nums[num_cnt-1];
  temp.is_num = true;
  num_op.push(temp);
  while (!op.empty()) { num_op.push(op.top()); op.pop(); }

  stack<NumSym> num_op_reverse;
  while (!num_op.empty()) {
    temp = num_op.top();
    num_op.pop();
    num_op_reverse.push(temp);
  }

  stack<int> numbers;
  while (!num_op_reverse.empty()) {
    temp = num_op_reverse.top();
    num_op_reverse.pop();
    if (temp.is_num) numbers.push(temp.val);
    else {
      int a = numbers.top();
      numbers.pop();
      int b = numbers.top();
      numbers.pop();
      int res;
      switch (temp.val) {
        case '+':
          res = b + a;
          break;
        case '-':
          res = b - a;
          break;
        case '*':
          res = b * a;
          break;
        case '/':
          res = b / a;
          break;
      }
      numbers.push(res);
    }
  }

  return numbers.top();
}

int main() {
  string line;
  getline(cin, line);
  int t = stoi(line);
  while (t--) {
    getline(cin, line);
    int n = stoi(line);
    vector<int> nums(n);
    vector<char> symbol(n-1);
    getline(cin, line);
    string::iterator loc;
    long order;
    for (int i = 0; i < 2*(n-1); ++i) {
      if (i % 2) {
        loc = find(line.begin(), line.end(), ' ');
        order = distance(line.begin(), loc);
        symbol[i / 2] = *(loc - 1);
        line.erase(0, 1 + order);
      } else {
        loc = find(line.begin(), line.end(), ' ');
        order = distance(line.begin(), loc);
        nums[i / 2] = stoi(line.substr(0, order));
        line.erase(0, 1 + order);
      }
    }
    nums[n-1] = stoi(line);

    for (int i = 0; i < n-1; ++i) {
      for (int j = i; j >=0; --j) {
        if (nums[j+1] < nums[j]) {
          int prev_val = EvalExpression(nums, symbol);
          swap(nums[j+1], nums[j]);
          int post_val = EvalExpression(nums, symbol);
          if (prev_val != post_val) swap(nums[j+1], nums[j]);
        }
      }
    }
    cout << endl;
    for (int i = 0; i < n-1; ++i) {
      cout << nums[i] << ' ' << symbol[i] << ' ';
    }
    cout << nums[n-1] << endl;
  }

  return 0;
}
