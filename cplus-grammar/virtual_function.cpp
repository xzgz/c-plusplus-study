#include <iostream>

using namespace std;

class Base1 {

 public:

  virtual void f() { cout << "Base1::f" << endl; }

  virtual void g() { cout << "Base1::g" << endl; }

  virtual void h() { cout << "Base1::h" << endl; }

};

class Base2 {

 public:

  virtual void f() { cout << "Base2::f" << endl; }

  virtual void g() { cout << "Base2::g" << endl; }

  virtual void h() { cout << "Base2::h" << endl; }

};

class Base3 {

 public:

  virtual void f() { cout << "Base3::f" << endl; }

  virtual void g() { cout << "Base3::g" << endl; }

  virtual void h() { cout << "Base3::h" << endl; }

};

class Derive : public Base3, public Base2, public Base1
{
 public:
  virtual void f() { cout << "Derive::f" << endl; }
  virtual void g1() { cout << "Derive::g1" << endl; }
  void h1() { cout << "Derive::h1" << endl; }
  void PrintMyFuncAddress(long * compa_addr)
  {
    void (Derive::*pfunc)() = &Derive::h1;
    cout << "Derive::h1 address: " << (void *)&pfunc << endl;
    cout << "Derive::h1 - pVtab: " << (void *)(compa_addr - (long *)&pfunc) << endl;
  }
};

typedef void(*Fun)();
typedef void(*Fun2)(int a);
typedef void(Derive::*ClassMember)();


int main()
{
  Fun pFun = NULL;
  ClassMember cm_h1 = &Derive::h1;

  Derive d;
  int *pInt;
  long *pLong;
  Derive *pDerive;
  long **pVtab = (long **)&d;
  cout << "sizeof(int): " << sizeof(int) << endl
	   << "sizeof(long): " << sizeof(long) << endl
       << "sizeof(int *): " << sizeof(pInt) << endl
       << "sizeof(long *): " << sizeof(pLong) << endl
       << "sizeof(Derive *): " << sizeof(pDerive) << endl;

  cout << "sizeof(Derive): " << sizeof(Derive) << endl;
  cout << "pVtab: " << pVtab << endl;
  cout << "pVtab+1: " << pVtab + 1 << endl;
  cout << "&pVtab[0]: " << &pVtab[0] << endl;
  cout << "&pVtab[1]: " << &pVtab[1] << endl;
  (d.*cm_h1)();
//  cout << "&d.h1: " << (long *)(d.*cm_h1) << endl;
  d.PrintMyFuncAddress((long *)pVtab);

  Fun2 pFun2;
  pFun2 = (Fun2)pVtab[0][0];
  cout << "pFun = (Fun)pVtab[0][0](" << (long *)pFun << "): ";
//  pFun2();    //error: too few arguments to function

  pFun = (Fun)*((long *)*((long *)&d + 0) + 0);
//  pFun = (Fun)pVtab[0][0];
  cout << "pFun = (Fun)pVtab[0][0](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[0][1];
  cout << "pFun = (Fun)pVtab[0][1](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[0][2];
  cout << "pFun = (Fun)pVtab[0][2](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[0][3];
  cout << "pFun = (Fun)pVtab[0][3](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[0][4];
  cout << "pFun = (Fun)pVtab[0][4](" << (long *)pFun << "): \n";
//  pFun();

//  pFun = (Fun)pVtab[3][0];
//  cout << "pFun = (Fun)pVtab[3](" << (long *)pFun << "): ";
//  pFun();

  pFun = (Fun)pVtab[1][0];
  cout << "pFun = (Fun)pVtab[1][0](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[1][1];
  cout << "pFun = (Fun)pVtab[1][1](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[1][2];
  cout << "pFun = (Fun)pVtab[1][2](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[1][3];
  cout << "pFun = (Fun)pVtab[1][3](" << (long *)pFun << "): \n";
//  pFun();

  pFun = (Fun)pVtab[2][0];
  cout << "pFun = (Fun)pVtab[2][0](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[2][1];
  cout << "pFun = (Fun)pVtab[2][1](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[2][2];
  cout << "pFun = (Fun)pVtab[2][2](" << (long *)pFun << "): ";
  pFun();

  pFun = (Fun)pVtab[2][3];
  cout << "pFun = (Fun)pVtab[2][3](" << (long *)pFun << "): \n";
//  pFun();

  Base1 *b1 = new Derive();
  b1->f();
  return 0;
}

