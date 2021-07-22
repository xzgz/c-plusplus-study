#include "common_function.h"
#include <stack>
#include <iostream>

using namespace std;

/*
 * 给你一个栈，请你逆序这个栈。不能申请额外的数据结构，只能使用递归函数。
 */
int f(stack<int>& s) {
    int result = s.top(); s.pop();
    if (s.empty()) {
        return result;
    } else {
        int last = f(s);
        s.push(result);
        return last;
    }
}

void Reverse(stack<int>& s) {
    if (s.empty()) {
        return;
    }
    int i = f(s);
    Reverse(s);
    s.push(i);
}

stack<int> Reverse2(stack<int>& s) {
    stack<int> res;
    while (!s.empty()) {
        res.push(s.top()), s.pop();
    }
    return move(res);
}

int main() {
    cout << "before reverse:\n";
    stack<int> s1({ 1, 2, -1, 7, 9, 0 });
    stack<int> s2({ 1, 2, -1, 7, 9, 0 });
    for (; !s1.empty(); cout << s1.top() << endl, s1.pop());
    Reverse(s2);
//    s2 = Reverse2(s2);
    cout << "after reverse:\n";
    for (; !s2.empty(); cout << s2.top() << endl, s2.pop());
}
