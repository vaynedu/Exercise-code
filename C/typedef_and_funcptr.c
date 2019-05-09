#include <stdio.h>

int (*func)(int);


int gfunc(int v)
{
  printf("value = %d\n", v);
}

int main()
{
  func = gfunc;

  gfunc(521);
  
  func(521);
  
  (*func)(521);

  return 0;
}
