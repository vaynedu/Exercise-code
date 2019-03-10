/*==========================================================
     > File Name: refence_point.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 01 Aug 2016 11:47:18 PM CST
===========================================================*/

#include <iostream>

using namespace std;

class refClass
{
   private:
       double &ref;
   public:
       refClass(double var = 521.521):ref(var){}
};


int main()
{
    //const int *pa;
    //int const *pb;
    int *const pc;
    int *pd = NULL;
    cout << sizeof(pd) << endl;

    cout << sizeof(refClass)<< endl;

    return 0;
}














