#include <bits/stdc++.h>

using namespace std;

/*
4. 寻找两个正序数组的中位数
难度：困难

给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。

进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？

示例 1：
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2

示例 2：
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5

示例 3：
输入：nums1 = [0,0], nums2 = [0,0]
输出：0.00000

示例 4：
输入：nums1 = [], nums2 = [1]
输出：1.00000

示例 5：
输入：nums1 = [2], nums2 = []
输出：2.00000

提示：
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/median-of-two-sorted-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

题解：refer to: https://www.cnblogs.com/pursuiting/p/10479923.html
*/

double find_kth(std::vector<int>::const_iterator A, int m,
        std::vector<int>::const_iterator B, int n, int k) {
    double median;
    // always assume that m is equal or smaller than n
    if (m > n) {
        median = find_kth(B, n, A, m, k);
        return median;
    }
    if (m == 0) {
        median = *(B + k - 1);
        return median;
    }
    if (k == 1) {
        median = min(*A, *B);
        return median;
    }

    // divide k into two parts
    int ia = min(k / 2, m), ib = k - ia;
    if (*(A + ia - 1) < *(B + ib - 1)) {
        median = find_kth(A + ia, m - ia, B, n, k - ia);
        return median;
    }
    else if (*(A + ia - 1) > *(B + ib - 1)) {
        median = find_kth(A, m, B + ib, n - ib, k - ib);
        return median;
    }
    else {
        median = A[ia - 1];
        return median;
    }
}

double findMedianSortedArrays(const vector<int>& A, const vector<int>& B) {
    const int m = A.size();
    const int n = B.size();
    int total = m + n;
    double median;
    if (total & 1) {
        median = find_kth(A.begin(), m, B.begin(), n, total / 2 + 1);
        return median;
    } else {
        median = (find_kth(A.begin(), m, B.begin(), n, total / 2)
                + find_kth(A.begin(), m, B.begin(), n, total / 2 + 1)) / 2.0;
        return median;
    }
}

int main() {
//    vector<int> A = { 1, 3 };
//    vector<int> A = { 1, 2 };
//    vector<int> A = { 0, 0 };
//    vector<int> A = {};
    vector<int> A = { 2 };

//    vector<int> B = { 2 };
//    vector<int> B = { 3, 4 };
//    vector<int> B = { 0, 0 };
//    vector<int> B = { 1 };
    vector<int> B = {};

    double median;
    median = findMedianSortedArrays(A, B);
    cout << "median: " << median << endl;

    return 0;
}
