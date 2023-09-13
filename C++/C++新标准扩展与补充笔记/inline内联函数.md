#include<iostream>
#include<string>
using namespace std;

//inline内联函数
//用法:如果有函数声明,可以只在函数声明时添加
//作用:给编译器一个建议,建议编译器智能优化内联函数的代码,当采用调用内联函数时,直接执行被优化后的函数代码,或者直接执行原函数内部的代码
//而不去调用函数,可以在一些情况优化程序
//注意:适用于函数体内代码量极少.甚至只有一两句, 但又调用很频繁的情况

inline void A(int a);  

void A(int a)
{
	cout<< a<<endl;
}
int main()
{
	//调用内联函数,是否真正的内联由编译器自行决定
	for (int i = 0; i < 100;i++) 
		A(i);
	system("pause");
	return 0;
}