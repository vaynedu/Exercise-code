/*==========================================================
     > File Name: construct_two.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sat 30 Jul 2016 09:08:23 PM CST
===========================================================*/

//display(y)  y被作为参数传递给函数
//my_string x = y  对象y被显示用来初始化对象
//y = func() y得到一个返回对象

#include <iostream>
#include <string.h>

using namespace std;

class my_string
{
   private:
       char *s;
   public:
       my_string(const char *str){
           s = new char[strlen(str) + 1];
           cout << " Allocating room for s \n";
           strcpy(s,str);
       }
       ~my_string(){
           if(s)  delete []s;
           cout << " Free s \n";
       }
       void show(){
           cout << s << "\n";
       }
};


void display(my_string ob)
{
   ob.show();
}


int main(int argc,char *argv[])
{
    my_string obj("hello!");

    display(obj);

    obj.show();

    return 0;
}


