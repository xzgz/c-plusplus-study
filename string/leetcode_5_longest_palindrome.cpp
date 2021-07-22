#include <iostream>
#include <vector>

using namespace std;

string LongestPalindrome(string& s) {
    int n = s.length();
    if (n <= 0) return s;

    int max_length_begin = 0;
    // dp[j] 表示以位置 j 结尾的最长回文子串的起始位置
    // 其长度就是 j - dp[j] + 1
    int dp[n];
    dp[0] = 0;

    // 记录最大回文子串的长度
    // 0 - 0 + 1
    int max_length = 1;

    for (int j = 1; j < n; j++) {
        if (dp[j - 1] > 0 && s[j] == s[dp[j - 1] - 1]) {
            // 当前位置的字符和上一次回文串的左邻字符相同
            // 回文串得到扩展
            dp[j] = dp[j - 1] - 1;
        } else {
            // 从左向右找
            int left = dp[j - 1];
            int right = j;
            int start = left;  // 最近一次的回文查找起始位置

            while (left < right) {
                if (s[left] != s[right]) {
                    // 遭遇失配字符，重置 right
                    right = j;
                    start = left + 1;
                } else {
                    // 否则，两边继续收拢
                    right--;
                }
                left++;
            }

            dp[j] = start;
        }

        // 更新最大值
        int length = j - dp[j] + 1;
        if (length > max_length) {
            max_length = length;
            max_length_begin = dp[j];
        }
    }

    return s.substr(max_length_begin, max_length);
}

class Solution {
public:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return (right - left - 2) / 2;
    }

    string longestPalindrome(string s) {
        int start = 0, end = -1;
        string t = "#";
        for (char c: s) {
            t += c;
            t += '#';
        }
        s = t;
        cout << s << endl;

        vector<int> arm_len;
        int right = -1, j = -1;
        for (int i = 0; i < s.size(); ++i) {
            int cur_arm_len;
            if (right >= i) {
                int i_sym = j * 2 - i;
                int min_arm_len = min(arm_len[i_sym], right - i);
                cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
            } else {
                cur_arm_len = expand(s, i, i);
            }
            arm_len.push_back(cur_arm_len);
            if (i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
            if (cur_arm_len * 2 + 1 > end - start) {
                start = i - cur_arm_len;
                end = i + cur_arm_len;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) {
            if (s[i] != '#') {
                ans += s[i];
            }
        }
        return ans;
    }
};

int main() {
    string s = "babbahaddabak";
    string longest_palindrome = LongestPalindrome(s);
    cout << "the longest palindrome of string " << s << " is " << longest_palindrome << endl;

    Solution so;
    s = "babad";
    longest_palindrome = so.longestPalindrome(s);
    cout << "the longest palindrome of string " << s << " is " << longest_palindrome << endl;

    return 0;
}
