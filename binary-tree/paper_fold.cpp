#include <iostream>

using namespace std;

void PrintProcess(int i, int N, bool down) {
    if (i <= N) {
        PrintProcess(i + 1, N, true);
        string val = down ? "°¼" : "Í¹";
        cout << val << '\t';
        PrintProcess(i + 1, N, false);
    }
}

void PrintAllFold(int N) {
    PrintProcess(1, N, true);
}

int main() {
    PrintAllFold(3);
}
