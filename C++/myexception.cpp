/*==========================================================
     > File Name: myexception.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 18 Jul 2016 08:23:34 AM CST
===========================================================*/

#include <iostream>
#include <cstring>


using namespace std;

class MyException
{
   public:
        char str_what[80];
        MyException()
        {
            *str_what = 0;
        }
        MyException(const char *s)
        {
            strcpy(str_what,s);
        }

};

int main(int argc,char *argv[])
{
    int m,n;
    cout << "please input two integers:";
    cin >> m >> n;
    try
    {
        if(n == 0){
            throw MyException("Cannot divide by zero!");
        }else{
            cout << "m/n = " << (m/n)<<endl;
        }
    }
    catch(MyException& e)
    {
        cout << e.str_what << endl;
    }
    return  0;
}




