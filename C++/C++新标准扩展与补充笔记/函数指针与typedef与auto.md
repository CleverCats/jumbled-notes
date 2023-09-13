#include<iostream>
#include<vector>
using namespace std;
int fun(int a)
{
	return a;
}
int main()
{
	//int fun(int a) 将函数名去掉  格式:   函数返回值类型  (指针)  (参数列表)
	int(*p)(int a);

	//函数名即代表函数的入口地址,使用该类型的指针接收同类型的函数
	p = fun;  //与p=&fun 等价 因为函数名即与函数首地址意义相同
	//注意:一定要将	（*p）用括号括起来,代表(*p)优先结合

	//************如果不加( ) 即为 int *p (int a);表示一个函数声明 ,函数名为 p ,函数返回值为 int*  和函数指针是两个概念*********

	//函数(*p)即取代fun,调用时(*p)(1973)与p(1973)等价,因为函数名即与函数首地址意义相同
	cout << "return_fun =" << (*p)(1973) << endl;


	//使用typedef给类型取别名,使用POINT,代表一个 返回值类型为 int 参数列表为(int a) 的函数指针类型
	typedef int(*POINT)(int a);

	//实例化一个该类型的指针
	POINT p_f1; 

	p_f1 = fun;
	cout << "return_*p =" << (*p_f1)(2020) << endl;
	

	//*********************************************************typedef与auto的区别************************************
	//typedef是给类型名取别名,auto是自动识别类型名，如下举例
	vector<int>v;
	for (int i=0;i < 10;i++)
	{
		v.push_back(i*10);
	}
	//m_iter为vector<int>::iterator类型迭代器的别名
	typedef vector<int>::iterator m_itr;
	//使用别名
	for (m_itr i = v.begin(); i != v.end(); i++)
	{
		cout << *i << endl;
	}
	//auto自动识别v.begin()为vector<int>::iterator,省去了 vector<int>::iterator i = v.begin()这样啰嗦的声明
	//auto i =     i必须同时初始化,等号右边不能是类型名,而需要是某个类型的对象,由auto来完成类型推断 ,而typedef 必须是类型名	, 因为typedef的作用就是给类型名取别名
	for (auto i = v.begin(); i != v.end(); i++)
	{
		cout << *i << endl;
	}
	/*auto是c++11标准定义的一个类型推断的关键字，
	auto能够让编译器自动去分析表达式所属的类型,与特定的数据类型不同（比如double）,让编译器通过初始值来推算变量的类型。显然auto定义必须有初始值。*/
	system("PAUSE");
	return 0;
}