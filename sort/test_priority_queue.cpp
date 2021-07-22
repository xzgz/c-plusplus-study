#include <iostream>
#include <queue>

using namespace std;

void TestPriorityQueue() {
    cout << "TestPriorityQueue():" << endl;
    priority_queue<int> p;
    p.push(1);
    p.push(2);
    p.push(8);
    p.push(5);
    p.push(43);
    for(int i = 0; i < 5; ++i) {
        cout << p.top() << endl;
        p.pop();
    }
}

void TestSmallPrioritizeQueue() {
    cout << "TestSmallPrioritizeQueue():" << endl;
    priority_queue<int, vector<int>, less<int> > p;
    p.push(1);
    p.push(2);
    p.push(8);
    p.push(5);
    p.push(43);
    for(int i = 0; i < 5; ++i) {
        cout << p.top() << endl;
        p.pop();
    }
}

void TestBigPrioritizeQueue() {
    cout << "TestBigPrioritizeQueue():" << endl;
    priority_queue<int, vector<int>, greater<int> > p;
    p.push(1);
    p.push(2);
    p.push(8);
    p.push(5);
    p.push(43);
    for(int i = 0; i < 5; ++i) {
        cout << p.top() << endl;
        p.pop();
    }
}

struct Node {
    int x;
    int y;
//    Node(const Node& rhs) {
//        x = rhs.x;
//        y = rhs.y;
//    }
    Node(int x0, int y0) {
        x = x0;
        y = y0;
    }
    bool operator < (const Node& rhs) const {
        if(x == rhs.x) {
            return y > rhs.y;
        } else {
            return x > rhs.x;
        }
    }
};

struct Cmp {
    bool operator()(Node a, Node b) {
        if(a.x == b.x) {
            return a.y > b.y;
        } else {
            return a.x > b.x;
        }
    }
};
void TestCustomPrioritizeQueue1() {
    cout << "TestCustomPrioritizeQueue1():" << endl;
    unsigned int seed = time(nullptr);
    srand(seed);
    priority_queue<Node, vector<Node>, Cmp> p;
    for (int i = 0; i < 10; ++i) {
        p.push(Node(rand(), rand()));
    }
    while (!p.empty()) {
        cout << p.top().x << "\t" << p.top().y << endl;
        p.pop();
    }
}

// when it is true, the element will move down
auto CmpFun2 = [](Node a, Node b) {
    if(a.x == b.x) {
        return a.y > b.y;
    } else {
        return a.x > b.x;
    }
};
void TestCustomPrioritizeQueue2() {
    cout << "TestCustomPrioritizeQueue2():" << endl;
    unsigned int seed = time(nullptr);
    srand(seed);
//    priority_queue<Node, vector<Node>, decltype(&CmpFun2)> p(CmpFun2);  // error
    priority_queue<Node, vector<Node>, decltype(CmpFun2)> p(CmpFun2);
    for (int i = 0; i < 10; ++i) {
        p.push(Node(rand(), rand()));
    }
    while (!p.empty()) {
        cout << p.top().x << "\t" << p.top().y << endl;
        p.pop();
    }
}

static bool CmpFun1(Node a, Node b) {
    if(a.x == b.x) {
        return a.y > b.y;
    } else {
        return a.x > b.x;
    }
}
void TestCustomPrioritizeQueue3() {
    cout << "TestCustomPrioritizeQueue3():" << endl;
    unsigned int seed = time(nullptr);
    srand(seed);
    priority_queue<Node, vector<Node>, decltype(&CmpFun1)> p(CmpFun1);
//    priority_queue<Node, vector<Node>, decltype(CmpFun1)> p(CmpFun1);  // error
    for (int i = 0; i < 10; ++i) {
        p.push(Node(rand(), rand()));
    }
    while (!p.empty()) {
        cout << p.top().x << "\t" << p.top().y << endl;
        p.pop();
    }
}

void TestCustomPrioritizeQueue4() {
    cout << "TestCustomPrioritizeQueue4():" << endl;
    unsigned int seed = time(nullptr);
    srand(seed);
    priority_queue<Node> p;
    for (int i = 0; i < 10; ++i) {
        p.push(Node(rand(), rand()));
    }
    while (!p.empty()) {
        cout << p.top().x << "\t" << p.top().y << endl;
        p.pop();
    }
}

class mycomparison
{
    bool reverse;
public:
    mycomparison(const bool& revparam=false)
    {reverse=revparam;}
    bool operator() (const int& lhs, const int&rhs) const
    {
        if (reverse) return (lhs>rhs);
        else return (lhs<rhs);
    }
};
void TestCustomPrioritizeQueue5() {
    cout << "TestCustomPrioritizeQueue5():" << endl;

    int myints[] = { 20, 10, 60, 10, 10, 20, 20 };
    int myints_len = sizeof(myints) / sizeof(int);
    cout << "myints_len = " << myints_len << endl;
    std::priority_queue<int> first;
    std::priority_queue<int> second(myints, myints + myints_len);
    std::priority_queue<int, std::vector<int>, std::greater<int> > third(myints,myints + myints_len);
    // using mycomparison:
    typedef std::priority_queue<int, std::vector<int>, mycomparison> mypq_type;

    mypq_type fourth(myints, myints + myints_len);                                     // less-than comparison
    mypq_type fifth(myints, myints + myints_len, mycomparison(true));    // greater-than comparison

#define PRINT_PRIORITY_QUEUE(queue_name) \
    cout << #queue_name << endl; \
    while (!queue_name.empty()) { \
        cout << queue_name.top() << endl; \
        queue_name.pop(); \
    }

    cout << second.top() << endl;
    PRINT_PRIORITY_QUEUE(first);
    PRINT_PRIORITY_QUEUE(second);
    PRINT_PRIORITY_QUEUE(third);
    PRINT_PRIORITY_QUEUE(fourth);
    PRINT_PRIORITY_QUEUE(fifth);
}

int main() {
    TestPriorityQueue();
    TestSmallPrioritizeQueue();
    TestBigPrioritizeQueue();
    TestCustomPrioritizeQueue1();
    TestCustomPrioritizeQueue2();
    TestCustomPrioritizeQueue3();
    TestCustomPrioritizeQueue4();
    TestCustomPrioritizeQueue5();

    return 0;
}
