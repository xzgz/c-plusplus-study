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
#include <vector>
#include <memory>
using namespace std;

class Person {
  public:
//    string name;
//    shared_ptr<Person> mother;
//    shared_ptr<Person> father;
//    vector<weak_ptr<Person> > kids;  // weak pointer !!!
//
//    Person(const string& n,
//            shared_ptr<Person> m = nullptr,
//            shared_ptr<Person> f = nullptr)
//     : name(n), mother(m), father(f) {
//    }

    string name;
    weak_ptr<Person> mother;
    weak_ptr<Person> father;
    vector<shared_ptr<Person> > kids;

    Person(const string& n,
           weak_ptr<Person> m = shared_ptr<Person>(nullptr),
           weak_ptr<Person> f = shared_ptr<Person>(nullptr))
            : name(n), mother(m), father(f) {
    }

    ~Person() {
      cout << "delete " << name << endl;
    }
};

shared_ptr<Person> initFamily (const string& name) {
//    shared_ptr<Person> dad(new Person(name+"'s dad"));
//    shared_ptr<Person> mom(new Person(name+"'s mom"));
//    shared_ptr<Person> kid(new Person(name, mom, dad));
//    mom->kids.push_back(kid);
//    dad->kids.push_back(kid);

    shared_ptr<Person> null(nullptr);
    shared_ptr<Person> dad(new Person(name+"'s dad", null));
    shared_ptr<Person> mom(new Person(name+"'s mom"));
    shared_ptr<Person> kid(new Person(name, mom, dad));
    mom->kids.push_back(kid);
    dad->kids.push_back(kid);
    return kid;
}

int main() {
    shared_ptr<Person> p = initFamily("nico");
//    string name = "nico";
//    shared_ptr<Person> mom(new Person(name+"'s mom"));
////    shared_ptr<Person> dad(new Person(name+"'s dad"));
//    shared_ptr<Person> p(new Person(name, mom, nullptr));
//    mom->kids.push_back(p);
////    dad->kids.push_back(p);

    cout << "nico's family exists" << endl;
    cout << "- nico is shared " << p.use_count() << " times" << endl;
    cout << "- nico's mother shared " << p->mother.use_count() << " times" << endl;
//    cout << "- name of 1st kid of nico's mom: "
//         << p->mother.lock()->kids[0]->name << endl;

    p = initFamily("jim");
    cout << "jim's family exists" << endl;

    shared_ptr<int> ip1(new int);
    cout << "ip1's use_count: " << ip1.use_count() << endl;
    shared_ptr<int> ip2 = ip1;
    cout << "ip1's use_count: " << ip1.use_count() << endl;
    cout << "ip2's use_count: " << ip2.use_count() << endl;

    try {
        shared_ptr<string> sp(new string("hi")); // create shared pointer
        weak_ptr<string> wp = sp; // create weak pointer out of it
        sp.reset(); // release object of shared pointer
        cout << wp.use_count() << endl; // prints: 0
        cout << boolalpha << wp.expired() << endl; // prints: true
        shared_ptr<string> p(wp); // throws std::bad_weak_ptr
    } catch (const std::exception& e) {
        cerr << "exception: " << e.what() << endl; // prints: bad_weak_ptr
    }

    return 0;
}
