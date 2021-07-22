#include <future>
#include <chrono>
#include <iostream>

struct X
{
  void foo(int i, std::string const& str) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << i << " " << str << std::endl;
  }
  std::string bar(std::string const& str) {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << str << std::endl;
    return str;
  }
};

X baz(X& x) {
  std::cout << "Invoke baz." << std::endl;
  return x;
}

struct Y
{
  double operator () (double d) { std::cout << "Invoke Y::operator(" << d << ")." << std::endl; }
};

class move_only {
 public:
  move_only() {};
  move_only(move_only&&) {}
  move_only(move_only const&) = delete;
  move_only& operator = (move_only&&) {}
  move_only& operator = (move_only const&) = delete;
  void operator () () { std::cout << "Invoke move_only::operator()." << std::endl; }
};

int main(int argc, char **argv) {
  X x;
//  auto hello = std::async(&X::foo, x, 42, "hello");
//  auto goodbye = std::async(&X::bar, x, "goodbye");
  auto hello = std::async(std::launch::async, &X::foo, x, 42, "hello");
  auto goodbye = std::async(std::launch::async, &X::bar, x, "goodbye");
//  auto hello = std::async(std::launch::deferred, &X::foo, x, 42, "hello");
//  auto goodbye = std::async(std::launch::deferred, &X::bar, x, "goodbye");

  Y y;
//  auto f3 = std::async(Y(), 3.141);
//  auto f4 = std::async(y, 2.718);
//  auto f5 = std::async(move_only());
//  auto f6 = std::async(baz, std::ref(x));
  auto f3 = std::async(std::launch::async, Y(), 3.141);
  auto f4 = std::async(std::launch::async, y, 2.718);
  auto f5 = std::async(std::launch::async, move_only());
  auto f6 = std::async(std::launch::async, baz, std::ref(x));

  hello.get();
  goodbye.get();
//  std::cout << goodbye.get() << std::endl;
//  auto start = std::chrono::high_resolution_clock::now();
//  std::this_thread::sleep_for(std::chrono::seconds(2));
//  auto end = std::chrono::high_resolution_clock::now();
//  std::chrono::duration<double, std::milli> elapsed = end-start;
//  std::cout << "Waited " << elapsed.count() << " ms\n";
//  hello.wait();
//  goodbye.wait();
  f3.wait();
  f4.wait();
  f5.wait();
  f6.wait();

  return 0;
}
