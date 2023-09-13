#include<iostream>
using namespace std;
int main()
{

	//调用其它文件的函数只需要写函数声明,就可以使用了
	//函数的话没必要加extern，全局变量的话需要加，如果变量加static修饰的话,变量的作用域只限于当前被修饰的文件,不可被其它文件调用
	void p();
	void f();
		//fun1.cpp

		/*#include<iostream>
		using namespace std;

	    static int B 修饰后作用域只限于当前文件,不可被其它文件调用 
		/*int B=20;

		void p()
		{
			cout << B << endl;
		}*/
	
		
	//告诉编译器,我在其它文件里面已经定义过B了,让编译器去寻找,可以取代#include".cpp/h"的包含
	extern int B;
	cout << B << endl;
	B = 40;
	p();
	f();
	system("pause");
	return 0;
}