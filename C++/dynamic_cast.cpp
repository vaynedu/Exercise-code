/*==========================================================
     > File Name: dynamic_cast.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sun 17 Jul 2016 08:56:05 PM CST
===========================================================*/

#include <iostream>
#include <cstring>

using namespace std;

class A
{
    public:
       virtual void f()
       {
           cout<<"hello,I am class A "<<endl;
       }
};

class B:public A
{
    public:
        void f()
        {
            cout<<"hello I am class B"<<endl;
        }
};

class C
{
    void pp()
    {
        return ;
    }
};


int func()
{
    return 1;
}


int main(int argc,char *argv[])
{
    A *a1 = new B;
    A *a2 = new A;
    B *b;
    C *c;

    b = dynamic_cast<B*>(a1); // bottom
    if(b == NULL){
       cout << "NULL" <<endl;
    }else{
       cout << "NOT NULL" <<endl;
    }

    b = dynamic_cast<B*>(a2);
    if(b == NULL){
       cout << "NULL" <<endl;
    }else{
       cout << "NOT NULL" <<endl;
    }

    c = dynamic_cast<C*>(a1);
    if(c == NULL){
       cout << "NULL" <<endl;
    }else{
       cout << "NOT NULL" <<endl;
    }





    return 0;
}
























