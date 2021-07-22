/*
leetcode 33. Search in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
You are given a target value to search. If found in the array return its index, otherwise return -1.
You may assume no duplicate exists in the array.
Your algorithm's runtime complexity must be in the order of O(log n).

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/

#include <vector>
#include <iostream>

using namespace std;

/*
解题思路：由于数组中不存在重复的元素，题目的复杂性就有所降低。为了保持思路的简洁，
我们只关注数组三个位置的值：*first, *mid, *last。
第一步：判断下列情况哪一种成立：(1) *first <= *mid；(2) *first > *mid。
第二步：if (1)，说明first和mid之间是单调递增的，可以判断target是否在first和mid之间，
若在，则令last=mid，若不在，则令first=mid+1，再从第一步重新开始；if (2)，
说明mid和last之间是单调递增的，可以判断target是否在mid和last之间，若在，
则令first=mid+1，若不在，则令last=mid，再从第一步重新开始。
重复执行第一、二步，直至*mid==target或first==last+1。
这道题求解思路的关键在找到单调递增区域，然后迭代，直至满足终止条件。
注意这里的终止条件，一开始的*first、*last分别对应着数组的首个值和末尾值。
为了让mid能够迭代到数组的末尾位置，即mid==last，根据求中点的表达式mid=first+(last-first)/2，
可以解出first==last。当target位于数组末尾位置时，为了能返回target的位置，
循环的终止条件应设为first==last+1。
*/
class Solution {
 public:
  int search(const vector<int>& nums, int target) {
    int first = 0, last = nums.size() - 1;
    while (first != last + 1) {
      const int mid = first + (last - first) / 2;
      if (nums[mid] == target) return mid;
      if (nums[first] <= nums[mid]) {
        if (nums[first] <= target && target < nums[mid]) last = mid;
        else first = mid + 1;
      } else {
        if (nums[mid] < target && target <= nums[last]) first = mid + 1;
        else last = mid;
      }
    }
    return -1;
  }
};

int main() {
  int a[] = { 6, 0, 1, 2, 5 };
  Solution solu;
  vector<int> vec_arr(a, a+5);
  int index = solu.search(vec_arr, -1);
  cout << "target index: " << index << endl;

  return 0;
}
