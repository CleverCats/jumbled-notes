
#include<iostream>
#include<string>
using namespace std;
class A
{
public:
	A() :i(1)
	{
		cout << "普通构造" << endl;
	}
	A(const A&a) :i(a.i)
	{
		cout << "拷贝构造" << endl;
	}
	//临时对象调用移动构造,如果不写移动构造,则会调用默认拷贝构造,或者程序员自己写的拷贝构造
	//右值引用并没有特殊于左值引用,只是特别的可以引用即将销毁的临时变量,让临时变量有了名称,达到续航作用
	//但是它与左值引用相同,它终究只是一个引用,出了它所在的作用域后仍然会被销毁
	A(A&& a) : i(a.i)
	{
		cout << "移动构造" << endl;
		cout <<"临时匿名adress= "<< this << endl;
	}

	~A()
	{
		cout << "调用析构函数" << endl;
	}
	int i;
};

A test()
{
	A temp;
	cout << "adress= " << &temp.i << endl;
	cout << "value= " << temp.i << endl;

	//编译器会在return temp时对temp进行处理
	//1.  系统会**选择性**的对temp做 std::move（temp）转换右值的操作
	//2.  然后会生成一个临时对象进行 A temp1(temp)  如果存在移动构造,编译器会调用temp1(不可见的临时对象)对temp的移动构造函数
	//2.1 如果不存在移动构造，编译器不会采用 std::move（temp）转换右值的操作 ,但同样会生成一个临时对象,A temp1(temp) ,调用拷贝构造函数
	//3.  最后将这个匿名的临时对象在main中代替 test();进行运算
	//4.  注意:这个临时对象不是在 test()这个作用域中产生的,如果在这里产生,出了函数作用域就会被销毁,也达不到相当于取代main中的test()的作用了
		  //所以说这个临时变量可以看作在堆区(看作main函数中吧)内生成的
	return temp;
}
int main()
{
	//临时对象被temp4接管,地址相同
	A&& temp4 = test();   //test()中 A temp一次普通构造, return remp产生临时对象进行 A temp1(temp)临时构造—优先选择移动构造
	


		//A& temp5 = test();   编译器也允许绑定

		/*哈哈，楼主的问题已经是“老生常谈”了。
		函数的返回值是“右值”，这是标准上明确规定的。
		但是，对于返回内建类型和返回自定义类型，还是有区别的：
		返回内建类型，返回值不能被修改（这正是“右值”的体现）；
		返回自定义类型，返回值可以被修改，这违反了“右值”的含义，
		但是标准说它又是一个“右值”，怎么办呢？那就把这个返回值成为“可以修改的右值”吧！
		（可以修改的右值，的确是一个自相矛盾的字眼儿，但是没办法，现实是残酷的）*/

		//总结:不建议左值引用绑定return对象的做法,因为return 的返回值在 C++标准中是临时的右值


	cout << "-----------------------------" << endl;

	cout << "adress= " << &temp4.i << endl;
	cout << "value= " << temp4.i << endl;
	system("pause");
	return 0;

}
