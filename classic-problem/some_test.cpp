//#include <bits/stdc++.h>
#include "include/utils.h"
#include "common_function.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
#include <exception>

using namespace std;

typedef void (*Ptf)();

void MyFunction() {
    cout << "MyFunction\n";
}

void TestFunPtr() {
    cout << "TestFunPtr:" << endl;
    Ptf fun1 = &MyFunction;
    Ptf fun2 = MyFunction;
    fun1();
    fun2();
}

void TestInputStringToArray() {
    string str;
    getline(cin, str);

    vector<int> arr;
    String2IntArray(arr, str);
    for (int n : arr) cout << n << " ";
    cout << endl;

    arr.clear();
    String2IntArray2(arr, str);
    for (int n : arr) cout << n << " ";
    cout << endl;
}

void TestGenerateRandomNumber() {
    cout << "RAND_MAX: " << RAND_MAX << endl;
    unsigned int seed = time(nullptr);

    vector<int> test_array;
    test_array = GenerateRandom1DIntegerArrayUseRandSideClose(3, 15, 20);
    Print1DVector(test_array);
    SleepCrossPlatform(2000);
//    SleepCrossPlatformUseSTL(2000);
    test_array = GenerateRandom1DIntegerArrayUseRandSideClose(3, 15, 20);
    Print1DVector(test_array);

    int length = 10000000;
    int number_kind = 27;
    int base_number = 22;
    vector<int> count_array(number_kind + 1);
    vector<int> arr;
//    arr = GenerateRandom1DIntegerArrayUseRandSideClose(base_number, base_number + number_kind, length);
    arr = GenerateRandom1DIntegerArrayUseRandSideOpen(base_number, base_number + number_kind, length);
//    arr = GenerateRandom1DIntegerArrayUseRandLeftClose(base_number, base_number + number_kind, length);
//    arr = GenerateRandom1DIntegerArrayUseRandRightClose(base_number, base_number + number_kind, length);
//    arr = GenerateRandom1DIntegerArray<int>(base_number, base_number + number_kind, length);

    for (int val : count_array) {
        cout << val << '\t';
    }
    cout << endl;
    cout << "length/number_kind: " << length / number_kind << endl;
    cout << "length/(number_kind + 1): " << length / (number_kind + 1) << endl;
    cout << "length/(number_kind - 1): " << length / (number_kind - 1) << endl;

    for (int val : arr) {
        count_array[val - base_number]++;
    }
    for (int val : count_array) {
        cout << val << '\t';
    }
    cout << endl;
}

void TestSetprecision() {
    float a, b, c;
    int g, h;
    a = 3.1;
    b = 2.9;
    c = 5.02;
    g = -3.9;
    h = 6;
    cout << a << '\t' << fixed << setprecision(8) << b << '\t' << c
         << '\t' << g << '\t' << h << endl;
    cout << 0 % 3 << endl;
    cout << 2 % 3 << endl;
    cout << 5 % 3 << endl;
    cout << 333333337 * 3 % 1000000007 << endl;
}

int addInt1(int a, int b) {
    int res = a + b;
    if(a > 0 && b > 0 && res < 0) throw overflow_error("addInt1 -- too big");
    if(a < 0 && b < 0 && res > 0) throw overflow_error("addInt1 -- too small");
    return res;
}
int addInt2(int a, int b) {
    if(a > 0 && b > 0 && a > numeric_limits<int>::max() - b) throw overflow_error("addInt2 -- too big");
    if(a < 0 && b < 0 && a < numeric_limits<int>::min() - b) throw overflow_error("addInt2 -- too small");
    return a + b;
}
int addInt3(int a, int b) {
    int x = a + b;
    if ((x ^ a) < 0 && (x ^ b) < 0) throw overflow_error("addInt3 -- too big or too small");
    return x;
}
void TestIntAddOverFlow() {
    cout << "TestIntAddOverFlow:" << endl;
    int a = -numeric_limits<int>::max();
    int b = -2;
    int c;
//    c = addInt1(a, b);
//    c = addInt2(a, b);
    c = addInt3(a, b);
    cout << "c = " << c << endl;
}

void TestFloatBigSubBig() {
    cout << "TestFloatBigSubBig:" << endl;

    float f1 = 2.34E+10f;
    float f2 = f1 + 10.0f;
    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f2 - f1 = " << f2 - f1 << endl;
}

void TestConstPtr() {
    cout << "TestConstPtr:" << endl;

    float f3 = 0.1;
    const float *pf = &f3;
    printf("%f\n", *pf);
    f3 = 0.2;
    printf("%f\n", *pf);
//    *pf = 0.3;  // error: assignment of read-only location *pf
    f3 = 0.3;
    printf("%f\n", *pf);

    float f4 = 1.2;
    pf = &f4;
    printf("%f\n", *pf);

    const float f5 = 1.3;
//    float *pf2 = &f5;  // invalid conversion from const float* to float* [-fpermissive]
}

