#include <stdio.h>
#include <stdlib.h>

int main()
{
  char c;
//第一次调用getchar()函数
//程序执行时，您可以输入一串字符并按下回车键，按下回车键后该函数才返回
  c=getchar();
//显示getchar()函数的返回值
  printf("%c\n",c);
//暂停
//  system("ls");
  while((c=getchar())!='\n')
  {
    printf("%c",c);
  }
//暂停
//  system("ls");
  return 0;
}