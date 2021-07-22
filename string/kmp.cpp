#include "common_function.h"
#include <iostream>
#include <vector>

using namespace std;

vector<int> GetNext(const string& t) {
    int t_len = t.size();
    if (t_len == 1) return { -1 };

    // next[0] == -1, next[1] == 0
    // for i>=2, next[i] == k (k>=1) means t(0)t(1)...t(k-1) == t(i-k)t(i-k+1)...t(i-1)
    vector<int> next(t_len, 0);
    next[0] = -1;
    next[1] = 0;
    int i = 2;
    int cn = 0;
    while (i < t_len) {
        if (t[i - 1] == t[cn]) {
            next[i++] = ++cn;
        } else if (cn > 0) {
            cn = next[cn];
        } else {
            next[i++] = 0;
        }
    }

    return next;
}

int KMP(const string& s, const string& t) {
    if (s.empty() || t.empty() || s.length() < t.length()) return -1;
    int x = 0;
    int y = 0;
    int s_len = s.size();
    int t_len = t.size();
    vector<int> next = GetNext(t);
    Print1DVector<int>(next);

    while (x < s_len && y < t_len) {
        if (s[x] == t[y]) {
            ++x;
            ++y;
        } else if (next[y] == -1) {
            ++x;
        } else {
            y = next[y];
        }
    }

    return y == t_len ? x - y : -1;
}

int main() {
    string s = "abcdabcabcda";
    string t;
    t = "abcabcd";
//    t = "abcdft";
//    t = "abcabcabcd";
    int loc = KMP(s, t);
    cout << loc << endl;

    return 0;
}
