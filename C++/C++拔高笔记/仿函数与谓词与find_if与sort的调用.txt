#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
class Control
{
public:
	bool operator()(int val) //一个参数的bool型仿函数  -  一元谓词
	{
		return val>5;
	}
};
class Sort
{
public:
	bool operator()(int val1, int val2)  //两个参数的bool型仿函数  -  二元谓词
	{
		return val2 < val1;
	}
};
template<typename V>
void PrintVector(const V &v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	/*for (V::iterator i = 0; i != v.end(); i++)  //不可行
	{
		cout << *i << endll;
	}*/
}
void Assign()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	/*第一个和第二个参数为条件遍历区间(迭代器类型),第三个参数为Control的匿名无参构造.
	即 Control 匿名对象( )  因为函数对象中重载了()且返回值为bool型即存在一元谓词,
	此时的Control()为一个调用一元谓词的返回值类型 bool型,用来作为find_if的查询条件*/
	vector<int>::iterator it=find_if(v.begin(), v.end(), Control()); //返回满足条件的第一个迭代器,如果全部不满足,返回最后一个迭代器
	if (it != v.end())
	{
		cout << "搜索成功:" << *it << endl;
	}
	else
	{
		cout << "不存在限定条件下的值" << endl;
	}
	sort(v.begin(), v.end(), Sort());  //sort也可以有三个参数,第三个参数用来自定义排序规则,默认为升序
	PrintVector(v);
}
int main()
{
	Assign();
	system("PAUSE");
	return 0;
}