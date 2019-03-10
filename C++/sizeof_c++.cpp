/*==========================================================
     > File Name: sizeof_c++.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Wed 03 Aug 2016 12:24:44 AM CST
===========================================================*/

#include <iostream>

//G++ 编译器 centos7.0 按照8字节对齐，sizeof（）务必注意

using namespace std;

class Base{
    //int  i;
   // static int me; //仅仅计算非静态成员数据的类型大小
    virtual void display(){
         cout << " Base" << endl;
    }
};
class Dreived:public virtual Base{
    //char x;
    virtual void display(){
        cout << "Base " <<endl;
    }
};
int main()
{
    cout << "sizeof(Base) = " << sizeof(Base) << endl;
    cout << "sizeof(Dreived) = " << sizeof(Dreived) <<endl;
    return 0;
}




















