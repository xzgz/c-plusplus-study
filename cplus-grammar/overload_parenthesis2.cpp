#include <iostream>

template <typename T, typename Func>
void for_each(T* begin, T* end, const Func& f)
{
  while (begin != end) f(*begin++);
  std::cout << std::endl;
}

void PrintFunc(const int& x)
{
  std::cout << x << " ";
}

template <typename T>
void print(const T& x)
{
  std::cout << x << " ";
}

template <typename T>
struct Print
{
  int operator () (const int& x) const
  {
    std::cout << x << " ";
    return 0;
  }
//  float operator () (const T& x) const  // duplicate declaration of function 'operator()'
//  {
//    std::cout << x << " ";
//    return 0;
//  }
  int operator () (const T& x, int i) const
  {
    std::cout << x << " ";
    return 0;
  }
};

struct PrintForYuTangCEO
{
  typedef void(*Func_Type)(const int&);
  operator Func_Type() const {
    std::cout << "Invoke operator Func_Type() const.\n";
    return &print<int>;
  }
//  Func_Type operator () (const int&) const {
//    std::cout << "Invoke Func_Type operator () (const int&) const.\n";
//    return &print<int>;
//  }
  Func_Type operator () () const {
    return &print<int>;
  }
};

template <typename T, typename Func, typename C>
void for_each_More_Ex(T* begin, T* end, Func C::*f, const C& obj)
{
  while (begin != end) (obj.*(f))(*begin++);
  std::cout << std::endl;
}

template <typename T>
struct Print_Exciting
{
  mutable int count = 0;

  void print(const T& x) const
  {
    std::cout << count << ":" << x << " ";
    count++;
  }
};

template <typename Func, typename C, Func C::*f, typename T>
void for_each_More_More_Ex(T* begin, T* end, const C& obj)
{
  while (begin != end) (obj.*(f))(*begin++);
  std::cout << std::endl;
}

template <typename T>
void for_each_simple(T *begin, T *end)
{
  while (begin != end) std::cout << *begin++ << " ";
  std::cout << std::endl;
}

int main(int argc, char **argv) {

  int arr[5] = { 1, 2, 3, 4, 5 };

  for_each_simple(arr, arr + 5);
  for_each_simple<int>(arr, arr + 5);

  for_each(arr, arr + 5, PrintFunc);
  for_each<int>(arr, arr + 5, PrintFunc);

  for_each(arr, arr + 5, print<int>);
  for_each<int>(arr, arr + 5, print<int>);

//  for_each(arr, arr + 5, Print<int>);                 // error
  for_each(arr, arr + 5, Print<int>());
  for_each<int>(arr, arr + 5, Print<int>());
  for_each(arr, arr + 5, Print<int>{});
  for_each<int>(arr, arr + 5, Print<int>{});

  for_each(arr, arr + 5, PrintForYuTangCEO{});
  for_each<int>(arr, arr + 5, PrintForYuTangCEO());

  for_each_More_Ex(arr, arr + 5, &Print_Exciting<int>::print, Print_Exciting<int>());
  for_each_More_Ex<int>(arr, arr + 5, &Print_Exciting<int>::print, Print_Exciting<int>{});

//  for_each_More_More_Ex(arr, arr + 5, Print_Exciting<int>{});  // error
  for_each_More_More_Ex<void (const int&) const, Print_Exciting<int>,
          &Print_Exciting<int>::print>(arr, arr + 5, Print_Exciting<int>{});
  for_each_More_More_Ex<void (const int&) const, Print_Exciting<int>,
          &Print_Exciting<int>::print, int>(arr, arr + 5, Print_Exciting<int>{});

  return 0;
}
