#include<iostream>
using namespace std;
class A
{
public:

	//virtual关键字:允许父类指针接收子类指针后可以调用子类中与父类虚函数同名(重写的父类虚函数)的函数
	virtual void fun()
	{
		cout << "A_fun called" << endl;
	}


	//final关键字:父类虚函数专业  写在父类虚函数尾部
	//作用:  禁止子类重写父类的虚函数
	//扩展:  当父类写了虚函数,子类的同名函数也将成为虚函数  
	virtual void fun1() final
	{

	}


	//同理虚析构的使用也可以在使,父类指针接收子类指针后可以操作子类的析构函数
	//注:同理 当父类析构为虚析构后，无论子类析构函数是否使用virtual关键字,子类的析构函数都将成为虚析构
	virtual ~A()
	{
		cout << "~A () 被调用" << endl;
	}
};
class B:public A
{
public:

	//override关键字:子类重写虚函数声明(不可以写在实现)专用  写在子类中的需要重写父类的函数的虚函数的尾部
	//效果:添加该关键字后,如果重新的虚函数与父类的虚函数有所不同,那么会报错
	//作用:防止程序员误操作,保证子类能正确重写父类的虚函数


	//父类定义成虚函数，子类中和父类虚函数相同名称，参数表相同的函数会自动变成虚函数。不管加没有
	/* virtual 可加可不加 */ virtual void fun() override;

	~B()
	{
		cout << "~B () 被调用" << endl;
	}

};
void B::fun()
{
	cout << "B_fun called" << endl;
}
int main()
{
	//父类指针接收new子类对象返回的子类指针
	//因为本质上p是父类指针,一般指针p能调用的函数只能是父类的成员函数
	//但若将子类与父类的**同名函数**加上关键字virtual 声明为虚函数,且子类中重写(不是覆盖)了该函数,那么再次调用则为子类的同名函数
	A*p = new B;
	//作用:实现动态绑定,使用一个A*p指针就可以动态接收并调用所有重写过父类虚函数的同名函数

	p->fun();


	//有new一定要有delete
	//(基类析构为虚析构的情况下)delete p后先调用子类析构,在调用父类析构
	delete p;
	system("PAUSE");
	return 0;
}