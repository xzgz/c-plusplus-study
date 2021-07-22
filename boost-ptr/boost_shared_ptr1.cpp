#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <boost/shared_ptr.hpp>

//  The application will produce a series of
//  objects of type Foo which later must be
//  accessed both by occurrence (std::vector)
//  and by ordering relationship (std::set).

struct Foo
{
  Foo( int _x ) : x(_x) {}
  ~Foo() { std::cout << "Destructing a Foo with x=" << x << "\n"; }
  int x;
  /* ... */
};

typedef boost::shared_ptr<Foo> FooPtr;

typedef struct FooPtrOps
{
  bool operator()( const FooPtr & a, const FooPtr & b )
  { return a->x > b->x; }
  void operator()( const FooPtr & a )
  { std::cout << a->x << "\n"; }
} foo_ptr_ops;

foo_ptr_ops ins_foo_ptr_ops1 = foo_ptr_ops();
FooPtrOps *ins_foo_ptr_ops2 = new FooPtrOps();
FooPtrOps *ins_foo_ptr_ops3 = new foo_ptr_ops;


int main()
{
  {
    std::vector<FooPtr>         foo_vector;
    std::set<FooPtr,FooPtrOps>  foo_set; // NOT multiset!

    FooPtr foo_ptr( new Foo( 2 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset( new Foo( 1 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset( new Foo( 3 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    foo_ptr.reset ( new Foo( 2 ) );
    foo_vector.push_back( foo_ptr );
    foo_set.insert( foo_ptr );

    std::cout << "foo_vector:\n";
    std::for_each( foo_vector.begin(), foo_vector.end(), ins_foo_ptr_ops1 );

    std::cout << "\nfoo_set:\n";
    std::for_each( foo_set.begin(), foo_set.end(), *ins_foo_ptr_ops3 );

    FooPtr foo_ptr1( new Foo( 10 ) );
    FooPtr foo_ptr2( new Foo( 20 ) );
    std::cout << "foo_ptr1: " << foo_ptr1->x << '\n';
    std::cout << "foo_ptr2: " << foo_ptr2->x << '\n';

    foo_ptr1.swap(foo_ptr2);
    std::cout << "After swap:\n";
    std::cout << "foo_ptr1: " << foo_ptr1->x << '\n';
    std::cout << "foo_ptr2: " << foo_ptr2->x << '\n';

    foo_ptr2.swap(foo_ptr1);
    std::cout << "Swap again:\n";
    std::cout << "foo_ptr1: " << foo_ptr1->x << '\n';
    std::cout << "foo_ptr2: " << foo_ptr2->x << '\n';

	int a = 4;
	int b[4] = {6, 7, 0, 5};
	int *c = new int();
	int *d = new int[3];

	/*
	 * Because variable a and b are on stack, while boost::shared_ptr will call delete method,
	 * the following two rows of code will cause error.
	 */
//	boost::shared_ptr<int> bsa(&a);  // Error: Signal: SIGABRT (Aborted)
//  boost::shared_ptr<int> bsb(b);  // Error: Signal: SIGABRT (Aborted)
	boost::shared_ptr<int> bsc(c);
	boost::shared_ptr<int> bsd(d);
	std::cout << "bsc: " << *bsc << " bsd: " << *bsd << std::endl;

    std::cout << "The variable field finished." << "\n";
  }

  int *c = new int();
  int *d = new int[3];
  boost::shared_ptr<int> bsc(c);
  boost::shared_ptr<int> bsd(d);
  std::cout << "bsc: " << *bsc << " bsd: " << *bsd << std::endl;

  std::cout << "\nProgram done.\n";
}



