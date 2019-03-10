
#include <iostream>

using namespace std;

bool f[1009] = {};


int main(int argc,char *argv[])
{
    int i = 0;
    int j = 0;

    f[1] = true;

    for(i = 2; i <= 1000; ++i){
       if(f[i]){
           continue;
       }

       j = i + i;
       while(j <= 1000){
           f[j] = true;
           j += i;
       }
    }

    int a,ans = 0;
    cin >> a;
    for(i = 2; i*2 <= a; ++i ){
         if(!f[i] && !f[a-i]){
            ans++;
         }//end for
    }

    cout << ans << endl;
    return 0;
}
