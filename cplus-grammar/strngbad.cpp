// strngbad.cpp -- StringBad class methods
#include <cstring>                    // string.h for some
#include <iostream>
using std::cout;

class StringBad
{
 private:
  char *str;                 // pointer to string
  int len;                   // length of string
  static int num_strings;    // number of objects
 public:
  StringBad(const char * s); // constructor
  StringBad();               // default constructor
  ~StringBad();              // destructor
  // friend function
  friend std::ostream& operator << (std::ostream& os, const StringBad& st);
  int length() const { return len; }
};

// initializing static class member
int StringBad::num_strings = 0;

// class methods
// construct StringBad from C string
StringBad::StringBad(const char *s)
{
  len = std::strlen(s);                  // set size
  str = new char[len + 1];          // allot storage
  std::strcpy(str, s);                   // initialize pointer
  num_strings++;                    // set object count
  cout << num_strings << ": \"" << str
       << "\" object created\n";    // For Your Information
}

StringBad::StringBad()                // default constructor
{
  len = 4;
  str = new char[4];
  std::strcpy(str, "C++");               // default string
  num_strings++;
  cout << num_strings << ": \"" << str
       << "\" default object created\n";  // FYI
}

StringBad::~StringBad()               // necessary destructor
{
  cout << "\"" << str << "\" object deleted, ";    // FYI
  --num_strings;                    // required
  cout << num_strings << " left\n"; // FYI
  delete [] str;                    // required
}

std::ostream & operator<<(std::ostream & os, const StringBad & st)
{
  os << st.str;
  return os;
}

void callme1(StringBad &rsb)
{
  cout << "String passed by reference:\n";
  cout << "    \"" << rsb << "\"\n";
}

void callme2(StringBad sb)
{
  cout << "String passed by value:\n";
  cout << "    \"" << sb << "\"\n";
}

int main(int argc, char **argv)
{
  StringBad motto("motto");     // call StringBad::StringBad(const char *s)
  StringBad ditto1 = "ditto1";  // call StringBad::StringBad(const char *s)
  StringBad ditto2;             // call StringBad::StringBad()
  cout << "ditto2=" << ditto2 << ", length=" << ditto2.length() << "\n";
  // The following expression will call the default assignment operation ('='),
  // which has the form of String& String::operator = (const String& st) and
  // copy all elements to the new instance ditto2;
  ditto2 = ditto1;
  cout << "ditto2=" << ditto2 << ", length=" << ditto2.length() << "\n";

  return 0;
}


