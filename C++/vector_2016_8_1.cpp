/*==========================================================
     > File Name: vector_2016_8_1.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 01 Aug 2016 08:11:49 PM CST
===========================================================*/
#include <iostream>
#include <vector>

using namespace std;

int main(int argc,char *argv[])
{
    vector<int> v;
    v.reserve(2);
    v[0] = 1;
    cout << "v.size() = " << v.size()<< endl;
    cout << "v.capacity() = " << v.capacity()<<endl;
    cout << v[0] << endl;

    //v.at(0) = 1;
    //cout << v.at(0) << endl;
    v.push_back(521);
    cout << "v.size() = " << v.size()<< endl;
    cout << "v.capacity() = " << v.capacity()<<endl;
    cout << v[0] << endl;

    return 0;
}








