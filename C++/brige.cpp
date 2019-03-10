/*==========================================================
     > File Name: brige.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Wed 03 Aug 2016 01:33:50 AM CST
===========================================================*/

#include <iostream>
#include <string>

using namespace std;

class OS
{
   private:
        string name;
   public:
        OS(string n):name(n){};
        void set_name(string n){
             this->name = n;
        }
        string  get_name(){
             return this->name;
        }
};

class XP : public OS
{
   public:
       XP(string n = "XP"):OS(n){};
};
class Win7 : public OS
{
   public:
       Win7(string n = "Win7"):OS(n){};
};
class Mylinux : public OS
{
   public:
       Mylinux(string n = "Linux"):OS(n){};
};


class Computer
{
   private:
        string brand;
        OS  os;
   public:
        Computer(OS xt,string b):brand(b),os(xt){};
        void set_os(OS os){
            this->os = os;
        }
        OS get_os(){
            return this->os;
        }
        void init(){
            cout << brand << "电脑正在运行" << os.get_name() <<endl;
        }
};


class Dell : public Computer
{
   public:
       Dell(OS os,string b = "Dell"):Computer(os,b){};
};

class Lenovo : public Computer
{
   public:
       Lenovo(OS os,string b = "Lenovo"):Computer(os,b){};
};


int main(int argc,char *argv[])
{
    XP xp;
    Win7 win7;
    Mylinux mylinux;

    Dell dell(xp);
    Lenovo lenovo(win7);
    dell.init();
    lenovo.init();

    dell.set_os(mylinux);
    dell.init();

    return 0;
}






