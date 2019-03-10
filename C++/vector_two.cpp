/*==========================================================
     > File Name: vector_two.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 18 Jul 2016 03:15:32 PM CST
===========================================================*/


#include <iostream>
#include <vector>

using namespace std;


int main(int argc,char *argv[])
{
    vector<int>v(100);
    int i;
    for(i = 0; i < v.size(); i++){
        v[i] = i;
        cout << v[i] << " ";
    }
    cout << endl;
    vector<int>::const_iterator ii;
    for(ii = v.begin(); ii!=v.end(); ii++){
        cout << *ii << " ";
    }
    cout<<endl;

    ii = v.begin();
    while(ii < v.end()){
         cout << *ii << " ";
         ii = ii + 2;
    }
    cout << endl;
    return 0;
}
