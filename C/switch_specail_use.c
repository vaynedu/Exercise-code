#include <stdio.h>


int main()
{

  int num = 0;

  scanf("%d", &num);


  switch(num)
  {
     case 0 ... 10:
          printf("0 - 10\n");
          break;
     case 11 ... 20:
          printf("10 - 20\n");
          break;
     case 21 ... 30:
          printf("20 - 30\n");
          break;
     defalut:
          printf("ojbk\n");
  }

  return 0;
}

