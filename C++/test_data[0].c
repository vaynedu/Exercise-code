#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Test
{
	int a;
	char data[0];
};

int main()
{
	char str[] = "I love you";

//	printf("sizeof(struct Test) = %d\n",sizeof(struct Test));

	struct Test *test = (struct Test *)malloc(sizeof(struct Test) + 10);

	test->a = 521;
	memcpy(test->data,str,sizeof(str));
 


	printf("test->a = %d\n",test->a);
	printf("test->data = %s\n",test->data);
  

	return 0;
}