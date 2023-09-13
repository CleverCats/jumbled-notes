#include<iostream>
using namespace std;
class A
{
public:
	void print()
	{
		cout << "Father print_void was called" << endl;
	}
	void print1(int)
	{
		cout << "Father print1_int was called" << endl;
	}
	void print2(int, int)
	{
		cout << "Father print2_int_int was called" << endl;
	}
	void print2(int,int,int)
	{
		cout << "Father print2_int_int_int was called" << endl;
	}


};
class  B:public A
{
public:


	
	//因为当父类与子类存在同名函数,子类函数会屏蔽掉(不是覆盖)父类函数,默认一般调用为子类的函数
	//调用方法1: sonObj(sonObj为子类的对象).::father(father为父类名)::fun(); 
	//调用方法2: 在子类成员函数中使用father::fun();作用域调用
	//调用方法3: 在子类的public::权限下声明 using father::函数名（不包括( )）;  //即using namespace的意思

	//调用方法3_C++11: 让父类同名函数在子类中可见,说白了就是"让父类同名函数可以在子类中以重载的方式来使用"
	//注意:采用using 方法3 using 的是函数名,不包括（）的参数列表,所以相当于将父类中这个函数的所有重载都在子类可以被重载的形式调用
	//如果使用uisng此方式下父类子类都有合适的重载版本相同,那么默认调用子类的版本
	using A::print1;
	using A::print2;
	void print()
	{
		cout << "Son print_void was called" << endl;
	}
	void print1()
	{
		cout << "Son print1_void was called" << endl;
	}
	void print2(int)
	{
		cout << "Son print2_int  was called" << endl;
	}
	void print2(int, int, int)
	{
		cout << "Son print2_int_int_int was called" << endl;
	}

	
};
int main()
{
	B b;
	//调用子类
	b.print();

	//调用父类
	b.A::print();

	//调用父类中的单参print1
	b.A::print1(10);

	//在未使用using 父类::函数名;时,只调用子类,使用了了后默认也调用子类,但若子类没有与其匹配的函数，则调用继承于父类的重载版本
	b.print1();

	//因为未在子类中检测到合适的函数，所以调用父类中重载的print1
	b.print2(10,10);

	//如果使用uisng此方式下父类子类都有合适的重载版本相同,那么默认调用子类的版本
	b.print2(10, 10, 10);
	system("pause");
	return 0;
}