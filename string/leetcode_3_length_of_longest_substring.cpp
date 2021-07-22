#include <iostream>

using namespace std;

int lengthOfLongestSubstring(string s) {
    int last[128];
    for (int i = 0; i < 128; ++i) {
        last[i] = -1;
    }

    int n = s.length();
    int max_len = 0;
    int start = 0;
    for (int i = 0; i < n; ++i) {
        start = max(start, last[s[i]] + 1);
        int len = i - start + 1;
        max_len = max(max_len, len);
        last[s[i]] = i;
    }

    return max_len;
}

int main() {
    string s = "abcabcbb";
    int max_len = lengthOfLongestSubstring(s);
    cout << "the max_len is " << max_len << endl;

    return 0;
}
