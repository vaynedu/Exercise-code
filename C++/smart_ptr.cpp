/*==========================================================
     > File Name: smart_ptr.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Thu 04 Aug 2016 11:17:31 AM CST
===========================================================*/
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class report
{
  private:
     string str;
  public:
     report(const string &s):str(s){
          cout << " Object created\n";
     }
     ~report(){
          cout << "Object delete\n";
     }
     void comment() const{
        cout << str <<endl;
     }

};

int main()
{
    {
        auto_ptr<report>ps(new report("using auto ptr"));
        ps->comment();
    }

    /*
    {
        shared_ptr<report>ps(new report("using shared_ptr"));
        ps->comment();

    }

    {
        unique_ptr<report>ps(new report("using unique_ptr"));
        ps->comment();
    }
    */
    return 0;
}






