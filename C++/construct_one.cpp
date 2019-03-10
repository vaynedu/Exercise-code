/*==========================================================
     > File Name: construct_one.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Sat 30 Jul 2016 08:35:50 PM CST
===========================================================*/
#include <iostream>

using namespace std;

class Square
{
    private:
          int  side;
    public:
          Square(int x);
          ~Square();
          void display();
};

Square::Square(int x)
{
    this->side = x;
    cout << "Construcring\n";
}
Square::~Square()
{
    cout << "Destructing\n";
}

void Square::display()
{
    cout << side << "\n";
}


void  fs(Square ob)
{
    ob.display();
}

int main(int argc,char *argv[])
{
    Square s(10);

    fs(s);
    s.display();

    return 0;
}






















