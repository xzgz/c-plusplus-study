#include <bits/stdc++.h>

using namespace std;

class A {
 public:
  A() {}
  A(int a) {}
//  static int a = 5;  // error: ISO C++ forbids in-class initialization of non-const static member ‘A::a’
  static int a;
  const static int b = 1;
  static const int c;
};

//A::a = 3;  // error: ‘a’ in ‘class A’ does not name a type

int A::a = 3;

// error: ‘static’ may not be used when defining (as opposed to declaring) a static data member
//const static int A::c = 2;

// error: conflicting declaration ‘int A::c’
// error: declaration of ‘const int A::c’ outside of class is not definition
//int A::c = 2;

int const A::c = 2;

void Initialize() {
//  int A::a = 3;  // error: qualified-id in declaration before ‘=’ token
}

int main() {
  Initialize();
  A oa;
//  A oa(0);  // can be compiled
//  A oa = A();  // the same as "A oa;"
//  int A::a = 2;  // error: qualified-id in declaration before ‘=’ token
//  A::b = 3;  // error: assignment of read-only variable ‘A::b’
  cout << oa.a << endl;
  oa.a = 4;
  cout << A::a << endl;
  A::a = 10;
  cout << A::a << endl;
  cout << A::b << endl;
  cout << A::c << endl;

  A oa1, oa2;
  oa2.a = 19;
  oa1.a = 9;
  cout << oa1.a << endl;
  cout << oa2.a << endl;
}
