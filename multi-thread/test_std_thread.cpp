#include <thread>
#include <iostream>

using namespace std;

#define DELAY_NUM 1e9
#define THREAD_NUM 4
int end_thread_count = 0;

void ThreadFunc1(string& str, int& a) {
    cout << "str = " << str << endl;
    cout << "a = " << a << endl;
    str = "change by ThreadFunc1";
    a = 13;
}

void ThreadFunc2(string str, int a) {
    cout << "str = " << str << endl;
    cout << "a = " << a << endl;
    str = "change by ThreadFunc2";
    a = 13;
}

void TestThreadFunc1() {
    cout << "**TestThreadFunc1**\n";

    string str("main");
    int a = 9;
    std::thread th(ThreadFunc1, ref(str), ref(a));
    th.join();

    cout << "str = " << str << endl;
    cout << "a = " << a << endl;
}

void TestThreadFunc2() {
    cout << "**TestThreadFunc2**\n";

    string str("main");
    int a = 9;
    std::thread th(ThreadFunc2, str, a);
    th.join();

    cout << "str = " << str << endl;
    cout << "a = " << a << endl;
}

class ThreadObject
{
public:

    void threadFunc(const std::string &str, double d)
    {
        std::cout << "ThreadObject::threadFunc: str = " << str << "\t d = " << d << std::endl;
    }

    void operator () (const std::string &str, int i)
    {
        std::cout << "TheadObject::operator (): str = " << str << "\t i = " << i << std::endl;
    }
};

void TestThreadObject() {
    cout << "**TestThreadObject**\n";

    int score = 99;
    std::thread th1([&score]() {
        std::cout << "score = " << score << std::endl; });

    th1.join();

    ThreadObject to;
    string str1 = "xiaoming";
    std::thread th2(&ThreadObject::threadFunc, &to, str1, 98);
    th2.join();

    string str2 = "xiaohua";
    std::thread th3(to, str2, 97);
    th3.join();
}

struct args_struct {
    int thread_id;
};

void ThreadRunFunc(args_struct *args) {
    int thread_id = args->thread_id;
    int delay = DELAY_NUM;
    for(int i = 0; i < 4; ++i) {
        while(delay > 0) { delay--; }
        cout << thread_id << endl;
        delay = DELAY_NUM;
    }
    end_thread_count += 1;
}

void TestThreadRunFunc1() {
    cout << "**TestThreadRunFunc1**\n";

    const int thread_num = THREAD_NUM;
    thread thread_array[thread_num];
    args_struct *args_array = new args_struct[thread_num];
    for(int i = 0; i < thread_num; ++i) {
        args_array[i].thread_id = i;
        thread_array[i] = thread(ThreadRunFunc, &args_array[i]);
    }

    for(int i = 0; i < thread_num; ++i) {
        cout << "before thread.join() " << i << endl;
        thread_array[i].join();
        cout << "after thread.join() " << i << endl;
    }
    while(end_thread_count != THREAD_NUM) {}
    delete [] args_array;
}

void TestThreadRunFunc2() {
    cout << "**TestThreadRunFunc2**\n";

    const int thread_num = THREAD_NUM;
    thread thread_array[thread_num];
    args_struct *args_array = new args_struct[thread_num];
    for(int i = 0; i < thread_num; ++i) {
        args_array[i].thread_id = i;
        thread_array[i] = thread(ThreadRunFunc, &args_array[i]);
    }

    for(int i = 0; i < thread_num; ++i) {
        cout << "before thread.detach() " << i << endl;
        thread_array[i].detach();
        cout << "after thread.detach() " << i << endl;
    }
    while(end_thread_count != THREAD_NUM) {}
    delete [] args_array;
}

int main() {
//  TestThreadFunc1();
//  TestThreadFunc2();
//  TestThreadObject();
    TestThreadRunFunc1();
//  TestThreadRunFunc2();

    return 0;
}
