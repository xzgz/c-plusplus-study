// string1.cpp -- String class methods
#include <cstring>                 // string.h for some
#include <iostream>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;

class String
{
 private:
  char *str;              // pointer to string
  int len;                // length of string
  static int num_strings; // number of objects
  static const int CINLIM = 80;  // cin input limit
 public:
  // constructors and other methods
  String(const char * s); // constructor
  String();               // default constructor
  String(const String &); // copy constructor
  ~String();              // destructor
  int length () const { return len; }
  // overloaded operator methods
  String& operator = (const String&);
  String& operator = (const char *);
  char& operator [] (int i);
  const char& operator [] (int i) const;
  // overloaded operator friends
  friend bool operator < (const String& st, const String& st2);
  friend bool operator > (const String& st1, const String& st2);
  friend bool operator == (const String& st, const String& st2);
  friend ostream& operator << (ostream& os, const String& st);
  friend istream& operator >> (istream& is, String& st);
  // static function
  static int HowMany();
  void DoSomething() { std::cout << "Do something.\n"; }
};

// initializing static class member
int String::num_strings = 0;

// static method
int String::HowMany()
{
    return num_strings;
}

// class methods
String::String(const char *s)     // construct String from C string
{
    len = std::strlen(s);          // set size
    str = new char[len + 1];       // allot storage
    std::strcpy(str, s);           // initialize pointer
    num_strings++;                 // set object count
}

String::String()                   // default constructor
{
    len = 4;
    str = new char[1];
    str[0] = '\0';                 // default string
    num_strings++;
}

String::String(const String& st)
{
    num_strings++;             // handle static member update
    len = st.len;              // same length
    str = new char [len + 1];  // allot space
    std::strcpy(str, st.str);  // copy string to new location
}

String::~String()                     // necessary destructor
{
    --num_strings;                    // required
    delete [] str;                    // required
}

// overloaded operator methods

// assign a String to a String
String& String::operator = (const String& st)
{
    if (this == &st)
        return *this;
    delete [] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

// assign a C string to a String
String& String::operator = (const char *s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

// read-write char access for non-const String
char & String::operator[](int i)
{
    return str[i];
}

// read-only char access for const String
const char & String::operator[](int i) const
{
    return str[i];
}

// overloaded operator friends

bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2)
{
    return st2.str < st1.str;
}

bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

// simple String output
ostream& operator << (ostream& os, const String& st)
{
    os << st.str;
    return os;
}

// quick and dirty String input
istream& operator >> (istream& is, String& st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}

void callme1(String & rsb)
{
  cout << "String passed by reference:\n";
  cout << "    \"" << rsb << "\"\n";
}

void callme2(String sb)
{
  cout << "String passed by value:\n";
  cout << "    \"" << sb << "\"\n";
}

int main(int argc, char **argv) {
  String str0();                      // don't call String::String()
  cout << str0 << "\n";
//  str0.DoSomething();                 // error: request for member ‘DoSomething’ in ‘ss’, which is of non-class type ‘String()’
  String str00{};
  cout << str00 << "\n";
  str00.DoSomething();
  String str1;                        // call String::String()
  str1.DoSomething();
//  String() str2;                      // syntax error
//  String{} str2;                      // syntax error
//  String str2 = String;               // syntax error
  String str3 = String();             // call String::String()
  String motto1("motto1");            // call String::String(const char *s)
//  String("motto2") motto2;            // syntax error
  String motto2 = String("motto2");   // call String::String(const char *s)
  String ditto(motto1);               // call String::String(const String& st)
  String metoo1 = motto1;             // call String::String(const String& st)
  String metoo2;
  metoo2 = metoo1;                    // call String& String::operator = (const String& st)
  String metoo3;
  metoo3 = "metoo3";                      // call String& String::operator = (const char *s)
//  String metoo4 = "metoo4";               // call String::String(const char *s)
  String also = String(motto1);           // call String::String(const String& st)
  String *palso1 = new String;            // call String::String()
  String *palso2 = new String();          // call String::String()
  String *palso3 = new String(motto1);    // call String::String(const String& st)
  String *palso4 = new String("good");    // call String::String(const char *s)
//  String *palso5 = new String("good")[3]; // error
  String *palso5 = new String[3];         // call String::String(const char *s) 3 times

  return 0;
}
