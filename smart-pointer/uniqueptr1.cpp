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

class DirCloser
{
  public:
    void operator () (DIR* dp) {
        if (closedir(dp) != 0) {
            std::cerr << "OOPS: closedir() failed" << std::endl;
        }
    }
};

template <typename T>
using uniquePtr = std::unique_ptr<T, void(*)(T*)>;      // alias template

int main() {
    // open current directory:
    unique_ptr<DIR,DirCloser> pDir(opendir("."));

    // process each directory entry:
    struct dirent *dp;
    while ((dp = readdir(pDir.get())) != nullptr) {
        string filename(dp->d_name);
        cout << "process " << filename << endl;
        //...
    }

    std::string* sp = new std::string("hello");
    std::unique_ptr<std::string> up1(sp);
//    std::unique_ptr<std::string> up2(sp); // ERROR: up1 and up2 own same data

    class ClassA {
    public:
        string name;
        explicit ClassA(const string& nm) : name(nm) {}
        ~ClassA() {
            cout << "delete " << name << endl;
        }
    };
    std::unique_ptr<ClassA> upca1(new ClassA("upca1"));
//    std::unique_ptr<ClassA> upca2(upca1);             // ERROR: not possible
    std::unique_ptr<ClassA> upca3(std::move(upca1));    // OK
    cout << "std::unique_ptr<ClassA> upca3(std::move(upca1));" << endl;

    std::unique_ptr<ClassA> upca4;                      // create another unique_ptr
//    upca4 = upca1;                                    // ERROR: not possible
    upca4 = std::move(upca1);                           // transfers ownership from upca1 to upca4
    std::unique_ptr<ClassA> upca5(new ClassA("upca5"));
    // move assign the unique_ptr
    // delete object owned by upca5
    // transfer ownership from upca1 to upca5
    upca5 = std::move(upca1);
    cout << "upca5 = std::move(upca1);" << endl;

    std::unique_ptr<ClassA> ptr;
    ptr = std::unique_ptr<ClassA>(new ClassA("ptr"));   // OK, delete old object
    ptr = nullptr;                                              // deletes the associated object, if any
    cout << "ptr = nullptr;" << endl;

//    std::unique_ptr<std::string> up(new std::string[10]);         // runtime ERROR
    std::unique_ptr<std::string[]> up(new std::string[10]);     // OK
//    std::cout << *up << std::endl;                                // ERROR: * not defined for arrays
    std::cout << up[0] << std::endl;                                // OK

    std::unique_ptr<int, void(*)(int*)> upi1(new int[10], [](int *p) {
        cout << "void(*)(int*) -- delete [] p, p[2] = " << p[2] << endl;
        delete [] p;
    });
    std::unique_ptr<int, std::function<void(int*)> > upi2(new int[10], [](int *p) {
        cout << "std::function<void(int*)> -- delete [] p, p[2] = " << p[2] << endl;
        delete[] p;
    });
    auto del_fun = [](int *p) {
        cout << "auto del_fun -- delete [] p, p[2] = " << p[2] << endl;
        delete [] p;
    };
    std::unique_ptr<int, std::function<void(int*)> > upi3(new int[10], del_fun);
    uniquePtr<int> upi4(new int[10], [](int *p) {
        cout << "uniquePtr<int> -- delete [] p, p[2] = " << p[2] << endl;
        delete[] p;
    });
}
