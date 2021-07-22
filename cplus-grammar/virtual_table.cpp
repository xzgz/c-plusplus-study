#include <iostream>

using namespace std;

struct Base {
 public:
  virtual void f() {
    cout << "Base::f";
    cout << endl;
  }
  void a() {
    cout << "Base::a";
    cout << endl;
  }
  virtual void g() {
    cout << "Base::g";
    cout << endl;
  }
  virtual void h() {
    cout << "Base::h";
    cout << endl;
  }
  int x1;
  int x2;
  int x3;
};

typedef void(*Fun)();
typedef void(Base::*BaseFun)();

int main()
{
  Base b;
  Base c;
  Fun f = (Fun)*((long*)*(long*)(&b) + 0);
  Fun g = (Fun)*((long*)*(long*)(&b) + 1);
  Fun h = (Fun)*((long*)*(long*)(&b) + 2);
  BaseFun base_a = &Base::a;
  f();
  g();
  h();
  (b.*(base_a))();
  (c.*base_a)();
//  (c.base_a)();  // error: 'struct Base' has no member named 'base_a'

  cout << "b bytes: " << sizeof(b) << endl;
  cout << "&b bytes: " << sizeof(&b) << endl;
  cout << "long bytes: " << sizeof(long) << endl;
  cout << "Base bytes: " << sizeof(Base) << endl;
  cout << "Base::a bytes: " << sizeof(base_a) << endl;
  cout << "BaseFun bytes: " << sizeof(BaseFun) << endl;
  cout << "Fun bytes: " << sizeof(Fun) << endl;
  cout << "int bytes: " << sizeof(int) << endl;
  char buf[32] = { 0 };
  sprintf(buf, "%u", base_a);
  int addr_a = atoi(buf);
//  char *addr_a = buf;

  cout << "b's address: " << (long)&b << endl;
  cout << "b.a address: " << addr_a << endl;
  cout << "virtual table address: " << *(long *)&b << endl;
  cout << "virtual table address in pointer format: " << (long *)*((long *)&b + 4) << endl;
  cout << "the 1th 8 bytes in virtual table address: " << *((long *)*(long *)&b + 0) << endl;
  cout << "the 2th 8 bytes in virtual table address: " << *((long *)*(long *)&b + 1) << endl;
  cout << "the 3th 8 bytes in virtual table address: " << *((long *)*(long *)&b + 2) << endl;
  cout << "x1 in b addr: " << (long)&(b.x1) << endl;
  cout << "x2 in b addr: " << (long)&(b.x2) << endl;
  cout << "x3 in b addr: " << (long)&(b.x3) << endl;
  cout << "the 1th 8 bytes in b: " << *((long *)&b + 0) << endl;
  cout << "the 2th 8 bytes in b: " << *((long *)&b + 1) << endl;
  cout << "the 3th 8 bytes in b: " << *((long *)&b + 2) << endl;
  cout << "the 4th 8 bytes in b: " << *((long *)&b + 3) << endl;
  cout << "the 5th 8 bytes in b: " << *((long *)&b + 4) << endl;
  cout << "the 6th 8 bytes in b: " << *((long *)&b + 5) << endl;
  cout << "the 7th 8 bytes in b: " << *((long *)&b + 6) << endl;
  cout << "the 8th 8 bytes in b: " << *((long *)&b + 7) << endl;
  cout << "the 9th 8 bytes in b: " << *((long *)&b + 8) << endl;
  cout << "the 10th 8 bytes in b: " << *((long *)&b + 9) << endl;
  cout << "the 11th 8 bytes in b: " << *((long *)&b + 10) << endl;

  cout << "b's address in pointer format: " << (long *)&b << endl;
  cout << "virtual table address in pointer format: " << (long *)*(long *)&b << endl;
  cout << "the 1th 8 bytes in virtual table address in Fun pointer format: " << (Fun)*((long *)*(long *)&b + 0) << endl;
  cout << "the 2th 8 bytes in virtual table address in Fun pointer format: " << (Fun)*((long *)*(long *)&b + 1) << endl;
  cout << "the 3th 8 bytes in virtual table address in Fun pointer format: " << (Fun)*((long *)*(long *)&b + 2) << endl;
  cout << "the 1th 8 bytes in virtual table address in long pointer format: " << (long *)*((long *)*(long *)&b + 0) << endl;
  cout << "the 2th 8 bytes in virtual table address in long pointer format: " << (void *)*((long *)*(long *)&b + 1) << endl;
  cout << "the 3th 8 bytes in virtual table address in long pointer format: " << (long *)*((long *)*(long *)&b + 2) << endl;

  cout << "c's address: " << (long)&c << endl;
  cout << "virtual table address: " << *(long *)&c << endl;
  cout << "the 1th 8 bytes in virtual table address: " << *((long *)*(long *)&c + 0) << endl;
  cout << "the 2th 8 bytes in virtual table address: " << *((long *)*(long *)&c + 1) << endl;
  cout << "the 3th 8 bytes in virtual table address: " << *((long *)*(long *)&c + 2) << endl;
  cout << "x1 in c addr: " << (long)&(c.x1) << endl;
  cout << "x2 in c addr: " << (long)&(c.x2) << endl;
  cout << "x3 in c addr: " << (long)&(c.x3) << endl;
  cout << "the 1th 8 bytes in b: " << *((long *)&c + 0) << endl;
  cout << "the 2th 8 bytes in b: " << *((long *)&c + 1) << endl;
  cout << "the 3th 8 bytes in b: " << *((long *)&c + 2) << endl;
}
