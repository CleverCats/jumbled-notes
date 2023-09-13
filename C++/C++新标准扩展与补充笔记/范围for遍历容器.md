#include<iostream>
#include<string>
#include<vector>
using namespace std;
void test()
{
	//C++11中可以通过大括号{ }初始化
	vector<int>v1{ 1, 2, 3, 4, 5 };

	//auto的范围for遍历也可用于容器
	for (auto &v : v1)
	{
		//v.push_back(50); //这种操作会导致容器顺序混乱.在使用范围for遍历时,千万不要改变容器的容量
		cout << v << endl;
	}
}
int main()
{
	test();
	system("pause");
	return 0;
}