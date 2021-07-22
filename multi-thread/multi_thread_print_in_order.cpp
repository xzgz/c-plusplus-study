#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <algorithm>
#include <functional>

using namespace std;

condition_variable cond;
mutex print_mutex;
int step = 0;

void print_thread(int num)
{
  for (int i = 0; i < 10; i++)
  {
    unique_lock<mutex> lk(print_mutex);
    cond.wait(lk, [&]() { return num == step; });
    std::cout << char('A' + num);
    step = (step + 1) % 3;
    cond.notify_all();
  }
}

// refer to: https://www.cnblogs.com/break-python/p/5549972.html
void RunThread1() {
  thread t2(print_thread, 1);
  thread t1(print_thread, 0);
  thread t3(print_thread, 2);
  t2.join();
  t1.join();
  t3.join();
  cout << endl;
}

// refer to: https://blog.csdn.net/noBle_Ora/article/details/60464695
void RunThread2() {
  std::vector<std::thread> threads;
  threads.push_back(std::thread(print_thread, 2));
  threads.push_back(std::thread(print_thread, 1));
  threads.push_back(std::thread(print_thread, 0));
  std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
  cout << endl;
}

int main() {
  RunThread1();
  RunThread2();
}
