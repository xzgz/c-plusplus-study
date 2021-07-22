/*
leetcode 349:
Given two arrays, write a function to compute their intersection.
Example:
Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2].
Note:
Each element in the result must be unique.
The result can be in any order.
思路：用个set把nums1都放进去，然后遍历nums2的元素，如果在set中存在，说明是交集的部分，
加入结果的set中，最后再把结果转为vector的形式即可
*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    set<int> s(nums1.begin(), nums1.end()), res;
    for (int i = 0; i < nums2.size(); ++i) {
      if (s.count(nums2[i])) res.insert(nums2[i]);
    }
    return vector<int>(res.begin(), res.end());
  }
};

int main() {
  vector<int> a = { 2, 5, 3, 34, 5, 8, 12, 9 };
  vector<int> b = { 7, 0, 6, 2, 5, 10, 12, 11 };
  Solution so;
  vector<int> inter_array = so.intersection(a, b);
  for (vector<int>::iterator it = inter_array.begin(); it != inter_array.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

