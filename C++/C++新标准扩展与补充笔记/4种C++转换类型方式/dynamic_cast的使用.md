#include<iostream>
using namespace std;
class A
{
public:
	void fun();
	virtual ~A(){};
};
void A::fun()
{
	cout << "call A fun()" << endl;
}
class B:public::A
{
public:
	void fun1();
};
void B::fun1()
{
	cout << "call B fun1()" << endl;
}
class C :public::A
{
public:
	void fun3()
	{
		cout << "call C fun3" << endl;
	}
};
int main()
{
	A*p = new B;
	p->fun();
	//可以使用c语言类型的强制类型转换
	//可以将p类型指针成功转为C类型指针,但极度不安全,因为p实际上是B类型的指针,只有转换为B类型指针才是安全的
	//C*p1 = (C*)p;   //可以但是极度不安全

	//在多态条件下,即基类为虚基类(至少存在一个虚函数成员),才可以使用dynamic_cast来进行类型的动态转换
	//作用:dynamic_cast会进行类型转换的安全检测,p实际上是B类型的指针,所以采用B*p1 = dynamic_cast<B*>(p);将p转换为B*类指针是安全的,转换成功
	//如果 C*p1 = dynamic_cast<C*>(p);因为p实际上不是C类指针,所以检测到转换不安全,此时会返回一个空指针,表示转换不成功

	B*p1 = dynamic_cast<B*>(p);               //指针类型转换,失败返回空指针
	if (p1!= nullptr)
	{
		cout << "安全转换成功,p实际上是B*类型指针" << endl;

		//调用B*类指针可以调用的成员函数
		p1->fun1();
	}
	else
	{
		//通过安全检测,因为需要转换类型与实际类型不符,返回空指针
		cout << "安全转换失败,p实际上不是B*类型指针" << endl;
	}


	A *p2 = new B;
	//ref为 *p2 的引用
	A &ref = *p2;

	//使用dynamic_cast将ref转换为C类型对象的引用ref1
	//因为ref实际上是B类型对象的引用,所以 dynamic_cast经过检测会判断转换失败,系统抛出std::bad_cast异常,需要程序员自行处理
	try
	{
		C &ref1 = dynamic_cast<C&>(ref);

		//如果安全转换成功的话则调用该对象的引用的成员函数
		ref1.fun3();
	}
	catch (std::bad_cast)
	{
		cout << "引用转换失败,ref实际上是B类型的引用,不能安全转换为C类型引用" << endl;
	}

	system("PAUSE");
	return 0;
}