/*
题目：将该栈从顶到底从大到小排序，只允许申请一个辅助栈，可以申请有限个变量，
除此之外不能再申请额外的数据结构
思路：设要排序的栈为st，辅助栈为help，从st弹出的元素记为cur，help的栈顶元素记为top。
      1)如果cur小于或等于top，则将cur压入help；
      2)如果cur大于top，则将help中的元素逐一弹出并压入st，直到cur小于等于top，再将cur压入help。
      3)一直执行上述操作，直到st为空结束，这时再把help中的元素一一压回st就行了，算法结束。
*/

#include "common_function.h"
#include <stack>
#include <iostream>

using namespace std;

template <typename T>
void SortStackByHelpStack(stack<T>& st) {
  stack<T> help;
  while (!st.empty()) {
    T cur = st.top();
    st.pop();
    for (; !help.empty() && cur > help.top(); st.push(help.top()), help.pop());
    help.push(cur);
  }
  for (; !help.empty(); st.push(help.top()), help.pop());
}

int main() {
  stack<int> st({ 1, 2, -1, 7, 9, 0 });

  SortStackByHelpStack(st);

  for (; !st.empty(); cout << st.top() << endl, st.pop());

  return 0;
}
