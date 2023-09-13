#include<iostream>
#include<string>
//标准库命名空间
using namespace std;

//使用关键字namespace创建一个命名空间A
//可以通过命名空间来访问其下的成员
namespace A
{
	void f1()
	{
		cout << "namespace A::f1()" << endl;
	}
}

//已经存在命名空间A后,如下语句的作用是对成员的添加
//所以由此也可以用如下方法向std标准库命名空间中添加新成员
namespace A
//namespace std   //向std标准库命名空间中添加新成员
{
	void f2()
	{
		cout << "namespace A::f2()" << endl;
	}
}
namespace B
{
	void f1()
	{
		cout << "namespace B::f2()" << endl;
	}
}
class C
{
public:
	C()
	{
		m_str = "c++ nb";
	}
	string m_str;
};
using namespace B;
namespace D
{
	ostream& operator<<(ostream& os, string str)
	{
		os << str << endl;
	}
}
int main()
{
	//需要指定命名空间
	A::f1();
	A::f2();
	//已经使用了 using namespace B;后可以省略B的作用域B::的书写(前提不发生和其他同名命名空间下成员函数的二义性)
	f1();
	system("pause");
	return 0;
}