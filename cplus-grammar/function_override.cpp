#include <bits/stdc++.h>

using namespace std;

class A {
 public:
  A() {}
  A(int a) {}
  ~A() {}
  virtual void f1() { cout << "A::virtual_f1()\n"; }
  virtual void f1(int a) { cout << "A::virtual_f1(int)\n"; }
  virtual void f1(int a, int b) { cout << "A::virtual_f1(int, int)\n"; }
//  virtual void f2() = 0;
  virtual void f2() { cout << "A::virtual_f2()\n"; }

  void f3(int a) { cout << "A::f3(int)\n"; }
  void f3(int a, int b) { cout << "A::f3(int, int)\n"; }
  void f3(int a, int b, int c) { cout << "A::f3(int, int, int)\n"; }
  void f4(int a) { cout << "A::f4(int)\n"; }
};

class B : public A {
 public:
//  B() {}
  ~B() {}
  virtual void f1() { cout << "B::virtual_f1()\n"; }
  void f1(int a, int b) { cout << "B::virtual_f1(int, int)\n"; }
  void f2() { cout << "B::virtual_f2()\n"; }  // f2 is a virtual function no matter use "virtual" or not

  void f3(int, int b, int c) {
    cout << "B::f3(int, int, int)\n";
  }

  void f5() {
//    this->f1(0);  // error: no matching function for call to ‘B::f1(int)’
//    this->f3(0);  // can be compiled only when there are no f3 in class B
//    this->f3(0, 0);  // can be compiled only when there are no f3 in class B
    this->f3(0, 0, 0);
  }
};

int main() {
  A *poa;
  B *pob;
  A oa;
  B ob;

  poa = new B();
//  poa = new B;  // the same as "poa = new B();"
  poa->f1();
  poa->f1(0);
  poa->f1(0, 0);
  poa->f2();
  cout << endl;

  poa->f3(0);
  poa->f3(0, 0);
  poa->f3(0, 0, 0);

  cout << "\n*******************\n\n";
  pob = new B();
//  pob->f1(0);  // error: no matching function for call to ‘B::f1(int)’
//  pob->f3(0);  // can be compiled only when there are no f3 in class B
//  pob->f3(0, 0);  // can be compiled only when there are no f3 in class B
  pob->f3(0, 0, 0);
  pob->f4(0);

  cout << "\n*******************\n\n";
  oa = ob;
  oa.f1();
  oa.f1(0);
  oa.f1(0, 0);
  oa.f2();

  cout << "\n*******************\n\n";
  A oa2 = B();
  oa2.f1();
  oa2.f1(0);
  oa2.f1(0, 0);
  oa2.f2();

  cout << "\n*******************\n\n";
  A& roa = ob;
  roa.f1();
  roa.f1(0);
  roa.f1(0, 0);
  roa.f2();

  delete poa;
  return 0;
}
