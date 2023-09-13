#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;
void PrintVector(int val)
{
	cout << val << endl;
}
class ClassPrint
{
public:
	void operator()(int val)  //伪函数
	{
		cout << val << endl;
	}
};
void CreatVector()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.begin(), v.end(),PrintVector); //利用普通函数遍历,参数为函数名
	cout << "-------------------------------------------------" << endl;
	for_each(v.begin(), v.end(), ClassPrint());  //利用匿名类对象调用伪函数变量,参数为匿名类对象

}
int main()
{
	CreatVector();
	system("PAUSE");
	return 0;
}