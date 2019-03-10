//给定N张扑克牌和一个随机函数，设计一个洗牌算法
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

void randomshuffle(int *a,int n)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < n; i++){
        j = rand()%(n-i) + i;
        swap(a[i],a[j]);  
    }
} 


int main()
{
    srand((unsigned)time(NULL));
    int n = 9;
    int a[] = {1,2,3,4,5,6,7,8,9};
    randomshuffle(a,n);

    for(int i = 0; i < n; i++){
        cout << a[i] << endl;
    }
    return 0;
}