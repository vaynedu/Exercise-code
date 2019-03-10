/*==========================================================
     > File Name: vptr_vtbl.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Wed 03 Aug 2016 08:12:53 AM CST
===========================================================*/

#include <iostream>


using namespace  std;

class Base
{
   public:
      virtual void f() { cout << "Base :: f" << endl;}
      virtual void g() { cout << "Base :: g" << endl;}
      virtual void h() { cout << "Base :: h" << endl;}
};

typedef  void (*Func)(void);


int main()
{
    Base b;
    Func pFun = NULL;
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "virtual address: " << (int*)(&b) << endl;
    pFun = (Func)*((int *)*(int*)(&b));
    pFun();
   // pFun = (Func)*((int *)*(int*)(&b) + 1);
   // pFun();
   // pFun = (Func)*((int *)*(int*)(&b) + 2);
   // pFun();
    return 0;
}


























