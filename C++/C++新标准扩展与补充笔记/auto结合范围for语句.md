#include<iostream>
#include<string>
using namespace std;
int main()
{
	//C++11 可以省略=符号
	int A []{1, 2, 3, 4, 5, }; 

	//范围for语句
	//遍历数组A, auto &n=A[i];直到最后一个元素
	for (auto &n : A)
	{
		cout << n << endl;
	}
	system("pause");
	return 0;
}