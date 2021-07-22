#include <iostream>
#include <pthread.h>

using namespace std;

#define DELAY_NUM 1e9
#define THREAD_NUM 4
int end_thread_count = 0;

struct args_struct {
  int thread_id;
};

void *ThreadRunFunc(void *args) {
  args_struct *args_str = (args_struct *)args;
  int thread_id = args_str->thread_id;
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
  pthread_t thread_id[thread_num];
  args_struct *args_array = new args_struct[thread_num];
  for(int i = 0; i < thread_num; ++i) {
    args_array[i].thread_id = i;
    pthread_create(&thread_id[i], NULL, ThreadRunFunc, &args_array[i]);
  }

  for(int i = 0; i < thread_num; ++i) {
    cout << "before pthread_join " << i << endl;
    pthread_join(thread_id[i], NULL);
    cout << "after pthread_join " << i << endl;
  }
  while(end_thread_count != THREAD_NUM) {}
  delete [] args_array;
}

void TestThreadRunFunc2() {
  cout << "**TestThreadRunFunc2**\n";

  const int thread_num = THREAD_NUM;
  pthread_t thread_id[thread_num];
  args_struct *args_array = new args_struct[thread_num];
  for(int i = 0; i < thread_num; ++i) {
    args_array[i].thread_id = i;
    pthread_create(&thread_id[i], NULL, ThreadRunFunc, &args_array[i]);
  }

  for(int i = 0; i < thread_num; ++i) {
    cout << "before pthread_detach " << i << endl;
    pthread_detach(thread_id[i]);
    cout << "after pthread_detach " << i << endl;
  }
  while(end_thread_count != THREAD_NUM) {}
  delete [] args_array;
}

int main() {
//  TestThreadRunFunc1();
  TestThreadRunFunc2();

  return 0;
}
