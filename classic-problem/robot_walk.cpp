#include <vector>
#include <iostream>

using namespace std;

/*
 * �������ų�һ�е�N��λ�ã���Ϊ1~N��Nһ�����ڻ����2����ʼʱ�����������е�Mλ����(Mһ����1~N�е�һ��)�����
 * ����������1λ�ã���ô��һ��ֻ����������2λ�ã��������������Nλ�ã���ô��һ��ֻ����������N-1λ�ã��������
 * �������м�λ�ã���ô��һ�����������߻��������ߡ��涨�����˱�����K��������������Pλ��(PҲ��1~N�е�һ��)�ķ�
 * ���ж����֣������ĸ�����N��M��K��P�����ط�������
 */

int Walk(int N, int cur, int rest, int P) {
    if (rest == 0) return cur == P ? 1 : 0;
    if (cur == 1) return Walk(N, cur + 1, rest - 1, P);
    if (cur == N) return Walk(N, cur - 1, rest - 1, P);
    return Walk(N, cur + 1, rest - 1, P) + Walk(N, cur - 1, rest - 1, P);
}

int Ways1(int N, int M, int K, int P) {
    if (N < 2 || K < 1 || M < 1 || M > N || P < 1 || P > N) {
        return 0;
    }
    return Walk(N, M, K, P);
}

int WalkDp(int N, int cur, int rest, int P, vector<vector<int> > dp) {
    if (dp[cur][rest] != -1) return dp[cur][rest];
    if (rest == 0) {
        dp[cur][rest] = cur == P ? 1 : 0;
        return dp[cur][rest];
    }
    if (cur == 1) {
        dp[cur][rest] = Walk(N, cur + 1, rest - 1, P);
        return dp[cur][rest];
    }
    if (cur == N) {
        dp[cur][rest] = Walk(N, cur - 1, rest - 1, P);
        return dp[cur][rest];
    }
    dp[cur][rest] = Walk(N, cur + 1, rest - 1, P) + Walk(N, cur - 1, rest - 1, P);
    return dp[cur][rest];
}

int WaysDp(int N, int M, int K, int P) {
    if (N < 2 || K < 1 || M < 1 || M > N || P < 1 || P > N) {
        return 0;
    }
    vector<vector<int> > dp(N + 1, vector<int>(K + 1, -1));
    return WalkDp(N, M, K, P, dp);
}

int main() {
    int N, M, K, P;
    N = 7;
    M = 4;
    K = 4;
    P = 2;
    int way_count;
    way_count = Ways1(N, M, K, P);
    cout << "from " << M << " to " << P << " with " << K << " steps, the way_count: " << way_count << endl;
    way_count = WaysDp(N, M, K, P);
    cout << "from " << M << " to " << P << " with " << K << " steps, the way_count: " << way_count << endl;

    return 0;
}
