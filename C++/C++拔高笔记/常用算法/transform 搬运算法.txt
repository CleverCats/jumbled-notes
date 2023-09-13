#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
void PrintVector(int val)
{
	cout << val << endl;
}
class MyChange
{
public:
	int operator()(int val)  //仿函数
	{
		return val * 10;
	}
};
void CreatVector()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v1;  //目标容器
	v1.resize(v.size());  //预先开辟目标容器大小
	transform(v.begin(), v.end(), v1.begin(), MyChange());   //transform搬运算法 （原容器起始迭代器,原容器的结束迭代器,目标容器的起始迭代器,仿函数）
	//仿函数会把元素取出来,放入仿函数中在返回来
	for_each(v.begin(), v.end(), PrintVector); //利用普通函数遍历,参数为函数名
	cout << "------------------------------------------------------" << endl;
	for_each(v1.begin(), v1.end(), PrintVector);

}
int main()
{
	CreatVector();
	system("PAUSE");
	return 0;
}