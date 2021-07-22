#include <bits/stdc++.h>

using namespace std;

class Wife;
class Husband;

class Wife {
 public:
//  shared_ptr<Husband> h;
  weak_ptr<Husband> h;
  Wife() { cout << "hello wife\n"; }
  ~Wife() { cout << "bye wife\n"; }
};

class Husband {
 public:
//  shared_ptr<Wife> w;
  weak_ptr<Wife> w;
  Husband() { cout << "hello husband\n"; }
  ~Husband() { cout << "bye husband\n"; }
};

int& make_int() {
  int i = 1;
  return i;
}

int main() {

  {
    shared_ptr<Wife> w_sp(new Wife());
    shared_ptr<Husband> h_sp(new Husband());
//    w_sp->h = make_shared<Husband>(*h_sp);
//    h_sp->w = make_shared<Wife>(*w_sp);
    w_sp->h = h_sp;
    h_sp->w = w_sp;
    cout << "w_sp.use_count() " << w_sp.use_count() << endl;
    cout << "h_sp.use_count() " << h_sp.use_count() << endl;

    shared_ptr<int> sp1(new int(22));
    shared_ptr<int> sp2;
    cout << "sp1.use_count() " << sp1.use_count() << endl;
    sp2 = sp1;
    cout << "sp1.use_count() " << sp1.use_count() << endl;
    cout << "sp2.use_count() " << sp2.use_count() << endl;
  }

  return 0;
}
