/*
leetcode 128:
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
Your algorithm should run in O(n) complexity.

Example:
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
*/

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

/*
解题思路：首先构造一个关联容器unordered_map<int, bool> used;用来记录每个元素是否使用。对数组中的每个元素，
以该元素为中心，通过+1和-1往右和往左筛查关联容器是否包含改元素的相邻元素，直到不连续为止，记录下最长的长度。
*/
class Solution
{
 public:
  int longestConsecutive(const vector<int> &nums)
  {
    unordered_map<int, bool> used;
    for (auto i : nums) used[i] = false;

    int longest = 0;
    for (auto i : nums)
    {
      if (used[i]) continue;
      int length = 1;
      used[i] = true;
      for (int j = i + 1; used.find(j) != used.end(); ++j)
      {
        used[j] = true;
        ++length;
      }
      for (int j = i - 1; used.find(j) != used.end(); --j)
      {
        used[j] = true;
        ++length;
      }
      longest = max(longest, length);
    }
    return longest;
  }
};


int main()
{
    int a[] = {300, 4, 200, 9, 3, 2, 8, 7, 6, 5};
    Solution solu;
    vector<int> vec_arr(a, a+10);
    cout << *(a+9) << endl;
    int res_vec_len = solu.longestConsecutive(vec_arr);
    cout << "original length: " << vec_arr.size() << endl
         << "processed length: " << res_vec_len << endl;

    return 0;
}


//class Solution3 {
// public:
//  int longestConsecutive(vector<int> &nums) {
//    unordered_map<int, int> map;
//    int size = nums.size();
//    int l = 1;
//    for (int i = 0; i < size; i++) {
//      if (map.find(nums[i]) != map.end()) continue;
//      map[nums[i]] = 1;
//      if (map.find(nums[i] - 1) != map.end()) {
//        l = max(l, mergeCluster(map, nums[i] - 1, nums[i]));
//      }
//      if (map.find(nums[i] + 1) != map.end()) {
//        l = max(l, mergeCluster(map, nums[i], nums[i] + 1));
//      }
//    }
//    return size == 0 ? 0 : l;
//  }
// private:
//  int mergeCluster(unordered_map<int, int> &map, int left, int right) {
//    int upper = right + map[right] - 1;
//    int lower = left - map[left] + 1;
//    int length = upper - lower + 1;
//    map[upper] = length;
//    map[lower] = length;
//    return length;
//  }
//};


//class Solution1 {
// public:
//  int longestConsecutive(const vector<int> &nums) {
//    unordered_set<int> my_set;
//    for (auto i : nums) my_set.insert(i);
////        cout << "before erase, the set is:" << endl;
////        for (auto it = my_set.begin(); it != my_set.end(); ++it)
////        {
////            cout << *it << endl;
////        }
//
//    int longest = 0;
//    for (auto i : nums) {
//      int length = 1;
//      for (int j = i - 1; my_set.find(j) != my_set.end(); --j) {
//        my_set.erase(j);
//        ++length;
//      }
//      for (int j = i + 1; my_set.find(j) != my_set.end(); ++j) {
//        my_set.erase(j);
//        ++length;
//      }
//      longest = max(longest, length);
//    }
//    return longest;
////        return my_set;
//  }
//};