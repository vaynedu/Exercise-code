/*==========================================================
     > File Name: operator.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 01 Aug 2016 08:23:28 AM CST
===========================================================*/
#include <iostream>

using namespace std;

class A1
{
   public:
       int operator=(int a)
       {
           return 5;
       }
       int operator+(int a)
       {
           return 2;
       }

};

class B1: public A1
{
   public:
       int operator-(int a)
       {
           return 1;
       }

};

int main()
{
    B1 v;
    cout << (v + 2)<<endl;
    cout << (v - 2)<<endl;
   // cout << (v = 2)<<endl;

    return 0;
}










