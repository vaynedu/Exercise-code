/*****************************************************************************************
智能指针：实际指行为类似于指针的类对象 ，它的一种通用实现方法是采用引用计数的方法。
1.智能指针将一个计数器与类指向的对象相关联，引用计数跟踪共有多少个类对象共享同一指针。
2.每次创建类的新对象时，初始化指针并将引用计数置为1；
3.当对象作为另一对象的副本而创建时，拷贝构造函数拷贝指针并增加与之相应的引用计数；
4.对一个对象进行赋值时，赋值操作符减少左操作数所指对象的引用计数（如果引用计数为减至0，则删除对象），并增加右操作数所指对象的引用计数；这是因为左侧的指针指向了右侧指针所指向的对象，因此右指针所指向的对象的引用计数+1；
5.调用析构函数时，构造函数减少引用计数（如果引用计数减至0，则删除基础对象）。
6实现智能指针有两种经典策略：一是引入辅助类，二是使用句柄类。这里主要讲一下引入辅助类的方法
*****************************************************************************************/

//基础对象类，要做一个对Point类的智能指针

class Point
{
    public:
        Point(int xVal = 0,int yVal = 0):x(xVal),y(yVal){}
        int getX() const {
            return x;
        }
        int getY() const {
            return y;
        }
        void setX(int xVal){
            x = xVal;
        }
        void setY(int yVal){
            y = yVal;
        }
    private:
        int x;
        int y;
};

//辅助类，该类成员访问权限全部为private，因为不想让用户直接使用该类

class RefPtr
{
    friend class SmartPtr;  //定义智能指针类为友元，因为智能指针类需要直接操纵辅助类
    RefPtr(Point *ptr):p(ptr),count(1){}
    ~RefPtr(){
        delete p;
    }

    int count;              //引用计数
    Point *p;               //基础对象指针
};


//智能指针类
class SmartPtr
{
    public:
       SmartPtr(Point *ptr):rp(new RefPtr(ptr)){}  //构造函数
       SmartPtr(const SmartPtr &sp):rp(sp.rp){      //复制构造函数
            ++rp->count;
       }
       SmartPtr &operator = (const SmartPtr &rhs){
           ++rhs.rp->count;             //首先将右操作数引用计数加1
           if(--rp->count == 0){         //然后将引用计数减1，可以应对自赋值
                delete rp;
           }
           rp = rhs.rp;
           return *this;
       }
       ~SmartPtr(){
          if(--rp->count == 0){     //当引用计数减为0时，删除辅助类对象指针，从而删除基础对象
            delete rp;    
          }
       }
    private:
        RefPtr *rp;  //辅助类对象指针
};
