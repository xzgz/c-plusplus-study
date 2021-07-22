#include <bits/stdc++.h>

using namespace std;

//void TestExtern();  // OK
extern void TestExtern();  // OK

void TestMultiDefinition();

/*
from the following three examples, we can see that the declaration of function default is extern
extern void TestStaticFunction();  // error: ‘void TestStaticFunction()’ was declared ‘extern’ and later ‘static’
void TestStaticFunction();  // error: ‘void TestStaticFunction()’ was declared ‘extern’ and later ‘static’
static void TestStaticFunction();  // OK
*/
static void TestStaticFunction();

extern int extern_int;
void TestExternInt() {
    cout << "[TestExternInt] extern_int: " << extern_int << endl;
}

//int static_int;  // multiple definition of `static_int'
//extern static int static_int;  // cannot combine with previous 'extern' declaration specifier
static int static_int;  // OK

void TestStaticInt() {
    cout << "[TestStaticInt] static_int: " << static_int << endl;
}

void ArraySizeInFun(int a [], int *b, int c[]) {
    cout << "ArraySizeInFun-sizeof(a): " << sizeof(a) << " " << a[3] << endl;
    cout << "ArraySizeInFun-sizeof(b): " << sizeof(b) << endl;
    cout << "ArraySizeInFun-sizeof(c): " << sizeof(c) << endl;
}

void TestArraySize() {
    int a[5];
    int *b;
    int *c = a;
    int *d = new int;
    int *e = new int();
    int *f = new int[6];
    cout << "sizeof(a): " << sizeof(a) << " " << a[3] << endl;
    cout << "sizeof(b): " << sizeof(b) << endl;
    cout << "sizeof(c): " << sizeof(c) << endl;
    cout << "sizeof(d): " << sizeof(d) << " " << *d << endl;
    cout << "sizeof(e): " << sizeof(e) << " " << *e << endl;
    cout << "sizeof(f): " << sizeof(f) << " " << f[3] << endl;
    ArraySizeInFun(a, b, c);

    delete d;
    delete e;
    delete [] f;
}

int main() {
    TestExtern();
    TestMultiDefinition();
    TestStaticFunction();
    TestExternInt();
    TestStaticInt();
    TestArraySize();

    return 0;
}

void TestMultiDefinition() {
    cout << "TestMultiDefinition-main_file" << endl;
}

static void TestStaticFunction() {
    cout << "TestStaticFunction-main_file" << endl;
}
