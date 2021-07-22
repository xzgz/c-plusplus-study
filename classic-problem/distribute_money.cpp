#include "common_function.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

/*
 * 一开始有100个人，每个人有100元钱。每轮每人都要把自己的1元钱，等概率、随机给别人（不能是自己）。如果某个人没钱了，则这个人这
 * 一轮不需要给钱。请问：
 * 如果发生了很多轮，请问钱的分布是大体平均还是极不平均？
 */
vector<int> DistributeMoney(int people_count, int turns, int init_money) {
    vector<int> distributed_money(people_count, 0);
    vector<int> initial_money(people_count, init_money);

    unsigned int seed = time(nullptr);
    srand(seed);
    random_device rd;
    default_random_engine e(rd());
    uniform_int_distribution<int> u(0, people_count - 1);

    int give_to;
    vector<int> give_to_arr(people_count);
    for (int i = 0; i < turns; ++i) {
        for (int j = 0; j < people_count; ++j) {
            do {
//                give_to = GenerateRandom1DIntegerArray<int>(0, people_count - 1, 1)[0];
                give_to = rand() % people_count;
//                give_to = u(e);
//                cout << give_to << endl;
            } while (give_to == j);
            give_to_arr[j] = give_to;

            if (initial_money[j] > 0) {
                initial_money[j]--;
                distributed_money[give_to]++;
            }
        }

//        for (int k = 0; k < people_count; ++k) {
//            if (give_to_arr[k] != k && initial_money[k] > 0) {
//                initial_money[k]--;
//                distributed_money[give_to_arr[k]]++;
//            }
//        }
    }
    Print1DVector<int>(initial_money);

    return distributed_money;
}

int main() {
    TimerClock tc(true);
    vector<int> dm = DistributeMoney(100, 500000, 100);
    Print1DVector<int>(dm);
    sort(dm.begin(), dm.end());
    Print1DVector<int>(dm);
}
