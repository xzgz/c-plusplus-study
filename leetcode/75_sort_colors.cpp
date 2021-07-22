#include <vector>
#include <iostream>

using namespace std;

/*
75. 颜色分类
难度：中等
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

注意：请不要使用代码库中的排序函数来解决这道题。

进阶：
你能想出一个仅使用常数空间的一趟扫描算法吗？

示例 1：

输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]
示例 2：

输入：nums = [2,0,1]
输出：[0,1,2]
示例 3：

输入：nums = [0]
输出：[0]
示例 4：

输入：nums = [1]
输出：[1]

提示：
n == nums.length
1 <= n <= 300
nums[i] 为 0、1 或 2

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

题解：refer to: https://www.cnblogs.com/jimmycheng/p/7231963.html
*/

void sortColors(vector<int>& nums) {
  int red = 0;
  int blue = nums.size() - 1;
  for (int i = 0; i <= blue; ++i) {
    int temp;
    if (nums[i] == 0) {
	  temp = nums[red];
	  nums[red] = nums[i];
	  nums[i] = temp;
	  ++red;
	} else if (nums[i] == 2) {
      temp = nums[blue];
      nums[blue] = nums[i];
      nums[i] = temp;
      --i;
      --blue;
    }
  }
}

int main() {
  vector<int> nums = { 2, 0, 2, 1, 1, 0 };
//  vector<int> nums = { 2, 0, 1 };
  sortColors(nums);
  for (int n : nums) cout << n << " ";

  return 0;
}
