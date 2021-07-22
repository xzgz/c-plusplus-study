/*
leetcode 80. Remove Duplicates from Sorted Array II:
Given a sorted array nums, remove the duplicates in-place such that duplicates appeared
at most twice and return the new length.
Do not allocate extra space for another array, you must do this by modifying the input
array in-place with O(1) extra memory.

Example 1:
Given nums = [1,1,1,2,2,3],
Your function should return length = 5, with the first five elements of nums
being 1, 1, 2, 2 and 3 respectively.
It doesn't matter what you leave beyond the returned length.

Example 2:
Given nums = [0,0,1,1,1,1,2,3,3],
Your function should return length = 7, with the first seven elements of nums
being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.
It doesn't matter what values are set beyond the returned length.
*/

#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

/*
解题思路：此题与26. Remove Duplicates from Sorted Array相似，解决方法仍然是设置左右两个指示器pl和pr。
让pr从左往右移动，当*pr和*(pl-1)相同时，说明*(pl-1)和*pl相同(因为nums数组是一个有序数组)，
因此*pr已不能再加入修改后的数组中，将其跳过。当*pr和*(pl-1)不相同时，令pl+=1, *pl=*pr。
最后pl的大小即为修改后数组的长度。
*/
class Solution
{
 public:
  int removeDuplicates(vector<int>& nums)
  {
    if (nums.size() <= 2) return nums.size();

    int index = 2;
    for (int i = 2; i < nums.size(); ++i)
    {
      if (nums[i] != nums[index - 2])
        nums[index++] = nums[i];
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
        cout << vec_arr[i] << " ";
    }
    cout << endl;
    assert(res_vec_len != vec_arr.size());
    cout << res_vec_len << " " << vec_arr.size() << endl;

    return 0;
}

