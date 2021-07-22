/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 * (C) Copyright Nicolai M. Josuttis 2012.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#include <iostream>
#include <string>
#include <memory>    // for unique_ptr
#include <dirent.h>  // for opendir(), ...
#include <cstring>   // for strerror()
#include <cerrno>    // for errno

using namespace std;

class ClassA {
public:
    string name;
    explicit ClassA(const string& nm) : name(nm) {}
    ClassA(const ClassA& x) {
        cout << "ClassA(const ClassA& x) -- x.name: " << x.name << endl;
        name = x.name;
    }
//    const ClassA& operator=(const ClassA& x) {
//        cout << "const ClassA& operator=(const ClassA& x) -- x.name: " << x.name << endl;
//        name = x.name;
//        return *this;
//    }
    const ClassA& operator=(ClassA& x) {
        cout << "const ClassA& operator=(ClassA& x) -- x.name: " << x.name << endl;
        name = x.name;
        x.name += "_pass_assignment";
        return x;
    }
    ~ClassA() {
        cout << "delete " << name << endl;
        name += "_over";
    }
};

// Sink() gets ownership
void Sink(std::unique_ptr<ClassA> up) {
    cout << "get into Sink" << endl;
}

std::unique_ptr<ClassA> Source(int id) {
    // ptr owns the new object
    std::unique_ptr<ClassA> ptr(new ClassA("ptr" + std::to_string(id)));
    // transfer ownership to calling function
    return ptr;
}

class ClassB {
private:
    // pointer members
    ClassA* ptr1;
    ClassA* ptr2;
public:
    // constructor that initializes the pointers
    // - will cause resource leak if second new throws
    ClassB(const string& val1, const string& val2) : ptr1(new ClassA(val1)), ptr2(new ClassA(val2)) {}

    // copy constructor
    // - might cause resource leak if second new throws
    ClassB(const ClassB& x) : ptr1(new ClassA(*x.ptr1)), ptr2(new ClassA(*x.ptr2)) {}

    // assignment operator
    const ClassB& operator=(const ClassB& x) {
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;
        return *this;
    }
    ~ClassB () {
        delete ptr2;
        delete ptr1;
    }
};

class ClassBUP {
private:
    // unique_ptr members
    std::unique_ptr<ClassA> ptr1;
    std::unique_ptr<ClassA> ptr2;
public:
    // constructor that initializes the pointers
    // - will cause resource leak if second new throws
    ClassBUP(const string& val1, const string& val2) : ptr2(new ClassA(val1)), ptr1(new ClassA(val2)) {}

    // copy constructor
    // - might cause resource leak if second new throws
    ClassBUP(const ClassBUP& x) : ptr1(new ClassA(*x.ptr1)), ptr2(new ClassA(*x.ptr2)) {
        cout << "ClassBUP(const ClassBUP& x)" << endl;
    }

    // assignment operator
    const ClassBUP& operator=(const ClassBUP& x) {
        cout << "const ClassBUP& operator=(const ClassBUP& x)" << endl;
        *ptr1 = *x.ptr1;
        *ptr2 = *x.ptr2;
        return *this;
    }
    // no destructor necessary
    // (default destructor lets ptr1 and ptr2 delete their objects)
};

int main() {
    std::unique_ptr<ClassA> up(new ClassA("up"));
    // up loses ownership
    cout << "Sink(std::move(up));" << endl;
    Sink(std::move(up));
    Sink(std::move(up));

    cout << endl;
    {
        std::unique_ptr<ClassA> p;
        for (int i = 0; i < 10; ++i) {
            // p gets ownership of the returned object
            // (previously returned object of Source() gets deleted)
            p = Source(i);
        }
        cout << "last-owned object of p gets deleted:" << endl;
    }

    cout << endl;
    ClassB cb("ClassB_ptr1", "ClassB_ptr2");
    ClassBUP cbup("ClassBUP_ptr1", "ClassBUP_ptr2");
    ClassBUP cbup2(cbup);
    ClassBUP cbup3 = cbup2;
    ClassBUP cbup4("cbup4_ptr1", "cbup4_ptr2");
    cbup = cbup4;

    return 0;
}
