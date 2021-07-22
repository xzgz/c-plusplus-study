/*
leetcode 26:
Given a sorted array nums, remove the duplicates in-place such that each element appear
only once and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input
array in-place with O(1) extra memory.

Example 1:
Given nums = [1,1,2],
Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,0,1,1,1,2,2,3,3,4],
Your function should return length = 5, with the first five elements of nums being modified to
0, 1, 2, 3, and 4 respectively.
It doesn't matter what values are set beyond the returned length.
*/

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

/*
思路：设置两个指示器，左侧指示器pl和右侧指示器pr。pr从左往右移动，当pr所指的数值与pl所指数值不相同时，
将pl右移一位，并将pr所指数值赋给pl。最后pl的大小即为修改后数组的长度。
*/
class Solution
{
 public:
  int removeDuplicates(vector<int>& nums)
  {
    if (nums.empty()) return 0;

    int index = 1;
    for (int i = 1; i < nums.size(); ++i)
    {
      if (nums[i] != nums[index - 1])
      {
        nums[index++] = nums[i];
//        nums[++index] = nums[i];    // logic error
      }
    }
    return index;
  }
};


int main()
{
    int a[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 4};
    Solution solu;
    vector<int> vec_arr(a, a+11);
    int res_vec_len = solu.removeDuplicates(vec_arr);
    for (int i = 0; i < res_vec_len; ++i)
    {
        cout << vec_arr[i] << endl;
    }
    assert(res_vec_len != vec_arr.size());
    cout << res_vec_len << " " << vec_arr.size() << endl;

    return 0;
}


//class Solution2 {
// public:
//  int removeDuplicates(vector<int>& nums) {
//    return distance(nums.begin(), unique(nums.begin(), nums.end()));
//  }
//};
//
//class Solution3 {
// public:
//  int removeDuplicates(vector<int>& nums) {
//    return distance(nums.begin(), removeDuplicates(nums.begin(), nums.end(), nums.begin()));
//  }
//
//  template<typename InIt, typename OutIt>
//  OutIt removeDuplicates(InIt first, InIt last, OutIt output) {
//    while (first != last) {
//      *output++ = *first;
//      first = upper_bound(first, last, *first);
//    }
//    return output;
//  }
//};