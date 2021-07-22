#include <iostream>
#include <set>

using namespace std;

class A {
 public:
  int a = 10;
};

int main () {
  std::set<int> myset;
  std::set<int>::iterator itlow, itup;

  for (int i=1; i<10; i++) myset.insert(i*10); // 10 20 30 40 50 60 70 80 90

  itlow=myset.lower_bound(30);                //        ^
  itup=myset.upper_bound(60);                 //                    ^

  cout << "*itlow, *(itlow+1): " << *itlow << " ";
  cout << *(++itlow) << endl;
  cout << "*itup, *(itup+1): " << *itup << " ";
  cout << *(++itup) << endl;
  myset.erase(itlow,itup);                     // 10 20 70 80 90

  std::cout << "myset contains:";
  for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << '\n';

//  A a;
//  int aa = (&a)->a;
//  int *pa = &a.a;
//  cout << a.a << endl;
//  cout << aa << endl;
//  cout << *pa << endl;
//  *pa = 20;
//  cout << a.a << endl;
//  cout << aa << endl;
//  cout << *pa << endl;

  A *pa = new A[3];
  A **ppa = &pa;
  cout << (*ppa)[0].a << endl;
  cout << (*ppa)[1].a << endl;
  cout << (*ppa)[2].a << endl;

  return 0;
}
