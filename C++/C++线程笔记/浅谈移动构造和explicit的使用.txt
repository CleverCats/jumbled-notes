#include<iostream>
#include<string>
using namespace std;
class A
{
public:
	string m_str;	
	
	explicit A(string str) :m_str(str)
	{
		cout << "实例化对象" << endl;
	};
	//移动构造
	A(const A&& a):m_str(a.m_str)
	{
		cout << "移动构造调用 " << endl;
	
		cout << "a adress= " << &a<< endl;
		cout << "移动构造结束 " << endl;
	};
	A(const A&t)
	{
		cout << "普通构造调用 " << endl;
		m_str = t.m_str;
		cout << "t adress = " << &t.m_str << endl;
		cout << "普通构造结束 " << endl;
	}
	A operator+(const A&t)
	{
		//拼接字符串
		A temp(this->m_str.append(t.m_str)); 
		cout << "in operator temp adress = " << &temp << endl; 

		//返回临时对象
		return temp;
		//正常来说temp因为在栈区,出了作用域后temp就会被回收,采用移动构造则可以将其地址转移出去,让其他对象接管它，不必被回收
	}

};
int main()
{
	A a("Hellow ");
	A b("World "); 
	A d(a);   //调用拷贝构造
	cout << "a adress=" << &a << endl;
	A c(a + b);//调用移动构造
	system("pause");
	return 0;
}
//在C++中，explicit关键字用来修饰类的构造函数，被修饰的构造函数的类，不能发生相应的隐式类型转换，只能以显示的方式进行类型转换
/*C++中的 explicit关键字主要是用来修饰类的构造函数，表明该构造函数是显式的，禁止单参数构造函数的隐式转换。

所谓隐式转换，即，将构造函数一个值（其类型为构造函数对应的数据类型）转换为一个类对象。

如果C++类的构造函数只有一个参数，那么在编译的时候就会有一个缺省的转换操作：将该构造函数对应数据类型的数据转换为该类对象，通过下面的程序能很好地理解：
cit 关键字作用于单个参数的构造函数,或其他参数有默认值
public:
class MyClass

{

public:

MyClass(int num);

}

MyClass obj = 10; //ok, convert int to MyClass

上面的代码中编译器自动将整型转换为MyClass类对象，实际上等同于下面的操作：

MyClass temp(10);

MyClass obj = temp;

上面的所有的操作即是所谓的“隐式转换”。

如果要避免这种自动转换的功能，可以在声明构造函数的时候前面添加上explict关键字，将类的构造函数声明为“显示”，这样就可以防止这种自动的转换操作。
*/