/*==========================================================
     > File Name: try_catch_one.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 18 Jul 2016 08:13:02 AM CST
===========================================================*/

#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
    int m,n;
    cout << "please input two integer:";
    cin  >>m >> n;
    try
    {
        if(n == 0){
           throw "Divided by 0!";
        }
        cout << (m/n)<< endl;
    }
    catch(const char *arg)
    {
        cout << arg << endl;
        return -1;
    }
    catch(int)
    {
        cout << "Divided by 0" <<endl;
        return -1;
    }

    return 0;
}
















