#include<iostream>
#include<list>
using namespace std;
bool Compare(int a, int b)  //实现排序的一个函数
{
	return a > b;
}
void PrintList(const list<int> &L)
{
	for (list<int>::const_iterator i=L.begin();i!=L.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}
void test()
{
	list<int>L;
	L.push_back(10);
	L.push_back(18);
	L.push_back(17);
	L.push_back(11);
	L.push_back(25);
	cout << "原始数据" << endl;
	PrintList(L);
	cout << "数据反转" << endl;
	L.reverse();  //reverse 反转
	PrintList(L);
	cout << "数据排序"<< endl;
	L.sort();  //默认从小到大
	PrintList(L);
	cout << "数据倒序" << endl;
	L.sort(Compare);       //暂时不用了解底层原理,调用Compare函数
	PrintList(L);
} 
int main()
{
	test(); 
	system("pause");
	return 0;
}