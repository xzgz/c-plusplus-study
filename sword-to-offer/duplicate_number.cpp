#include <bits/stdc++.h>

using namespace std;

/*
题目描述：
在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，
但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重
复的数字。例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一
个重复的数字2。
 */
class Solution {
 public:
  // Parameters:
  //        numbers:     an array of integers
  //        length:      the length of array numbers
  //        duplication: (Output) the duplicated number in the array number
  // Return value:       true if the input is valid, and there are some duplications in the array number
  //                     otherwise false
  bool duplicate(int numbers[], int length, int* duplication) {
	for (int i = 0; i < length; ++i) {
	  while (numbers[i] != i) {
		if (numbers[i] == numbers[numbers[i]]) {
		  *duplication = numbers[i];
		  return true;
		} else {
		  int temp = numbers[numbers[i]];
		  numbers[numbers[i]] = numbers[i];
		  numbers[i] = temp;
		}
	  }
	}

	return false;
  }
};

int main() {
  int nums[] = { 2, 1, 3, 3, 4 };
  int lenth = 5;
  int dup;
  Solution so;
  bool f = so.duplicate(nums, lenth, &dup);
  cout << f << dup;

  return 0;
}
