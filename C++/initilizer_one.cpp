/*==========================================================
     > File Name: initilizer_one.cpp
     > Author: ds
     > E-mail: 1219345363@qq.com
     > Create time: Mon 01 Aug 2016 10:14:51 AM CST
===========================================================*/

#include <stdio.h>
#include <iostream>


using namespace std;

class point
{
    protected:
          int m_x;
          int m_y;
    public:
          point(int m = 0,int n = 0){
               m_x = m;
               m_y = n;
               cout << "constructor \n";
          }
          point(point &p)
          {
              m_x = p.GetX();
              m_y = p.Gety();
              cout << "copy  constructor\n";
          }
          int GetX(){
              return m_x;
          }
          int Gety(){
              return m_y;
          }

};

class point3d
{
   private:
        point m_p;
        int m_z;
   public:
        point3d(point p,int z){
           m_p = p;
           m_z = z;
        }
        point3d(int i,int j,int z):m_p(i,j){
           m_z = z;
        }
        void display(){
           cout << m_p.GetX() << " " << m_p.Gety() << " " << m_z << endl;
        }

};

int main(int argc,char *argv[])
{

    point    p(5,2);
   // point3d  p3d(p,1);
    point3d   p3d(5,2,1);
    p3d.display();

    return 0;
}










