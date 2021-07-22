/*
leetcode 4:
There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log(m+n)).
You may assume nums1 and nums2 cannot be both empty.

Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0

Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5
*/

#include <vector>
#include <iostream>

using namespace std;

/*
解题思路：现在考虑一个更通用的问题：给定两个已经排序好的数组，找到两者所有元素中第k大的元素。
假设两个数组A和B的元素个数都大于k/2，我们将A的第k/2个元素A[k/2-1]和B的第k/2个元素B[k/2-1]进行比较，
有以下三种情况：
1. A[k/2-1] == B[k/2-1]
2. A[k/2-1] > B[k/2-1]
3. A[k/2-1] < B[k/2-1]
如果是A[k/2-1] < B[k/2-1]则说明A[0]到A[k/2-1]肯定在AUB的top k元素的范围内，
反之则B[0]到B[k/2-1]肯定在AUB的top k元素的范围内。如果A[k/2-1] == B[k/2-1]，
说明第k大的元素为A[k/2-1]或B[k/2-1](这里假设排序好的数组是从小到大排列的，
并且假设k是偶数。所的结论对k是奇数也是成立的)。
*/
class Solution
{
 public:
  double findMedianSortedArrays(const vector<int>& A, const vector<int>& B) {
      const int m = A.size();
      const int n = B.size();
      int total = m + n;
      if (total & 1)
          return find_kth(A.begin(), m, B.begin(), n, total / 2 + 1);
      else
          return (find_kth(A.begin(), m, B.begin(), n, total / 2)
                  + find_kth(A.begin(), m, B.begin(), n, total / 2 + 1)) / 2.0;
  }

  int find_kth(std::vector<int>::const_iterator A, int m,
               std::vector<int>::const_iterator B, int n, int k)
  {
      //always assume that m is equal or smaller than n
      if (m > n) return find_kth(B, n, A, m, k);
      if (m == 0) return *(B + k - 1);
      if (k == 1) return min(*A, *B);

      //divide k into two parts
      int ia = min(k / 2, m), ib = k - ia;
      if (*(A + ia - 1) < *(B + ib - 1))
          return find_kth(A + ia, m - ia, B, n, k - ia);
      else if (*(A + ia - 1) > *(B + ib - 1))
          return find_kth(A, m, B + ib, n - ib, k - ib);
      else
          return A[ia - 1];
  }
};


int main()
{
    int a1[] = {1, 2};
    int a2[] = {3, 4};
    vector<int> nums1(a1, a1+2);
    vector<int> nums2(a2, a2+2);
    Solution solu;
    double median = solu.findMedianSortedArrays(nums1, nums2);
    cout << "median: " << median << endl;

    return 0;
}


//static const auto speedup = []() {std::ios::sync_with_stdio(false); std::cin.tie(NULL); return 0;}();
//class Solution2
//
//{
// public:
//  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
//  {
//      size_t size1 = nums1.size();
//      size_t size2 = nums2.size();
//
//      size_t sumSizes = (size1 + size2);
//
//      if (sumSizes % 2 == 0)
//      {
//          size_t middle = sumSizes / 2;
//          size_t curr1 = 0;
//          size_t curr2 = 0;
//          bool lastWas1 = false;
//
//          while (curr1 + curr2 < middle)
//          {
//              if (curr1 < size1 && (curr2 >= size2 || nums1[curr1] < nums2[curr2]))
//              {
//                  ++curr1;
//                  lastWas1 = true;
//              }
//              else
//              {
//                  ++curr2;
//                  lastWas1 = false;
//              }
//          }
//
//          if (curr1 >= size1)
//          {
//              if (curr2 == 0 || lastWas1)
//              {
//                  return (nums1[curr1 - 1] + nums2[curr2]) / 2.0;
//              }
//              else
//              {
//                  return (nums2[curr2] + nums2[curr2 - 1]) / 2.0;
//              }
//          }
//          else if (curr2 >= size2)
//          {
//              if (curr1 == 0 || !lastWas1)
//              {
//                  return (nums2[curr2 - 1] + nums1[curr1]) / 2.0;
//              }
//              else
//              {
//                  return (nums1[curr1] + nums1[curr1 - 1]) / 2.0;
//              }
//          }
//          else
//          {
//              if (nums1[curr1] < nums2[curr2])
//              {
//                  if (!lastWas1)
//                  {
//                      return (nums1[curr1] + nums2[curr2 - 1]) / 2.0;
//                  }
//                  else
//                  {
//                      return (nums1[curr1] + nums1[curr1 - 1]) / 2.0;
//                  }
//              }
//              else
//              {
//                  if (lastWas1)
//                  {
//                      return (nums1[curr1 - 1] + nums2[curr2]) / 2.0;
//                  }
//                  else
//                  {
//                      return (nums2[curr2] + nums2[curr2 - 1]) / 2.0;
//                  }
//              }
//
//              //return nums1[curr1] > nums2[curr2] ? nums2[curr2] : nums1[curr1];
//          }
//      }
//      else
//      {
//          size_t middle = sumSizes / 2;
//          size_t curr1 = 0;
//          size_t curr2 = 0;
//
//          while (curr1 + curr2 < middle)
//          {
//              if (curr1 < size1 && (curr2 >= size2 || nums1[curr1] < nums2[curr2]))
//              {
//                  ++curr1;
//              }
//              else
//              {
//                  ++curr2;
//              }
//          }
//
//          if (curr1 >= size1)
//          {
//              return nums2[curr2];
//          }
//          else if (curr2 >= size2)
//          {
//              return nums1[curr1];
//          }
//          else
//          {
//              return nums1[curr1] > nums2[curr2] ? nums2[curr2] : nums1[curr1];
//          }
//      }
//  }
//};

