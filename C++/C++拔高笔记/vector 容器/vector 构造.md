#include<iostream>          //动态扩展不是在原有空间后面开辟新空间,而是找到一个更大的空间
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
void print(int vect)
{
	cout << vect << "  ";
}
void PrintVector(vector<int> v)
{
	for_each(v.begin(), v.end(), print);
}
void test()
{
	vector<int>v1;   //默认构造一个名为v的vector<int>类型的容器
	for (int i = 0; i < 7; i++)
	{
		v1.push_back(i);
	}
	vector<int>v2(v1.begin(), v1.end()-1);   //区间拷贝
	vector<int>v3(5, 10);   //5个10的方式初始化构造
	vector<int>v4(v3);   //拷贝构造
	PrintVector(v1);
	cout << endl;
	PrintVector(v2);
	cout << endl;
	PrintVector(v3);
	cout << endl;
	PrintVector(v4);
	cout << endl;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
