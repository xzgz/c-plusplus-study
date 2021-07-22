#include <vector>
#include <iostream>

using namespace std;

/*
 * 假设有排成一行的N个位置，记为1~N，N一定大于或等于2。开始时机器人在其中的M位置上(M一定是1~N中的一个)，如果
 * 机器人来到1位置，那么下一步只能往右来到2位置；如果机器人来到N位置，那么下一步只能往左来到N-1位置；如果机器
 * 人来到中间位置，那么下一步可以往左走或者往右走。规定机器人必须走K步，最终能来到P位置(P也是1~N中的一个)的方
 * 法有多少种？给定四个参数N、M、K、P，返回方法数。
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
