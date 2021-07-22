#include "common_function.h"
#include <iostream>

using namespace std;

#define PRINT_INFO 0

unsigned long Hanoi(int n, string from, string to, string other) {
    if (n == 1) {
#if PRINT_INFO
        cout << "Move 1 from " + from + " to " + to << endl;
#endif
        return 1;
    } else {
        unsigned long steps = 0;
        steps += Hanoi(n - 1, from, other, to);
        steps += 1;
#if PRINT_INFO
        cout << "Move " << n << " from " << from << " to " << other << endl;
#endif
        steps += Hanoi(n - 1, other, to, from);
#if PRINT_INFO
        cout << "Move " << n << " from " << other << " to " << to << endl;
#endif
        return steps;
    }
}

unsigned long Hanoi(int n) {
    if (n > 0) {
        return Hanoi(n, "left", "right", "mid");
    } else {
        return 0;
    }
}

int main() {
    unsigned long steps;
    {
        TimerClock tc(true);
         steps = Hanoi(10);
    }
    cout << "steps: " << steps << endl;
}
