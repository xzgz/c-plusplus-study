#include "common_function.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

/*
 * 计算一个非负整数N的阶乘。
 */
unsigned long long int Factorial(int N) {
    if (N < 0) return 0;

    unsigned long long int result = 1;
    for (int i = 2; i <= N; ++i) {
        result *= i;
    }
    return result;
}

/*
 * 计算 0! + 1! + 2! + 3! + ... + N!。
 */
unsigned long long int AccumulateFactorial1(int N) {
    if (N < 0) return 0;

    unsigned long long int result = 0;
    for (int i = 0; i <= N; ++i) {
        result += Factorial(i);
    }
    return result;
}

unsigned long long int AccumulateFactorial2(int N) {
    if (N < 0) return 0;

    unsigned long long int result = 1;
    unsigned long long int temp = 1;
    for (int i = 1; i <= N; ++i) {
        temp *= i;
        result += temp;
    }
    return result;
}

int main() {
    int N = 21;
    std::random_device rd;
    unsigned int seed = rd();
    cout << "seed: " << seed << endl;

    vector<int> arr = GenerateRandom1DIntegerArray<int>(seed, 0, 21, 20);
    unsigned long long result = 0;

    for (int val : arr) {
        result = Factorial(val);
        cout << "N: " << val << "\tN!: " << result << endl;
    }

    int length = 100000;
    arr = GenerateRandom1DIntegerArray<int>(seed, 0, 21, length);
    vector<unsigned long long> res1(length);
    vector<unsigned long long> res2(length);

    {
        cout << "AccumulateFactorial1 ";
        TimerClock tc(true);
        for (int i = 0; i < arr.size(); ++i) {
            result = AccumulateFactorial1(arr[i]);
            res1[i] = result;
        }
    }
    {
        cout << "AccumulateFactorial1 used ";
        TimerClock tc(true);
        for (int i = 0; i < arr.size(); ++i) {
            result = AccumulateFactorial2(arr[i]);
            res2[i] = result;
        }
    }

    if (res1 == res2) {
        cout << "res1 == res2" << endl;
    }
    PrintNowTime();
}
