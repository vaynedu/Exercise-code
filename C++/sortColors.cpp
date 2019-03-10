
//荷兰国旗
//[0...i-1]   0
//[i...k-1]   1
//[k...j-1]
//[j...n-1]   2

#include <iostream>
#include <algorithm>

using namespace std;

void sortColors(int a[],int n)
{
    int i = 0;
    int k = 0;
    int j = n;

    for(k = 0; k < j; ++k){
        if(a[k] == 0){
            swap(a[i++],a[k]);
        }else if(a[k] == 2){
            swap(a[--j],a[k--]);
        }
    }
}

void print(int a[],int n)
{
    int i = 0;
    for(i = 0; i < n; i++){
        cout << a[i] <<' ';
    }
    cout << endl;
}

int main()
{
    int a[] = {1,0,2,1,0,1,0,1,2,0};
    
    sortColors(a,10);

    print(a,10);

    return 0;
}
