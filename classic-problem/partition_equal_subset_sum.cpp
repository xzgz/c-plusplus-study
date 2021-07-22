#include <bits/stdc++.h>

using namespace std;

/*
leetcode 416:
Given a non-empty array containing only positive integers, find if the array can be partitioned into
two subsets such that the sum of elements in both subsets is equal.
Note:
Each of the array element will not exceed 100.
The array size will not exceed 200.

Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
*/

/*
思路：可以看作背包问题。背包的总容量为数组中所有数总和的一半，从数组中选数，将背包恰好装满。
detail: https://juejin.im/post/5b40c99ee51d45190b615f33#heading-0
*/
class Solution1 {
 private:
  vector<vector<int> > memo;
  bool TryPartition(const vector<int>& nums, int index, int sum) {
    if (sum == 0) return true;
    if (sum < 0 || index < 0) return false;
    if (memo[index][sum] != -1) return memo[index][sum] == 1;

    memo[index][sum] = (TryPartition(nums, index - 1, sum) ||
                        TryPartition(nums, index - 1, sum - nums[index])) ? 1 : 0;

    return memo[index][sum] == 1;
  }

 public:
  bool CanPartition(vector<int>& nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      assert(nums[i]);
      sum += nums[i];
    }
    if (sum % 2) return false;
    memo = vector<vector<int> >(nums.size(), vector<int>(sum / 2 + 1, -1));
    return TryPartition(nums, nums.size() - 1, sum / 2);
  }
};

class Solution2 {
 public:
  bool CanPartition(vector<int>& nums) {
    int sum = 0;
    for (int i = 0; i < nums.size(); ++i) {
      assert(nums[i]);
      sum += nums[i];
    }
    if (sum % 2) return false;

    int n = nums.size();
    int c = sum / 2;
    vector<int> memo(c + 1, false);
    for (int i = 0; i <= c; ++i) memo[i] = nums[0] == i;
    for (int i = 0; i < n; ++i)
      for (int j = c; j >= nums[i]; --j) {
        memo[j] = memo[j] || memo[j - nums[i]];
        if (memo[j] && j == c) return true;
      }

    return false;
  }
};

int main() {
  vector<int> nums1 = { 1, 5, 11, 5 };
  vector<int> nums2 = { 1, 2, 3, 5 };
//  Solution1 so;
  Solution2 so;

  bool can_be_partitioned = false;
  can_be_partitioned = so.CanPartition(nums1);
  if (can_be_partitioned) cout << "nums1 can be partioned\n";
  else cout << "nums1 can not be partioned\n";
  can_be_partitioned = false;
  can_be_partitioned = so.CanPartition(nums2);
  if (can_be_partitioned) cout << "nums2 can be partioned\n";
  else cout << "nums2 can not be partioned\n";
}
