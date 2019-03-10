#include <stdio.h>
#include <string.h>

#define  MAXLEN 100000

int longtest(char *str,int len)
{
	int i = 0;
	int result = 1;

	if(str == NULL || len <= 0){
	    return 0;
	}

	for(i = 0; i < len/2 ; ++i){
		if(str[i] != str[len - i - 1]){
		    result = 0;
			break;
		}
	}
	return result;

}



int main(int argc,char *argv[])
{
    char str[MAXLEN];
    int len = 0;
	int i = 0;
	int max = 0;


	memset(str,0x00,sizeof(str));
	scanf("%s",str);
	len = strlen(str);


	for( i = len; i >= 0; i--){
		if(longtest(str,i)){
		     max = i;
			 break;
		}
	}
	printf("%d\n",max);
	return 0;
}