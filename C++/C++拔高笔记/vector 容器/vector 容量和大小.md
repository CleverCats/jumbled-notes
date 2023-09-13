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
	for (int i = 0; i < 20; i++)
	{
		v1.push_back(i);
	}
	PrintVector(v1);
	if (v1.empty())
	{
		cout << "容器为空" << endl;
	}
	else
	{             //v1.capacity()<=v1.size()  容器容量>=容器大小（当前元素个数）
		cout << "容器容量:" << v1.capacity() << " " << "容器大小（当前元素个数）:" << v1.size() << endl;
	}
	cout << "扩充容器resize" << endl;
	v1.resize(10,9);  //重新指定容器的大小(不是容量),超出容器原大小部分后默认位置默认为0,这里为9.如果小于原容器大小那么将截舍掉多余的部分
	PrintVector(v1);
	cout << "容器容量:" << v1.capacity() << " " << "容器大小（当前元素个数）:" << v1.size() << endl;
	v1.push_back(10086);
	cout << "扩充后添加数据" << endl;
	PrintVector(v1);
	cout << "容器容量:" << v1.capacity() << " " << "容器大小（当前元素个数）:" << v1.size() << endl;
}
int main()
{
	test();
	system("PAUSE");
	return 0;
}