void TestCPlusPlusInherit() {
    cout << "TestCPlusPlusInherit:" << endl;

    class D
    {
    public:
        D(){cout<<"D()"<<endl;}
        ~D(){cout<<"~D()"<<endl;}

    protected:
        int d;
    };

    class B : virtual public D
    {
    public:
        B(){cout<<"B()"<<endl;}
        ~B(){cout<<"~B()"<<endl;}
    protected:
        int b;
    };

    class A : virtual public D
    {
    public:
        A(){cout<<"A()"<<endl;}
        ~A(){cout<<"~A()"<<endl;}
    protected:
        int a;
    };

    class C : public B, public A
    {
    public:
        C(){cout<<"C()"<<endl;}
        ~C(){cout<<"~C()"<<endl;}
    protected:
        int c;
    };

    C c;
    cout << "sizeof(c) = " << sizeof(c) << endl;

//    D d;
//    cout << "sizeof(d) = " << sizeof(d) << endl;
//
//    A a;
//    cout << "sizeof(a) = " << sizeof(a) << endl;
//
//    B b;
//    cout << "sizeof(b) = " << sizeof(b) << endl;
}

void TestVirtualTable() {
    class A {
    public:
        A() : m_data1(0), m_data2(0) {}

        virtual void vfunc1() { cout << "A::vfunc1" << endl; };

        virtual void vfunc2() { cout << "A::vfunc2" << endl; };

        void func1() { cout << "A::func1" << endl; };

        void func2() { cout << "A::func2" << endl; };
    private:
        int m_data1, m_data2;
    };

    class B : public A {
    public:
        B() : A(), m_data3(0) {}

        virtual void vfunc1() { cout << "B::vfunc1" << endl; };

        void func1() { cout << "B::func1" << endl; };
    private:
        int m_data3;
    };

    class C : public B {
    public:
        C() : B(), m_data1(0), m_data4(0) {}

        virtual void vfunc2() { cout << "C::vfunc2" << endl; };

        void func2() { cout << "C::func2" << endl; };
    private:
        int m_data1, m_data4;
    };

    B bObject;
    A *p = &bObject;
    p->vfunc1();
    A *pa = new B;
    pa->vfunc1();
    delete pa;

    cout << "**************" << endl;
    A aObject = (A)bObject;
    aObject.vfunc1();
//    B *pb = &aObject;  // error: invalid conversion from TestVirtualTable()::A* to TestVirtualTable()::B* [-fpermissive]

    cout << "**************" << endl;
    C cObject;
    p = &cObject;
    p->vfunc1();
    p->vfunc2();

    cout << "**************" << endl;
    bObject.func1();
    bObject.func2();
    bObject.A::func1();
    cObject.A::func1();
    cObject.func2();

    system("ls -l ./; pwd");
}

class Test {
public:
//    Test() : y(1), r(y), d(3), xx(5) {}     // error: const int Test::xx is a static data member; it can only be initialized at its definition
    Test() : y(1), r(y), d(3) {}            // 对于常量型成员变量和引用型成员变量，必须通过参数化列表的方式进行初始化。
    ~Test() {}

//    static void testStaticFun()
//    {
//        cout << "y = " << y << endl;            //Error:静态成员函数不能访问非静态成员
//    }

    void testFun() {
        ++x2;
        cout << "x2 = " << x2 << endl;
    }

    int y;      //普通变量成员
    int &r;     //引用成员变量
    const int d;    //常量成员变量
    static int c;   //静态成员变量
    static const int x = 2.1;   //静态常量整型成员变量
//    static int x2 = 1;          // error: ISO C++ forbids in-class initialization of non-const static member Test::x2
    static int x2;
    static const int xx;        //静态常量整型成员变量声明
    static const double z;  //静态常量非整型成员变量声明
    static constexpr const float zz = 1.998;    //静态常量非整型成员变量
};
const int Test::xx = 4;     // 静态常量整型成员变量定义
int Test::x2 = 4;     // 静态常量整型成员变量定义
const double Test::z = 5.1; // 静态常量非整型成员变量定义
int Test::c = 2;
//constexpr const float Test::zz = 12.223;  // error: duplicate initialization of Test::zz
void TestStatic() {
    cout << Test::x << endl;
    cout << Test::zz << endl;
    cout << "Test::x2 = " << Test::x2 << endl;
    Test t;
    t.testFun();
    cout << "Test::x2 = " << Test::x2 << endl;
}

int main() {
    TimerClock tc(true);
//    TestFunPtr();
//    TestInputStringToArray();
//    TestGenerateRandomNumber();
//    TestSetprecision();
//    TestIntAddOverFlow();
//    TestFloatBigSubBig();
//    TestConstPtr();
//    TestCPlusPlusInherit();
//    TestVirtualTable();
    TestStatic();

    return 0;
}
