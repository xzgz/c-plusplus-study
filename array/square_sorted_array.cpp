/*
leetcode 977. Squares of a Sorted Array
Given an array of integers A sorted in non-decreasing order, return an array of
the squares of each number, also in sorted non-decreasing order.

Example 1:
Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Example 2:
Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]

Note:
1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A is sorted in non-decreasing order.
*/

#include <vector>
#include <iostream>

using namespace std;

/*
思路：将数组中每个元素平方之后，最大的值肯定在数组的两侧，因此从数组两侧向中间查找即可。
具体做法为：设置两个指示器，分别指向数组的首尾两端。比较两端数值绝对值的大小，大的优先
平方放入结果数组中，同时相应的指示器向中间移动一个位置，直到两个指示器相遇，得到绝对值最小的元素。
*/
class Solution {
 public:
  vector<int> SortedSquares(vector<int>& A) {
    vector<int> answer(A.size(), 0);
    int l = 0, r = A.size() - 1;
    int left, right;

    while(l <= r) {
      left = abs(A[l]);
      right = abs(A[r]);
      if(left < right) {
        answer[r-l] = right * right;
        r -= 1;
      } else {
        answer[r-l] = left * left;
        l += 1;
      }
    }

    return answer;
  }
};

int main() {
  int a[] = {-4, -1, 0, 3, 10};
  Solution solu;
  vector<int> vec_arr(a, a+4);
  vector<int> ret = solu.SortedSquares(vec_arr);
  for(int i = 0; i < ret.size(); ++i) {
    cout << ret[i] << " ";
  }

  return 0;
}
