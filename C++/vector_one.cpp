/*==========================================================
     > File Name: vector_one.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 18 Jul 2016 02:59:41 PM CST
===========================================================*/

#include <vector>
#include <iostream>


using namespace std;

int main(int argc,char *argv[])
{
    vector<int>v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);

    vector<int>::const_iterator i;
    for(i = v.begin(); i!=v.end(); ++i){
          cout << *i << ",";
    }
    cout << endl;
    return 0;
}
