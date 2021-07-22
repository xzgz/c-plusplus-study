#include "common_function.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

/*
 * ��Χ�ϳ��Ե�ģ��
 * ����һ����������array��������ֵ��ͬ��ֽ���ų�һ���ߣ����A�����B��������ÿ��ֽ�ƣ��涨���A���ã����B���ã�
 * ����ÿ�����ÿ��ֻ��������������ҵ�ֽ�ƣ����A�����B�������������뷵������ʤ�ߵķ�����
 */

int S(vector<int>& array, int L, int R);

int F(vector<int>& array, int L, int R) {
    if (L == R) return array[L];
    int max_score = max(array[L] + S(array, L + 1, R), array[R] + S(array, L, R - 1));
    return max_score;
}

int S(vector<int>& array, int L, int R) {
    if (L == R) return 0;
    int max_score = min(F(array, L + 1, R), F(array, L, R - 1));
    return max_score;
}

int Win(vector<int>& array) {
    if (array.empty()) return 0;
    int max_score = max(F(array, 0, array.size() - 1), S(array, 0, array.size() - 1));
    return max_score;
}

int WinDp(vector<int>& array) {
    if (array.empty()) return 0;
    int N = array.size();
    vector<vector<int> > f(N, vector<int>(N, 0));
    vector<vector<int> > s(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        f[i][i] = array[i];
    }
    for (int i = 1; i < N; ++i) {
        int L = 0;
        int R = i;
        while (L < N && R < N) {
            f[L][R] = max(array[L] + s[L + 1][R], array[R] + s[L][R - 1]);
            s[L][R] = min(f[L + 1][R], f[L][R - 1]);
            L++;
            R++;
        }
    }
    int max_score = max(f[0][N - 1], s[0][N - 1]);
    return max_score;
}

int main() {
    vector<int> array = GenerateRandom1DIntegerArray<int>(1, 100, 30);
    cout << "array:" << endl;
    Print1DVector(array);

    int score;
    {
        TimerClock tc(true);
        score = WinDp(array);
    }
    cout << "WinDp score: " << score << endl;

    {
        TimerClock tc(true);
        score = Win(array);
    }
    cout << "Win score: " << score << endl;

    return 0;
}
