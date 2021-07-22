#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

void SharedDeleter(string *p) {
    string s = *p;
    cout << "start delete " << s << endl;
    delete p;
    cout << "deleted " << s << endl;
}

void FalseSharedDeleter(string *p) {
    string s = *p;
    cout << "do not delete " << s << " here" << endl;
}

void SharedArrayDeleter(string *p) {
    string s = p[0];
    cout << "start delete array " << s << endl;
    delete [] p;
    cout << "deleted array " << s << endl;
}

int main() {
//    // two shared pointers representing two persons by their name
//    shared_ptr<string> pNico(new string("nico"));
//    shared_ptr<string> pJutta(new string("jutta"));
//
//    // capitalize person names
//    (*pNico)[0] = 'N';
//    pJutta->replace(0, 1,"J");
//
//    // put them multiple times in a container
//    vector<shared_ptr<string> > whoMadeCoffee;
//    whoMadeCoffee.push_back(pJutta);
//    whoMadeCoffee.push_back(pJutta);
//    whoMadeCoffee.push_back(pNico);
//    whoMadeCoffee.push_back(pJutta);
//    whoMadeCoffee.push_back(pNico);
//
//    // print all elements
//    for (const auto& ptr : whoMadeCoffee) {
//        cout << *ptr << " ";
//    }
//    cout << endl;
//
//    // overwrite a name again
//    *pNico = "Nicolai";
//
//    // print all elements again
//    for (const auto& ptr : whoMadeCoffee) {
//        cout << *ptr << " ";
//    }
//    cout << endl;
//
//    // print some internal data
//    cout << "use_count: " << whoMadeCoffee[0].use_count() << endl;
//
//    shared_ptr<string> pMake = make_shared<string>("Make");
//    cout << *pMake << endl;
//
////    shared_ptr<string> pSharedWithDeleter1(new string("SharedWithDeleter1"),
////            [](string *p) { cout << "delete " << *p << " in lamda function" << endl; delete p; });
//    shared_ptr<string> pSharedWithDeleter2(new string("SharedWithDeleter2"), SharedDeleter);
//    cout << "pSharedWithDeleter2 use_count: " << pSharedWithDeleter2.use_count() << endl;
//    shared_ptr<string> pSharedWithDeleter3;
////    pSharedWithDeleter3.reset(pSharedWithDeleter2.get(), [](string *p) {});
//    pSharedWithDeleter3.reset(pSharedWithDeleter2.get(), FalseSharedDeleter);
////    shared_ptr<string> pSharedWithDeleter3 = pSharedWithDeleter2;
//    cout << "pSharedWithDeleter2 use_count: " << pSharedWithDeleter2.use_count() << endl;
//    shared_ptr<string> pSharedWithDeleter4 = pSharedWithDeleter3;
//    cout << "pSharedWithDeleter2 use_count: " << pSharedWithDeleter2.use_count() << endl;
//    cout << "pSharedWithDeleter3 use_count: " << pSharedWithDeleter3.use_count() << endl;
//    cout << "pSharedWithDeleter4 use_count: " << pSharedWithDeleter4.use_count() << endl;
//    pSharedWithDeleter3.reset();
//    cout << "pSharedWithDeleter3 use_count: " << pSharedWithDeleter3.use_count() << endl;
//    cout << "pSharedWithDeleter4 use_count: " << pSharedWithDeleter4.use_count() << endl;
//    pSharedWithDeleter4.reset();


//    // shared_ptr<string> pSharedArrayWithDeleter1(new string[10]); // runtime error
//    shared_ptr<string> pSharedArrayWithDeleter1(new string[10],
//            [](string *p) { delete [] p; cout << "delete SharedArray in lamda function" << endl; });
//    shared_ptr<string> pSharedArrayWithDeleter2(new string[10], default_delete<string[]>());
//    shared_ptr<string> pSharedArrayWithDeleter3(new string[10], SharedArrayDeleter);
//    *pSharedArrayWithDeleter3 = "SharedArrayWithDeleter3";
//    pSharedArrayWithDeleter3.get()[0] = "1";

    struct TestSharePtr {
        int a;
        int b;
        string c;
    };
    shared_ptr<TestSharePtr> test_ptr;
//    TestSharePtr *share_ptr = new TestSharePtr();
//    test_ptr.reset(share_ptr);
//    shared_ptr<TestSharePtr> test_ptr = make_shared<TestSharePtr>();
//    shared_ptr<string> test_ptr = make_shared<string>();
//    TestSharePtr *test_ptr;
    cout << "test_ptr: " << test_ptr << endl;
    cout << "0: " << 0 << endl;
    cout << "NULL: " << NULL << endl;
    if (test_ptr == 0) {
        cout << "test_ptr == 0" << endl;
    }
    if (test_ptr == NULL) {
        cout << "test_ptr == NULL" << endl;
    }
    if (test_ptr == nullptr) {
        cout << "test_ptr == nullptr" << endl;
    }
    if (0 == nullptr) {
        cout << "0 == nullptr" << endl;
    }
}
