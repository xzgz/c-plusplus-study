#include <iostream>

template <typename T, std::size_t ROWS, std::size_t COLS>
struct Matrix {
  T data[ROWS][COLS];

  T operator() (int x, int y) const
  {
    return data[x][y];
  }

  T& operator () (int x, int y) {
    return data[x][y];
  }
  void operator () () {
    std::cout << "Invoke Matrix::operator().\n";
  }

  template <typename... Args>
  T get(Args&&... args) const
  { return this->operator()(std::forward<Args>(args)...); };
};

struct Matrix2 {
  int row_;
  int col_;
  int *data_ = nullptr;

  Matrix2() {}
  Matrix2(int row, int col) : row_(row), col_(col) {
    data_ = new int[row_ * col_];
  }
  ~Matrix2() {
    if (data_ != NULL)
      delete [] data_;
  }

  int operator () (int row, int col) {
    return *(data_ + row * row_ + col);
  }
  void operator () () {
    std::cout << "Invoke Matrix2::operator().\n";
  }
};

int main(int argc, char **argv) {
  Matrix<int, 10, 20> m;
  m(5, 5) = 10;
  std::cout << m.get(5, 5) << std::endl;
  std::cout << m(5, 5) << std::endl;
  std::cout << Matrix<int, 10, 20>()(5, 5) << std::endl;
  std::cout << Matrix<int, 10, 20>{}(5, 5) << std::endl;
  Matrix<int, 10, 20>()();
  Matrix<int, 10, 20>{}();
//  std::cout << Matrix<int, 10, 20>() << std::endl;  // error

  Matrix2 m1(2, 2);
  std::cout << m1(0, 1) << std::endl;
  Matrix2()();
  Matrix2{}();
  Matrix2();  // object destroyed immediately after creation
//  Matrix2;  // error: declaration does not declare anything

  std::cout << Matrix2(2, 2)(0, 1) << std::endl;
//  std::cout << Matrix2(2, 2) << std::endl;          // error

  return 0;
}
