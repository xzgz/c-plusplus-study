/*
leetcode 81. Search in Rotated Sorted Array II
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
(i.e., [0,0,1,2,2,5,6] might become [2,5,6,0,0,1,2]).
You are given a target value to search. If found in the array return true, otherwise return false.

Example 1:
Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true
Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false
Follow up:
This is a follow up problem to Search in Rotated Sorted Array, where nums may contain duplicates.
Would this affect the run-time complexity? How and why?
*/

#include <vector>
#include <iostream>

using namespace std;

/*
解题思路：这题与Search in Rotated Sorted Array之间的区别在于数组中可能会有重复的元素。解题思路与前者一样，
关键仍然是找到单调递增区域。在前者的代码中，nums[first] <= nums[mid]这句就不适用了，应将”=“去掉。
因为数组的旋转点可能会位于重复的元素中间，这样当”=“条件成立时，first与mid之间并不一定是单调递增的，
有可能是重复的元素被截断所致，因此只需要first++跳过重复的元素重新从第一步开始即可。但”<“条件成立时，一定是单调递增的。
*/
class Solution {
 public:
  int search(const vector<int>& nums, int target) {
    int first = 0, last = nums.size();
    while (first != last + 1) {
      int mid = (first + last) / 2;
      if (nums[mid] == target) return mid;
      if (nums[first] < nums[mid]) {
        if (nums[first] <= target && target < nums[mid]) last = mid;
        else first = mid + 1;
      } else if (nums[first] > nums[mid]) {
        if (nums[mid] < target && target <= nums[last]) first = mid + 1;
        else last = mid;
      } else first++;
    }
    return -1;
  }
};

int main() {
//  int a[] = { 2, 2, 5, 6, 0, 1, 2 };
  int a[] = { 6, 0, 1, 2, 5 };
  Solution solu;
//  vector<int> vec_arr(a, a+7);
  vector<int> vec_arr(a, a+5);
  int index = solu.search(vec_arr, 6);
  cout << "target index: " << index << endl;

  return 0;
}
