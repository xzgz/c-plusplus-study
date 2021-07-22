/*
leetcode 350:
Given two arrays, write a function to compute their intersection.
Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Note:
Each element in the result should appear as many times as it shows in both arrays.
The result can be in any order.
思路：先给两个数组排序，然后用两个指针分别指向两个数组的起始位置，如果两个指针指的数字相等，
则存入结果中，两个指针均自增1，如果第一个指针指的数字大，则第二个指针自增1，反之亦然
*/

#include <bits/stdc++.h>

using namespace std;

class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    vector<int> res;
    int i = 0, j = 0;
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    while (i < nums1.size() && j < nums2.size()) {
      if (nums1[i] == nums2[j]) {
        res.push_back(nums1[i]);
        ++i; ++j;
      } else if (nums1[i] > nums2[j]) {
        ++j;
      } else {
        ++i;
      }
    }
    return res;
  }
};

class Solution2 {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int, int> m;
    vector<int> res;
    for (auto a : nums1) ++m[a];
    for (auto a : nums2) {
      if (m[a]-- > 0) res.push_back(a);
    }
    return res;
  }
};


int main() {
//  vector<int> a = { 2, 5, 3, 34, 5, 8, 12, 9 };
//  vector<int> b = { 7, 0, 6, 2, 5, 10, 12, 11 };
  vector<int> a = { 1, 2, 2, 1 };
  vector<int> b = { 2, 2 };
//  vector<int> a = { 4, 9, 5 };
//  vector<int> b = { 9, 4, 9, 8, 4 };
  Solution2 so;
  vector<int> inter_array = so.intersect(a, b);
  for (vector<int>::iterator it = inter_array.begin(); it != inter_array.end(); ++it) {
    cout << *it << " ";
  }
  cout << endl;

  unordered_map<int, int> test;
  test[4] = 5;
  cout << "test[4]: " << test[4] << "\ntest[5]: " << test[5] << "\ntest[0]: " << test[0]
       << "\ntest[4.1]: " << test[4.1] << "\ntest[4.5]: " << test[4.5] << "\ntest[4.9]: " << test[4.9]
       << "\ntest[3]: " << test[3] << "\ntest[3.9]: " << test[3.9] << endl;
}

