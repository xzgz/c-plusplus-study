#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;


class Book
{
 private:
  string name_;

 public:
  Book(string name) : name_(name)
  {
    cout << "Creating book " << name_ << " ..." << endl;
  }

  ~Book()
  {
    cout << "Destroying book " << name_ << " ..." << endl;
  }
};

int main()
{
  cout << "=====Main Begin=====" << endl;
  {
    boost::shared_ptr<Book> myBook1(new Book("「1984」"));
    cout << "myBook1: " << myBook1.use_count() << endl;
    boost::shared_ptr<Book> myBook2(myBook1);
    cout << "myBook1: " << myBook1.use_count() << endl;
    boost::shared_ptr<Book> myBook3;
    myBook3 = myBook1;

    cout << "\n****************************\n";
    cout << "myBook1: " << myBook1.use_count() << endl;
    cout << "myBook2: " << myBook2.use_count() << endl;
    cout << "myBook3: " << myBook3.use_count() << endl;

    cout << "\n****************************\n";
    myBook1.reset();
    cout << "myBook1: " << myBook1.use_count() << endl;
    cout << "myBook2: " << myBook2.use_count() << endl;
    cout << "myBook3: " << myBook3.use_count() << endl;

    cout << "\n****************************\n";
    myBook3.reset();
    cout << "myBook1: " << myBook1.use_count() << endl;
    cout << "myBook2: " << myBook2.use_count() << endl;
    cout << "myBook3: " << myBook3.use_count() << endl;

    cout << "\n****************************\n";
    myBook2.reset();
    cout << "myBook1: " << myBook1.use_count() << endl;
    cout << "myBook2: " << myBook2.use_count() << endl;
    cout << "myBook3: " << myBook3.use_count() << endl;

    cout << "After reset ..." << endl;
  }
  cout << "===== Main End =====" << endl;

  return 0;
}