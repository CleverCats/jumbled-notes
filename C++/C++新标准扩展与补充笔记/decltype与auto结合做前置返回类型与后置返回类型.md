#include<iostream>
#include<vector>
using namespace std;
int& fc(int &i)
{
	cout << typeid(i).name() << endl;
	return i;
}
double fc(double &i)
{
	return i;
}
template<class T>

//auto这里不是类型推断,只是后置返回值类型的 auto 结合 decltype的语法格式
auto Func(T &arg)->decltype(fc(arg))  //type arg = int &
{
	//true type arg = int &
	return fc(arg);
}
/*
//C++14 decltype(auto)作为前置返回类型，也可用于变量声明(将其看作一个无类型丢弃的自动类型推断)
//auto做类型推断时会丢弃掉原数据的数据类型(除非使用万能引用)
//decltype能够"捡回"auto即将丢弃掉的类型 但如果需要捡回必须使用 decltype(auto)结合使用
/*
****************************************************
注意不要误解:  若 const int &n=10;  auto m=n; 此时auto已经丢掉const 与 引用 type m = int
此时 decltype(m) k;  type k = int ; m的类型为int ,因为 m已经丢掉了 const 与 引用 ,所以 type k = int;
但若使用 decltype(auto) s = n; 则相当于 decltype阻止auto丢掉类型限定,此时 type s = const int &;
****************************************************
*/
/*
template<class T>
decltype(auto) Func2(T& m)  //type auto = T; type decltype(auto) = T & //decltype "捡回" auto丢弃掉的类型
{
	return m;  //type m= T &
	//****************************************************
	//注意:如果使用 return (m);  (m)相当于一个表达式.此时decltype(auto)会推断出 引用类型  返回局部变量的引用可能造成严重后果
	//****************************************************
}
*/
int main()
{
	int n = 10; double m = 20.5;
	cout << Func(n) << endl;

	int &temp = n;
	decltype(temp) tmp_2=n;
	tmp_2 = 100;
	cout << n << endl;
	cout << "----------------------" << endl;

	//type n = int
	//decltype(Func2(n)) x = 10; //type x = int &         VS2013不支持decltype(auto)做返回值类型
	
	const int &p = 10;
	auto p2 = p; //会丢掉 const  &  仅为int

	//C++14中

	//decltype(auto) p3 = p;    //可以找回 "auto即将丢掉"的  const  & 还原为 const int &.
	/*注意不要误解:  若 const int &n = 10;  auto m = n; 此时auto已经丢掉const 与 引用 type m = int
	此时 decltype(m) k;  type k = int; m的类型为int, 因为 m已经丢掉了 const 与 引用, 所以 type k = int;
	但若使用 decltype(auto) s = n; 则相当于 decltype阻止auto丢掉类型限定, 此时 type s = const int &;*/
	system("PAUSE");
	return 0;
}