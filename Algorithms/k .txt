#include <stdio.h>
#include <string.h>

#define mod 100000007 

long int sum = 0;

int dp[105][105] = {0};



void k_good_num(int k,int l)
{
    int i = 0;
    int j = 0;
    int x = 0;

    for(i = 0; i < k; i++){
        dp[1][i] = 1;
    }//end for 
    for(i = 2; i <= l; i++){
        for(j = 0; j < k; j++){
            for(x = 0; x < k; x++){
                if(x!=j-1 && x!=j+1){
                    dp[i][j] += dp[i-1][x];
                    dp[i][j] %= mod;
                }//end if
            }//end for3
        }//end for2
    }//end for 1
}

void print_k_num(int k,int l)
{
    int i = 0;

    for(i = 1; i < k; i++){
        sum += dp[l][i];
        sum %= mod;
    }//end for

	printf("sum = %d\n",sum);
}

int main(int argc,char *argv[])
{
    int k = 0;
    int l = 0;

    while(scanf("%d%d",&k,&l) != EOF){
        k_good_num(k,l);
        print_k_num(k,l);
        
		sum = 0;
		memset(dp,0x00,sizeof(dp));
    }

	return 0;
}
