#include <iostream>
#include <vector>

using namespace std;

/*
 * 一个数组中有一个数出现了奇数次，其他数都出现了偶数次，找到并返回这个数。
 */
int OneNumberOddTime(const vector<int>& array) {
    int num = 0;
    for (int val : array) {
        num ^= val;
    }
    return num;
}

/*
 * 一个数组中有两个数出现了奇数次，其他数都出现了偶数次，找到并返回这两个数。
 */
vector<int> TwoNumberOddTime(const vector<int>& array) {
    int num = 0;
    for (int val : array) {
        num ^= val;
    }

    // num必然有一个bit位是1，提取它最右边的1
    int right_one = num & (~num + 1);
    int one = 0;
    for (int val : array) {
        if ((val & right_one) != 0) one ^= val;
    }
    int another = one ^ num;

    vector<int> result(2);
    result[0] = one;
    result[1] = another;
    return result;
}

int GetBit1Count(int number) {
    int count = 0;
    while (number != 0) {
        count++;
        int right_one = number & (~number + 1);
        number ^= right_one;
    }
    return count;
}

int main() {
    vector<int> arr1 = { -3, 3, 2, 3, -3, 4, 4 };
    vector<int> arr2 = { -3, 3, 2, 3, -3, 4, 4, 4 };
    int odd = OneNumberOddTime(arr1);
    vector<int> res = TwoNumberOddTime(arr2);
    cout << "odd: " << odd << endl;
    cout << "one: " << res[0] << " another: " << res[1] << endl;

    int number = 6;
    int count = GetBit1Count(number);
    cout << "number: " << number << "\tbit 1 count: " << count << endl;
}
