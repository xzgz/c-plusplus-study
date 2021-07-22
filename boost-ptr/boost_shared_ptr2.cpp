#include <boost/shared_ptr.hpp>
#include <iostream>
#include <algorithm>


void print_val(int v)
{
    std::cout << v << " ";
}

class example
{
 public:
  example();
  void do_something();
  int val[3];
  class implementation;
  boost::shared_ptr< implementation > _imp;  // hide implementation details
};

class example::implementation
{
 public:
  ~implementation() { std::cout << "destroying implementation\n"; }
};

example::example() : _imp( new implementation ) {}

void example::do_something()
{
  std::cout << "use_count() is " << _imp.use_count() << "   ";
  std::for_each(val, val + 3, print_val);
  std::cout << "\n";
}

int main()
{
  example a;
  a.val[0] = 4;
  a.val[1] = 5;
  a.val[2] = 6;
  a.do_something();
  example b(a);
  b.do_something();
  example c;
  c = a;
  a.do_something();
  b.do_something();
  c.do_something();
  return 0;
}


