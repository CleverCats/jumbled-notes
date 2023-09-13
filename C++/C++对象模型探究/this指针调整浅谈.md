#include<iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout << "A 被构造 this = " << this << endl;
	}
	void funA()
	{
		cout << "A func this = " << this << endl;
	}
	int a=1, b=2;
};
class B
{
public:
	B()
	{
		cout << "B 被构造 this = " << this << endl;
	}
	void funB()
	{
		cout << "B  func this = " << this << endl;
	}
	int c=3, d=4;
};
//构造顺序 A-B-C
class C :public A, public B
{
public:
	C()
	{
		cout << "C 被构造 this = " << this << endl;
	}
	void funC()
	{
		cout << "C func this = " << this << endl;
	}
	int e=5, f=6;
};
int main()
{
	C obj;       
	obj.funA();
	obj.funB(); 
	obj.funC();
	cout<<"adress obj = adress C = adress A =" <<&obj << endl;
	//this指针调整解析:
	/*C先继承A 然后继承 B 那么C就与A的 this指针相同,起始位置都是A的指针起始位置---A的this指针
	Bthis指针在A的this指针往下 sizeof(A) 个字节
	所以调用 obj.funC(); 与 obj.funA(); 时都是通过同一个this指针调用,当调用obj.funB时编译器将this指针下移sizeof(A)个字节,到B的this指针处
	然后通过该B的this调用obj.funB()*/

	/*总结:调用那个子类的成员函数,这个this指针就会被编译器自动调整到对象内存布局中去,对应该子类对象的起始地址那去(this指针)*/
	system("PAUSE");
	return 0;
}