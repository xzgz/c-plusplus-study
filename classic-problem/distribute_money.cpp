#include "common_function.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

/*
 * һ��ʼ��100���ˣ�ÿ������100ԪǮ��ÿ��ÿ�˶�Ҫ���Լ���1ԪǮ���ȸ��ʡ���������ˣ��������Լ��������ĳ����ûǮ�ˣ����������
 * һ�ֲ���Ҫ��Ǯ�����ʣ�
 * ��������˺ܶ��֣�����Ǯ�ķֲ��Ǵ���ƽ�����Ǽ���ƽ����
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
