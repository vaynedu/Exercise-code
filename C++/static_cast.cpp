/*==========================================================
     > File Name: static_cast.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 17 Jul 2016 08:41:40 PM CST
===========================================================*/

#include <iostream>

class A{
    //
};
class B:public A{

};

class C{

};


int main(int argc,char *argv[])
{
    int d = static_cast<int>(521.521);

    std::cout << d <<std::endl;

    A *a = new A();
    B *b;
    C *c;

    b = static_cast<B*>(a);

    //c = static_cast<B*>(a);
    return 0;
}
