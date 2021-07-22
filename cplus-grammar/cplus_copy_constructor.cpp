#include <iostream>
//#include <string>

using namespace std;


// Improperly declared function:  parameter should be const reference:
  void print_me_bad( std::string& s )
  {
      cout << s << std::endl;
  }

  // Properly declared function: function has no intent to modify s:
  void print_me_good( const std::string& s )
  {
      std::cout << s << std::endl;
  }


  class A
  {
  private:
      int v_;
      string s_;
  public:
      A(string s = "default")
      {
          v_ = 8;
          s_ = s;
          cout << "object created " << s << endl;
      }
      A(const A& a, string s = "default")
      {
          v_ = 8;
          s_ = s;
          cout << "copy construct - const " << s << endl;
      }
      A(A& a, string s = "default")
      {
          v_ = 8;
          s_ = s;
          cout << "copy construct " << s << endl;
      }
      ~A() { cout << "object deleted " << s_ << endl; }
      void setvalue(int value = 6);
      int getvalue() { return v_; }
  };

  void A::setvalue(int value)
  {
      v_ = value;
  }

  void ReferenceA(A& a)
  {
      cout << "Reference a" << endl;
  }

  void ParameterA(A a)
  {
      cout << "Parameter a" << endl;
  }


int main()
{
//    std::string hello( "Hello" );

//    print_me_bad( hello );  // Compiles ok; hello is not a temporary
////    print_me_bad( std::string( "World" ) );  // Compile error; temporary object
////    print_me_bad( "!" ); // Compile error; compiler wants to construct temporary
//                         // std::string from const char*

//    print_me_good( hello ); // Compiles ok
//    print_me_good( std::string( "World" ) ); // Compiles ok
//    print_me_good( "!" ); // Compiles ok


    A a1("a1");                //calls A(), before function return, calls ~A()
//    A *b = new A();      //calls only A()
//    A *b = new A();      //calls only A()
//    delete b;            //calls only ~A(), it must be with new
//    A a2 = a1;           //calls A(const A& a), before function return, calls ~A()
//    A a3(a1);            //calls A(const A& a), before function return, calls ~A()

//    A(a4);                //calls A(), before function return, calls ~A()
//    cout << a4.getvalue() << endl;
//    A a6 = A(a5);         //error: 'a5' was not declared in this scope
//    A(a4);                //error: redeclaration of 'A a4'
//    A a6 = A(a4);         //error: a5 no declaration
//    A *a8 = new A(a7);    //error: 'a7' was not declared in this scope
//    A *a8 = new A(a4);   //calls only A(const A& a)
//    delete a8;           //calls only ~A(), it must be with new
//    ReferenceA(a1);      //don't call construction
    ParameterA(a1);      //calls A(const A& a), before function ParameterA return, calls ~A()

    return 0;
}




