#include <stdio.h>
#include <sys/time.h>

inline double seconds() {
  struct timeval tp;
  struct timezone tzp;
  int i = gettimeofday(&tp, &tzp);
  return ((double) tp.tv_sec + (double) tp.tv_usec * 1.e-6);
}

void Test() {
  double iStart, iElaps;
  iStart = seconds();
  iElaps = seconds() - iStart;
  printf("%f sec\n", iElaps);
}

int main() {
  Test();

//  char ch1;
//  char ch2;
//
//  ch1 = getchar();
//  ch2 = getchar();
//  printf("%d  %d", ch1, ch2);
  return 0;
}
