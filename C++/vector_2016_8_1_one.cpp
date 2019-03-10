/*==========================================================
     > File Name: vector_2016_8_1_one.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 01 Aug 2016 08:21:53 PM CST
===========================================================*/
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector <int >v;
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(1);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(2);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(3);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(4);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(5);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(6);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(7);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(8);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(9);
    cout << "v.size() = " << v.size() << " , " << "v.capacity() = " << v.capacity() <<endl;
    v.push_back(10);
    return 0;
}

