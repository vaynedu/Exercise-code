/*==========================================================
     > File Name: max_min__8_5.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Fri 05 Aug 2016 10:58:10 PM CST
===========================================================*/
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

void result(vector<int>& a,int n)
{
    if(n > 1){
       sort(a.begin(),a.end());
       int m1 = 1;
       int m2 = 1;
       for(int i = 0; i < n -1; ++i){
           if(a[i+1] != a[i]){
               break;
           }
           ++m1;
       }
       for(int i = n -1; i > 0; --i){
            if(a[i - 1] != a[i]){
               break;
            }
           ++m2;
       }
       int max = m1 * m2;

       int min_temp = a[1] - a[0];
       int min = 0;
       for(int i = 2; i < n; ++i){
            if(a[i] - a[i-1] < min_temp){
                 min_temp = a[i] - a[i-1];
            }
       }//end for
       if(min_temp == 0){
           for(int i = 1; i < n; ++i){
               int j = i - 1;
               while(j >= 0 && a[j] == a[i]){
                     ++min;
                     --j;
               }
           }
       }else{
            for(int i = 1; i < n; ++i){
                if(a[i] - a[i -1] == min_temp){
                    ++min;
                }
            }
       }
       cout << min << ' ' << max << endl;

    }
}


int main()
{
    int num;
    while(cin >> num){
        int temp;
        vector<int>data;
        for(int i= 0; i < num; ++i){
            cin >> temp;
            data.push_back(temp);
        }
        result(data,num);
    }

    return 0;
}




















